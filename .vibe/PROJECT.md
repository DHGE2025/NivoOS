# Nivo OS: project guide

## Stack and status

Target: C# with Cosmos OS Development Kit. Current executable sandbox prototype:
freestanding C11 / GNU assembly, x86 BIOS Multiboot via GRUB, VGA text desktop.
`cosmos/Kernel.cs` is an uncompiled Cosmos kernel draft; it is not part of the
native build. .NET and Cosmos are unavailable here. Cosmos project integration,
graphical rendering, keyboard/mouse input and working dock applications remain open.

## Run contract

`.vibe/preview.json` is the command source of truth. Native toolchain, no HTTP.
No dependencies to fetch; all commands work offline with supplied tools.

- Install: null
- Build: `make all`
- Test: `make test`
- Run: `make run`

Build generates `build/kernel.elf` and `build/nivo.iso`. Run boots the ISO with
headless QEMU, validates serial markers and debug-exit status, and finishes
within a 15-second subprocess timeout. Do not turn it into an interactive run.

## Layout and conventions

- `src/`: small C kernel, Multiboot entry, linker script and pure desktop renderer.
- `cosmos/`: C# Cosmos draft, to integrate using a supported Cosmos template.
- `scripts/run.py`: Python standard-library QEMU runner.
- `tests/`: native C assertions and Python unittest; `make test` also boots the ISO.
- `build/`: generated output only; ignored together with caches and .env files.

Keep the renderer independent from hardware so tests can inspect VGA cells.
Use compiler warnings as errors. Do not add runtime dependencies unnecessarily.
Test normal behavior, boundaries and failure cases; see `.vibe/tests/README.md`.
After build/run command changes update preview.json and execute build, tests and
bounded run. Do not claim the C# draft is tested until Cosmos actually builds it.
