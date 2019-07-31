# µBlink firmware

Edit any configuration you need to edit in build_config.sh (or leave it as it is),

To compile µBlink, just use the provided build script. This will also install esp-idf and
the required toolchains automatically.

```sh
$ ./build.sh
```

In order to flash your µBlink, press the 'flash' button on your board and
use the following command:

```sh
$ ./build.sh flash [SERIAL_DEVICE]
```

Check out the build.sh command for further options:

```sh
$ ./build.sh help
```

## Makefile

For your convenience, a makefile is provided:

```sh
$ UBLINK_DEVICE=$SERIAL_DEVICE make build flash
```

## Configuration

Edit build_config.sh or provide the appropriate environment variables manually.

E.g. the following command could be used to install the toolchain at a custom location (provided the build_config.sh is untouched).

```sh
IDF_PATH="$HOME/esp-idf" IDF_TOOLS_PATH="$HOME/esp-idf/toolchain" ./build.sh setup_toolchain
```

## Todo

* Set up LED PWM
* WIFI
* CLI

