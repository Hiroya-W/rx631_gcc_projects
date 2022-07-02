PROJECT_NAME = gcc_rx_project

BUILD = build

CC = rx-elf-gcc
CP = rx-elf-g++

ASRCS = generate/start.S
CSRCS =$(wildcard generate/*.c)
CPSRCS =$(wildcard src/*.cpp)
OBJS = $(addprefix $(BUILD)/, $(patsubst %.S, %.o, $(ASRCS))) \
       $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(CSRCS))) \
       $(addprefix $(BUILD)/, $(patsubst %.cpp, %.o, $(CPSRCS)))
LIBS =
LINKER = ./generate/linker_script.ld

.PHONY: all clean

all: $(PROJECT_NAME).elf $(PROJECT_NAME).mot $(PROJECT_NAME).siz

clean:
	rm -rf $(BUILD) *.elf *.map *.mot

$(PROJECT_NAME).elf: $(OBJS)
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 \
	-g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -o "$(PROJECT_NAME).elf" $(OBJS) $(USER_OBJS) $(LIBS) -T $(LINKER) \
	-Wl,--start-group -lm -lc -lgcc -lstdc++ -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=$(PROJECT_NAME).map

$(PROJECT_NAME).mot: $(PROJECT_NAME).elf
	rx-elf-objcopy "$(PROJECT_NAME).elf" -O srec -I elf32-rx-be-ns  "$(PROJECT_NAME).mot"

$(PROJECT_NAME).siz: $(PROJECT_NAME).elf
	rx-elf-size --format=berkeley "$(PROJECT_NAME).elf"

$(BUILD)/generate/%.o: generate/%.S
	@mkdir -p $(dir $@)
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100\
	 -g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -DCPPAPP -I./src \
	 -Wa,-adlhn="$(patsubst %.o,%.lst,$@)" -MMD -MP -MF"$(patsubst %.o,%.d,$@)" -MT"$@" -c "$^" -o "$@"

$(BUILD)/generate/%.o: generate/%.c
	@mkdir -p $(dir $@)
	$(CC) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 \
	-g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate \
	-Wa,-adlnh="$(patsubst %.o,%.lst,$@)" -MMD -MP -MF"$(patsubst %.o,%.d,$@)" -MT"$@" "$^" -c -o "$@"

$(BUILD)/src/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CP) -O0 -ffunction-sections -fdata-sections -fdiagnostics-parseable-fixits -Wstack-usage=100 \
	-g2 -mcpu=rx600 -misa=v1 -mlittle-endian-data -I./generate \
	-Wa,-adlnh="$(patsubst %.o,%.lst,$@)" -MMD -MP -MF"$(patsubst %.o,%.d,$@)" -MT"$@" "$^" -c -o "$@"
