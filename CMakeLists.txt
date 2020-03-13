zephyr_interface_library_named(zoot)
set(WITH_ZEPHYR 1)
set(WITH_ZEPHYR_LIB 1)
set(ZEPHYR_EXTRA_MODULES cozy)

target_include_directories(zoot INTERFACE include)

zephyr_library()
zephyr_library_sources(
    src/parse.c
    src/auth.c
    )
zephyr_library_link_libraries(zoot)
zephyr_include_directories(include)

target_link_libraries(zoot INTERFACE 
    zephyr_interface
    cozy
    )

