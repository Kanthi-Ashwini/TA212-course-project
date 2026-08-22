# Dual-Axis Solar Tracker — Embedded Drive Control

TA212 course project. Arduino firmware driving the two axes of a solar-tracker
mount: an H-bridge channel per axis, with independent direction and 8-bit PWM
speed control, in two operating modes.

> **Scope:** this is the **drive stack**, not a closed-loop tracker. Neither
> sketch reads a light sensor, and there is no sun-position algorithm. See
> [Limitations](#limitations).

---

## Repository layout

```
TeleopControl/TeleopControl.ino   Serial-driven manual control (calibration)
AutoSweep/AutoSweep.ino           Timed autonomous reversal sweep (demo)
docs/PINOUT.md                    Pin map and direction encoding
docs/KNOWN_ISSUES.md              Honest list of what is unfinished
```

Both sketches share one hardware abstraction:

```c
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm);
```

`direct` is `CW`, `CCW` or `BRAKE`; `pwm` is 0–255. Direction is latched on two
digital pins and magnitude written separately, so the two are independent.
Full pin map in [`docs/PINOUT.md`](docs/PINOUT.md).

---

## `TeleopControl` — manual mode

An interactive serial console at **9600 baud**, used to jog each axis while
calibrating travel against mechanical backlash.

| Key | Action |
|---|---|
| `w` | Axis 1 forward |
| `s` | Axis 1 reverse |
| `e` | Axis 1 stop |
| `a` | Axis 2 left |
| `d` | Axis 2 right |
| `q` | Axis 2 stop |
| `+` | Speed +10 (clamped at 255) |
| `-` | Speed −10 (clamped at 0) |

Speed starts at 250 and applies to both axes. Every command echoes back over
serial so the operator can confirm what the board received.

## `AutoSweep` — autonomous mode

Unattended demonstration sweep. Both axes start at PWM 150 and reverse on
independent, non-blocking `millis()` timers:

- Axis 1 reverses every **3 s**
- Axis 2 reverses every **5 s**

Because the scheduling is `millis()`-based rather than `delay()`-based, the two
intervals run concurrently — neither axis blocks the other, and the loop stays
responsive.

---

## Hardware

- Arduino (Uno-class, 5 V)
- Dual-channel H-bridge motor shield with enable and current-sense breakouts
- Two DC gearmotors, one per axis
- External motor supply sized to the gearmotors

## Build & upload

Open the sketch folder in the Arduino IDE (or `arduino-cli`) and upload:

```bash
arduino-cli compile --fqbn arduino:avr:uno TeleopControl
arduino-cli upload  --fqbn arduino:avr:uno -p <PORT> TeleopControl
```

For manual mode, open Serial Monitor at **9600 baud** after uploading.

---

## Limitations

Fully documented in [`docs/KNOWN_ISSUES.md`](docs/KNOWN_ISSUES.md). The short
version:

1. **No light sensing** — no LDR, no `analogRead`, no tracking algorithm.
   `AutoSweep` reverses on a fixed timer; it demonstrates the mechanism but
   does not follow the sun.
2. **No position feedback** — no encoder or limit switch; both modes are
   open-loop and nothing stops an axis at its mechanical limit.
3. **Current sensing unused** — `CURRENT_SEN_1/2` and `CS_THRESHOLD` are
   defined but never read, so the stall cutout does not exist.
4. **`AutoSweep` mis-configures the sense pins** as `OUTPUT` instead of
   `INPUT`.

Closing the light-sensing loop is the main outstanding work.
