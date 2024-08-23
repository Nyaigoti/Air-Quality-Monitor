
# Air Quality Monitor

This project is an IoT-based Air Quality Monitor that measures temperature, humidity, and gas levels (using the MQ-2 sensor) and displays the data on an LCD screen. The data is also sent to the Blynk IoT platform for remote monitoring.


## Features
- Measures temperature and humidity using the DHT11 sensor.
- Detects gas levels using the MQ-2 gas sensor.
- Displays the collected data on a 16x2 I2C LCD screen.
- Sends real-time data to the Blynk platform for remote monitoring.
## Components Used
- ESP32 Microcontroller
- DHT11 Temperature and Humidity Sensor
- MQ-2 Gas Sensor
- 16x2 I2C LCD Display
- Blynk IoT Platform
## Wiring
1. **ESP32 Pinout**:
    - DHT11: Data pin connected to GPIO 2.
    - MQ-2: Analog output connected to A0.
    - LCD: I2C connected to SDA (GPIO 21) and SCL (GPIO 22).
    
2. **Power Supply**:
    - Connect the sensors and LCD to the 3.3V and GND pins of the ESP32.
## Installation
1. **Blynk Setup**:
    - Create a new project in Blynk.
    - Set up the ESP32 device.
    - Use the following Virtual Pins:
        - V0 for Temperature
        - V1 for Humidity
        - V2 for Gas levels
    - Generate and copy the Blynk Auth Token.

2. **Library Installation**:
    - Install the following libraries in Arduino IDE:
        - Blynk library
        - DHT Sensor library
        - LiquidCrystal I2C library

3. **Code Setup**:
    - Replace the `BLYNK_AUTH_TOKEN`, `ssid`, and `pass` variables with your Blynk Auth Token and Wi-Fi credentials.
    - Upload the code to the ESP32.
## Usage
1. Power on the ESP32.
2. The LCD screen will display "Air Monitoring" and then begin showing the real-time temperature, humidity, and gas levels.
3. Monitor the data remotely using the Blynk app.