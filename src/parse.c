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

/* any parsing failure results in total manifest rejection */
#define CBOR_ENTER_ARR(nc1, nc2) \
    if (nanocbor_enter_array(&nc1, &nc2) < 0) return 1;

#define CBOR_ENTER_MAP(nc1, nc2) \
    if (nanocbor_enter_map(&nc1, &nc2) < 0) return 1;

#define CBOR_GET_INT(nc, val) \
    if (nanocbor_get_uint32(&nc, &val) < 0) return 1;

#define CBOR_GET_BSTR(nc, val, len_val) \
    if (nanocbor_get_bstr(&nc, (const uint8_t **) &val, &len_val) < 0) \
    return 1;

int _suit_parse_sequence(suit_context_t * ctx,
        const uint8_t * seq, size_t len_seq)
{
    /* component selector */
    size_t idx = 0;

    nanocbor_value_t top, arr, subarr;
    nanocbor_decoder_init(&top, seq, len_seq);
    uint8_t * tmp; size_t len_tmp; bool pass;

    CBOR_ENTER_ARR(top, arr);
    int32_t arr_key; 
    while (!nanocbor_at_end(&arr)) {
        CBOR_GET_INT(arr, arr_key);
        switch (arr_key) {

            /* DIRECTIVE set global parameters (TODO) */
            case suit_directive_override_params:
                nanocbor_skip(&arr); break;
            
            /* DIRECTIVE set local parameters (TODO) */
            case suit_directive_set_params:
                nanocbor_skip(&arr); break;

            /* DIRECTIVE run this component */
            case suit_directive_run:
                ctx->comps[idx].run = true;
                nanocbor_skip(&arr); break;

            /* DIRECTIVE copy this component (TODO) */
            case suit_directive_copy:
                nanocbor_skip(&arr); break;

            /* DIRECTIVE set component index */
            case suit_directive_set_comp_idx:
                CBOR_GET_INT(arr, idx);
                if (idx > ctx->num_comps) return 1;
                break;

            /* CONDITION check component offset (TODO) */
            case suit_condition_comp_offset:
                nanocbor_skip(&arr); break;

            /* 
             * This directive provides an ordered list of command
             * sequences to attempt. The first to succeed is 
             * accepted. If all fail, the manifest is rejected. 
             */

            /* DIRECTIVE try each */
            case suit_directive_try_each:
                pass = false;
                CBOR_ENTER_ARR(arr, subarr);
                while (!nanocbor_at_end(&subarr)) {
                    CBOR_GET_BSTR(subarr, tmp, len_tmp);
                    if (!_suit_parse_sequence(ctx, tmp, len_tmp)) {
                        pass = true; break;
                    }
                }
                if (!pass) return 1;
                nanocbor_skip(&arr); break;
             
            /* 
             * The conditions and directives are ignored because:
             *  - vendor IDs are checked by default
             *  - class IDs are checked by default
             *  - digests are checked if they have been specified
             *  - components are fetched if a uri has been specified
             */ 

            /* CONDITION check vendor ID */
            case suit_condition_vendor_id:
                nanocbor_skip(&arr); break;

            /* CONDITION check class ID */ 
            case suit_condition_class_id:
                nanocbor_skip(&arr); break;
            
            /* CONDITION check component digest */
            case suit_condition_image_match:
                nanocbor_skip(&arr); break;

            /* DIRECTIVE fetch this component */
            case suit_directive_fetch:
                nanocbor_skip(&arr); break;

            /* UNSUPPORTED */
            default: 
                DUMPD(arr_key);
                return 1;

        }
    }
    return 0;
}

int _suit_parse_common(suit_context_t * ctx,
        const uint8_t * com, size_t len_com)
{
    nanocbor_value_t top, map, arr, elem;
    nanocbor_decoder_init(&top, com, len_com);
    uint8_t * tmp; size_t len_tmp;

    CBOR_ENTER_MAP(top, map);
    int32_t map_key; 
    while (!nanocbor_at_end(&map)) {
        CBOR_GET_INT(map, map_key);
        switch (map_key) {

            /* The number of components listed in the manifest must
             * not exceed the device's specified limit (see I-D 
             * Section 5.4). The components are referenced by index 
             * in the manifest. The component IDs can be discarded.
             */
            case suit_common_comps:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                nanocbor_decoder_init(&arr, tmp, len_tmp);
                CBOR_ENTER_ARR(arr, elem);
                ctx->num_comps = elem.remaining;
                if (ctx->num_comps > SUIT_MAX_COMPONENTS) 
                    return 1;
                break;

            case suit_common_seq:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

            default:
                nanocbor_skip(&map);
                break;
        }
    }
    return 0;
}

int suit_parse_init(suit_context_t * ctx,
        const uint8_t * man, size_t len_man)
{
    nanocbor_value_t top, map;
    nanocbor_decoder_init(&top, man, len_man);
    uint8_t * tmp; size_t len_tmp;

    /* initialize command sequences */
    for (size_t idx = 0; idx < SUIT_MAX_COMPONENTS; idx++) {
        ctx->comps[idx].run = false;
        ctx->comps[idx].md = NULL;
        ctx->comps[idx].uri = NULL;
        ctx->comps[idx].vendor_id = NULL;
        ctx->comps[idx].class_id = NULL;
    }

    /* parse top-level map */
    CBOR_ENTER_MAP(top, map);
    int32_t map_key; 
    while (!nanocbor_at_end(&map)) {
        CBOR_GET_INT(map, map_key);
        switch (map_key) {

            case suit_header_common:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_common(ctx, tmp, len_tmp))
                    return 1;
                break;

            case suit_header_manifest_version:
                CBOR_GET_INT(map, ctx->version);
                if (ctx->version != 1) return 1;
                break;

            case suit_header_manifest_seq_num:
                CBOR_GET_INT(map, ctx->seq_num);
                break;

            case suit_header_payload_fetch:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

            case suit_header_install:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

            case suit_header_validate:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

            case suit_header_load:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

            case suit_header_run:
                CBOR_GET_BSTR(map, tmp, len_tmp);
                if (_suit_parse_sequence(ctx, tmp, len_tmp))
                    return 1;
                break;

        }
    }
    return 0;
}
