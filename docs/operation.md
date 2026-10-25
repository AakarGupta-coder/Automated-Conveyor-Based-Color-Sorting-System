# System Operation, Calibration, and Build Guide

## 1. Development Environment & Toolchain

### 1.1 Hardware Prerequisites
* **1x** Arduino Uno R3 (or compatible ATmega328P board)
* **1x** TCS3200 (or TCS230) Color Sensor Breakout Board with 4 integrated white LEDs
* **1x** Continuous Rotation Servo Motor (turntable drive)
* **2x** TowerPro SG90 (or SG900) 9g Micro Servos (diverter flap actuators)
* **1x** USB Type-A to Type-B programming cable
* **1x** Regulated 5V DC 2A–3A bench power supply or powered USB bus
* Prototyping breadboard, male-to-male and male-to-female jumper wires
* 360° circular carousel frame, gantry tower, diverter gates, and collection chutes

### 1.2 Software Prerequisites
* **Arduino IDE:** Version 1.8.19+ or Arduino IDE 2.x
* **Core Libraries:** Built-in standard `<Servo.h>` (no external third-party library installations required)
* **OS Compatibility:** Tested on Windows 10/11 64-bit, compatible with macOS and Linux

---

## 2. Build and Upload Procedure

### Step 1: Clone Repository
```bash
git clone https://github.com/AakarGupta-coder/Automated-Conveyor-Based-Color-Sorting-System.git
cd Automated-Conveyor-Based-Color-Sorting-System
```

### Step 2: Open Sketch in Arduino IDE
Open the sketch file directly located at:
`src/conveyor_color_sorting/conveyor_color_sorting.ino`

*(Arduino IDE requires the parent folder name to match the sketch file name).*

### Step 3: Configure Target Board and COM Port
1. In the top menu, navigate to **Tools > Board > Arduino AVR Boards > Arduino Uno**.
2. Connect your Arduino Uno to the PC via the USB cable.
3. Navigate to **Tools > Port** and select the assigned COM port (e.g., `COM3`, `COM4`, or `/dev/ttyUSB0` on Linux).

### Step 4: Verify and Upload
1. Click **Verify** (`Ctrl + R`) to compile the sketch.
2. Click **Upload** (`Ctrl + U`) to flash the firmware onto the ATmega328P.
3. Upon upload completion, the status bar displays `Done uploading.`.

---

## 3. Serial Monitor Diagnostics & Telemetry

Open the Serial Monitor (`Ctrl + Shift + M`) in the Arduino IDE and verify that the baud rate is set to **9600 baud**.

### Initial Boot Banner
When the microcontroller resets, it initializes the dual flaps to 125°, begins carousel rotation, and prints:

```text
================================
INVENTORY SYSTEM READY
Big servo: D10
Flap 1: D11
Flap 2: D12
Both flaps initialized at 125 degrees.
Conveyor remains running during color detection.
================================
```

### Real-Time Polling Telemetry
Every 500 ms during normal operation, the firmware streams the raw frequency values and status:

```text
R:4428 G:3698 B:4535 | COLOR: BASE | BASE
R:4435 G:3689 B:4548 | COLOR: BASE | BASE
R:4431 G:3695 B:4540 | COLOR: BASE | BASE
```

### Detection and Actuation Event Stream
When a package enters the optical hood, consecutive non-base reads trigger classification:

```text
R:15490 G:18210 B:19820 | COLOR: WHITE | POSSIBLE PACKAGE
DETECTED COLOR: WHITE
R:15520 G:18240 B:19870 | COLOR: WHITE | POSSIBLE PACKAGE
R:15545 G:18230 B:19855 | COLOR: WHITE | POSSIBLE PACKAGE

PACKAGE CONFIRMED!
Color detection complete.
Conveyor continues for 3100 ms.

BIG SERVO STOPPED
Both flaps moving to 30 degrees.
Both flaps returning to 125 degrees.
Both flaps returned to 125 degrees.
Big servo restarted.
READY FOR NEXT PACKAGE!
```

---

## 4. Calibration & Tuning Workflow

<p align="center">
  <img src="../media/images/test_packages_white_brown.jpg" alt="White and Brown Test Package Specimens" width="60%" />
</p>

### 4.1 Belt Baseline Calibration
1. Ensure the conveyor belt surface under the sensor gantry is completely empty.
2. Observe the raw frequency readings (`R`, `G`, `B`) on the Serial Monitor.
3. If the ambient lighting or belt material has changed, update lines 30–34 in `conveyor_color_sorting.ino`:
   ```cpp
   const float BASE_R = 4432;
   const float BASE_G = 3693;
   const float BASE_B = 4541;
   const float BASE_TOLERANCE = 0.35; // 35% tolerance window
   ```

### 4.2 Package Color Centroid Calibration
1. Place a white test specimen directly beneath the optical hood. Note the average `R`, `G`, `B` values over 10 sample lines.
2. Place a brown kraft test specimen under the hood. Note its average `R`, `G`, `B` values.
3. Update the reference constants in lines 39–46:
   ```cpp
   // Measured WHITE reference values
   const float WHITE_R = 15531;
   const float WHITE_G = 18231;
   const float WHITE_B = 19863;

   // Measured BROWN reference values
   const float BROWN_R = 19070;
   const float BROWN_G = 13023;
   const float BROWN_B = 13031;
   ```

### 4.3 Conveyor Transit Delay Calibration (`STOP_DELAY`)
The variable `STOP_DELAY` (line 23) determines how long the conveyor continues moving after package detection before stopping at the diverter gate:

$$\text{Transit Time} = \frac{\text{Arc Distance from Sensor Hood to Gate}}{\text{Angular Velocity of Turntable}}$$

* If the package stops **before** reaching the diverter flap, increase `STOP_DELAY` (e.g., from `3200` to `3400` ms).
* If the package **overshoots** past the diverter flap, decrease `STOP_DELAY` (e.g., from `3200` to `3000` ms).

### 4.4 Diverter Gate Angle Calibration
* `FLAP_HOME = 125;` — Mechanical rest angle flush with track perimeter.
* `FLAP_PUSH = 30;` — Actuated angle diagonal across track to deflect package into chute.
* If flaps do not open sufficiently, adjust `FLAP_PUSH` toward `20°` or verify servo horn spline alignment.
