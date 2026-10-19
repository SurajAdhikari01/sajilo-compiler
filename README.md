# Sajilo

**Sajilo** (सजिलो — Nepali for *"Easy"* / *"Simple"*) is a statically-typed compiled programming language and custom C++ compiler. It combines expressive Nepali-inspired keywords with standard modern programming syntax, featuring a Pratt expression parser, scoped symbol table, semantic analysis, an Intermediate Representation (IR) engine emitting Three-Address Code (TAC), and an upcoming x86_64 code generator.

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
│   │   ├── IR/               # Intermediate Representation (TAC instructions)
│   │   │   ├── Assign.hpp    # Assignment instructions (dest = src)
│   │   │   ├── Binary.hpp    # Binary operation instructions (t0 = a + b)
│   │   │   ├── CondJump.hpp  # Conditional branch instructions (planned)
│   │   │   ├── FunctionCall.hpp # Function & syscall invocations (planned)
│   │   │   ├── IR.hpp        # Base IR instruction interface
│   │   │   ├── Jump.hpp      # Unconditional jump instructions (planned)
│   │   │   ├── Label.hpp     # Basic block jump labels (planned)
│   │   │   └── Param.hpp     # Parameter passing instructions (planned)
│   │   ├── lexer.hpp         # Lexer and tokenizer
│   │   ├── parser.hpp        # Parser state machine & IR instruction manager
│   │   ├── statements/       # Function, If, While, Manau, Return, etc.
│   │   ├── symbolTable.hpp   # Scoped symbol table and type tracking
│   │   ├── token.hpp         # Token definitions and types
│   │   └── utils.hpp         # Utility functions
│   └── src/                  # Implementation files
│       ├── Expressions/      # Pratt parser logic & expression semantics
│       ├── IR/               # IR instruction generation implementations
│       │   ├── Assign.cpp    # Linear assignment lowering
│       │   ├── Binary.cpp    # Binary TAC instruction lowering
│       │   └── IR.cpp        # IR base implementation
│       ├── statements/       # Statement parsers, semantic analysis & IR dispatch
│       ├── lexer.cpp         # Tokenizer implementation
│       ├── parser.cpp        # Statement dispatch & IR emission loop
│       └── main.cpp          # CLI entry point
└── language/                 # Sajilo sample programs (.sj) & generated artifacts
    ├── test.sj               # Test suite & sample programs
    └── out.ir                # Generated Intermediate Representation (TAC)
```

---

## Intermediate Representation (IR)

Sajilo features a decoupled **Three-Address Code (TAC)** Intermediate Representation. Rather than translating high-level AST constructs directly into machine code, the compiler lowers statements and expressions into a linear sequence of simplified 3-address instructions. This isolates frontend language syntax from backend machine architectures and forms the basis for future optimization passes.

### Architecture

- **`IR` Base Class**: Abstract base class (`compiler/include/IR/IR.hpp`) defining `virtual void generate_ir(CodeGenContext &, Parser &) = 0;`.
- **Instruction Collector**: `Parser` manages an instruction stream (`std::vector<std::unique_ptr<IR>> instructions;`) populated during AST lowering.
- **Virtual Temporaries**: A monotonic label counter in `CodeGenContext` allocates virtual registers (`t0`, `t1`, `t2`, ...) for intermediate expression results.
- **Output Target**: When parsing and semantic analysis succeed, the IR instructions are serialized and emitted to **`out.ir`**.

### Implementation Status

The IR layer is actively being implemented as a dedicated subsystem:

| IR Component | Subsystem / Instruction | Status | Details |
| :--- | :--- | :---: | :--- |
| **Linear Assignment** | `Assign` (`dest = src`) | **Implemented** | Handles variable assignments, `manau` initialized declarations, and chained assignments (`a = b = 50;`). |
| **Binary Operations** | `Binary` (`tN = a op b`) | **Implemented** | Arithmetic (`+`, `-`, `*`, `/`) and comparison operators (`<`, `<=`, `>`, `>=`, `==`, `!=`) evaluated with temporary registers. |
| **Temporary Generation** | `CodeGenContext::temp_label` | **Implemented** | Auto-increments temporary variable names (`t0`, `t1`, ...). |
| **AST Lowering Visitor** | `generate_ir` across AST | **Implemented** | Traverses `Function`, `Scope`, `Manau`, `ExpressionStatement`, and Pratt binary expressions. |
| **IR Serialization** | `Parser::parse()` | **Implemented** | Emits the complete instruction stream into `out.ir`. |
| **Control-Flow Jumps** | `Jump`, `CondJump`, `Label` | *In Progress* | Header scaffolds and statement traversal exist for `jaba` (if-else) and `jabasamma` (while loops); branch jump emission is being wired up. |
| **Call & Syscall Params** | `Param`, `FunctionCall` | *In Progress* | Scaffolding in place for function calls and runtime built-ins (`exit`, `read`, `write`, `laijau`). |
| **Unary Expressions** | Unary TAC Lowering | *In Progress* | Increment (`++`), decrement (`--`), and negation (`-`) TAC generation. |

### Example IR Output

Given the following Sajilo code:

```sajilo
func main(int arg1, int arg2) -> deu(int) {
    manau int a = 10;
    manau int b = 20;
    manau:const int MAX_LIMIT = 100;

    jabasamma (a < MAX_LIMIT) {
        a = a + 1;
    }
}
```

The compiler lowers the statements into `out.ir`:

```text
a = 10
b = 20
MAX_LIMIT = 100
t0 = a < MAX_LIMIT
t1 = a + 1
a = t1
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
./compiler/build/sajilo language/test.sj
```

The compiler currently runs the following pipeline:
1. **Lexical Analysis (Tokenizer)**: Converts `.sj` source code into a clean token stream.
2. **Pratt Parsing**: Builds a structured Abstract Syntax Tree (AST) handling precedence and associativity.
3. **Semantic Analysis**: Validates symbols against scoped symbol tables, verifies type compatibility, and emits compiler errors with source locations.
4. **Intermediate Representation (IR) Emission**: Lowers AST nodes into Three-Address Code (TAC), allocates virtual temporary registers, and emits the linear instruction stream to `out.ir`.

---

## Roadmap / Future Work (TODO)

The frontend parsing, semantic analysis, and the initial Intermediate Representation (IR) pipeline are currently in place. The next phases of development focus on completing the IR subsystem and the x86_64 code generator:

- [ ] **Intermediate Representation (IR)**: Complete the Three-Address Code (TAC) pipeline
  - [x] Decoupled IR architecture (`IR` base class and instruction buffer in `Parser`)
  - [x] Assignment instructions (`Assign`) for variable definitions, initializations, and reassignments
  - [x] Binary operations (`Binary`) with virtual temporary register allocation (`t0`, `t1`, ...)
  - [x] Recursive AST traversal across statements, scopes, and expressions
  - [x] Linear IR serialization to `out.ir`
  - [ ] Jump and conditional branch instructions (`Jump`, `CondJump`, `Label`) for `jaba` and `jabasamma`
  - [ ] Parameter passing and call instructions (`Param`, `FunctionCall`) for syscalls (`read`, `write`, `exit`, `laijau`) and user functions
  - [ ] Unary expression IR lowering
  - [ ] Basic block structuring and IR optimization passes (constant folding, dead code elimination)
- [ ] **Assembly Code Generation**: Backend x86_64 code generator lowering IR / AST:
  - Function prologue, epilogue, and stack frame management
  - Register allocation from virtual temporaries
  - Translation of TAC instructions into x86_64 assembly
  - Control-flow conditional and unconditional jump emission (`jaba`, `jabasamma`)
  - Linux/POSIX syscall generation for `read`, `write`, and `exit`
- [ ] **Assembler & Linker Integration**: Automatically invoke `nasm` and `ld` from the CLI to produce standalone executable binaries directly from `.sj` files.
- [ ] **Function Calls**: Add syntax and semantics for invoking user-defined functions with arguments.
- [ ] **Multiple Top-Level Functions**: Enhance top-level statement dispatch to seamlessly parse multiple function declarations per file.
- [ ] **Expanded Type System**: Add support for `bool`, `float`, and composite types (arrays, structs).