# 🔋 Battery Monitoring System – STM32F411 Project

> Developed By: Vaishnavi Jadhav and Darshan Salian    
> Course: ECEN 5613 – Embedded System Design  
> Date: December 2024  

---

## 📌 Overview

This project implements a real-time **Battery Monitoring System (BMS)** that tracks essential parameters such as **voltage**, **current**, and **temperature** of a 4-cell lithium-ion battery pack. The system uses **ADS1115 ADC**, **differential amplifiers**, **STM32F411VET6**, and **EEPROM** for accurate measurement, storage, and communication of battery metrics.

It provides **real-time GUI display** over UART using a custom **C# Windows Forms application**, enabling user-friendly monitoring and debugging.

---

## 🔧 Key Features

- 🔍 **Voltage Monitoring**: Differential amplifiers + ADS1115 for precise per-cell voltage.
- 🌡 **Temperature Sensing**: TEMP36 sensors interfaced via STM32 ADC.
- ⚡ **Current Measurement**: ACS712 Hall-effect current sensor with isolation.
- 💾 **EEPROM Logging**: I²C-based 24LC16B for non-volatile data storage.
- 🕒 **Real-Time Clock**: Onboard RTC for timestamping data entries.
- 📤 **UART Output**: Transmits structured data to PC GUI.
- 🖥 **Graphical User Interface**: C#-based Windows GUI for data visualization.
- 📐 **Custom PCB Design**: Includes voltage scaling, signal conditioning, and connector layout.

---

📊 GUI Features
📡 Displays voltages (BAT1–BAT4)

🌡 Displays temperatures (TEMP1–TEMP4)

⚡ Shows load current in mA

🕒 Structured serial parsing using delimiters (A, B, C…)

🧩 COM port selection and baud rate configuration

🧼 Graceful port handling and disconnect

❌ Error status and diagnostics

---

## 🧩 Embedded Technologies Used

This project integrates multiple core embedded technologies across sensing, communication, signal conditioning, and data management:

---

### 🖥 Microcontroller Platform
- **STM32F411VET6** (ARM Cortex-M4)
  - Central control unit for real-time data acquisition, processing, and communication.
  - Programmed using **STM32CubeIDE** with HAL driver layer and register-level optimization.

---

### 🎛️ Analog Signal Processing
- **Differential Amplifier Circuits** (LM358)
  - Used to measure voltage across each battery cell in a series configuration with **floating references**.
  - Solves the **differential ground** problem by accurately measuring voltage between two non-grounded nodes.
  - Ensures safe voltage levels within the **0–5 V input range** of the **ADS1115 ADC**.
- **Voltage Scaling with Precision Resistors**
  - Brings per-cell voltage (up to 4.2 V) safely within ADC input range while preserving resolution.

---

### 📈 Data Acquisition
- **ADS1115 (16-bit I²C ADC)**
  - Digitizes four differential voltage signals from battery cells.
  - Configured for single-ended mode with programmable gain amplifier (PGA).
- **STM32 Internal ADC (12-bit)**
  - Reads analog output from:
    - **TEMP36** temperature sensors (PC0–PC3)
    - **ACS712** current sensor (PC4)

---

### 💾 Non-Volatile Storage
- **EEPROM 24LC16B (I²C-based)**
  - Used for long-term storage of timestamped voltage, temperature, and current data.
  - Communicates over I2C2 at 100 kHz with burst read/write operations.

---

### 📡 Serial Communication
- **USART2 UART Interface**
  - Structured real-time data transmission to GUI.
  - Custom delimiter-based protocol (`a`, `b`, `c`, ...) for parsing battery parameters on the PC side.

---

### ⏱ Real-Time Clock (RTC)
- STM32’s **built-in RTC peripheral**
  - Used for timestamping battery readings.
  - HAL-based configuration for time and date management.

---

### 🖼 GUI (Graphical User Interface)
- Developed in **C# (Windows Forms)**
  - Reads structured UART stream and displays battery voltages, temperatures, and current.
  - Supports dynamic COM port selection and error-handling during communication.

---

### 🔧 Hardware-Level Techniques
- **Differential Ground Management**
  - Voltage readings are made across series-connected battery cells using **differential amplifiers**, eliminating dependency on a shared ground.
  - Enables **floating reference handling** without damaging ADC or introducing noise.
- **Pull-up Resistors**
  - 4.7 kΩ resistors on I2C lines (SDA, SCL) for stable communication.
- **Decoupling Capacitors**
  - Used for analog sensors and op-amps to reduce noise and transient voltage spikes.
    
---





🧪 Testing Strategy

✅ Hardware unit testing of amplifiers, ADC scaling, EEPROM wiring

✅ Software module testing for each peripheral before integration

✅ Simulated real-world load (~200mA draw) for stress testing

✅ Verification using known reference values


---
