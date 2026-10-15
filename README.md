# Sajilo

**Sajilo** (सजिलो — Nepali for *"Easy"* / *"Simple"*) is a statically-typed compiled programming language and custom C++ compiler. It combines expressive Nepali-inspired keywords with standard modern programming syntax, featuring a Pratt expression parser, scoped symbol table, semantic analysis, and an upcoming Intermediate Representation (IR) and x86_64 code generator.

---

## File Extension

Sajilo source code files use the **`.sj`** extension:

```text
main.sj
all_syntax.sj
```

---

## Language Reference & Syntax

### 1. Comments
Comments begin with a hash symbol `#` and continue until the end of the line:
```sajilo
# This is a single-line comment in Sajilo
```

### 2. Data Types
Sajilo currently supports the following primitive types:
- `int`: Signed integers (e.g. `10`, `-5`)
- `string`: Double-quoted string literals (e.g. `"hello world"`)

---

### 3. Keyword Dictionary

| Keyword | Nepali Meaning | English Equivalent / Role |
| :--- | :--- | :--- |
| `func` | कार्य | Function declaration |
| `deu` | देऊ (*Give*) | Function return type specifier |
| `manau` | मानौं (*Let / Assume*) | Variable declaration |
| `const` | स्थिर | Constant modifier (`manau:const`) |
| `jaba` | जब (*When*) | `if` conditional statement |
| `natra` | नत्र (*Otherwise*) | `else` conditional branch |
| `jabasamma` | जबसम्म (*As long as*) | `while` loop |
| `laijau` | लैजाऊ (*Take*) | `return` statement |
| `read` | पढ्नु | Reads input into a buffer |
| `write` | लेख्नु | Writes output from a buffer |
| `exit` | बाहिरिनु | Exits the program with a status code |

---

### 4. Functions
Functions are declared using `func`, followed by the parameter list, return type specification `-> deu(<type>)`, and the function body:

```sajilo
func add(int a, int b) -> deu(int) {
    laijau(a + b);
}

func main(int argc, int argv) -> deu(int) {
    laijau(0);
}
```

---

### 5. Variable Declarations (`manau`)
Variables are introduced using `manau`:

```sajilo
# Uninitialized variable
manau int x;

# Initialized variable
manau int a = 10;
manau string greeting = "Namaste";

# Constants (cannot be re-assigned)
manau:const int MAX_USERS = 100;
manau:const string APP_NAME = "SajiloApp";
```

---

### 6. Expressions & Operators

Sajilo uses a **Pratt Parser** for operator precedence and associativity:

#### Assignments
Assignment is right-associative, allowing chained assignments:
```sajilo
a = 20;
a = b = 50;           # Evaluates b = 50 first, then assigns to a
buffer = "new text";
```

#### Arithmetic Operators
Standard precedence applies (`*` and `/` bind tighter than `+` and `-`):
```sajilo
manau int result = (a + b) * 2 - (b / 5);
```

#### Comparison & Relational Operators
Evaluate conditions between compatible types:
```sajilo
a == b    # Equal to
a != b    # Not equal to
a < b     # Less than
a <= b    # Less than or equal to
a > b     # Greater than
a >= b    # Greater than or equal to
```

#### Logical Operators
```sajilo
(a < 10) && (b > 5)   # Logical AND
(a == 0) || (b != 0)  # Logical OR
```

#### Bitwise & Shift Operators
```sajilo
manau int bitwise = (a & b) | (c ^ 1);
manau int shifted = (a << 2) >> 1;
```

#### Unary Prefix Operators
Used as statements:
```sajilo
++a;    # Pre-increment
--b;    # Pre-decrement
-a;     # Negation
+b;     # Positive
!flag;  # Logical NOT
~mask;  # Bitwise NOT
```

---

### 7. Control Flow

#### `jaba` / `natra` (If-Else)
Conditional branching with optional `natra` branch:
```sajilo
jaba (a < b) {
    c = a + b;
} natra {
    c = a - b;
}
```

#### `jabasamma` (While Loop)
Executes a block as long as the condition evaluates to true:
```sajilo
jabasamma (a < MAX_USERS) {
    a = a + 1;
}
```

---

### 8. Block Scopes
Braced blocks `{ ... }` create isolated lexical scopes with their own symbol lifetime:
```sajilo
{
    manau int inner = 42;
    c = inner + a;
}
# inner is no longer accessible outside this block
```

---

### 9. System Built-ins

#### `write(variable, length);`
Outputs string buffer content:
```sajilo
manau string msg = "Hello from Sajilo!\n";
write(msg, 19);
```

#### `read(variable, length);`
Reads user input into a string variable:
```sajilo
manau string buffer = "                   ";
read(buffer, 10);
```

#### `exit(status_code);`
Terminates the program with the specified integer status code:
```sajilo
exit(0);
```

#### `laijau(expression);`
Returns an integer value from a function:
```sajilo
laijau(c);
```

---

## Complete Example Program

Check [`language/all_syntax.sj`](language/all_syntax.sj) for a full runnable example:

```sajilo
# Sajilo Language - Comprehensive Example

func main(int arg1, int arg2) -> deu(int) {

    # 1. Variables
    manau int a = 10;
    manau int b = 20;
    manau int c = 0;
    manau:const int MAX_LIMIT = 100;
    manau string buffer = "hello world";

    # 2. Assignments & Arithmetic
    c = 30;
    a = b + 2;
    c = (a + b) * 2 - (b / 5);
    a = b = 50;

    # 3. Bitwise & Unary
    manau int bit_result = (a & b) | (c ^ 1);
    manau int shifted = (a << 2) >> 1;
    ++a;
    --b;

    # 4. Conditionals
    jaba (a < b) {
        c = a + b;
    } natra {
        c = a - b;
    }

    # 5. Loops
    jabasamma (a < MAX_LIMIT) {
        a = a + 1;
    }

    # 6. Scopes
    {
        manau int inner_var = 42;
        c = inner_var + a;
    }

    # 7. I/O & Exit
    write(buffer, 11);
    read(buffer, 11);
    exit(0);
    laijau(c);
}
```

---

## Project Structure

```text
sajilo-compiler/
├── compiler/
│   ├── CMakeLists.txt        # CMake build configuration
│   ├── Makefile              # Convenience build targets
│   ├── include/              # Header files
│   │   ├── Error.hpp         # Diagnostics and error string constants
│   │   ├── Expression/       # Binary, Unary, and Primary AST expressions
│   │   ├── lexer.hpp         # Lexer and tokenizer
│   │   ├── parser.hpp        # Parser state machine
│   │   ├── statements/       # Function, If, While, Manau, Return, etc.
│   │   ├── symbolTable.hpp   # Scoped symbol table and type tracking
│   │   ├── token.hpp         # Token definitions and types
│   │   └── utils.hpp         # Utility functions
│   └── src/                  # Implementation files
│       ├── Expressions/      # Pratt parser logic & expression semantics
│       ├── statements/       # Statement parsers & code generation
│       ├── lexer.cpp         # Tokenizer implementation
│       ├── parser.cpp        # Statement dispatch loop
│       └── main.cpp          # CLI entry point
└── language/                 # Sajilo sample programs (.sj)
    ├── all_syntax.sj         # Feature showcase
    └── test.sj               # Test suite
```

---

## Building the Compiler

Requirements: C++20 compatible compiler (`clang++` or `g++`) and `CMake >= 3.10`.

```sh
cd compiler
cmake -B build
cmake --build build
```

This generates the compiler binary at:
```text
compiler/build/sajilo
```

---

## Running a Program

Pass any `.sj` source file as an argument to the compiler:

```sh
# From the root directory:
./compiler/build/sajilo language/all_syntax.sj
```

The compiler currently runs the full frontend pipeline:
1. **Lexical Analysis (Tokenizer)**: Converts `.sj` source code into a clean token stream.
2. **Pratt Parsing**: Builds a structured Abstract Syntax Tree (AST) handling precedence and associativity.
3. **Semantic Analysis**: Validates symbols against scoped symbol tables, verifies type compatibility, and emits compiler errors with source locations.

---

## Roadmap / Future Work (TODO)

The frontend parsing and semantic analysis are currently in place. The next phases of development focus on the compiler middle-end and backend:

- [ ] **Intermediate Representation (IR)**: Design and implement an IR pipeline (such as Three-Address Code / SSA representation) between the AST and target emission to allow optimizations.
- [ ] **Assembly Code Generation**: Complete the backend x86_64 code generator:
  - Function prologue, epilogue, and stack frame management
  - Register allocation
  - Translation of binary/unary expressions into machine instructions
  - Control-flow conditional and unconditional jump emission (`jaba`, `jabasamma`)
  - Linux/POSIX syscall generation for `read`, `write`, and `exit`
- [ ] **Assembler & Linker Integration**: Automatically invoke `nasm` and `ld` from the CLI to produce standalone executable binaries directly from `.sj` files.
- [ ] **Function Calls**: Add syntax and semantics for invoking user-defined functions with arguments.
- [ ] **Multiple Top-Level Functions**: Enhance top-level statement dispatch to seamlessly parse multiple function declarations per file.
- [ ] **Expanded Type System**: Add support for `bool`, `float`, and composite types (arrays, structs).