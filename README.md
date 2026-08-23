# STM32F401 Motor Control

Register-level Arduino sketches for controlling a motor driver from an
**STM32F401** board.

## Important limitations

- This project is written for the STM32F401 only.
- Use GPIO pins on port A only: `PA0` through `PA7`.
- Pin arguments are numbers, not Arduino pin names:
  - `0` = `PA0`
  - `1` = `PA1`
  - `2` = `PA2`
  - `3` = `PA3`
  - `4` = `PA4`
  - `5` = `PA5`
  - `6` = `PA6`
  - `7` = `PA7`
- Use only **one motor driver at a time**. Do not initialize or drive the
  `L298N`, `BTS7960`, and `MDD10A` in the same program.
- The PWM value is from `0` to `999`. Positive values command forward motion,
  negative values command reverse motion, and `0` stops the motor.
- Connect the STM32F401 ground to the motor-driver ground. Do not power the
  motor from the STM32F401 board.

## Setup

1. Install the Arduino IDE.
2. Install the STM32 board package that provides STM32F401 support.
3. Select the correct STM32F401 board and upload method in **Tools > Board**.
4. Open `main.ino` in this folder.
5. Select exactly one driver in `setup()` by leaving one initialization call
   active and keeping the others commented out.
6. Set the pin numbers to the STM32 port-A pins wired to the driver.
7. Connect the driver inputs, motor supply, motor, and common ground.
8. Upload the sketch to the STM32F401.

## Selecting a driver

The driver implementations are:

- `L298N`: two direction pins and one PWM enable pin.
- `BTS7960`: one RPWM pin and one LPWM pin.
- `MDD10A`: one direction pin and one PWM pin.

Keep only one initialization call active in `setup()`. The matching `drive()`
function must be the only driver function called from `loop()`.

### L298N example

```cpp
#define IN1 0  // PA0
#define IN2 1  // PA1
#define ENA 2  // PA2

void setup()
{
  L298N_init(IN1, IN2, ENA);
}

void loop()
{
  L298N_drive(IN1, IN2, ENA, 500);  // Forward, half speed
  delay(2000);
  L298N_drive(IN1, IN2, ENA, 0);    // Stop
  delay(1000);
  L298N_drive(IN1, IN2, ENA, -500); // Reverse, half speed
  delay(2000);
  L298N_drive(IN1, IN2, ENA, 0);    // Stop
  delay(1000);
}
```

### BTS7960 example

```cpp
#define RPWM 3  // PA3
#define LPWM 4  // PA4

void setup()
{
  BTS7960_init(RPWM, LPWM);
}

void loop()
{
  BTS7960_drive(RPWM, LPWM, 500);  // Forward
  delay(2000);
  BTS7960_drive(RPWM, LPWM, 0);    // Stop
  delay(1000);
  BTS7960_drive(RPWM, LPWM, -500); // Reverse
  delay(2000);
  BTS7960_drive(RPWM, LPWM, 0);    // Stop
  delay(1000);
}
```

### MDD10A example

```cpp
#define DIR 5  // PA5
#define PWM 6  // PA6

void setup()
{
  MDD10A_init(DIR, PWM);
}

void loop()
{
  MDD10A_drive(DIR, PWM, 500);  // Forward
  delay(2000);
  MDD10A_drive(DIR, PWM, 0);    // Stop
  delay(1000);
  MDD10A_drive(DIR, PWM, -500); // Reverse
  delay(2000);
  MDD10A_drive(DIR, PWM, 0);    // Stop
  delay(1000);
}
```

## Files

- `main.ino`: example application and driver selection.
- `L298N.h` / `L298N.ino`: L298N interface and implementation.
- `BTS7960.h` / `BTS7960.ino`: BTS7960 interface and implementation.
- `MDD10A.h` / `MDD10A.ino`: MDD10A interface and implementation.
- `setup.h`: STM32F401 register definitions and bit helpers.
