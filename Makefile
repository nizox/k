NASM = nasm
CC = clang
CXX = clang++
CFLAGS = -g -m64 -W -nostdlib -fno-builtin -fno-stack-protector -mno-red-zone
CFLAGS += -Iinclude -Isub/
CFLAGS += -DLUA_ANSI
CXXFLAGS = ${CFLAGS} -fno-exceptions -fno-rtti -std=c++11
BUILD = build

CSRCS = 	src/c/start.c		\
			src/c/screen.c			\
			src/c/string.c			\
			src/c/print.c			\
			src/c/printk.c

CPPSRCS = 	src/_cplusplus.cpp				\
			src/exceptions.cpp				\
			src/isr.cpp						\
			src/idt.cpp						\
			src/start.cpp					\
			src/video.cpp					\
			src/memory.cpp					\
			src/kheap.cpp					\
			src/allocator.cpp

LUA_PATH	=	sub/lua

LIB_LUA		=	build/obj/libluacore.a

OBJS = ${OBJ} $(addprefix ${BUILD}/obj/,${CSRCS:.c=.o} ${CPPSRCS:.cpp=.o})

# The system image must be a valid disk so we compute a valid size
# It should make a 10MiB image
CYLINDERS = 20
HEADS = 16
SPT = 63 # Sector Per Track
SECTORS = $(shell echo "${CYLINDERS} * ${HEADS} * ${SPT}" | bc)

all: ${BUILD}/system

CORE_O=	sub/lua/lapi.o sub/lua/lcode.o sub/lua/lctype.o sub/lua/ldebug.o \
		sub/lua/ldo.o sub/lua/ldump.o sub/lua/lfunc.o sub/lua/lgc.o sub/lua/llex.o \
		sub/lua/lmem.o sub/lua/lobject.o sub/lua/lopcodes.o sub/lua/lparser.o sub/lua/lstate.o \
		sub/lua/lstring.o sub/lua/ltable.o sub/lua/ltm.o sub/lua/lundump.o sub/lua/lvm.o \
		sub/lua/lzio.o


${BUILD}:
	mkdir -p $@
	mkdir -p $@/obj/src/c
	cp util/bochsrc $@/bochsrc

${LIB_LUA}: ${CORE_O} sub/lua/libluacore.a
	cp ${LUA_PATH}/libluacore.a ${LIB_LUA}

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

${BUILD}/kernel: util/linker.ld ${BUILD} ${OBJS} ${LIB_LUA}
	ld -static -T util/linker.ld --oformat=binary -o $@ ${OBJS} ${CORE_O}


${BUILD}/kernel.elf: util/linker.ld ${BUILD} ${OBJS}
	ld -static -T util/linker.ld --oformat=elf64-x86-64 -o $@ ${OBJS} build/obj/libluacore.a


${BUILD}/system: ${BUILD}/bootloader ${BUILD}/kernel
	# Create the system image
	dd if=/dev/zero of=$@ bs=512 count=${SECTORS}
	dd if=${BUILD}/bootloader of=$@ bs=512 conv=notrunc
	dd if=${BUILD}/kernel of=$@ bs=512 seek=32 conv=notrunc


clean:
	rm -rf ${BUILD}
	rm sub/lua/*.o

.PHONY: clean all
