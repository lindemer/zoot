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

#include <ztest.h>
#include <zoot/suit.h>
#include "vectors.h"

const uint8_t * key = SUIT_TEST_KEY_256_PUB;
const uint8_t env0[231] = SUIT_EXAMPLE_0;
const uint8_t env1[266] = SUIT_EXAMPLE_1;
const uint8_t env2[271] = SUIT_EXAMPLE_2;

void test_suit_boot(void) {
    uint8_t * man;
    size_t len_man;
    zassert_false(suit_authenticate_pem(
                env0, sizeof(env0), key, (const uint8_t **) &man, &len_man),
                "Failed to authenticate envelope contents."); 
}
 
void test_suit_download_install(void) {
    uint8_t * man;
    size_t len_man;
    zassert_false(suit_authenticate_pem(
                env1, sizeof(env1), key, (const uint8_t **) &man, &len_man),
                "Failed to authenticate envelope contents."); 
}

void test_suit_download_install_boot(void) {
    uint8_t * man;
    size_t len_man;
    zassert_false(suit_authenticate_pem(
                env2, sizeof(env2), key, (const uint8_t **) &man, &len_man),
                "Failed to authenticate envelope contents."); 
}
