################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\Debug" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\Core" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\User" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\Peripheral\inc" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS\include" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS\portable\Common" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS\portable\GCC\RISC-V" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"C:\Users\mjc\Documents\proj\CH32C307V-EVT-R1\CH32V307-FreeRTOS\FreeRTOS\portable\MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

