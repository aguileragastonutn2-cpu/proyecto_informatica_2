# Four-Tank Liquid Level Control System

## Project Overview

This project consists of a prototype designed to monitor and control the liquid level in four independent tanks using an Arduino UNO.

The system measures the liquid level using ultrasonic sensors and automatically controls individual valves to prevent overflow.

## Current Features

- Four ultrasonic sensors for independent tank level measurement.
- Liquid level calculation in percentage.
- LCD 16x2 I2C display for real-time monitoring.
- Four servo motors representing individual tank valves.
- Automatic valve closure when a tank reaches 90% capacity.
- LED indicator representing the water pump.
- Manual reset button to restart the filling cycle.

## Simulation

The circuit is designed and tested using Wokwi.

**Wokwi Simulation:**  
https://wokwi.com/projects/481150759719233537

## Hardware

- Arduino UNO
- 4 HC-SR04 ultrasonic sensors
- 4 servo motors
- LCD 16x2 I2C
- LED and 220 Ω resistor
- Pushbutton

## Project Status

**Current stage:** Arduino circuit simulation and automatic tank control.

Further development will include Processing integration, bidirectional serial communication, graphical monitoring, and historical data storage.

## Repository Structure

```text
proyecto_informatica_2/
├── Arduino/
├── Processing/
├── Documentation/
└── README.md
```

## Author

Electronics and Programming Project – UTN
