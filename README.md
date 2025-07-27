# 🔋 Battery Monitoring System – STM32F411 Project

> Developed by: **Vaishnavi Jadhav** & **Darshan Salian**  
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


🧪 Testing Strategy

✅ Hardware unit testing of amplifiers, ADC scaling, EEPROM wiring

✅ Software module testing for each peripheral before integration

✅ Simulated real-world load (~200mA draw) for stress testing

✅ Verification using known reference values


---
