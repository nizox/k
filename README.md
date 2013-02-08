Kernel
======

Kernel is an experimental and educational project.

First, you will need the following software before building the kernel:

 - nasm
 - clang

Addionnally, if you intend to develop or debug the kernel,
you would install:

 - bochs
 - qemu

`gcc` should be able to replace `clang` but we wont test the kernel with it.

We make use of the excellent
[Pure64](http://www.returninfinity.com/pure64.html) bootloader but it required
few modifications to run our kernel.


Compilation
-----------

    git clone --recursive git://github.com/nizox/k.git
    cd k/
    make

Emulation
---------

With `bochs`:

    cd build/
    bochs

With `qemu`:

    cd build/
    qemu-system-x86_64 -drive file=system

Documentation
-------------

Every piece of code is documented in place.

Notes
-----

 - Pure64 initializes long mode (64bits mode) for us, including the GDT.
   We must do it ourself if we want to be multiboot compliant.

Todo
----

 - Prepare exception and IRQ handling
 - Write text to the screen (console code)
 - Paging and memory allocation
