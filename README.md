# 🌱 Greenhouse Management System using Embedded Systems

A smart greenhouse automation system built using ESP32 and IoT technologies to monitor and control environmental conditions like temperature, humidity, soil moisture, CO levels, and light intensity. It uses MQTT to send data to a Node-RED server, stores it in AdmiralDB, and visualizes it on Grafana using InfluxDB. Based on threshold values, actuators like fans and water pumps are automatically triggered.

---

## 🚀 Features

- Real-time monitoring of:
  - 🌡️ Temperature & Humidity
  - 🌱 Soil Moisture
  - 💡 Light Intensity
  - 🛢️ CO Gas Levels
- Wireless data transmission using MQTT protocol
- Node-RED dashboard for data routing
- Cloud storage with AdmiralDB and InfluxDB
- Data visualization using Grafana
- Actuator control based on threshold: Fan & Water Pump
- Scalable and suitable for agricultural applications

---

## 🛠️ Hardware & Tools Used

- **ESP32** – Microcontroller with Wi-Fi support
- **DHT11 / DHT22** – Temperature & Humidity Sensor
- **Soil Moisture Sensor**
- **LDR (Light Dependent Resistor)** – Light sensor
- **MQ-7 or MQ-135** – CO Gas Sensor
- **Relay Module** – For controlling fan and pump
- **Water Pump & Fan** – Actuators
- **Node-RED** – For flow control and logic
- **MQTT Broker (e.g., Mosquitto)** – Communication protocol
- **AdmiralDB** – Cloud database
- **InfluxDB + Grafana** – Real-time data visualization

---

## 📐 System Architecture



## 🧪 How It Works

1. ESP32 reads data from all sensors.
2. It publishes sensor data to MQTT broker.
3. Node-RED receives the data and stores it in AdmiralDB & InfluxDB.
4. Grafana fetches and displays data on a real-time dashboard.
5. Based on thresholds (set in Node-RED), ESP32 receives commands to switch ON/OFF the fan or water pump.

---

