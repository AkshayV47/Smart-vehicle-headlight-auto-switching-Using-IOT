# Smart-vehicle-headlight-auto-switching-Using-IOT

🚗 Smart Vehicle Headlight Auto Switching System using ESP8266
📌 Project Overview

The Smart Vehicle Headlight Auto Switching System is an IoT-based solution designed to automatically control vehicle headlights based on surrounding light conditions. Using an LDR sensor, the system intelligently switches headlights between ON and OFF modes to improve driving safety and reduce driver effort.

The system supports both automatic and manual control, and can be monitored and controlled remotely using the Blynk IoT platform. This makes it suitable for modern smart vehicle and intelligent transportation applications.

🎯 Key Features

🌗 Automatic headlight switching using LDR sensor

🎛️ Manual headlight control via Blynk IoT

🌐 WiFi-enabled control using ESP8266

💡 Dual light output (Light Pad – 2)

⚡ Reliable operation with regulated Power Supply

🔄 Supports Automatic + Manual modes

🚘 Enhances night driving safety

🛠️ Components Used

ESP8266 (NodeMCU)

LDR Sensor

Light Pad / Headlight Module (2 outputs)

Power Supply Module

Relay / Driver Circuit

Blynk IoT Platform

Connecting Wires & Resistors

⚙️ Working Principle

The LDR sensor continuously monitors ambient light intensity.

The ESP8266 processes the sensor data.

In Automatic Mode:

Headlights turn ON in low-light conditions

Headlights turn OFF in sufficient daylight

In Manual Mode:

Headlights can be controlled directly from the Blynk app

The system seamlessly switches between manual and automatic modes as selected by the user.

🔁 System Flow
LDR Sensor → ESP8266 → Light Intensity Check
                          ↓
              Automatic / Manual Mode
                          ↓
                  Headlight Control
                          ↓
                    Vehicle Lighting

🌍 Applications

Smart vehicles

Two-wheelers and four-wheelers

Automotive safety systems

Smart transportation solutions

IoT-based vehicle automation

🚀 Advantages

Improves road safety

Reduces driver distraction

Saves energy

Easy to install and use

Low-cost IoT solution

📌 Future Enhancements

High-beam / low-beam auto switching

Oncoming vehicle detection

Mobile alerts and diagnostics

CAN bus integration

Voice control support

📂 Repository Contents

ESP8266 source code

Circuit diagram

Blynk dashboard setup

System flowchart

Project documentation
