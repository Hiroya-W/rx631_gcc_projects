################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gcc_rx_project.cpp 

LST += \
gcc_rx_project.lst 

OBJS += \
./src/gcc_rx_project.o 

MAP += \
gcc_rx_project.map 

CPP_DEPS += \
./src/gcc_rx_project.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I"C:/Users/HIRO/e2_studio/workspace2/gcc_rx_project/generate" -DCPPAPP -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -c "$<" -o "$@")
	@echo $< && rx-elf-g++ @"$@.in"

