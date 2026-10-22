# Sajilo

**Sajilo** (सजिलो — Nepali for _"Easy"_ / _"Simple"_) is a statically-typed compiled programming language and custom C++ compiler. It combines expressive Nepali-inspired keywords with standard programming syntax, featuring a Pratt expression parser, scoped symbol table, semantic analysis, and an Intermediate Representation (IR) engine emitting Three-Address Code (TAC).

Sajilo source files use the **`.sj`** extension.

---

## Keyword Dictionary

| Keyword     | Nepali Meaning         | Role / Equivalent                    |
| :---------- | :--------------------- | :----------------------------------- |
| `func`      | कार्य                  | Function declaration                 |
| `deu`       | देऊ (_Give_)           | Function return type specifier       |
| `manau`     | मानौं (_Assume / Let_) | Variable declaration                 |
| `const`     | स्थिर                  | Constant modifier (`manau:const`)    |
| `jaba`      | जब (_When_)            | `if` conditional statement           |
| `natra`     | नत्र (_Otherwise_)     | `else` conditional branch            |
| `jabasamma` | जबसम्म (_As long as_)  | `while` loop                         |
| `laijau`    | लैजाऊ (_Take_)         | `return` statement                   |
| `read`      | पढ्नु                  | Reads input into a buffer            |
| `write`     | लेख्नु                 | Writes output from a buffer          |
| `exit`      | बाहिरिनु               | Exits the program with a status code |

### Supported Data Types

- `int`: Signed integer values (e.g. `10`, `-5`)
- `string`: Double-quoted string literals (e.g. `"hello world"`)

---

## Language Syntax

### 1. Variables & Constants

```sajilo
# Variables
manau int count = 10;
manau string msg = "namaste";

# Constants (immutable)
manau:const int MAX_LIMIT = 100;
```

### 2. Functions

Functions are declared using `func`, parameter lists, and return types marked with `-> deu(<type>)`:

```sajilo
func add(int a, int b) -> deu(int) {
    laijau(a + b);
}

func main(int argc, int argv) -> deu(int) {
    laijau(0);
}
```

### 3. Control Flow

```sajilo
# If / Else
jaba (a < b) {
    write("a is smaller", 12);
} natra {
    write("b is smaller", 12);
}

# While Loop
jabasamma (count < MAX_LIMIT) {
    count = count + 1;
}
```

### 4. System Operations

```sajilo
manau string buffer = "sajilo";
read(buffer, 16);     # Reads up to 16 bytes into buffer
write(buffer, 6);     # Writes 6 bytes from buffer
exit(0);              # Terminates with exit code
laijau(count);        # Returns a value from function
```

---

## Intermediate Representation (IR)

Sajilo compiles high-level source code into a linear Three-Address Code (TAC) representation. String literals are extracted into static data pools (`str0`, `str1`), functions generate typed signature labels (e.g., `main(int,int):`), and expressions are lowered using virtual temporaries (`t0`, `t1`, ...) and jump blocks (`b0:`, `b1:`).

### Example

**Source (`test.sj`):**

```sajilo
func main(int var, int hell) -> deu(int) {
  manau int test = 10;
  manau int a = 1;
  manau int b = 2;

  jaba(a + b) {
    a + b;
    laijau(test);
  } natra {
    exit(0);
  }

  manau:const int number = 10;
  manau string buffer = "sajilo";
  read(buffer, number);
  exit(number);
}
```

**Generated IR (`out.ir`):**

```text
str0: "sajilo"

main(int,int):
test = 10
a = 1
b = 2
t0 = a + b
if false t0 jmp b1

b0:
t1 = a + b
return test
jmp b2

b1:
param 0
call __sys_exit
jmp b2

b2:
number = 10
buffer = str0
param buffer
param number
call __sys_read
param number
call __sys_exit
```

---

## Building the Compiler

Requires a C++20 compiler (`clang++` or `g++`) and `CMake >= 3.10`.

```sh
cd compiler
cmake -B build
cmake --build build
```

The compiled binary will be placed at `compiler/build/sajilo`.

---

## Usage

Run the compiler by passing the source `.sj` file along with the desired output format:

### Text IR Output

```sh
./compiler/build/sajilo input.sj -o text out.ir
```

### JSON Output

Emits structured output including IR text, error messages, and compilation status:

```sh
./compiler/build/sajilo input.sj -o json out.json
```

Example JSON output structure:

```json
{
  "status": true,
  "output": "str0: \"sajilo\"\n\nmain(int,int):\n...",
  "error": ""
}
```
