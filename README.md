# emcppbase

**目前状态**

玩具，不要用于生产环境

**主要目标**

平台无关的C++嵌入式应用快速开发框架，提供的基础设施能帮助用户在业务逻辑模块中写可移植、可复用的平台无关代码，以便在PC上完成这部分代码的调试、同时也方便移植到不同平台上，为项目加速。

框架可以在小资源微处理器（RAM>=8K~）上使用，可以适配在桌面系统、RTOS、裸机上。

**特点**

- 不使用STL，而是使用[ETL](https://www.etlcpp.com/documentation.html)作为模板库
- 不追求零开销抽象，有节制地使用一些基本的OPP特性使代码易于复用
- 简单适配core部分即可在目标环境下使用大部分功能，易于与厂商SDK集成
- 不鼓励在嵌入式项目中隐藏板级适配的细节，像Arduino、PlatformIO这样的项目做了很足的板级抽象，能让初学者快速上手，但同时也阻碍了进阶使用者修改板级（比如需要fork一份板级适配包、修改一些陌生的配置文件）
- 使用CMake构建工具，交叉编译到不同平台，同时便于IDE集成

**embase-core**

基本类型、宏定义、容器、平台功能抽象

- 日志 embase_log
- 工具宏 embase_macros
- 字符串工具 embase_string
- 任务调度器 embase_task
- 线程抽象（需要OS支持） embase_thread
- 函数集 embase_codec

**embase-arduino**

Arduino兼容层，方便使用基于它的库，同时使用它的硬件抽象接口

**embase-hw**

扩充硬件抽象接口；硬件驱动

**使用方法**

```

构建
$ just build

执行单元测试
$ just test

```
