# Pin map

Both sketches share one pin map, matching a dual-channel H-bridge motor shield
(two direction pins + one PWM pin + one enable pin + one current-sense pin per
channel).

| Signal | Pin | Notes |
|---|---|---|
| `MOTOR_A1_PIN` | D7 | Axis 1 direction A |
| `MOTOR_B1_PIN` | D8 | Axis 1 direction B |
| `MOTOR_A2_PIN` | D4 | Axis 2 direction A |
| `MOTOR_B2_PIN` | D9 | Axis 2 direction B |
| `PWM_MOTOR_1` | D5 | Axis 1 speed (8-bit PWM) |
| `PWM_MOTOR_2` | D6 | Axis 2 speed (8-bit PWM) |
| `EN_PIN_1` | A0 | Axis 1 driver enable |
| `EN_PIN_2` | A1 | Axis 2 driver enable |
| `CURRENT_SEN_1` | A2 | Axis 1 current sense — **declared, never read** |
| `CURRENT_SEN_2` | A3 | Axis 2 current sense — **declared, never read** |

## Direction encoding

`motorGo(motor, direction, pwm)` is the single entry point for both channels:

| `direction` | A pin | B pin | Effect |
|---|---|---|---|
| `CW` (1) | LOW | HIGH | Forward |
| `CCW` (2) | HIGH | LOW | Reverse |
| `BRAKE` (0) | LOW | LOW | Coast / brake |

Speed is written separately with `analogWrite(PWM_MOTOR_n, pwm)`, so direction
and magnitude are independent.
