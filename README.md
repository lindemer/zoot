# Zoot
**Zoot** can be linked as an external module to any Zephyr app. This library is built on [Cozy](https://github.com/motet/cozy).

## Current coverage of draft-ietf-suit-manifest-XX
This work is in the very early stages.

## Usage
Add the following line to your app's `CMakeLists.txt`:

    set(ZEPHYR_EXTRA_MODULES <absolute_path_to>/zoot)

Add the following lines to your app's `prj.conf`:

    CONFIG_ZOOT=y
    CONFIG_MBEDTLS_CFG_FILE="config-suite-b.h"

Access the **Zoot** API from your source files with `#include <zoot/suit.h>`.

## Tests and examples
Run tests from the `tests` directory with `west build -t run -b native_posix`. See unit tests in `tests/src/tests.c` for examples.
