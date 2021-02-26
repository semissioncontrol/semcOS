TOOLCHAIN       = arm-none-eabi
CC              = $(TOOLCHAIN)-gcc
OBJCOPY         = $(TOOLCHAIN)-objcopy

MODEL           = model-2
CPU             = cortex-a7

CFLAGS= -mcpu=$(CPU) -fpic -ffreestanding -g
CSRCFLAGS= -O2 -Wall -Wextra
LFLAGS= -ffreestanding -O2 -nostdlib

KERNEL          = ./
KERNEL_HEADERS  = ./include
COMMON          = ./common
OBJECTS         = ./objects

KERNEL_SOURCES  = $(wildcard $(KERNEL)/*.c)
KERNEL_SOURCES += $(wildcard $(KERNEL)/$(MODEL)/*.c)
COMMON_SOURCES  = $(wildcard $(COMMON)/*.c)
ASM_SOURCES     = $(wildcard $(KERNEL)/*.S)

OBJECT_SOURCES  = $(patsubst $(KERNEL)/%.c, $(OBJECTS)/%.o, $(KERNEL_SOURCES))
OBJECT_SOURCES += $(patsubst $(COMMON)/%.c, $(OBJECTS)/%.o, $(COMMON_SOURCES))
OBJECT_SOURCES += $(patsubst $(KERNEL)/%.S, $(OBJECTS)/%.o, $(ASM_SOURCES))
HEADERS         = $(wildcard $(KERNEL_HEADERS)/*.h)

IMAGE           = semc-os

all: build run

build: $(OBJECT_SOURCES) $(HEADERS)
	$(CC) -T linker.ld -o $(IMAGE).elf $(LFLAGS) $(OBJECT_SOURCES)
	$(OBJCOPY) $(IMAGE).elf -O binary $(IMAGE).img

$(OBJECTS)/%.o: $(KERNEL)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERNEL) -I$(KERNEL_HEADERS) -c $< -o $@ $(CSRCFLAGS)

$(OBJECTS)/%.o: $(KERNEL)/$(MODEL)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERNEL) -I$(KERNEL_HEADERS) -c $< -o $@ $(CSRCFLAGS)

$(OBJECTS)/%.o: $(KERNEL)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERNEL) -c $< -o $@

$(OBJECTS)/%.o: $(COMMON)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KERNEL) -I$(KERNEL_HEADERS) -c $< -o $@ $(CSRCFLAGS)

run: build
	qemu-system-arm -m 128 -no-reboot -M raspi2 -serial stdio -kernel $(IMAGE).elf

clean:
	rm -rf $(OBJECTS)
	rm $(IMAGE).elf
	rm $(IMAGE).img