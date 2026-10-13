# Nivo OS

Ein erster bootfaehiger Desktop-Prototyp mit ruhiger, Apple-inspirierter
Textoberflaeche: Menueleiste, zentriertes Willkommen-Fenster und Dock.
Die Dock-Eintraege sind vorerst Beschriftungen; Eingabe und Anwendungen fehlen.

## Status und Stack

Das Ziel ist **C# mit dem Cosmos OS Development Kit**. Diese Linux-Sandbox
enthaelt weder .NET noch Cosmos. Deshalb ist der hier tatsaechlich baubare
Boot-Prototyp ein kleiner eigenstaendiger x86-Kernel in C und GNU-Assembler.
Er ist kein Cosmos-Kernel und fuehrt keinen C#-Code aus.
`cosmos/Kernel.cs` ist der separate, noch ungepruefte C#-Kernelentwurf.
Fuer dessen Integration in Cosmos muss eine Cosmos-kompatible Entwicklungsumgebung
bereitstehen: dort ein Kernelprojekt mit der offiziellen Cosmos-Projektvorlage
anlegen und dessen Kernelklasse durch diese Datei ersetzen. Es wird hier kein
fertiger Cosmos-Build oder eine Cosmos-ISO behauptet.

## Offline bauen, testen und starten

Voraussetzungen: GCC mit 32-Bit-Codegenerierung, GNU ld, make, GRUB
(`grub-file`, `grub-mkrescue` mit i386-PC-Modulen), xorriso, Python 3 und
`qemu-system-i386`. Diese Werkzeuge sind in der vorgesehenen Sandbox vorhanden.
Keine Installation und keine heruntergeladenen Abhaengigkeiten erforderlich.

```sh
make all       # build/nivo.iso und build/kernel.elf
make test      # C-Assertions, Python unittest und echter QEMU-Boot
make run       # ein headless Boot; endet automatisch binnen 15 Sekunden
make clean     # Buildausgabe entfernen
```

Der Run prueft den QEMU-Exitcode und die seriellen Bootmeldungen. Die
`isa-debug-exit`-Erweiterung beendet den Emulator nach dem Zeichnen; der
QEMU-Erfolgscode 33 wird vom Runner als Erfolg (0) ausgegeben. Bei einem
Timeout oder einer fehlenden Meldung endet der Runner mit Fehler (1).
Ohne dieses QEMU-Geraet bleibt der Kernel nach dem Zeichnen angehalten.
Die ISO ist fuer BIOS/x86 gedacht, nicht fuer UEFI oder ARM.

Optional den Desktop in einer Umgebung mit Display betrachten:

```sh
qemu-system-i386 -cdrom build/nivo.iso -m 32 -serial stdio
```

Dieser manuelle Aufruf wartet; QEMU selbst schliessen. Er ist nicht der
automatische Run-Befehl. Die Sandbox validiert Textzellen und seriellen
Bootoutput, keine grafische Bildschirmaufnahme.

## Layout

- `src/`: Multiboot-Einstieg, Linkerskript, Kernel und VGA-Textdesktop.
- `cosmos/`: C#-Entwurf fuer das angestrebte Cosmos-Projekt.
- `tests/`: Desktop-Speichergrenzen und Inhalte sowie Runner-Fehlerfaelle.
- `scripts/run.py`: begrenzter QEMU-Smoke-Test ohne Netzwerk.
- `build/`: ausschliesslich generierte Dateien, nicht versionieren.
- `.vibe/preview.json`: verbindliche Offline-Build-, Test- und Run-Befehle.
