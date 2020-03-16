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

int suit_parser_init(suit_parser_t * sp,
        const uint8_t * man, size_t len_man)
{
    nanocbor_value_t nc, map;
    nanocbor_decoder_init(&nc, man, len_man);

    if (nanocbor_enter_map(&nc, &map) < 0) return 1;
    int32_t map_key;
    uint8_t * common; size_t len_common;

    while (!nanocbor_at_end(&map)) {
        if (nanocbor_get_int32(&map, &map_key) < 0) return 1;
        switch (map_key) {
            case suit_header_common:
                if (GET_BSTR(map, common, len_common) < 0) return 1;
                break;
            case suit_header_manifest_version:
                if (nanocbor_get_uint32(&map, &sp->version) < 0) return 1;
                break;
            case suit_header_manifest_sequence_number:
                if (nanocbor_get_uint32(&map, &sp->sequence_number) < 0) return 1;
                break;
            case suit_header_payload_fetch:
                nanocbor_skip(&map);
                break;
            case suit_header_install:
                nanocbor_skip(&map);
                break;
            case suit_header_validate:
                nanocbor_skip(&map);
                break;
            case suit_header_load:
                nanocbor_skip(&map);
                break;
            case suit_header_run:
                nanocbor_skip(&map);
                break;
        }
        DUMPD(map_key);
    }

    DUMPD(sp->version);
    DUMPD(sp->sequence_number);
    return 0;
}
