# WiFi Stress Tester USB Stick

**Created:** 2025-06-12 18:46:05 CEST (UTC+2)  
**Author:** Mats-dev  
**Location:** Belgium

## ⚠️ IMPORTANT DISCLAIMER

This project is for **EDUCATIONAL AND TESTING PURPOSES ONLY**. Use this tool only on networks you own or have explicit permission to test. Unauthorized interference with networks can be illegal in many jurisdictions.

## 📝 Project Description

This project is a compact, USB-powered device designed to simulate WiFi congestion and interference. It's built using an ESP32-S3 microcontroller and is intended for testing the stability and performance of your own WiFi network under stressful conditions.

### Features

- Automatic operation on USB power
- SSID flooding (generates multiple fake networks)
- UDP broadcast traffic generation
- Fixed channel operation
- Status LED indicators
- No buttons or setup required

## 🛠️ Hardware Requirements

- ESP32-S3 based board
- USB power source (computer, charger, or power bank)
- Built-in LED on GPIO2 (can be modified in code)

## 📥 Installation

1. Install Arduino IDE
2. Add ESP32 board support to Arduino IDE:
   - Open Arduino IDE
   - Go to File -> Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
   - Go to Tools -> Board -> Boards Manager
   - Search for "esp32" and install "ESP32 by Espressif Systems"

3. Configure Arduino IDE:
   - Board: "ESP32S3 Dev Module" (or your specific board)
   - Upload Speed: "921600"
   - USB CDC On Boot: "Enabled"
   - USB DFU On Boot: "Enabled"
   - USB Mode: "Hardware CDC and JTAG"
   - Flash Size: "4MB"
   - Partition Scheme: "Default"

4. Upload the code:
   - Open `wifi_stress_tester.ino`
   - Select the correct port
   - Click Upload

## 🔧 Configuration

The following parameters can be modified in the code:

```cpp
#define WIFI_CHANNEL 1          // Target WiFi channel
#define MAX_SSIDS 100          // Maximum number of fake SSIDs
#define SSID_REFRESH_MS 1000   // SSID refresh interval
#define UDP_PACKET_SIZE 1024   // Size of UDP packets
#define UDP_INTERVAL_MS 10     // Packet transmission interval
#define UDP_PORT 12345        // UDP broadcast port
#define LED_BLINK_MS 500      // LED blinks every 0.5 seconds
```

## 📋 Usage

1. **Starting**: 
   - Simply plug the device into any USB power source
   - The LED will blink 3 times quickly to indicate startup
   - Device begins operating immediately

2. **Operation**:
   - LED blinks continuously every 0.5 seconds
   - Continuously generates fake SSIDs
   - Sends UDP broadcast packets
   - Operates on configured WiFi channel

3. **Stopping**:
   - Unplug from USB power
   - No other shutdown method is provided

## 📊 LED Indicators

- **Startup**: Three quick blinks (100ms on/off)
- **Normal Operation**: Continuous blinking every 0.5 seconds
- **No Light**: Device is powered off or malfunctioning

The LED provides visual confirmation that the device is working correctly. During normal operation, you should see the LED blinking at a steady 0.5-second interval. If the LED stops blinking but the device is still plugged in, this indicates a potential issue with the device's operation.

## ⚠️ Safety Notes

1. Only use on networks you own or have permission to test
2. The device can cause significant interference on the selected WiFi channel
3. Some WiFi devices may experience connectivity issues during testing
4. Consider local regulations regarding WiFi interference

## 🔍 Monitoring

You can monitor the device's operation using the Arduino Serial Monitor:
- Baud Rate: 115200
- Startup messages
- Channel confirmation
- Operation status

## ⚖️ Legal Disclaimer

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY.

Use of this tool to interfere with networks you do not own or have explicit permission to test may be illegal in your jurisdiction. The author(s) assume no liability for misuse of this tool.

## 🤝 Contributing

This is an educational project. If you have suggestions for improvements while maintaining the educational purpose, please feel free to:
1. Fork the repository
2. Create your feature branch
3. Submit a pull request

## 📜 License

This project is released under the MIT License. See the LICENSE file for details.
