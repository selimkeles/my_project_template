# C/C++ Project Template

A traditional GNU Make-based C/C++ project template for VSCode with clangd IntelliSense (via **Bear**), Unity unit testing, and a simple, predictable build.

---

## Requirements

### Linux

| Tool | Purpose |
|---|---|
| `make` | Build system |
| `gcc`, `g++` | Compiler |
| `bear` | Generates `compile_commands.json` for clangd |

```bash
# Ubuntu/Debian
sudo apt install make gcc g++ bear
```

> Windows: [MinGW-w64](https://www.mingw-w64.org/) + [MSYS2 make](https://www.msys2.org/) work with this Makefile. `bear` is optional on any platform where you already have a `compile_commands.json`.

---

## Project Structure

```
.
├── src/                        # Source files — headers live next to sources
│   ├── MyModule/
│   │   ├── myModule.h
│   │   └── myModule.cpp
│   └── main.cpp                # Application entry point
├── tests/
│   ├── unity/                  # Unity test framework (submodule)
│   ├── test.c                  # Test runner entry point
│   └── ...
├── .vscode/
│   ├── settings.json           # clangd config
│   ├── tasks.json              # make build/test/bear tasks
│   ├── launch.json             # Debug config (cppvsdbg / gdb)
│   └── c-cpp.code-snippets     # Project snippets
├── Makefile
├── .clang-format
└── .clangd
```

---

## Build

All source files under `src/` are discovered recursively, so new modules are picked up automatically — no Makefile edits needed.

```bash
make            # build build/bin/TemplateProject
make -j4        # parallel build
make run        # build and run
make test       # build and run the Unity tests
make clean      # remove build artifacts
```

Override the toolchain on the command line:

```bash
make CC=clang CXX=clang++
```

---

## IntelliSense (clangd + Bear)

IntelliSense is provided by **clangd** (not the built-in cpptools engine). clangd reads `compile_commands.json` from the workspace root.

Generate it with Bear once (or after changing sources / flags):

```bash
make bear
```

`make bear` performs a clean rebuild wrapped in Bear so every translation unit is recorded (including tests). The resulting `compile_commands.json` is gitignored — each developer generates their own.

Alternatively, wrap any build manually:

```bash
bear -- make
```

If squiggles appear after adding new files, re-run `make bear` (or `bear -- make`).

---

## Test

```bash
make test
```

Tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) framework. The test binary links every `src/` file except `main` plus the Unity sources. To add a test see [CONTRIBUTING.md](CONTRIBUTING.md).

---

## Debug

Debugging is configured via `launch.json` using `cppvsdbg` (Windows) or `gdb` (Linux). The `make build` task runs automatically before launch.

In VSCode: set a breakpoint → press `F5`.

---

## Snippets

Type the prefix in any `.c` or `.cpp` file and press `Tab`.

| Prefix | Expands to |
|---|---|
| `guard` | Include guard using filename |
| `cls` | C++ class skeleton |
| `str` | C typedef struct |
| `enm` | `enum class` with underlying type |
| `extc` | `extern "C"` block for C/C++ compatible headers |
| `fori` | Index-based `for` loop |
| `forr` | Range-based `for` loop (C++) |
| `sw` | `switch` statement |
| `todo` | `// TODO:` comment |
| `banner` | Section separator comment |

---

## License

MIT — see [LICENSE](LICENSE).