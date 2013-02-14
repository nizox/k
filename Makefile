NASM = nasm
CC = clang
CXX = clang++
CFLAGS = -m64 -W -nostdlib -fno-builtin -fno-stack-protector -mno-red-zone
CFLAGS += -Iinclude
CXXFLAGS = ${CFLAGS} -fno-exceptions -fno-rtti -std=c++11
BUILD = build

CSRCS = 	src/c/start.c			\
			src/c/interrupts.c 		\
			src/c/screen.c			\
			src/c/string.c			\
			src/c/print.c			\
			src/c/printk.c

CPPSRCS = 	src/_cplusplus.cpp		\
			src/start.cpp			\
			src/video.cpp

OBJS = ${OBJ} $(addprefix ${BUILD}/obj/,${CSRCS:.c=.o} ${CPPSRCS:.cpp=.o})

# The system image must be a valid disk so we compute a valid size
# It should make a 10MiB image
CYLINDERS = 20
HEADS = 16
SPT = 63 # Sector Per Track
SECTORS = $(shell echo "${CYLINDERS} * ${HEADS} * ${SPT}" | bc)

all: ${BUILD}/system


${BUILD}:
	mkdir -p $@
	mkdir -p $@/obj/src/c
	cp util/bochsrc $@/bochsrc


${BUILD}/mbr: ${BUILD} sub/bootloader/src/bootsectors/bmfs_mbr.asm
	# build the MBR boot sector
	# this code will load the bootloader from the disk and jump to it
	${NASM} sub/bootloader/src/bootsectors/bmfs_mbr.asm -o ${BUILD}/mbr


${BUILD}/loader: ${BUILD} sub/bootloader/src/pure64.asm
	${NASM} -Isub/bootloader/src/ sub/bootloader/src/pure64.asm \
	-o ${BUILD}/loader


${BUILD}/bootloader: ${BUILD}/mbr ${BUILD}/loader
	# Assemble the MBR with the loader
	# The loader must start at the 16th sector and is at most 8192 bytes
	# (see sub/bootloader/src/bootsectors/bmfs_mbr.asm line 27)
	dd if=/dev/zero of=$@ bs=512 count=32
	dd if=${BUILD}/mbr of=$@ bs=512 conv=notrunc
	dd if=${BUILD}/loader of=$@ bs=512 seek=16 conv=notrunc


${BUILD}/obj/%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD}/obj/%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<


${BUILD}/kernel: util/linker.ld ${BUILD} ${OBJS}
	ld -T util/linker.ld -o $@ ${OBJS}


${BUILD}/system: ${BUILD}/bootloader ${BUILD}/kernel
	# Create the system image
	dd if=/dev/zero of=$@ bs=512 count=${SECTORS}
	dd if=${BUILD}/bootloader of=$@ bs=512 conv=notrunc
	dd if=${BUILD}/kernel of=$@ bs=512 seek=32 conv=notrunc


clean:
	rm -rf ${BUILD}

.PHONY: clean all
