PROJECT_NAME = gcc_rx_project

CC = rx-elf-gcc
CP = rx-elf-g++

OBJS = ./src/main.o  ./generate/hwinit.o ./generate/inthandler.o ./generate/start.o ./generate/vects.o
LIBS =
LINKER = ./generate/linker_script.ld

all: $(PROJECT_NAME).elf $(PROJECT_NAME).mot $(PROJECT_NAME).siz

$(PROJECT_NAME).elf: $(OBJS)
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -o "$(PROJECT_NAME).elf" $(OBJS) $(USER_OBJS) $(LIBS) -T $(LINKER) -Wl,--start-group -lm -lc -lgcc -lstdc++ -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=$(PROJECT_NAME).map

$(PROJECT_NAME).mot: $(PROJECT_NAME).elf
	rx-elf-objcopy "$(PROJECT_NAME).elf" -O srec -I elf32-rx-be-ns  "$(PROJECT_NAME).mot"

$(PROJECT_NAME).siz: $(PROJECT_NAME).elf
	rx-elf-size --format=berkeley "$(PROJECT_NAME).elf"

src/main.o: src/main.cpp
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -DCPPAPP -Wa,-adlnh="main.lst" -MMD -MP -MF"src/main.d" -MT"src/main.o"  -c "src/main.cpp" -o "src/main.o"

generate/start.o: generate/start.S
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -DCPPAPP -I./src -Wa,-adlhn="start.lst" -MMD -MP -MF"generate/start.d" -MT"generate/start.o" -c "generate/start.S" -o "generate/start.o"

generate/hwinit.o: generate/hwinit.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="hwinit.lst" -MMD -MP -MF"generate/hwinit.d" -MT"generate/hwinit.o" "generate/hwinit.c" -c -o "generate/hwinit.o"

generate/inthandler.o: generate/inthandler.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="inthandler.lst" -MMD -MP -MF"generate/inthandler.d" -MT"generate/inthandler.o" "generate/inthandler.c" -c -o "generate/inthandler.o"

generate/vects.o: generate/vects.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="vects.lst" -MMD -MP -MF"generate/vects.d" -MT"generate/vects.o" "generate/vects.c" -c -o "generate/vects.o"

.PHONY: clean
clean:
	-rm generate/*.d src/*.d
	-rm generate/*.o src/*.o
	-rm ./*.lst
	-rm $(PROJECT_NAME).elf
	-rm $(PROJECT_NAME).lst
	-rm $(PROJECT_NAME).map
	-rm $(PROJECT_NAME).mot
