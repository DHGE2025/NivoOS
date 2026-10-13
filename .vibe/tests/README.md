# Tests

Every agent reads this before it writes code. Tests are not optional: each change that adds or
changes behaviour ships its tests in the same change, written by the agent, never left for later.

## How tests run

- Tests use the usual framework of the project's language and live where it expects them (for
  example `cargo test`, `go test ./...`, `pytest`, CTest, or a script that runs the program and
  checks its output). The first change with code sets `"testCommand"` in `.vibe/preview.json` to the command that runs all of them.
- The exit code decides: 0 means every test passed.
- Tests run in a sandbox **without network access**: dependencies come only from the install
  command, and tests never call real external services; stub them.
- There is no display and no hardware: test the logic directly and programs through their output
  (a CLI's stdout, a kernel's serial output in QEMU with a time limit).

## What to test

- The behaviour the change adds or fixes: the normal case, at least one edge case and an error case.
- A bug fix starts with a test that fails without the fix.
- Keep tests fast and independent: no fixed ports, no shared state between tests, no sleeps.
- Test names say what is expected, e.g. `'rejects an empty email'`.
- Never delete, skip or weaken a test to get green. Change a test only when the requested
  behaviour changed, and say so in your summary.

## Done means

- `The test command` passes.
- The build and the run command still work (see `.vibe/PROJECT.md`).
