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

int suit_parse_init(suit_context_t * ctx,
        const uint8_t * man, size_t len_man)
{
    nanocbor_value_t nc, map;
    nanocbor_decoder_init(&nc, man, len_man);

    uint8_t * sc; size_t len_sc;        /* suit_common */
    uint8_t * tmp; size_t len_tmp;      /* other bstrs */
    
    /* initialize optional fields with NULL values */
    nanocbor_decoder_init(&ctx->components, NULL, 0);
    nanocbor_decoder_init(&ctx->payload_fetch, NULL, 0);
    nanocbor_decoder_init(&ctx->install, NULL, 0);
    nanocbor_decoder_init(&ctx->common_sequence, NULL, 0);
    nanocbor_decoder_init(&ctx->validate, NULL, 0);
    nanocbor_decoder_init(&ctx->load, NULL, 0);
    nanocbor_decoder_init(&ctx->run, NULL, 0);

    /* parse top-level map */
    CBOR_ENTER_MAP(nc, map);
    int32_t map_key; 
    while (!nanocbor_at_end(&map)) {
        CBOR_GET_INT(map, map_key);
        switch (map_key) {

            case suit_header_common:
                CBOR_GET_BSTR(map, sc, len_sc);
                break;

            case suit_header_manifest_version:
                CBOR_GET_INT(map, ctx->version);
                if (ctx->version != 1) return 1;
                break;

            case suit_header_manifest_sequence_number:
                CBOR_GET_INT(map, ctx->sequence_number);
                break;

            case suit_header_payload_fetch:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&ctx->payload_fetch, tmp, len_tmp);
                break;

            case suit_header_install:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&ctx->install, tmp, len_tmp);
                break;

            case suit_header_validate:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&ctx->validate, tmp, len_tmp);
                break;

            case suit_header_load:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&ctx->load, tmp, len_tmp);
                break;

            case suit_header_run:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&ctx->run, tmp, len_tmp);
                break;
        }
    }
    return 0;
}
