# Text-to-Braille Converter (Arduino)

An Arduino-based system that converts text input (sent over Serial) into physical Braille output using 6 actuators representing the 6 dots of a Braille cell.

## Overview

The system reads characters from the Serial monitor/connection one at a time, maps each character (A–Z, space) to its corresponding 6-dot Braille pattern, and drives 6 digital output pins accordingly to physically represent the character. A separate "verify" pin is toggled high while a character is being displayed, which can be used to trigger a buzzer, LED, or sync signal.

## How It Works

1. A character is sent over Serial.
2. `letterToIndex()` converts the character to an index (0–25 for A–Z, 26 for space).
3. The corresponding 6-character binary string (e.g. `"100000"` for A) is looked up in the `braille_alphabet` array.
4. `showOutput()` writes HIGH/LOW to the 6 pins based on the binary string, holds the output for 2 seconds, then resets all pins LOW.

## Hardware Setup

| Component        | Arduino Pin |
|-------------------|-------------|
| Dot Actuator 1    | 6           |
| Dot Actuator 2    | 9           |
| Dot Actuator 3    | 7           |
| Dot Actuator 4    | 10          |
| Dot Actuator 5    | 8           |
| Dot Actuator 6    | 11          |
| Verify/Sync Pin   | 2           |

> **Note:** The pin order in the `pins[]` array is `{pin1, pin4, pin2, pin5, pin3, pin6}`. This is intentional based on the physical wiring/layout of the Braille cell actuators — double check this mapping against your own hardware before use.

## Braille Mapping

Each letter is represented as a 6-bit binary string corresponding to Braille dot positions:

```
Dot layout:
1 4
2 5
3 6
```

A `1` means the dot is raised (pin HIGH), `0` means it's flat (pin LOW).

| Letter | Pattern | Letter | Pattern |
|--------|---------|--------|---------|
| A | 100000 | N | 110110 |
| B | 101000 | O | 100110 |
| C | 110000 | P | 111010 |
| D | 110100 | Q | 111110 |
| E | 100100 | R | 101110 |
| F | 111000 | S | 011010 |
| G | 111100 | T | 011110 |
| H | 101100 | U | 100011 |
| I | 011000 | V | 101011 |
| J | 011100 | W | 011101 |
| K | 100010 | X | 110011 |
| L | 101010 | Y | 110111 |
| M | 110010 | Z | 100111 |
| Space | 000000 | | |

## Usage

1. Upload the sketch to your Arduino.
2. Open the Serial Monitor (or any serial connection) at **9600 baud**.
3. Type a character and send it.
4. The Arduino will:
   - Activate the matching dot pins.
   - Hold the pattern for 2 seconds (verify pin HIGH).
   - Reset all pins and wait 0.5 seconds before accepting the next character.
5. Invalid characters (anything outside A–Z and space) will print an error message to Serial instead of driving the pins.

## Requirements

- Arduino board (Uno/Nano/similar)
- 6 digital outputs wired to Braille dot actuators (solenoids, motors, etc.)
- 1 digital output for verify/sync signal
- Arduino IDE or PlatformIO

## Possible Improvements

- Support full sentence input/buffering instead of one character at a time.
- Replace blocking `delay()` calls with non-blocking timing (`millis()`) for smoother multitasking.
- Add support for numbers and punctuation.
- Store Braille patterns in `PROGMEM` to save SRAM on memory-constrained boards.

## License

MIT License — feel free to use, modify, and share.
