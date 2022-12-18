# emcppbase

主要目标：
- 适用于小资源微处理器（RAM>=8K~）的C++通用开发平台
- 不追求零开销抽象，有节制地使用一些基本的OPP特性使代码易于复用
- 使用CMake构建工具，交叉编译到不同平台，同时便于IDE集成
- 为在本地调试硬件无关代码提供条件

功能：
- embase-core：基本类型、宏定义、容器、平台功能抽象（如Thread提供统一接口，实现是Posix Threads、FreeRTOS Threads等）
- embase-hw：硬件设备抽象接口及驱动
- embase-arduino：Arduino兼容层
