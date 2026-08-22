#include <Core/Core.h>

using namespace Upp;

String ExtractRepoPath(const String& url)
{
	int pos = url.FindAfter("github.com/");
	if(pos < 0)
		return "";

	String path = url.Mid(pos);
	if(path.EndsWith(".git"))
		path.TrimLast(4);

	return path;
}

int FetchGitHubStars(const String& repo_path, const String& gh_token)
{
	HttpRequest http("https://api.github.com/repos/" + repo_path);
	http.Header("Authorization", "Bearer " + gh_token);
	http.Timeout(10000);

	String response = http.Execute();

	if(http.IsError() || http.GetStatusCode() != HttpStatus::OK) {
		Cout() << "  [!] HTTP Error (" << http.GetStatusCode() << ") for " << repo_path << "\n";
		return -1;
	}

	Value json = ParseJSON(response);
	if(!IsValueMap(json))
		return -1;

	Value stars = json["stargazers_count"];
	if(IsNull(stars))
		return -1;

	return stars;
}

ValueMap GenerateMeta(const ValueArray& nests, const String& gh_token)
{
	ValueArray meta_nests;
	for(int i = 0; i < nests.GetCount(); i++) {
		Value nest = nests[i];
		String name = nest["name"];
		String repo_url = nest["repository"];

		String repo_path = ExtractRepoPath(repo_url);

		int stars = -1;
		if(!IsNull(repo_path)) {
			for(int attempt = 0; attempt < 3; attempt++) {
				Cout() << "Fetching stars for '" << name << "' (" << repo_path << ")...";
				if(attempt > 1) {
					Cout() << " [Attempt=" << attempt + 1 << "]";
				}
				Cout() << "\n";
				stars = FetchGitHubStars(repo_path, gh_token);
				if(stars >= 0) {
					break;
				}
			}
		}
		else {
			Cout() << "Warning: Could not parse URL for '" << name << "'\n";
		}

		ValueMap item;
		item.Add("name", name);
		if(stars >= 0)
			item.Add("stars", stars);
		else
			item.Add("stars", Value());

		meta_nests.Add(item);
	}
	
	ValueMap meta;
    meta.Add("nests", meta_nests);
	
	return meta;
}

void PrintUsage()
{
	Cout() << "Usage: " << GetExeTitle() << " [options] <input_file> <output_file>\n\n"
		   << "Generates metadata JSON consumed by TheIDE (e.g., repository star counts).\n\n"
		   << "Arguments:\n"
		   << "  <input_file>   Path to nests.json (e.g., from UppHub repo root)\n"
		   << "  <output_file>  Path where meta.json should be written\n\n"
		   << "Options:\n"
		   << "  -h, --help     Display this help message and exit\n\n"
		   << "Environment Variables:\n"
		   << "  UPP_GH_TOKEN   GitHub Personal Access Token (required to avoid API rate "
	          "limits)\n";
}

CONSOLE_APP_MAIN
{
	const auto& cmd = CommandLine();
	if(cmd.GetCount() == 0 || (cmd.GetCount() == 1 && (cmd[0] == "-h" || cmd[0] == "--help"))) {
		PrintUsage();
		return;
	}

	if(cmd.GetCount() != 2) {
		Cerr() << "Error: Invalid number of arguments.\n\n";
		PrintUsage();
		SetExitCode(1);
		return;
	}
	auto input_file = cmd[0];
	auto output_file = cmd[1];

	auto gh_token = GetEnv("UPP_GH_TOKEN");
	if(gh_token.IsEmpty()) {
		Cerr() << "Error: UPP_GH_TOKEN environment variable not set.\n";
		SetExitCode(1);
		return;
	}

	if(!FileExists(input_file)) {
		Cerr() << "Error: " << input_file << " not found!\n";
		SetExitCode(1);
		return;
	}

	String jsonText = LoadFile(input_file);
	Value root = ParseJSON(jsonText);
	if(!IsValueMap(root) || IsNull(root["nests"])) {
		Cerr() << "Error: Invalid nests.json format\n";
		SetExitCode(1);
		return;
	}

	auto meta = GenerateMeta(root["nests"], gh_token);
	auto output = AsJSON(meta, true) + "\n";
	if(!SaveFile(output_file, output)) {
		Cerr() << "\nError saving " << output_file << "\n";
		SetExitCode(1);
		return;
	}

	Cout() << "\nSuccessfully generated " << output_file << "\n";
}
