# C Utilities Library

A collection of reusable C utility modules providing data structures, logging, random utilities, math helpers, and string operations. Designed to simplify common tasks and accelerate development of C projects.

## Features

- Generic doubly-linked lists (`linked_list`)
- Simple hash table implementation (`hashtable`)
- JSON utilities (`json_utils`)
- Logging utilities with levels (`log_utils`)
- Math helpers (`math_utils`, `math_utils_vec2`)
- Random number utilities (`rand_utils`)
- String utilities (`str_utils`)
- Unit-test ready with clear module separation

## Modules

| Module | Description |
|--------|-------------|
| `linked_list` | Generic doubly-linked list with sorting, searching, and selection capabilities. |
| `hashtable` | Simple hash table for storing key-value pairs. |
| `json_utils` | Utilities for JSON parsing and serialization. |
| `log_utils` | Logging with levels: DEBUG, INFO, WARN, ERROR. |
| `math_utils` | General math functions. |
| `math_utils_vec2` | 2D vector math utilities. |
| `rand_utils` | Random numbers and helpers. |
| `str_utils` | String manipulation utilities. |

## Building the Library

The library comes with a CMake file. It compiles all source files and creates a static library (`libvfcutils.a`).

### Release

```bash
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release

cmake --build build/release
```

### Debug

```bash
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug

cmake --build build/debug
```
