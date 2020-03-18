# Zoot
**Zoot** can be linked as an external module to any Zephyr app. This library is built on the [Cozy](https://github.com/motet/cozy) implementation of CBOR Object Signing and Encryption (COSE), which is itself built on [mbedTLS](https://github.com/zephyrproject-rtos/mbedtls) and [NanoCBOR](https://github.com/bergzand/NanoCBOR).

## Usage
**Zoot** parses CBOR-encoded SUIT manifests into C structs for further update handling, as shown below. This is done without allocating additional buffers or using heap memory.

```c
typedef struct suit_component_s suit_component_t;
struct suit_component_s {
    
    bool run;    /* component is referenced by a run directive */
    size_t size; /* image size (bytes) */

    /*
     * These values are initialized to 0. If not 0, they should be
     * processed accordingly by the update handler.
     */
    suit_digest_alg_t digest_alg;       /* digest algorithm */
    suit_archive_alg_t archive_alg;     /* compression algorithm */

    /* 
     * These pointers are initialized to NULL. If not NULL, they
     * should be processed accordingly by the update handler. NB
     * these reference locations in the encoded manifest itself.
     */
    uint8_t * uri; size_t len_uri;
    uint8_t * digest; size_t len_digest;
    uint8_t * class_id; size_t len_class_id;
    uint8_t * vendor_id; size_t len_vendor_id;
    suit_component_t * source;

};

typedef struct {

    size_t version;         /* always 1 */
    size_t sequence_number; /* rollback protection */
    size_t component_count; /* may be less than maximum allowed */

    /* 
     * Recipients should specify a limit to the number of manifest
     * components (see I-D Section 5.4).
     */
    suit_component_t components[SUIT_MAX_COMPONENTS];

} suit_context_t;
```

Manifest parsing is done with a single function call to:
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

## Current coverage [the latest Internet-Draft](https://tools.ietf.org/html/draft-ietf-suit-manifest-04)
**Zoot** can parse all of the manifests provided in the example section of the latest I-D. These are included as unit tests in  `tests/src/tests.c`. (Run `west build -t run -b native_posix` from the `tests` directory.) Most of the SUIT features which are not required to parse the examples have not been implemented.
