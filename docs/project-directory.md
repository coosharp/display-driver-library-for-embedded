```
display/
├── display.h                    # 主头文件（统一接口）
├── display_conf.h              # 配置头文件
├── backlight/                  # 背光控制模块
│   ├── disp_backlight.c       # 背光控制实现
│   └── disp_backlight.h       # 背光控制头文件
├── painter/                    # 绘图功能模块
│   ├── disp_painter.c         # 绘图功能实现
│   └── disp_painter.h         # 绘图功能头文件
├── panel/                      # 显示面板驱动模块
│   ├── disp_panel.c           # 面板管理实现
│   ├── disp_panel.h           # 面板管理头文件
│   └── interga/               # 具体面板实现
│       ├── panel_com.c        # 通用面板接口
│       ├── panel_com.h        # 通用面板头文件
│       ├── panel_st7735.c     # ST7735面板驱动
│       └── panel_st7735.h     # ST7735面板头文件
└── port/                      # 硬件端口抽象层
    ├── disp_backlight_port.c  # 背光端口实现
    └── disp_panel_spi_port.c  # 面板SPI端口实现
```

