all: local

DEBUG ?= 0

CMAKE_ARGS = -DCMAKE_VERBOSE_MAKEFILE=on

ifneq ($(DEBUG),)
CMAKE_ARGS +=  -DCMAKE_BUILD_TYPE=Debug
else
CMAKE_ARGS +=  -DCMAKE_BUILD_TYPE=Relase
endif

local:
	cmake -S. -Bbuild -GNinja $(CMAKE_ARGS)
	cd build/ && ninja

arm:
	cmake -S. -Bbuild_arm -GNinja -DTARGET_BOARD=arm -DCMAKE_TOOLCHAIN_FILE=../../../cmake/toolchain-arm-none-eabi.cmake $(CMAKE_ARGS)
	cd build_arm && ninja

clean:
	rm -rf build/ build_arm/

