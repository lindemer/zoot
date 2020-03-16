/*
 * Copyright 2020 RISE Research Institutes of Sweden
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in componentliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE_2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef SUIT_H
#define SUIT_H

#include <cozy/cose.h>

#define GET_BSTR(nc, out, len_out)                              \
    nanocbor_get_bstr(&nc, (const uint8_t **) &out, &len_out) 

/** 
 * @brief SUIT API
 * @{
 */

typedef enum {
    suit_md_alg_sha224 = 1,
    suit_md_alg_sha256 = 2,
    suit_md_alg_sha384 = 3,
    suit_md_alg_sha512 = 4,
    suit_md_alg_sha3_224 = 5,
    suit_md_alg_sha3_256 = 6,
    suit_md_alg_sha3_384 = 7,
    suit_md_alg_sha3_512 = 8,
} suit_md_alg_t;

typedef enum {
    suit_compress_info_alg = 1,
    suit_compress_info_params = 2,
} suit_compress_info_t;

typedef enum {
    suit_compress_alg_gzip = 1,
    suit_compress_alg_bzip2 = 2,
    suit_compress_alg_deflate = 3,
    suit_compress_alg_lz4 = 4,
    suit_compress_alg_lzma = 7,
} suit_compress_alg_t;

typedef enum {
    suit_unpack_info_alg = 1,
    suit_unpack_info_params = 2,
} suit_unpack_info_t;

typedef enum {
    suit_unpack_alg_delta = 1,
    suit_unpack_alg_hex = 2,
    suit_unpack_alg_elf = 3,
} suit_unpack_alg_t;

typedef enum {
    suit_envelope_delegation = 1,
    suit_envelope_authentication_wrapper = 2,
    suit_envelope_manifest = 3,
    suit_envelope_manifest_encrypt_info = 4,
    suit_envelope_manifest_encrypted = 5,
} suit_envelope_t;

typedef enum {
    suit_header_manifest_version = 1,
    suit_header_manifest_sequence_number = 2,
    suit_header_common = 3,
    suit_header_reference_uri = 4,
    suit_header_dependency_resolution = 7,
    suit_header_payload_fetch = 8,
    suit_header_install = 9,
    suit_header_validate = 10,
    suit_header_load = 11,
    suit_header_run = 12,
    suit_header_text = 13,
    suit_header_coswid = 14,
} suit_header_t;

typedef enum {
    suit_common_dependencies = 1,
    suit_common_components = 2,
    suit_common_dependency_components = 3,
    suit_common_sequence = 4,
} suit_common_t;

typedef enum {
    suit_dependency_digest = 1,
    suit_dependency_preix = 2,
} suit_dependency_t;

typedef enum {
    suit_component_id = 1,
    suit_component_dependency_index = 2,
} suit_component_t;

typedef enum {
    suit_condition_vendor_id = 1,
    suit_condition_class_id = 2,
    suit_condition_image_match = 3,
    suit_condition_use_before = 4,
    suit_condition_component_offset = 5,
    suit_condition_device_id = 24,
    suit_condition_image_not_match = 25,
    suit_condition_min_battery = 26,
    suit_condition_update_authorized = 27,
    suit_condition_version = 28,
} suit_condition_t;

typedef enum {
    suit_condition_version_gt = 1,
    suit_condition_version_ge = 2,
    suit_condition_version_eq = 3,
    suit_condition_version_le = 4,
    suit_condition_version_lt = 5,
} suit_condition_version_t;

typedef enum {
    suit_directive_set_component_index = 12,
    suit_directive_set_dependency_index = 13,
    suit_directive_abort = 14,
    suit_directive_try_each = 15,
    suit_directive_do_each = 16, // TBD
    suit_directive_map_filter = 17, // TBD
    suit_directive_process_dependency = 18,
    suit_directive_set_params = 19,
    suit_directive_override_params = 20,
    suit_directive_fetch = 21,
    suit_directive_copy = 22,
    suit_directive_run = 23,
    suit_directive_wait = 29,
    suit_directive_run_sequence = 30,
    suit_directive_swap = 32,
} suit_directive_t;

typedef enum {
    suit_wait_authorization = 1,
    suit_wait_power = 2,
    suit_wait_network = 3,
    suit_wait_other_device_version = 4,
    suit_wait_time = 5,
    suit_wait_time_of_day = 6,
    suit_wait_day_of_week = 7,
} suit_wait_t;

typedef enum {
    suit_param_vendor_id = 1,
    suit_param_class_id = 2,
    suit_param_image_digest = 3,
    suit_param_use_before = 4,
    suit_param_component_offset = 5,
    suit_param_strict_order = 12,
    suit_param_soft_fail = 13,
    suit_param_image_size = 14,
    suit_param_encrypt_info = 18,
    suit_param_compress_info = 19,
    suit_param_unpack_info = 20,
    suit_param_uri = 21,
    suit_param_source_component = 22,
    suit_param_run_args = 23,
    suit_param_device_id = 24,
    suit_param_min_battery = 26,
    suit_param_update_priority = 27,
    suit_param_version = 28,
    suit_param_wait_info = 29,
} suit_param_t;

typedef enum {
    suit_text_manifest_description = 1,
    suit_text_update_description = 2,
    suit_text_vendor_name = 3,
    suit_text_model_name = 4,
    suit_text_vendor_domain = 5,
    suit_text_model_info = 6,
    suit_text_component_description = 7,
    suit_text_manifest_json_source = 8,
    suit_text_manifest_yaml_source = 9,
    suit_text_version_dependencies = 10,
} suit_text_t;

typedef struct {
    suit_md_alg_t md_alg;
    uint8_t * hash;
    size_t len_hash;
} suit_digest_t;

typedef struct {
    bool is_hash;
    union {
        suit_digest_t hash;
        nanocbor_value_t sequence;
    };
} suit_severable_sequence_t;

typedef struct {
    uint32_t version;
    uint32_t sequence_number;
    nanocbor_value_t components;

    /* severable command sequences */
    suit_severable_sequence_t payload_fetch;
    suit_severable_sequence_t install;
    
    /* ordinary command sequences */
    suit_severable_sequence_t common_sequence;
    suit_severable_sequence_t validate;
    suit_severable_sequence_t load;
    suit_severable_sequence_t run;
} suit_parser_t;

int suit_parser_init(suit_parser_t * sp,
        const uint8_t * man, size_t len_man);

/**
 * @brief Authenticate a signed SUIT envelope and return the manifest
 * 
 * @param       pem     Pointer to PEM-formatted public key string
 * @param       env     Pointer to SUIT envelope
 * @param       len_env Size of envelope
 * @param[out]  man     Pointer to manifestifest within authenticated envelope
 * @param[out]  len_man Size of manifest
 *
 * @retval      0       TODO
 * @retval      1       TODO
 */
int suit_manifest_unwrap(const uint8_t * pem, 
        const uint8_t * env, const size_t len_env,
        const uint8_t ** man, size_t * len_man);

/**
 * @brief Generate a manifest envelope with authenticated wrapper
 *
 * @param       pem     Pointer to PEM-formatted private key string
 * @param       man     Pointer to SUIT manifest
 * @param       len_man Size of manifest
 * @param[out]  env     Pointer to SUIT envelope (buffer allocated by CALLER)
 * @param[out]  len_env Size of envelope
 *
 * @retval      0       TODO
 * @retval      1       TODO
 */
int suit_manifest_wrap(const uint8_t * pem,
        const uint8_t * man, const size_t len_man,
        uint8_t * env, size_t * len_env);

/**
 * @}
 */

#endif /* SUIT_H */
