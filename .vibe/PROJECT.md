# Nivo OS: project guide for agents

VibeYourFlow gives this file to every agent step automatically. Keep it short and true; update it
when the project changes. Kind: Operating system. Stack: C# mit dem Cosmos OS Development Kit. Wir entwickeln ein eigenes bootfähiges Betriebssystem mit einer minimalistischen, Apple-inspirierten Benutzeroberfläche..

Sandbox: Linux with the `native` toolchain (C and C++ (GCC, Clang, CMake), Go, Rust, Python with uv, Zig, QEMU, GRUB and the ARM embedded compiler).
No root, no Docker, no system packages. Only the install command has network access; build,
tests and the program run offline, and a dependency you add is available after the next install
step.

## Run contract (never break this)

The project must always build, pass its tests and run in the VibeYourFlow sandbox. How is defined
in `.vibe/preview.json`, which is the source of truth (workspace settings in the app override it).
Nothing is served over HTTP: the output of the run command shows in the run log.

- Install: nothing to install
- Build: none
- Run: not set yet

No program exists yet. As soon as you create one, fill in `.vibe/preview.json` (install, build,
test and run command) in the same change.

Rules:

1. After any change that affects how the project builds or runs (build files, dependencies, entry
   point), run the build and the run command before you finish. A change that breaks them is not
   done.
2. The run command finishes on its own: no interactive input, no server and no window that waits.
   Give long runs a time limit (for example `timeout 120 qemu-system-x86_64 ...`).
3. If you change a command, update `.vibe/preview.json` in the same change.
4. Never commit build output, caches or `.env` files; keep `.gitignore` up to date.

## Tests

Every change ships its tests, written by you in the same change; follow `.vibe/tests/README.md`.
No test command yet: the first change with code sets one up as `.vibe/tests/README.md` describes.

## Conventions

- Keep changes small and focused; follow the patterns already in the code.
- Put project-specific rules here (naming, folder layout, libraries to prefer or avoid).
