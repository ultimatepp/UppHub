
# UppHub
---------

This repository serves as the the official global registry for [UppHub](https://www.ultimatepp.org/app$ide$UppHub_en-us.html), the distributed source packages management system for [Ultimate++](https://www.ultimatepp.org/index.html).

*Note: This technology is currently a work-in-progress, subject to change, and only available via the nightly builds of Ultimate++.*

## Registering packages

In order to register your package(s), you need to follow the below simple steps:

1. Fork this repository.
2. Edit the `nests.json` file to add your package's information.
3. Validate the modified `nests.json` file, using some local (or online) JSON validator.
4. Create a `PR` regarding the changes.

## The structure of the registry file

The UppHub global registry file, `nests.json`, is a  simple JSON file containing the nests list. Each nest has several entries that need to be filled in.

| Key           | Value                                                               |
|---            | --                                                                  |
| `name`        | The name of the nest.                                               |
| `packages`    | The list of the package(s) in this nest.                            | 
| `description` | A short description of the nest.                                    |
| `repository`  | The link to the nest's repository.                                  |
| `status`      | The status of the nest: `stable`, `experimental`, etc.              |
| `category`    | The category of the nest: `networking`, `scientific`, `widget`, etc.|
| `readme`      | A link to the `README` file.                                        |

#### Notes

- The `description` will be displayed on the UppHub package manager.
- The values of `status` and `category` entries are *provisional, at the moment*.
- The `readme`  file is optional. But it will certainly help you introduce your package to U++ users, as it can be displayed via the UppHub package manager. The format of the README file can be plain text, qtf or markdown.

## Example nest

Let us assume that we wrote a nice little widget called `MessageCtrl`. and we want to register and publish it via UppHub. After forking this repository, we edit the `nests.json`file with our preferred editor, and append the following information to it.

```json
    {
      "name": "MessageCtrl",
      "packages": [
        "MessageCtrl"
      ],
      "description": "A passive notifications widget for U++",
      "repository": "https://github.com/ismail-yilmaz/MessageCtrl.git",
      "status": "stable",
      "category": "widget",
      "readme": "https://raw.githubusercontent.com/ismail-yilmaz/MessageCtrl/main/README.md"
    }
```
Once these changes are validated and merged, the package(s) will be visible and available for download via the UppHub package manager in our integrated development environment, [TheIDE](https://www.ultimatepp.org/app$ide$GettingStarted_en-us.html):

![TheIDE - UppHub: displaying the registered MessageCtrl Package](Doc/Pictures/UppHub.png)
