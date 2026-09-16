# Sajilo

Sajilo is a C++ compiler project for a small custom language. The codebase is still evolving, but the core compiler pipeline is in place: lexing, token handling, parsing, and early statement/expression support are all being actively developed.

## Current progress

The project is currently at the point where the compiler can be built and basic language constructs are recognized by the parser.

- Lexer support for delimiters, arithmetic, assignment, comparison, logical, bitwise, and other operators
- Keyword and literal handling for identifiers, integer and string values, comments, and language keywords
- Parser utilities for token matching, lookahead, expectations, and syntax diagnostics
- Statement parsing for:
  - function declarations
  - scopes and nested blocks
  - `read` and `write`
  - `if` / `else`
  - `while`
  - `return`
  - `exit`
  - variable declarations via `manau`
- Expression parsing using Pratt-style handling for primary, unary, and binary expressions
- Assembly-generation hooks and intermediate output generation to `out.asm`

The compiler is still a work in progress. Semantic validation, richer diagnostics, stronger type rules, and a fuller backend pipeline are still being developed.

## Verified build status

The project currently builds successfully with CMake in this workspace.

```sh
cd compiler
cmake -B build
cmake --build build
```

This produces the executable at:

```text
compiler/build/sajilo
```

The build succeeds as of the current repo state, although the compiler still emits warnings related to legacy `#import` headers in older source files.

## Running

Pass a Sajilo source file as the first argument:

```sh
cd compiler
./build/sajilo ../language/sample
```

The parser currently writes generated assembly to `out.asm` in the working directory. This is an intermediate artifact and is not automatically assembled or linked.

Example programs are in the `language/` folder, for example:

```text
func make(int var) -> deu(int) {
    manau int number = a + b;
    write(var, size);
    read(var, size);
}
```

## Project layout

```text
compiler/
  include/       Public headers for the lexer, parser, expressions, and statements
  src/           C++ implementation files
  CMakeLists.txt CMake configuration
  Makefile       Convenience build/install target
language/        Source samples and generated output
```

## Roadmap

- Complete expression parsing and precedence handling across the remaining operator set
- Strengthen AST and statement ownership patterns
- Improve semantic analysis and type checking
- Expand control-flow and statement coverage
- Finish code generation / backend work and produce a more reliable executable pipeline

Sajilo is still evolving, and the compiler continues to gain parser and language features as the project matures.