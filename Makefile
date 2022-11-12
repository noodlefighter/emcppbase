all: local

DEBUG ?= 0

#CMAKE_ARGS = -DEBSX_EXAMPLES=ON
CMAKE_ARGS += -DCMAKE_VERBOSE_MAKEFILE=on

ifneq ($(DEBUG),)
CMAKE_ARGS +=  -DCMAKE_BUILD_TYPE=Debug
else
CMAKE_ARGS +=  -DCMAKE_BUILD_TYPE=Relase
endif

B_LOCAL=build/
B_ARM=build_arm/

local:
	cmake -S. -B$(B_LOCAL) $(CMAKE_ARGS)
	cd $(B_LOCAL) && make -j $(cat /proc/cpuinfo |grep "processor"|wc -l)
#	//TARGET_BOARD=local ./misc/out_pack.sh $(B_LOCAL)

arm:
	cmake -S. -B$(B_ARM) -DCMAKE_TOOLCHAIN_FILE=lib/ebsx-main/toolchain-arm.cmake $(CMAKE_ARGS)
	cd $(B_ARM) && make -j $(cat /proc/cpuinfo |grep "processor"|wc -l)
	TARGET_BOARD=amp ./misc/out_pack.sh $(B_ARM)

clean:
	rm -rf build/ build_arm/

