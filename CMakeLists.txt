cmake_minimum_required(VERSION 3.15)
project(stm32f722_project C ASM)

# Compiler Settings
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# MCU properties
set(CPU_FLAGS "-mcpu=cortex-m7 -mthumb -mfloat-abi=soft")
set(COMMON_FLAGS "${CPU_FLAGS} -Wall -g -O0")

#  Compiler flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -DSTM32F722xx")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -T${CMAKE_SOURCE_DIR}/src/stm32f722ze.ld -Wl,--gc-sections")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/USART
)

set(SOURCES
    src/startup_stm32f722ze.s
    src/main.c
    src/system_stm32f7xx.c
    lib/USART/USART.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Hex and bin 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
