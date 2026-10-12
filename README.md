# ESP32 Closed-Loop PID Temperature Control System

Simulation of a closed-loop thermal control system using ESP32, dynamic PWM heater output, I2C LCD telemetry, and Ziegler-Nichols PID tuning.

## 📌 Features
- **Precision Thermal Control:** Dynamic temperature control between 30°C and 50°C.
- **Closed-Loop PID Logic:** Real-time feedback processing ($K_p, K_i, K_d$) to minimize overshoot and steady-state error.
- **PWM Modulation:** Proportional pulse-width modulation for accurate heater power adjustment.
- **Interactive UI & Telemetry:** 16x2 I2C LCD display for live setpoint/actual temperature telemetry and GPIO push-buttons for dynamic adjustment.

## 🛠️ Hardware & Tools
- **Microcontroller:** ESP32
- **Display:** 16x2 I2C LCD
- **Actuator/Sensors:** Push Buttons, PWM Heater Output
- **Simulation Environment:** Wokwi Simulator
- **Programming Language:** C / C++ (Embedded Systems)

## 📐 Tuning Methodology
Tuned using the **Ziegler-Nichols Method** by identifying the ultimate gain ($K_u$) and oscillation period ($T_u$) to calculate stable PID controller gains.
