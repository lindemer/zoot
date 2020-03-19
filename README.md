# Zoot
**Zoot** can be linked as an external module to any Zephyr app. This library is built on the [Cozy](https://github.com/motet/cozy) implementation of CBOR Object Signing and Encryption (COSE), which is itself built on [mbedTLS](https://github.com/zephyrproject-rtos/mbedtls) and [NanoCBOR](https://github.com/bergzand/NanoCBOR).

## Usage
**Zoot** parses CBOR-encoded SUIT manifests into manageable C structs further update handling. This is done without allocating additional buffers or using heap memory. Examples can be found in the tests directory. Parsing a SUIT manifest is done via a single function call to `suit_parse_init`, and the contents of an initialized context struct are accessed via API calls.
```c
int suit_parse_init(suit_context_t * ctx, const uint8_t * man, size_t len_man);
```

**Zoot** also handles signature validation and manifest integrity checks on SUIT envelopes. This requires a PEM-formatted public key, and currently only supports COSE Sign1 authentication wrappers. The following simultaneously validates a SUIT envelope and extracts the manifest within:
```c
int suit_manifest_unwrap(const uint8_t * pem, 
        const uint8_t * env, const size_t len_env,
        const uint8_t ** man, size_t * len_man);
```

## Linking
Add the following line to your app's `CMakeLists.txt`:

    set(ZEPHYR_EXTRA_MODULES <absolute_path_to>/zoot)

Add the following line to your app's `prj.conf`:

    CONFIG_ZOOT=y

Access the **Zoot** API from your source files with `#include <zoot/suit.h>`.

## Current coverage of [the latest Internet-Draft](https://tools.ietf.org/html/draft-ietf-suit-manifest-04)
**Zoot** can parse all of the manifests provided in the example section of the latest I-D. These are included as unit tests in  `tests/src/tests.c`. (Run `west build -t run -b native_posix` from the `tests` directory.) Most of the SUIT features which are not required to parse the examples have not been implemented.
