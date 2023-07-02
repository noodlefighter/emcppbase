# emcppbase

**目前状态**

玩具，不要用于生产环境

**主要目标**

平台无关的嵌入式应用开发工具集，为了方便在小资源微处理器（RAM>=8K~）上快速开发可移植、可复用的代码，同时为在桌面机上调试硬件无关代码提供条件。

**特点**

- 不使用STL，而是使用[ETL](https://www.etlcpp.com/documentation.html)作为模板库
- 不追求零开销抽象，有节制地使用一些基本的OPP特性使代码易于复用
- 简单适配即可在目标板上工作，易于与厂商SDK集成
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
