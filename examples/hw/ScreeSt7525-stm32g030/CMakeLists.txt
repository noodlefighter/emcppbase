cmake_minimum_required(VERSION 3.24.0)
project(screen_st7525)

# embase
add_subdirectory(../../.. embase)

set(TARGET_BOARD "pc" CACHE STRING "pc/arm")
message("TARGET_BOARD:" ${TARGET_BOARD})
if(${TARGET_BOARD} MATCHES "arm")
  set(MCU_FLAGS "-mcpu=cortex-m0plus")
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${MCU_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS}")
  set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${MCU_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_CURRENT_LIST_DIR}/STM32G030C8Tx_FLASH.ld")

  add_definitions("-DUSE_HAL_DRIVER -DSTM32G030xx")
  set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/startup_stm32g030xx.s
    ${CMAKE_CURRENT_LIST_DIR}/Core/Src/main.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/gpio.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/dma.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/iwdg.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/rtc.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/tim.c
    # ${CMAKE_CURRENT_LIST_DIR}/Core/Src/usart.c
    ${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32g0xx_it.c
    ${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32g0xx_hal_msp.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_iwdg.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_flash_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_dma.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_dma_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_dma.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_cortex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_exti.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rtc.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_rtc_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_tim_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_uart_ex.c
    ${CMAKE_CURRENT_LIST_DIR}/Core/Src/system_stm32g0xx.c
  )
endif()

set(SRCS
  ${SRCS}

  ${CMAKE_CURRENT_LIST_DIR}/app/app_entry.cpp
)

set(INCS
  ${CMAKE_CURRENT_LIST_DIR}/Core/Inc
  ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Inc
  ${CMAKE_CURRENT_LIST_DIR}/Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
  ${CMAKE_CURRENT_LIST_DIR}/Drivers/CMSIS/Device/ST/STM32G0xx/Include
  ${CMAKE_CURRENT_LIST_DIR}/Drivers/CMSIS/Include
  ${CMAKE_CURRENT_LIST_DIR}/Drivers/CMSIS/Include
  ${CMAKE_CURRENT_LIST_DIR}/app
)

add_executable(screen_st7525 ${SRCS})
target_include_directories(screen_st7525 PUBLIC ${INCS})
target_link_libraries(screen_st7525 embase-core embase-hw)


