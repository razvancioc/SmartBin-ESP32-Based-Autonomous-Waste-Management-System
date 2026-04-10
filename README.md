# SmartBin-ESP32-Based-Autonomous-Waste-Management-System

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![Platform](https://img.shields.io/badge/Platform-ESP32%20%7C%20Arduino-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

An automated, touchless waste disposal solution designed for hygiene and convenience. This project utilizes an **ESP32 microcontroller**, an **HC-SR04 ultrasonic sensor**, and a **PWM-controlled servo motor** to create a highly responsive, autonomous bin lid. 

This repository contains the C++ firmware, hardware schematics, and 3D-printable CAD files required to replicate the project.

---

## 🚀 System Overview

The SmartBin minimizes physical contact with waste receptacles. By utilizing high-frequency ultrasonic distance measurement (40kHz), the system detects an approaching hand or object and triggers a servo motor to articulate the lid smoothly and silently.

### Key Features
* **Non-Blocking Proximity Logic:** Calibrated for a 30cm detection threshold.
* **Precision Actuation:** 25° angular displacement for optimal lid opening using the `ESP32Servo` library.
* **Low Latency:** Dual-core ESP32 processing ensures instantaneous response times.
* **Parametric Design:** Fully 3D-printable chassis and mounting brackets.

---

## 🛠 Hardware Specifications

To build this project, you will need the following components:

| Component | Specification | Quantity |
| :--- | :--- | :--- |
| **Microcontroller** | ESP32 Development Board | 1 |
| **Sensor** | HC-SR04 Ultrasonic Sensor | 1 |
| **Actuator** | SG90 or MG90S Micro Servo | 1 |
| **Power Source** | 5V DC Supply / USB | 1 |
| **Enclosure** | 3D Printed Parts (See `/cad`) | 1 |

### Wiring & Pinout

| HC-SR04 Sensor | ESP32 Pin | Function |
| :--- | :--- | :--- |
| VCC | 5V / VIN | Power |
| Trig | GPIO 2 | Pulse Trigger |
| Echo | GPIO 15 | Echo Return |
| GND | GND | Ground |

| Servo Motor | ESP32 Pin | Function |
| :--- | :--- | :--- |
| VCC (Red) | 5V / VIN | Power |
| Signal (Orange) | GPIO 13 | PWM Control |
| GND (Brown) | GND | Ground |

## 🔧 Installation & Setup

Follow these steps to replicate the SmartBin system. This process involves mechanical assembly, circuit wiring, and firmware flashing.

### 1. Mechanical Assembly (CAD)
All structural components are located in the `/cad` directory.
* **Fabrication:** 3D print the `.stl` files using PLA or PETG.
* **Print Settings:** 0.2mm layer height, 3 wall perimeters, and 20% Infill (Gyroid recommended for strength).
* **Servo Mounting:** Secure the SG90/MG90S servo into the bracket before attaching the lid. Ensure the servo is at its `baseAngle` ($0^\circ$) during assembly to prevent mechanical binding.

### 2. Circuitry & Wiring
Refer to the table below for the ESP32 pinout configuration. Ensure all grounds (GND) are common.

| Component | Pin (ESP32) | Function |
| :--- | :--- | :--- |
| **HC-SR04 Trig** | GPIO 2 | Output Trigger |
| **HC-SR04 Echo** | GPIO 15 | Input Echo |
| **Servo Signal** | GPIO 13 | PWM Control |
| **Power (VCC)** | 5V / VIN | 5V DC Supply |

### 3. Firmware Deployment
The system is built using the Arduino framework for ESP32.

1.  **Environment:** Open the project in **Arduino IDE** or **PlatformIO**.
2.  **Library Requirement:** Install the `ESP32Servo` library via the Library Manager.
3.  **Upload:** Connect the ESP32 via USB and flash the `src/main.cpp` file.
4.  **Verification:** Open the Serial Monitor at **115200 baud**. You should see distance telemetry in real-time.

### 4. Calibration & Tuning
The behavior of the bin can be modified in the configuration section of the source code:

```cpp
// Change the detection range (cm)
const int detectionThreshold = 30; 

// Adjust the lid opening angle based on your hinge design
const int movementDegrees = 25;

