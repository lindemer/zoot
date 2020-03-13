/*
 * Copyright 2020 RISE Research Institutes of Sweden
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
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
    suit_archive_info_alg = 1,
    suit_archive_info_params = 2,
} suit_archive_info_t;

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
    suit_env_delegation = 1,
    suit_env_auth_wrapper = 2,
    suit_env_man = 3,
    suit_env_man_encrypt_info = 4,
    suit_env_man_encrypted = 5,
} suit_env_t;

typedef enum {
    suit_header_man_ver = 1,
    suit_header_man_seq_num = 2,
    suit_header_common = 3,
    suit_header_reference_uri = 4,
    suit_header_dep_resolution = 7,
    suit_header_pld_fetch = 8,
    suit_header_install = 9,
    suit_header_validate = 10,
    suit_header_load = 11,
    suit_header_run = 12,
    suit_header_text = 13,
    suit_header_coswid = 14,
} suit_header_t;

typedef enum {
    suit_common_deps = 1,
    suit_common_comps = 2,
    suit_common_dep_comps = 3,
    suit_common_seq = 4,
} suit_common_t;

typedef enum {
    suit_dep_digest = 1,
    suit_dep_prefix = 2,
} suit_dep_t;

typedef enum {
    suit_comp_id = 1,
    suit_comp_dep_idx = 2,
} suit_comp_t;

typedef enum {
    suit_cond_vendor_id = 1,
    suit_cond_class_id = 2,
    suit_cond_img_match = 3,
    suit_cond_use_before = 4,
    suit_cond_comp_offset = 5,
    suit_cond_device_id = 24,
    suit_cond_img_not_match = 25,
    suit_cond_min_batt = 26,
    suit_cond_update_auth = 27,
    suit_cond_ver = 28,
} suit_cond_t;

typedef enum {
    suit_cond_ver_gt = 1,
    suit_cond_ver_ge = 2,
    suit_cond_ver_eq = 3,
    suit_cond_ver_le = 4,
    suit_cond_ver_lt = 5,
} suit_cond_ver_t;

typedef enum {
    suit_dir_set_comp_idx = 12,
    suit_dir_set_dep_idx = 13,
    suit_dir_abort = 14,
    suit_dir_try_each = 15,
    suit_dir_do_each = 16, // TBD
    suit_dir_map_filter = 17, // TBD
    suit_dir_process_dep = 18,
    suit_dir_set_params = 19,
    suit_dir_override_params = 20,
    suit_dir_fetch = 21,
    suit_dir_copy = 22,
    suit_dir_run = 23,
    suit_dir_wait = 29,
    suit_dir_run_seq = 30,
    suit_dir_swap = 32,
} suit_dir_t;

typedef enum {
    suit_wait_auth = 1,
    suit_wait_power = 2,
    suit_wait_network = 3,
    suit_wait_other_device_ver = 4,
    suit_wait_time = 5,
    suit_wait_time_of_day = 6,
    suit_wait_day_of_week = 7,
} suit_wait_t;

typedef enum {
    suit_param_vendor_id = 1,
    suit_param_class_id = 2,
    suit_param_img_digest = 3,
    suit_param_use_before = 4,
    suit_param_comp_offset = 5,
    suit_param_strict_order = 12,
    suit_param_soft_fail = 13,
    suit_param_img_size = 14,
    suit_param_encrypt_info = 18,
    suit_param_archive_info = 19,
    suit_param_unpack_info = 20,
    suit_param_uri = 21,
    suit_param_src_comp = 22,
    suit_param_run_args = 23,
    suit_param_device_id = 24,
    suit_param_min_batt = 26,
    suit_param_update_prio = 27,
    suit_param_ver = 28,
    suit_param_wait_info = 29,
} suit_param_t;

typedef enum {
    suit_text_man_desc = 1,
    suit_text_update_desc = 2,
    suit_text_vendor_name = 3,
    suit_text_model_name = 4,
    suit_text_vendor_domain = 5,
    suit_text_model_info = 6,
    suit_text_comp_desc = 7,
    suit_text_man_json_src = 8,
    suit_text_man_yaml_src = 9,
    suit_text_ver_deps = 10,
} suit_text_t;

/**
 * @brief Authenticate a signed SUIT envelope and return the manifest
 * 
 * @param       pem     Pointer to PEM-formatted public key string
 * @param       env     Pointer to SUIT envelope
 * @param       len_env Size of env
 * @param[out]  man     Pointer to manifest within authenticated envelope
 * @param[out]  len_man Size of man
 *
 * @retval      0       TODO
 * @retval      1       TODO
 */
int suit_env_unwrap(const uint8_t * pem, 
        const uint8_t * env, const size_t len_env,
        const uint8_t ** man, size_t * len_man);

/**
 * @brief Generate a manifest envelope with authenticated wrapper
 *
 * @param       pem     Pointer to PEM-formatted private key string
 * @param       man     Pointer to SUIT manifest
 * @param       len_man Size of man
 * @param[out]  env     Pointer to SUIT envelope (buffer allocated by CALLER)
 * @param[out]  len_env Size of env
 *
 * @retval      0       TODO
 * @retval      1       TODO
 */
int suit_env_wrap(const uint8_t * pem,
        const uint8_t * man, const size_t len_man,
        uint8_t * env, size_t * len_env);

/**
 * @}
 */

#endif /* SUIT_H */
