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
│   ├── tasks.json              # make tasks: build / build-test / build-bear / clean-build / run
│   ├── launch.json             # Debug config (gdb / cppvsdbg) + run|test compounds
│   └── c-cpp.code-snippets     # Project snippets
├── Makefile
├── .clang-format
└── .clangd
```

---

## Build

All source files under `src/` are discovered recursively, so new modules are picked up automatically — no Makefile edits needed.

```bash
make              # build build/bin/TemplateProject
make -j4          # parallel build
make run          # build and run
make test         # build and run the Unity tests
make test-build   # build the test binary only (for debugging)
make clean-build  # remove build artifacts, then rebuild from scratch
make clean-test   # remove build artifacts, then rebuild the test binary
make bear         # rebuild under Bear -> compile_commands.json
make clean        # remove build artifacts
```

Override the toolchain on the command line:

```bash
make CC=clang CXX=clang++
```

### VSCode tasks

Every target above is also a task in `.vscode/tasks.json`. Run them with `Ctrl+Shift+B` (default: `build`) or through **Tasks: Run Task...** in the Command Palette.

| Task | Runs | Produces |
|---|---|---|
| `build` | `make -j build` | `build/bin/TemplateProject` |
| `build-test` | `make -j test-build` | `build/bin/test_TemplateProject` |
| `build-bear` | `make bear` | `compile_commands.json` for clangd |
| `clean-build` | `make clean-build` | fresh `build/bin/TemplateProject` |
| `run` | `make run` | build + run in the terminal |
| `test` | `make test` | build + run the Unity tests |
| `clean` | `make clean` | removes `build/` |

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

Debugging is configured via `launch.json`. Each configuration pre-launches the matching make task (`build` or `build-test`), so the binary is always up to date.

In VSCode: set a breakpoint → pick a configuration → press `F5`.

| Entry | Shown on | Debugger | Debugs |
|---|---|---|---|
| `Debug (gdb)` | Linux, macOS | `cppdbg` (GDB/MI) | `build/bin/TemplateProject` |
| `Debug (MSVC)` | Windows | `cppvsdbg` | `build/bin/TemplateProject.exe` |
| `Test (gdb)` | Linux, macOS | `cppdbg` (GDB/MI) | `build/bin/test_TemplateProject` |
| `Test (MSVC)` | Windows | `cppvsdbg` | `build/bin/test_TemplateProject.exe` |

Each configuration hides itself on the OS it does not run on, so the dropdown only ever shows the two entries for your platform:

```jsonc
"presentation": { "group": "1-run", "order": 1 },   // group + order in the dropdown
"windows": { "presentation": { "hidden": true } }   // hidden on Linux/macOS
```

Notes:

- `type` cannot be placed in an OS section — it selects the debug adapter — hence one configuration per debugger rather than one per target. Names must also stay unique: `launch.json` is looked up with `find()`, so two configurations sharing a name always resolve to the first.
- The two debuggers take different properties: `cppdbg` uses `MIMode` / `setupCommands` / `externalConsole`, `cppvsdbg` uses `console: integratedTerminal` and has no `MIMode`.
- No `compounds` are needed. A compound starts every configuration listed in it and VSCode does not filter those by OS, so a single compound could not serve both platforms.
- Running without the debugger is the `run` task (`make run`) in the terminal.

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