cmake_minimum_required(VERSION 3.10)
project(display-driver-library VERSION 1.0.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wextra")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")
endif()

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/display/core
    ${CMAKE_CURRENT_SOURCE_DIR}/display/backlight
    ${CMAKE_CURRENT_SOURCE_DIR}/display/panel
    ${CMAKE_CURRENT_SOURCE_DIR}/display/porting
    ${CMAKE_CURRENT_SOURCE_DIR}/display/common
)

# 创建显示驱动库
add_library(display_driver STATIC
    display/backlight/backlight.c
    display/backlight/backlight_ctrl.c
    display/core/display.c
    display/core/display_factory.c
    display/panel/panel_com.c
    display/panel/panel_simple.c
    display/panel/panel_st7735.c
    display/porting/display_port_backlight.c
    display/porting/display_port_spi.c
)

# 设置库的属性
set_target_properties(display_driver PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# 创建测试可执行文件
add_executable(display_test tests/test.c)

# 链接库
target_link_libraries(display_test display_driver)

# 安装配置
install(TARGETS display_driver
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY display/
    DESTINATION include/display
    FILES_MATCHING PATTERN "*.h"
)

# 添加测试
enable_testing()
add_test(NAME display_test COMMAND display_test)