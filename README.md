# ICAMS Environmental Sensor

A Bluetooth Mesh sensor network that monitors air quality, noise, and climate on the ICAMS shop floor to help keep it a safe work environment.

## Hardware

Each node is built on a Seeed Studio XIAO nRF52840, chosen for its small size, low cost, and simple integration.

## Sensors

- DFRobot Gravity Sound Level Meter V2.0: analog sound level (dBA)
- Adafruit SCD-40 breakout (Sensirion SCD40): CO2, temperature, humidity
- Sensirion SEN55: particulate matter (PM1.0 to PM10), VOC index, NOx index, temperature, humidity

### Architecture

Each node will have three sensors. The shop floor will have six nodes communicating with each other over [Bluetooth SIG Mesh](https://www.bluetooth.com/learn-about-bluetooth/feature-enhancements/mesh/). A gateway node bridges the mesh to a RAK7391 WisGate Connect, where a Python script in a Docker container collects the readings and publishes them to the Mosquitto MQTT broker.