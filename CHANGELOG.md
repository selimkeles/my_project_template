# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

### Added
- Initial project structure
- `make clean-build` and `make clean-test` targets for from-scratch rebuilds
- VSCode tasks `build`, `build-test`, `build-bear`, `clean-build`, `run` (plus `test`, `clean`)

### Changed
- Replaced CMake with a traditional GNU Make build system
- Added `make bear` target to generate `compile_commands.json` for clangd
- Moved test runner to Unity framework
- `launch.json` debug entries are now hidden per OS (`presentation.hidden` inside a `windows`/`linux`/`osx` section); the platform compounds were removed and `stopAtEntry` defaults to `false` everywhere

### Deprecated
- None

### Removed
- None

### Fixed
- None 