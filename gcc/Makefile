CC = rx-elf-gcc

OBJS = ./src/gcc_rx_project.o  ./generate/hwinit.o ./generate/inthandler.o ./generate/start.o ./generate/vects.o
LIBS =
LINKER = ./generate/linker_script.ld

all: gcc_rx_project.elf gcc_rx_project.mot gcc_rx_project.siz

gcc_rx_project.elf: $(OBJS)
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -o "gcc_rx_project.elf" $(OBJS) $(USER_OBJS) $(LIBS) -T $(LINKER) -Wl,--start-group -lm -lc -lgcc -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=gcc_rx_project.map

gcc_rx_project.mot: gcc_rx_project.elf
	rx-elf-objcopy "gcc_rx_project.elf" -O srec -I elf32-rx-be-ns  "gcc_rx_project.mot"

gcc_rx_project.siz: gcc_rx_project.elf
	rx-elf-size --format=berkeley "gcc_rx_project.elf"

src/gcc_rx_project.o: src/gcc_rx_project.c
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate -Wa,-adlnh="gcc_rx_project.lst" -MMD -MP -MF"src/gcc_rx_project.d" -MT"src/gcc_rx_project.o" "src/gcc_rx_project.c" -c -o "src/gcc_rx_project.o"

generate/start.o: generate/start.S
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I./src -Wa,-adlhn="start.lst" -MMD -MP -MF"generate/start.d" -MT"generate/start.o" -c "generate/start.S" -o "generate/start.o"

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
	-rm gcc_rx_project.elf
	-rm gcc_rx_project.lst
	-rm gcc_rx_project.map
	-rm gcc_rx_project.mot
