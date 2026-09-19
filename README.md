# chip8-emu

A CHIP-8 emulator written in C++ using SDL3.

## Build

Requires SDL3 (`libsdl3-dev` or equivalent) and a C++17 compiler.

```bash
make
```

## Run

```bash
./chip8 <scale> <delay> <rom> [--code]
```

- `scale` — window scale factor (e.g. `10` for a 640x320 window)
- `delay` — milliseconds between emulation cycles (controls CPU speed)
- `rom` — path to a `.ch8` ROM file
- `--code` — generates the code of the provided ROM in a text file

Example:

```bash
./chip8 10 3 roms/pong.ch8
```

## Controls

CHIP-8's original 16-key hex keypad is mapped to the keyboard as follows:

```
Chip-8 Keypad        Keyboard
1 2 3 C               1 2 3 4
4 5 6 D               Q W E R
7 8 9 E               A S D F
A 0 B F               Z X C V
```
