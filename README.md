# Sajilo

Sajilo is my work-in-progress compiler for a small programming language, written in C++.

The project is an ongoing exploration of how source code moves through a compiler: from
lexing and token handling, through parsing and AST construction, to scope handling and
eventual code generation.

## Current progress

- Lexer for delimiters, arithmetic, assignment, comparison, logical, bitwise, and other operators
- Token handling for identifiers, integer and string literals, comments, and language keywords
- Parser structure with token matching, lookahead, expectations, and syntax-error reporting
- Initial statement parsing for functions, scopes, `read`, `write`, `manau`, and `niski`
- Function and scope parsing with statement-level code generation hooks
- Initial primary and unary expression parsing structure
- Assembly output generation to `out.asm`

The compiler is not finished yet. Expression parsing, semantic analysis, diagnostics, type
handling, and a complete backend are still being developed.

## Building

Sajilo requires a C++20 compiler and CMake 3.20 or newer.

```sh
cd compiler
cmake -B build
cmake --build build
```

When the current source compiles, this creates the compiler executable at
`compiler/build/sajilo`.

The project is currently being developed and may not compile at every point in
the process. In the current tree, the build is blocked by an in-progress unary
operator reference in `compiler/src/Expressions/UnaryExpression.cpp`.

The repository also includes a Makefile. Its default target builds the project and installs
the executable system-wide, so it may require elevated permissions:

```sh
cd compiler
make
```

## Running

Pass a Sajilo source file as the first argument:

```sh
cd compiler
./build/sajilo ../language/sample
```

The parser currently writes generated assembly to `out.asm` in the current working directory.
The generated assembly is an intermediate output and is not assembled or linked automatically.

Example source syntax can be found in `language/sample` and `language/testfunc`:

```text
func make(int value) -> deu(int) {
    write(value, size)
    read(value, size)
}
```

## Project layout

```text
compiler/
  include/       Public headers for the lexer, parser, expressions, and statements
  src/           C++ implementation files
  CMakeLists.txt CMake build configuration
  Makefile       Convenience build and install targets
language/        Sample and experimental Sajilo source files and generated output
```

## Roadmap

- Complete primary, unary, binary, and ternary expression parsing
- Expand statement and control-flow support
- Improve syntax and semantic diagnostics
- Define and enforce the language's type and scope rules
- Build out AST ownership and traversal
- Continue developing assembly code generation and an executable build pipeline

Sajilo is still evolving, and I will continue sharing updates as the language and compiler
grow.