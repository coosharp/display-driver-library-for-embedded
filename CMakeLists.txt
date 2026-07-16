cmake_minimum_required(VERSION 3.10)
project(display-driver-library VERSION 1.0.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/display/sgfx_display.h
    COPYONLY
)

# 创建显示驱动库
add_library(display_driver STATIC
    sgfx/display/sgfx_display.c
    sgfx/interface/sgfx_spi.c
    sgfx/panel/command/sgfx_lcd.c
    sgfx/panel/command/sgfx_st7735.c
)

target_include_directories(display_driver
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/display
        ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/common
        ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/panel/command
        ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/interface
)

target_compile_options(display_driver PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -Wall -Wextra>
    $<$<CONFIG:Release>:-O2 -Wall>
)

# 设置库的属性
set_target_properties(display_driver PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)


# 安装配置
install(TARGETS display_driver
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)


install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/sgfx/display/sgfx_display.h
    DESTINATION include/sgfx/display
)

# 添加测试
enable_testing()
add_subdirectory(tests)