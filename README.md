# CyberPlants Automated Hydroponics Solution Maintenance and Monitoring

This repository contains instructions for setting up, maintaining, and monitoring the CyberPlants automated hydroponics system. The system includes hardware components like an ultrasonic depth sensor, immersible pump, and Arduino Uno, and allows for remote data access using Coolterm and TeamViewer.

> **Note**: Skip to [Section 3](#section-3-operating-the-system) if the system is intact and no parts are missing.

### Sections
- [Section 1: Hardware Setup](#section-1-hardware-setup)
- [Section 2: Circuit Diagram](#section-2-circuit-diagram)
- [Section 3: Calibration of Ultrasonic Sensor](./Section3_Calibration/Calibration_Instructions.md)
- [Section 4: System Setup](./Section4_SystemSetup/System_Setup_Instructions.md)
- [Section 5: Software Setup](./Section5_SoftwareSetup/Software_Setup_Instructions.md)

---

## Section 1: Hardware Setup

### Required Components
Ensure you have the following components ready before proceeding:

| Quantity | Component                   |
|----------|-----------------------------|
| 1        | Arduino Uno R3             |
| 1        | Ultrasonic Depth Sensor    |
| 1        | LCD                         |
| 2        | Push Buttons                |
| 1        | Immersible Water Pump       |
| 1        | 5V Relay                    |
| 1        | Power Source for Pump       |
| 2        | Float Switches              |
| 1        | Adaptor                     |
| 1        | 1A Fuse with Fuse Holder    |
| 1        | 10k Potentiometer           |
| 1        | 220 Ohm Resistor            |
| 2        | 10 kOhm Resistor            |


---

## Section 2: Circuit Diagram

### Overview
The system involves two primary setups:
1. **Monitoring Systems**: Set up to track solution levels.
2. **Maintaining & Failsafe Systems**: Set up to manage solution levels and prevent overflows.

### Written Schematic

#### Ultrasonic Sensor
- **VCC**: 5V  
- **GND**: GND  
- **TRIG**: D12  
- **ECHO**: D13  

#### LCD
- **VSS**: GND  
- **VDD**: 5V  
- **V0**: 10K potentiometer (1st leg)  
- **RS**: D2  
- **RW**: GND  
- **E**: D3  
- **DB4**: D4  
- **DB5**: D5  
- **DB6**: D6  
- **DB7**: D7  
- **A (or LED+)**: 220 Ohm resistor → 5V  
- **K (or LED-)**: GND  

#### 10K Potentiometer
- **1st Leg**: V0  
- **2nd Leg**: GND  
- **3rd Leg**: 5V  

#### Button 1
- **1st Leg**: 10K Ohm resistor → GND  
- **2nd Leg**: 5V  
- **3rd Leg**: D8  

#### Button 2
- **1st Leg**: 10K Ohm resistor → GND  
- **2nd Leg**: 5V  
- **3rd Leg**: D9  

#### Float Switch 1
- **1st Wire**: A0  
- **2nd Wire (or black wire)**: GND  

#### Float Switch 2
- **1st Wire**:
