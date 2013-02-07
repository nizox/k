NASM = nasm
CC = clang
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector
BUILD = build

SRCS = src/start.c
OBJS = ${OBJ} $(addprefix ${BUILD}/obj/,${SRCS:.c=.o})

# The system image must be a valid disk so we compute a valid size
# It should make a 10MiB image
CYLINDERS = 20
HEADS = 16
SPT = 63 # Sector Per Track
SECTORS = $(shell echo "${CYLINDERS} * ${HEADS} * ${SPT}" | bc)


all: ${BUILD}/system


${BUILD}:
	mkdir -p $@
	mkdir -p $@/obj/src
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
