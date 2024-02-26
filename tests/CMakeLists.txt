file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${snake_SOURCE_DIR}/src/*.h")

add_executable(point_tests point_tests.c ${HEADER_LIST})
add_executable(snake_obj_tests snake_obj_tests.c ${HEADER_LIST})

target_include_directories(point_tests PRIVATE "${snake_SOURCE_DIR}/src")
target_include_directories(snake_obj_tests PRIVATE "${snake_SOURCE_DIR}/src")

target_link_libraries(point_tests snake_lib)
target_link_libraries(snake_obj_tests snake_lib)

add_test(NAME point_tests COMMAND point_tests)
add_test(NAME snake_obj_tests COMMAND snake_obj_tests)
