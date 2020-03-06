zephyr_interface_library_named(zoot)
set(WITH_ZEPHYR 1)
set(WITH_ZEPHYR_LIB 1)
target_include_directories(zoot INTERFACE include)

zephyr_library()
add_subdirectory(cozy)
zephyr_library_sources(
    src/parse.c
    )
zephyr_library_link_libraries(zoot)
zephyr_include_directories(include)

target_link_libraries(zoot INTERFACE 
    zephyr_interface
    cozy
    )

