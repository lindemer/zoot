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

#include <zoot/suit.h>
#include <cozy/cose.h>

int suit_authenticate_pem(
        const uint8_t * env,
        const size_t len_env,
        const uint8_t * pem, 
        const uint8_t ** man,
        size_t * len_man)
{
    cose_sign_context_t ctx;
    if (cose_sign_init(&ctx, 1, pem, NULL, 0))
        return 1;

    uint8_t * auth;
    size_t len_auth;

    nanocbor_value_t nc, map;
    nanocbor_decoder_init(&nc, env, len_env);
    if (nanocbor_enter_map(&nc, &map) < 0) return 1;
    while (!nanocbor_at_end(&map)) {
        int32_t map_key;
        if (nanocbor_get_int32(&map, &map_key) < 0) return 1;
        if (map_key == suit_env_auth_wrapper) {
            if (nanocbor_get_bstr(&map, (const uint8_t **) &auth, &len_auth) < 0) 
                return 1;
            else break;
        }
        nanocbor_skip(&map);
    }

    int err = cose_sign_read(&ctx, auth, len_auth, NULL, 0, man, len_man);
    DUMPX(err)
    return err;
}
