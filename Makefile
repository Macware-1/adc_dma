# Target output
TARGET = build/firmware

# Tools
CXX = arm-none-eabi-g++
CC  = arm-none-eabi-gcc
LD  = arm-none-eabi-gcc
CP  = arm-none-eabi-objcopy

# Default build type: debug
BUILD ?= debug

# Flags
CFLAGS_DEBUG = -O0 -g
CFLAGS_RELEASE = -O2 -g0

ifeq ($(BUILD),debug)
    CFLAGS = $(CFLAGS_DEBUG)
else ifeq ($(BUILD),release)
    CFLAGS = $(CFLAGS_RELEASE)
else
    $(error Unknown BUILD type $(BUILD))
endif

APPLICATION_FLAG = -DNLED_BLINK
CFLAGS += $(APPLICATION_FLAG)

CXXFLAGS = -c $(CFLAGS) -mcpu=cortex-m4 -mthumb -std=c++11 -fno-exceptions -fno-rtti
CFLAGS_C = -c $(CFLAGS) -mcpu=cortex-m4 -mthumb
LDFLAGS  = -nostartfiles -T linker.ld
CPFLAGS  = -Obinary
HEADER   = -Iinclude

# Source and build paths
C_SOURCES   := $(wildcard src/*.c)
CPP_SOURCES := $(wildcard src/*.cpp)
STARTUP_SRC := startup.c

SOURCES := $(C_SOURCES) $(CPP_SOURCES) $(STARTUP_SRC)

OBJECTS := $(patsubst %.c, build/%.o, $(notdir $(C_SOURCES))) \
           $(patsubst %.cpp, build/%.o, $(notdir $(CPP_SOURCES))) \
           build/$(notdir $(STARTUP_SRC:.c=.o))

print-size: $(TARGET).elf $(TARGET).bin
	@echo "==== Size info (text = flash, data + bss = RAM) ===="
	@arm-none-eabi-size $(TARGET).elf
	@echo "==== Firmware binary size (bytes) ===="
	@stat --format="%s" $(TARGET).bin || ls -l $(TARGET).bin

all: $(TARGET).bin print-size

build/%.o: src/%.cpp | build
	$(CXX) $(HEADER) $(CXXFLAGS) -o $@ $<

build/%.o: src/%.c | build
	$(CC) $(HEADER) $(CFLAGS_C) -o $@ $<

build/%.o: %.c | build
	$(CC) $(HEADER) $(CFLAGS_C) -o $@ $<

$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(CP) $(CPFLAGS) $< $@

build:
	mkdir -p build

clean:
	rm -rf build

