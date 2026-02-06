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
    ${CMAKE_CURRENT_SOURCE_DIR}/display
    ${CMAKE_CURRENT_SOURCE_DIR}/display/backlight
    ${CMAKE_CURRENT_SOURCE_DIR}/display/painter
    ${CMAKE_CURRENT_SOURCE_DIR}/display/panel
    ${CMAKE_CURRENT_SOURCE_DIR}/display/panel/interga
    ${CMAKE_CURRENT_SOURCE_DIR}/display/port
)

# 创建显示驱动库
add_library(display_driver STATIC
    display/backlight/disp_backlight.c
    display/painter/disp_painter.c
    display/panel/disp_panel.c
    display/panel/interga/panel_com.c
    display/panel/interga/panel_st7735.c
    display/port/disp_backlight_port.c
    display/port/disp_panel_spi_port.c
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