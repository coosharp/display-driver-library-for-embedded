# 测试目录的 CMake 配置
add_executable(display_test test.c)

target_link_libraries(display_test PRIVATE display_driver)
