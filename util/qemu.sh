#!/bin/sh

# Minimal command line booting the kernel and enabling gdb remote
qemu-system-x86_64 -drive file=system -s $*
