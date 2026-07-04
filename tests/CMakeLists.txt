# 测试目录的CMake配置
cmake_minimum_required(VERSION 3.10)

# 如果这是独立构建，设置项目
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(display-driver-tests VERSION 1.0.0 LANGUAGES C)
    
    # 包含父目录的配置
    include(../CMakeLists.txt)
endif()

# 添加测试可执行文件
add_executable(display_test test.c)

# 链接显示驱动库
target_link_libraries(display_test display_driver)

# 设置包含目录
target_include_directories(display_test PRIVATE
    ${CMAKE_SOURCE_DIR}/display
    ${CMAKE_SOURCE_DIR}/display/backlight
    ${CMAKE_SOURCE_DIR}/display/panel
    ${CMAKE_SOURCE_DIR}/display/common
    ${CMAKE_SOURCE_DIR}/display/porting
)