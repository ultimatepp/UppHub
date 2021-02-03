# UppHub
**UppHub** is the repository that serves as a global registry for [**U++**](https://www.ultimatepp.org/index.html) distributed packages. This technology was build with passion for C++ developers. We hope you will enjoy it!

## Adding package into registry
To register your package/packages (nest) you need to edit ```nests.json``` file and create PR with the changes. Let's assume that we would like to add package ```MessageCtrl``` we need to make the following addition:
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

Currently supported fields by nest entry are:
* **name** - name of the nest
* **packages** - packages list in your nest (might be more than one)
* **description** - description of the nest
* **repository** - link to the repository
* **status** - status of the nest. It can take the following value:
    * stable
    * experimental
* **category** - category of the nest. It can take the following value:
    * networking
    * scientific
    * widget
* **readme** (optional) - link to the readme file. It will be display inside TheIDE, so it is very helpfull to ecourage users to use your package.

The UppHub is relativly new technology, so the above schema may be expanded in the future.

## Results
After merging the change the package/packages (nest) should be visible and ready to download in our integrated development enviroment **TheIDE**:
TBD..


## Validation
In order to make sure that the changes to registry are correct we validate file with registry. In order to do it manually you could run following command on your local machine:
```sh
jsonschema -i nests.json nests.schema.json
```

The jsonschema command can be download using pip (python package manager):
```sh
pip install jsonschema
```

## Additional information
If you would like to learn more about this tehcnology please read our official [documentation](https://www.ultimatepp.org/app$ide$UppHub_en-us.html).