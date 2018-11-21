# A subset-of-C compiler to LLVM IR

`csem` expects input from `stdin` and emits LLVM IR. This IR can then be used
with `clang` to produce an executable. This program was tested with LLVM
versions 3.9 and 7.0.

# How do I compile this?

There are two requirements: LLVM, for emitting the IR and compiling the IR, and
Bison, for generating the Yacc parser. For Debian-based distributions, e.g.
Ubuntu or Debian itself, enter the following command in the terminal:

    $ sudo apt install llvm bison

Once you have these installed, simply the following to compile the program:

    $ make

# How can I test the program?

Once you have the program compiled simply run:

    $ make test

If you wish to run your own tests or use the program yourself simply run the
following command where `input.c` is some C program file.

    $ ./csem < input.c
