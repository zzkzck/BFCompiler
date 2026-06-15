# BF Compiler Toy

A tiny Brainfuck compiler written in C++.

This is a small toy project for practicing C++ project construction. It is not intended to be a production-quality compiler.

## What It Does

This compiler reads a `.bf` file, tokenizes Brainfuck instructions, checks bracket matching, generates Apple Silicon ARM64 assembly, and compiles it into a native executable.

```text
.bf source
-> Lexer
-> Parser
-> ARM64 assembly
-> executable
```

## Platform

Currently supported platform:

```text
macOS on Apple Silicon
ARM64 / AArch64
clang
```

## Requirements

```text
macOS on Apple Silicon
Xcode Command Line Tools
CMake
```

Install Xcode Command Line Tools if needed:

```bash
xcode-select --install
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Usage

Compile a Brainfuck source file:

```bash
./build/BF input.bf
```

This generates:

```text
out.s
brainfuck_run
```

Run the generated program:

```bash
./brainfuck_run
```

## Example

`a.bf`:

```brainfuck
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.
```

Run:

```bash
./build/BF a.bf
./brainfuck_run
```

Expected output:

```text
A
```

If the terminal shows something like `A%`, the `%` is the shell prompt, not part of the program output.

## Supported Instructions

```text
>   move pointer right
<   move pointer left
+   increment current cell
-   decrement current cell
.   output current cell
,   input one byte
[   begin loop
]   end loop
```

All other characters are ignored.

## Features

- Supports all 8 Brainfuck instructions
- Checks matching `[` and `]`
- Compresses consecutive `+`, `-`, `>`, and `<`
- Generates Apple Silicon ARM64 assembly

## Limitations

- macOS Apple Silicon only
- No tape bounds checking
- Fixed tape size
- Very long repeated operations may fail due to ARM64 immediate limits
- This is a toy compiler, not a production compiler

## License

MIT License. See `LICENSE` for details.