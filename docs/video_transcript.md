# Voice Narration & Audio Transcript

This document provides the authentic audio transcript of the comprehensive operational video demonstration: [`media/videos/24BRS1321,1034 Project Video.mp4`](../media/videos/24BRS1321,1034%20Project%20Video.mp4).

---

## Recording Telemetry & Audio Parameters

* **Video File:** `media/videos/24BRS1321,1034 Project Video.mp4`
* **Audio Track:** AAC (LC), Stereo, 48,000 Hz, 192 kbps
* **Duration:** 72.60 Seconds (01:12.60)
* **Spoken Language:** English
* **Demonstration Speaker:** Project Engineer / Operator (Live Demonstration)

---

## Verbatim Chronological Transcript

| Timestamp Interval | Spoken Narration (Verbatim Transcript) | Physical Action / System Event Observed |
|:---:|:---|:---|
| **00:00 – 00:10** | *"So here we have warehouse inventory management system. It consists of this conveyor which is going to spin around. It is connected to the TCS..."* | Overhead camera framing stationary circular carousel turntable, optical gantry at 12 o'clock, and dual diversion chutes. |
| **00:10 – 00:20** | *"...TCS3200 RGB sensor that will detect whether the package is of a brown colour or white colour. And then it will go to each of these servo motors over here that will segregate them into..."* | Camera zooms towards optical gantry tower housing downward-facing TCS3200 photodiode array and dual SG90 gate micro-servos. |
| **00:20 – 00:30** | *"...respective pockets. So if you just plug in the Arduino, as you can see, the conveyor is now running. Now we place a brown package and..."* | Operator inserts USB cable. Arduino Uno boots, TCS3200 white illumination LEDs activate, continuous rotation servo spins turntable. |
| **00:30 – 00:40** | *"...we place some other blue or white one. So the brown package is going to go into this specific compartment. The brown is the heavy work and..."* | Brown Box #1 passes beneath optical shroud. TCS3200 acquires RGB frequency. Transit timer elapses; conveyor stops; left gate flap actuates to 30°, deflecting brown box into Compartment 2 (Left Chute). |
| **00:40 – 00:50** | *"...all other packages are considered light, such as the blue one, it will go into that specific compartment. Now if we place a..."* | Blue parcel ("ALL ON") transits under optical sensor. Classified into light/standard category. Right gate flap sweeps outward, diverting blue package into Compartment 1 (Right Chute). |
| **00:50 – 01:00** | *"...a brown one and another white one, so the white one will get sorted into compartment one and the brown one..."* | Continuous multi-item feed: White parcel (with directional marker) enters sensor. Acquired and classified. Transit timer triggers right flap divert into Compartment 1. |
| **01:00 – 01:10** | *"...into compartment two. So the white one goes into compartment one once again, and the brown one gets sorted into compartment two..."* | Fourth item (Brown Box #2) reaches diverter gates. Conveyor halts; left gate flap deflects brown box into Compartment 2. |
| **01:10 – 01:12** | *"...as such."* | Run concludes. 4 consecutive parcels sorted with 100% accuracy (Compartment 1: 1 Blue, 1 White; Compartment 2: 2 Brown). |

---

## Technical Architectural Insights from Spoken Narration

1. **Warehouse Inventory Application:** The spoken narrative establishes that the electromechanical sorter functions as a physical automated warehouse parcel intake and routing mechanism.
2. **Dual-Compartment Functional Logic:**
   * **Compartment 1 (Right Chute):** Assigned to standard/lightweight parcels (White wrapped packages and Blue wrapped packages).
   * **Compartment 2 (Left Chute):** Assigned to heavy/corrugated kraft parcels (Brown cardboard blocks).
3. **Continuous Streaming:** The demonstration proves that the Arduino Uno firmware operates without manual resets between cycles, accepting consecutive items in an uninterrupted workflow.
