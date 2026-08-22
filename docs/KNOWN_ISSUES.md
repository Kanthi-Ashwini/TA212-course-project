# Known issues

Carried over from the original sketches, left unfixed so the repo matches what
was actually built and demonstrated. Each is a small, self-contained fix.

### 1. Current sensing is wired but never used

`CURRENT_SEN_1` / `CURRENT_SEN_2` (A2/A3) are defined and `CS_THRESHOLD` is set
to 15, but no code ever calls `analogRead()` on them and `CS_THRESHOLD` is
referenced nowhere. The intended stall/over-current cutout was never
implemented — a jammed axis will keep driving.

*Fix:* read both channels in `loop()` and brake the offending axis when the
reading exceeds `CS_THRESHOLD`.

### 2. `AutoSweep` sets the current-sense pins to `OUTPUT`

```c
pinMode(CURRENT_SEN_1, OUTPUT);   // should be INPUT
pinMode(CURRENT_SEN_2, OUTPUT);   // should be INPUT
```

`TeleopControl` gets this right (`INPUT`). Harmless only because the pins are
never read; it must be corrected before issue 1 is addressed, since driving an
analog sense line as an output fights the shield's sense circuitry.

### 3. No position feedback of any kind

There is no encoder, limit switch or potentiometer. Both sketches are fully
open-loop: axis position is whatever the accumulated run time produced. There
is nothing preventing an axis from being driven past its mechanical stop.

### 4. No light sensing — this is a drive stack, not a tracker

Despite the project title, neither sketch reads an LDR or photodiode and no
sun-position or light-seeking algorithm exists. `AutoSweep` reverses each axis
on a fixed timer, which demonstrates the mechanism but does not track the sun.
Closing that loop is the main outstanding work.

### 5. `Serial.read()` consumes one byte per `loop()` iteration

`TeleopControl` reads a single character and then `delay(100)`. Pasting several
commands at once leaves the rest queued and applied at 10 Hz rather than being
handled or flushed.
