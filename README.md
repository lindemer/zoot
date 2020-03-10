# Zoot
**Zoot** can be linked as an external module to any Zephyr app. This library is built on the [Cozy](https://github.com/motet/cozy) implementation of CBOR Object Signing and Encryption (COSE).

## Current coverage of draft-ietf-suit-manifest-04
This work is in the early stages. T

## Usage
Add the following line to your app's `CMakeLists.txt`:

    set(ZEPHYR_EXTRA_MODULES <absolute_path_to>/zoot)

Add the following line to your app's `prj.conf`:

    CONFIG_ZOOT=y

Access the **Zoot** API from your source files with `#include <zoot/suit.h>`.

## Tests and examples
Run `west build -t run -b native_posix` from the `tests` directory. The unit tests in `tests/src/tests.c` are taken directly from [the I-D](https://tools.ietf.org/html/draft-ietf-suit-manifest-04).
