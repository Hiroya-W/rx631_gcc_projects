CC = rx-elf-gcc
CP = rx-elf-g++

PROJECT_NAME = project_name

ASRCS = generate/start.S
CSRCS = $(wildcard generate/*.c) $(wildcard include/*.c) $(wildcard src/*.c)
CPSRCS = $(wildcard include/*.cpp) $(wildcard src/*.cpp)

OBJS = $(addprefix build/, $(patsubst %.S, %.o, $(ASRCS))) \
	   $(addprefix build/, $(patsubst %.c, %.o, $(CSRCS))) \
	   $(addprefix build/, $(patsubst %.cpp, %.o, $(CPSRCS)))


INCLUDE_DIR = ./generate ./include
LINKER = ./generate/linker_script.ld

CFLAGS = -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data
INCLUDE = $(addprefix -I,$(INCLUDE_DIR))

.PHONY: all clean flash
.DEFAULT_GOAL := all

all: clean build/$(PROJECT_NAME).elf build/$(PROJECT_NAME).mot build/$(PROJECT_NAME).siz

clean:
	rm -rf build

flash:
	rx_prog --verbose --progress --speed=115200 --device=RX631 --write build/$(PROJECT_NAME).mot

build/$(PROJECT_NAME).elf: $(OBJS)
	$(CP) $(CFLAGS) -o $@ $(OBJS) -T $(LINKER) -Wl,--start-group -lm -lc -lgcc -lstdc++ -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=build/$(PROJECT_NAME).map

build/$(PROJECT_NAME).mot: build/$(PROJECT_NAME).elf
	rx-elf-objcopy $^ -O srec -I elf32-rx-be-ns $@

build/$(PROJECT_NAME).siz: build/$(PROJECT_NAME).elf
	rx-elf-size --format=berkeley $^

build/generate/start.o: generate/start.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -x assembler-with-cpp -Wa,--gdwarf2 -DCPPAPP -I./src -Wa,-adlhn=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@ -c $^ -o $@

build/src/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CP) $(CFLAGS) $(INCLUDE) -DCPPAPP -Wa,-adlnh=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@  -c $^ -o $@

build/include/%.o: include/%.cpp
	@mkdir -p $(dir $@)
	$(CP) $(CFLAGS) $(INCLUDE) -DCPPAPP -Wa,-adlnh=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@  -c $^ -o $@

build/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -Wa,-adlnh=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@ -c $^ -o $@

build/include/%.o: include/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -Wa,-adlnh=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@ -c $^ -o $@

build/generate/%.o: generate/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -Wa,-adlnh=$(patsubst %.o,%.lst,$@) -MMD -MP -MF$(patsubst %.o,%.d,$@) -MT$@ -c $^ -o $@
