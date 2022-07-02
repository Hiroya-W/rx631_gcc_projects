PROJECT_NAME = gcc_rx_project

BUILD = build

CC = rx-elf-gcc
CP = rx-elf-g++

OBJS = ./$(BUILD)/main.o  ./$(BUILD)/hwinit.o ./$(BUILD)/inthandler.o ./$(BUILD)/start.o ./$(BUILD)/vects.o
LIBS =
LINKER = ./generate/linker_script.ld

all: $(BUILD) $(PROJECT_NAME).elf $(PROJECT_NAME).mot $(PROJECT_NAME).siz

$(PROJECT_NAME).elf: $(OBJS)
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -o "$(PROJECT_NAME).elf" $(OBJS) $(USER_OBJS) $(LIBS) -T $(LINKER) -Wl,--start-group -lm -lc -lgcc -lstdc++ -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=$(PROJECT_NAME).map

$(PROJECT_NAME).mot: $(PROJECT_NAME).elf
	rx-elf-objcopy "$(PROJECT_NAME).elf" -O srec -I elf32-rx-be-ns  "$(PROJECT_NAME).mot"

$(PROJECT_NAME).siz: $(PROJECT_NAME).elf
	rx-elf-size --format=berkeley "$(PROJECT_NAME).elf"

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/main.o: src/main.cpp
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -DCPPAPP -Wa,-adlnh="$(BUILD)/main.lst" -MMD -MP -MF"$(BUILD)/main.d" -MT"$(BUILD)/main.o"  -c "src/main.cpp" -o "$(BUILD)/main.o"

$(BUILD)/start.o: generate/start.S
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -DCPPAPP -I./src -Wa,-adlhn="$(BUILD)/start.lst" -MMD -MP -MF"$(BUILD)/start.d" -MT"$(BUILD)/start.o" -c "generate/start.S" -o "$(BUILD)/start.o"

$(BUILD)/hwinit.o: generate/hwinit.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="$(BUILD)/hwinit.lst" -MMD -MP -MF"$(BUILD)/hwinit.d" -MT"$(BUILD)/hwinit.o" "generate/hwinit.c" -c -o "$(BUILD)/hwinit.o"

$(BUILD)/inthandler.o: generate/inthandler.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="$(BUILD)/inthandler.lst" -MMD -MP -MF"$(BUILD)/inthandler.d" -MT"$(BUILD)/inthandler.o" "generate/inthandler.c" -c -o "$(BUILD)/inthandler.o"

$(BUILD)/vects.o: generate/vects.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="$(BUILD)/vects.lst" -MMD -MP -MF"$(BUILD)/vects.d" -MT"$(BUILD)/vects.o" "generate/vects.c" -c -o "$(BUILD)/vects.o"

.PHONY: clean
clean:
	rm -rf $(BUILD) $(PROJECT_NAME).elf $(PROJECT_NAME).map $(PROJECT_NAME).mot
