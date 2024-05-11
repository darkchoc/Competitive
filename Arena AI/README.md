### Python3 Environment

This is a fully-fledged python3 environment, capable of running different targets such as a main file and tests.

### IntelliSense

IntelliSense is running across your entire project, allowing you to see when there are syntax errors or to get quick hints for how to resolve errors.

### Shell

A shell is provided to you so you can inspect your container in more detail. The shell can be used to install PIP packages using `pip install <package>`. In addition to installing packages, the shell can be used for executing a test suite if you have one defined.

_If you install dependencies with PIP, we recommend freezing them. Otherwise, they will be lost when the container running your code is restarted, and you will have to install them again._

**Note: while it's possible to edit files directly from the shell, we recommend using the editor to make your changes. That way, other people in the Pad can see your changes as they're being made.**

### Run Targets

The `.cpad` file serves as the configuration file for your project's run targets. The term "run target" refers to the predefined commands you can execute via the "Run Button" at the top of your Pad. This file is written in JSON format, making it easy to read and modify.

By default, your `.cpad` file should look like this:

```json
{
  "targets": {
    "run": {
      "label": "Main",
      "command": "python src/main.py"
    },
    "test": {
      "label": "Tests",
      "command": "python src/tests.py"
    }
  }
}
```

Each run target is defined by a unique key inside the `targets` object. There are two default targets available: `run` and `test`.

### Understanding The Run Target Structure

Each target has two properties: `label` and `command`.

- The `label` property is a user-friendly name that identifies the target. This allows you to set a human readable label for the specified command. This is what will show up in the run button's text when the target is selected.

- The `command` property specifies the actual command to be executed when the target is run. This command can be anything from a simple script execution, as seen in the example above (`"python src/main.py"`), to a more complex command involving multiple operations.

### Modifying and Creating Run Targets

If you want to change the command of an existing target, locate its key under the `targets` object and modify the `command` property accordingly.

For example, if you wish to change the command of the `run` target to execute a different script, you would modify the command property like so:

```json
"run": {
  "label": "Main",
  "command": "python src/new_script.py"
}
```

You can also add your own run targets in the same way. There is currently no limit on the amount of run targets in your project. The only constraint is that every target must have a unique key.

### Container Limits

The container running your application has a few limitations. Currently, we don't limit your CPU usage, though this may change in future. In addition to CPU, we monitor the network bandwidth that is consumed, and limit you to 75mb for the duration of the container. Finally, we limit the amount of memory accessible to each container to 2 GB.
