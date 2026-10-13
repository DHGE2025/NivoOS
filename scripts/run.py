"""Run one bounded QEMU smoke boot and validate its serial output."""
import subprocess
import sys


def main():
    try:
        result = subprocess.run([
            "qemu-system-i386", "-cdrom", "build/nivo.iso", "-m", "32",
            "-display", "none", "-serial", "stdio", "-monitor", "none",
            "-no-reboot", "-device", "isa-debug-exit,iobase=0xf4,iosize=0x04",
        ], capture_output=True, text=True, timeout=15)
    except (OSError, subprocess.TimeoutExpired) as error:
        print(f"Boot failed: {error}", file=sys.stderr)
        return 1
    print(result.stdout, end="")
    if result.returncode != 33 or "Nivo OS: boot OK" not in result.stdout or "Desktop: Willkommen" not in result.stdout:
        print(f"Boot failed (exit {result.returncode}): {result.stderr}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
