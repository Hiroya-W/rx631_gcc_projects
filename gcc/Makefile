CC = rx-elf-gcc

PROJECT_NAME = project_name
OBJS = ./src/gcc_rx_project.o ./generate/hwinit.o ./generate/inthandler.o ./generate/start.o ./generate/vects.o
INCLUDE = -I./generate
CFLAGS = -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -Wa,-adlnh=$*.lst
ASFLAGS = -Wa,--gdwarf2
DEPFLAGS = -MMD -MP -MF $*.d -MT $@
LINKER = ./generate/linker_script.ld
LDFLAGS = -Wl,--start-group -lm -lc -lgcc -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=$*.map

all: $(PROJECT_NAME).elf $(PROJECT_NAME).mot $(PROJECT_NAME).siz

%.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -T $(LINKER) $(LDFLAGS)

%.mot: %.elf
	rx-elf-objcopy $< -O srec -I elf32-rx-be-ns $@

# Idiom found at https://www.gnu.org/software/make/manual/html_node/Force-Targets.html
FORCE:

%.siz: %.elf FORCE
	rx-elf-size --format=berkeley $<

.PRECIOUS: %.o

%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $(CFLAGS) $(DEPFLAGS) $< -c -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(DEPFLAGS) $< -c -o $@

-include */*.d

.PHONY: clean
clean:
	-rm */*.d
	-rm */*.o
	-rm */*.lst
	-rm *.elf
	-rm *.map
	-rm *.mot
