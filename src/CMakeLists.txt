file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${snake_SOURCE_DIR}/src/*.h")

add_executable(snake snake.c ${HEADER_LIST})
add_library(snake_lib point.c snake_obj.c ${HEADER_LIST})

target_link_libraries(snake snake_lib curses)
target_link_libraries(snake_lib curses)
