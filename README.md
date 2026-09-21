# ICAMS Environmental Sensor

A Bluetooth Mesh sensor network that monitors air quality, noise, and climate on the ICAMS shop floor to help keep it a safe work environment.

## Hardware

Each node is built on a Seeed Studio XIAO nRF52840, chosen for its small size, low cost, and simple integration.

### Sensors

- DFRobot Gravity Sound Level Meter V2.0: analog sound level (dBA)
- Adafruit SCD-40 breakout (Sensirion SCD40): CO2, temperature, humidity
- Sensirion SEN55: particulate matter (PM1.0 to PM10), VOC index, NOx index, temperature, humidity

### Architecture

Each node will have three sensors. The shop floor will have six nodes communicating with each other over [Bluetooth SIG Mesh](https://www.bluetooth.com/learn-about-bluetooth/feature-enhancements/mesh/). The gateway node will run on the RAK7391 WisGate Connect.

## Software

### Firmware

The node firmware is a Zephyr application built with the nRF Connect SDK (NCS v3.4.1, Zephyr 4.4.2). There is one image for the six nodes, and the gateway will be the AX210N on the Wisgate.

The three sensors are read through Zephyr's sensor subsystem:

- SCD40 uses the in-tree `sensirion,scd4x` driver over I2C.
- SEN55 has no in-tree driver, so an out-of-tree driver lives in `firmware/drivers/sensor/sen5x/` with its devicetree binding in `firmware/dts/bindings/`.
- The sound level meter is analog and is read through the ADC in `src/sensors/sound_level.c`.

### Structure
```
Environmental_Sensor/
├── README.md
├── firmware/                  # one firmware image for sensor-node
│   ├── CMakeLists.txt / Kconfig / prj.conf
│   ├── boards/  (xiao_ble + nrf5340dk overlays)
│   ├── src/  main.c, sensors/, mesh/
│   ├── drivers/sensor/sen5x/
│   └── dts/bindings/sensor/sensirion,sen5x.yaml
└── gateway/                 
```

### Gateway software
