################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_SCRIPT += \
../generate/linker_script.ld 

S_UPPER_SRCS += \
../generate/start.S 

C_SRCS += \
../generate/hwinit.c \
../generate/inthandler.c \
../generate/vects.c 

LST += \
hwinit.lst \
inthandler.lst \
start.lst \
vects.lst 

C_DEPS += \
./generate/hwinit.d \
./generate/inthandler.d \
./generate/vects.d 

OBJS += \
./generate/hwinit.o \
./generate/inthandler.o \
./generate/start.o \
./generate/vects.o 

MAP += \
gcc_rx_project.map 

S_UPPER_DEPS += \
./generate/start.d 


# Each subdirectory must supply rules for building sources it contributes
generate/%.o: ../generate/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I"C:/Users/HIRO/e2_studio/workspace2/gcc_rx_project/generate" -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" "$<" -c -o "$@")
	@echo $< && rx-elf-gcc @"$@.in"
generate/%.o: ../generate/%.S
	@echo 'Building file: $<'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/HIRO/e2_studio/workspace2/gcc_rx_project/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c "$<" -o "$@")
	@echo $< && rx-elf-gcc @"$@.in"

