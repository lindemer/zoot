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

extern void test_suit_boot(void);
extern void test_suit_download_install(void);
extern void test_suit_download_install_boot(void);
extern void test_suit_load_external_storage(void);
extern void test_suit_load_decompress_external_storage(void);
extern void test_suit_compatibility_download_install_boot(void);
extern void test_suit_two_images(void);

/* test case main entry */
void test_main(void)
{
    ztest_test_suite(suit_tests,
        ztest_unit_test(test_suit_boot),
        ztest_unit_test(test_suit_download_install),
        ztest_unit_test(test_suit_download_install_boot),
        ztest_unit_test(test_suit_load_external_storage),
        ztest_unit_test(test_suit_load_decompress_external_storage),
        ztest_unit_test(test_suit_compatibility_download_install_boot),
        ztest_unit_test(test_suit_two_images));
    ztest_run_test_suite(suit_tests);
}
