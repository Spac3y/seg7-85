# seg7-85

A 4-digit 7-segment display driven by an ATtiny85, scrolling a text message across the display.

## How it works

The ATtiny85 bit-bangs two daisy-chained 74HC595 shift registers to drive a common-anode 4-digit 7-segment display (segments + digit select). A Timer1 CTC interrupt (~3 Hz) shifts the next character of the message into a 4-character rolling buffer, which is refreshed continuously via multiplexing.

Default message: `I LOVE YOU`.

## Hardware (BOM)

| Ref | Part | Qty |
|-----|------|-----|
| U1 | ATtiny85 (DIP-8) | 1 |
| U3, U4 | 74HC595 shift register (DIP-16) | 2 |
| U2 | 4-digit 7-segment display (CC56-12SURKWA) | 1 |
| R1–R4 | 220Ω (segment current limiting) | 4 |
| R5 | 10kΩ (reset pull-up) | 1 |
| C1–C3 | 10µF decoupling | 3 |
| SW1 | Push button (reset/mode) | 1 |
| J1 | 1x06 pin header | 1 |
| J2 | Molex KK-254 1x02 power connector | 1 |

Full BOM: [`kicad/attiny85_7seg.csv`](kicad/attiny85_7seg.csv)

## Repo layout

- `attiny-85_code/attiny-85_code.ino` — firmware (Arduino/AVR)
- `kicad/` — KiCad schematic, PCB layout, and design files
- `kicad/changes.md` — schematic/PCB change log

## Pinout (ATtiny85)

| Pin | Function |
|-----|----------|
| PB0 | Shift register data (SER/DS) |
| PB2 | Shift register clock (SRCLK/SHCP) |
| PB3 | Shift register latch (RCLK/STCP) |
| PB4 | Shift register reset (SRCLR/MR) |

## Building/flashing

Flash `attiny-85_code.ino` to the ATtiny85 using the Arduino IDE with an [ATtiny core](https://github.com/SpenceKonde/ATTinyCore) installed, via ISP.
