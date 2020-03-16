/*
 * Copyright 2020 RISE Research Institutes of Sweden
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#define SUIT_TEST_KEY_256_PRV                                                   \
    "-----BEGIN PRIVATE KEY-----\r\n"                                           \
    "MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgApZYjZCUGLM50VBC\r\n"      \
    "CjYStX+09jGmnyJPrpDLTz/hiXOhRANCAASEloEarguqq9JhVxie7NomvqqL8Rtv\r\n"      \
    "P+bitWWchdvArTsfKktsCYExwKNtrNHXi9OB3N+wnAUtszmR23M4tKiW\r\n"              \
    "-----END PRIVATE KEY-----\r\n"

#define SUIT_TEST_KEY_256_PUB                                                   \
    "-----BEGIN PUBLIC KEY-----\r\n"                                            \
    "MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEhJaBGq4LqqvSYVcYnuzaJr6qi/Eb\r\n"      \
    "bz/m4rVlnIXbwK07HypLbAmBMcCjbazR14vTgdzfsJwFLbM5kdtzOLSolg==\r\n"          \
    "-----END PUBLIC KEY-----\r\n"

/*
 * These examples can be found at:
 * https://tools.ietf.org/html/draft-ietf-suit-manifest-04#section-12
 */
#define SUIT_MANIFEST_0                                                         \
    "a50101020103585ea20244818141000458548614a40150fa6"                         \
    "b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f2ab4503820"    \
    "2582000112233445566778899aabbccddeeff0123456789abcdeffedcba98765432100"    \
    "e1987d001f602f60a438203f60c438217f6"

#define SUIT_MANIFEST_1                                                         \
    "a50101020203585ea20244818141000458548614a40150fa6"                         \
    "b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f2ab4503820"    \
    "2582000112233445566778899aabbccddeeff0123456789abcdeffedcba98765432100"    \
    "e1987d001f602f60958258613a115781b687474703a2f2f6578616d706c652e636f6d2"    \
    "f66696c652e62696e15f603f60a438203f6"

#define SUIT_MANIFEST_2                                                         \
    "a60101020303585ea20244818141000458548614a40150fa6"                         \
    "b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f2ab4503820"    \
    "2582000112233445566778899aabbccddeeff0123456789abcdeffedcba98765432100"    \
    "e1987d001f602f60958258613a115781b687474703a2f2f6578616d706c652e636f6d2"    \
    "f66696c652e62696e15f603f60a438203f60c438217f6"

#define SUIT_MANIFEST_3                                                         \
    "a701010204035863a2024782814100814101045856880c001"                         \
    "4a40150fa6b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f"    \
    "2ab45038202582000112233445566778899aabbccddeeff0123456789abcdeffedcba9"    \
    "8765432100e1987d001f602f6095827880c0013a115781b687474703a2f2f6578616d7"    \
    "06c652e636f6d2f66696c652e62696e15f603f60a45840c0003f60b4b880c0113a1160"    \
    "016f603f60c45840c0117f6"

#define SUIT_MANIFEST_4                                                         \
    "a701010205035863a2024782814100814101045856880c001"                         \
    "4a40150fa6b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f"    \
    "2ab45038202582000112233445566778899aabbccddeeff0123456789abcdeffedcba9"    \
    "8765432100e1987d001f602f6095827880c0013a115781b687474703a2f2f6578616d7"    \
    "06c652e636f6d2f66696c652e62696e15f603f60a45840c0003f60b4d880c0113a2130"    \
    "1160016f603f60c45840c0117f6"

#define SUIT_MANIFEST_5                                                         \
    "a701010205035863a2024782814101814100045856880c011"                         \
    "4a40150fa6b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f"    \
    "2ab45038202582000112233445566778899aabbccddeeff0123456789abcdeffedcba9"    \
    "8765432100e1987d001f602f6085823840c0013a115781b687474703a2f2f6578616d7"    \
    "06c652e636f6d2f66696c652e62696e094b880c0113a1160016f603f60a45840c0103f"    \
    "60c45840c0117f6"

#define SUIT_MANIFEST_6                                                         \
    "a501010203035899a202448181410004588f8814a20150fa6"                         \
    "b4a53d5ad5fdfbe9de663e4d41ffe02501492af1425695e48bf429b2d51f2ab450f825"    \
    "82e8405f614a2038202582000112233445566778899aabbccddeeff0123456789abcde"    \
    "ffedcba98765432100e1987d058308405f614a203820258200123456789abcdeffedcb"    \
    "a987654321000112233445566778899aabbccddeeff0e1a00012c2201f602f60958538"    \
    "60f8258248405f613a115781c687474703a2f2f6578616d706c652e636f6d2f66696c6"    \
    "5312e62696e58248405f613a115781c687474703a2f2f6578616d706c652e636f6d2f6"    \
    "6696c65322e62696e15f603f60a438203f6"
