# Hardware Wiring and Electrical Specification

## 1. Verified Pin Connections

The table below lists all verified electrical connections between the **Arduino Uno R3 (ATmega328P)** microcontroller and external hardware modules, verified against the source code (`src/conveyor_color_sorting/conveyor_color_sorting.ino`) and physical prototype wiring.

<p align="center">
  <img src="assets/figure_4_1_hardware_wiring.png" alt="Hardware Wiring and Interconnection Block Diagram" width="95%" />
</p>

### 1.1 Pin Interconnection Table

| Component | Component Pin | Arduino Pin | Wire Color (Harness) | Signal Type | Electrical Specification / Purpose |
|:---|:---:|:---:|:---:|:---:|:---|
| **TCS3200** | `S0` | **D4** | Orange | Digital Output | Frequency scaling selection bit 0 (`HIGH` = 20% scale) |
| **TCS3200** | `S1` | **D5** | Yellow | Digital Output | Frequency scaling selection bit 1 (`LOW` = 20% scale) |
| **TCS3200** | `S2` | **D6** | Green | Digital Output | Photodiode color filter selector bit 0 |
| **TCS3200** | `S3` | **D7** | Blue | Digital Output | Photodiode color filter selector bit 1 |
| **TCS3200** | `OUT` | **D8** | White | Digital Input | Square wave frequency output (measured via `pulseIn()`) |
| **TCS3200** | `OE` | **D9** | Purple | Digital Output | Output Enable (Active `LOW`, enables frequency output) |
| **TCS3200** | `VCC` | `5V` | Red | Power Rail | +5V DC regulated sensor power supply |
| **TCS3200** | `GND` | `GND` | Black | Ground Rail | System 0V reference ground |
| **Big Servo** | `PWM` (Orange) | **D10** | Orange | PWM / PPM | Continuous rotation carousel turntable motor command |
| **Big Servo** | `VCC` (Red) | `5V / Ext 5V` | Red | Power Rail | Motor power supply rail |
| **Big Servo** | `GND` (Brown) | `GND` | Brown | Ground Rail | Common motor reference ground |
| **Flap 1 (SG90)** | `PWM` (Orange) | **D11** | Yellow | PWM / PPM | Diverter gate 1 angular position servo (30°–125°) |
| **Flap 1 (SG90)** | `VCC` (Red) | `5V / Ext 5V` | Red | Power Rail | Micro servo power rail |
| **Flap 1 (SG90)** | `GND` (Brown) | `GND` | Black | Ground Rail | Common motor reference ground |
| **Flap 2 (SG90)** | `PWM` (Orange) | **D12** | Blue | PWM / PPM | Diverter gate 2 angular position servo (30°–125°) |
| **Flap 2 (SG90)** | `VCC` (Red) | `5V / Ext 5V` | Red | Power Rail | Micro servo power rail |
| **Flap 2 (SG90)** | `GND` (Brown) | `GND` | Black | Ground Rail | Common motor reference ground |

---

## 2. Sensor Module Detail & Internal Wiring

<p align="center">
  <img src="../media/images/tcs3200_sensor_module.jpg" alt="TCS3200 Sensor Breakout Module" width="45%" />
  &nbsp;&nbsp;
  <img src="../media/images/sensor_mounting_underside.jpg" alt="Sensor Mounting Underside and Gantry Wiring" width="45%" />
</p>

### 2.1 Optical Gantry Routing
As shown in the hardware photographs:
1. The TCS3200 board is secured within a darkened shroud to isolate photodiode channels from ambient light interference.
2. The 8-wire sensor jumper bundle is routed down the hollow cardboard upright pillar, shielding the delicate signal lines from mechanical snagging against the carousel rotor.
3. The integrated 4 white LEDs are permanently energized whenever the sensor's `VCC` rail is powered, bathing the target packages in consistent white light.

---

## 3. Power Architecture & Electrical Safeguards

> [!CAUTION]
> **Servo Inrush and Brownout Prevention:**
> Microcontroller 5V regulators (e.g., the onboard NCP1117ST50T3G on an Arduino Uno) typically cap sustained current output at ~500 mA when powered via USB, and ~800 mA when powered via DC barrel jack.

### 3.1 Actuator Current Budget
* **SG90 Micro Servos (x2):** Idle current ~10 mA each; dynamic motion current ~150–250 mA each; stall current up to 650 mA.
* **Continuous Drive Servo (x1):** Running current under carousel load ~200–350 mA; stall current ~800 mA.
* **TCS3200 Sensor + 4 LEDs:** ~25–35 mA total.

### 3.2 Recommended Dual-Rail Power Scheme
For benchtop reproduction and high-reliability operation without unexpected ATmega328P resets (brownout detector triggering):

```text
  +-----------------------------------------------------------+
  |                   EXTERNAL POWER SUPPLY                   |
  |                5.0V Regulated DC (2.0A - 3.0A)            |
  +-----------------------------------------------------------+
         | (+) 5V Rail                               | (-) GND Rail
         |                                           |
         +-----------------------+                   |
         |                       |                   |
    [Big Servo VCC]      [Dual SG90 VCC]             |
         |                       |                   |
    [Big Servo GND]      [Dual SG90 GND]             |
         |                       |                   |
         +-----------------------+-------------------+
                                                     |
                                            COMMON GROUND POINT
                                                     |
  +------------------------+                         |
  |      ARDUINO UNO       |                         |
  |  USB Powered (500mA)   |                         |
  |    GND Pin ------------+-------------------------+
  |    5V Pin -------------> [TCS3200 VCC]
  |    GND Pin ------------> [TCS3200 GND]
  +------------------------+
```

### 3.3 Electrical Grounding
A common 0V ground reference **must** be maintained between the Arduino ground pin and external servo power ground rail. Omitting this ground bridge prevents the servo control logic from interpreting the PWM pulses correctly, leading to servo jitter or complete failure to actuate.
