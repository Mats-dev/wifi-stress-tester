/*
 * WiFi Stress Tester USB Stick
 * Created: 2025-06-12 18:46:05 CEST (UTC+2)
 * Location: Belgium
 * Author: Mats-dev
 * 
 * DISCLAIMER AND WARNING:
 * This code is for EDUCATIONAL AND TESTING PURPOSES ONLY.
 * Use this ONLY on networks you own or have explicit permission to test.
 * Unauthorized interference with networks can be illegal in many jurisdictions.
 * 
 * The purpose of this tool is to test WiFi network resilience and performance
 * under stress conditions. It generates:
 * 1. Multiple fake SSIDs (SSID flooding)
 * 2. UDP broadcast traffic
 * 
 * To stop the device, unplug it from USB power.
 * NO WARRANTY IS PROVIDED. USE AT YOUR OWN RISK.
 */

#include <WiFi.h>
#include <WiFiUdp.h>

// =============== Configuration ===============
// Channel configuration
#define WIFI_CHANNEL 1          // Target WiFi channel
#define MAX_SSIDS 100          // Maximum number of fake SSIDs
#define SSID_REFRESH_MS 1000   // SSID refresh interval

// UDP flood configuration
#define UDP_PACKET_SIZE 1024   // Size of UDP packets
#define UDP_INTERVAL_MS 10     // Packet transmission interval
#define UDP_PORT 12345        // UDP broadcast port

// LED configuration
#define LED_PIN 2
#define LED_BLINK_MS 500      // LED blinks every 0.5 seconds

// =============== Global Variables ===============
unsigned long lastSSIDUpdate;
unsigned long lastUDPSend;
unsigned long lastLEDBlink;
bool ledState = false;
WiFiUDP udp;

// UDP packet buffer
uint8_t packetBuffer[UDP_PACKET_SIZE];

// Random SSID generation characters
const char charset[] = "0123456789"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz";

// =============== Function Declarations ===============
void setupWiFi();
String generateRandomSSID();
void broadcastSSIDs();
void sendUDPTraffic();
void startupBlink();
void handleLED();

// =============== Setup ===============
void setup() {
  // Initialize serial for debugging
  Serial.begin(115200);
  
  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Print startup message
  Serial.println("\n=== WiFi Stress Tester Starting ===");
  Serial.println("WARNING: Educational purposes only!");
  Serial.println("Use only on networks you own/control");
  Serial.println("To stop, unplug the USB device");
  
  // Initialize timers
  lastSSIDUpdate = 0;
  lastUDPSend = 0;
  lastLEDBlink = 0;
  
  // Setup WiFi
  setupWiFi();
  
  // Initialize UDP
  udp.begin(UDP_PORT);
  
  // Fill packet buffer with random data
  for(int i = 0; i < UDP_PACKET_SIZE; i++) {
    packetBuffer[i] = random(256);
  }
  
  // Indicate startup with three quick blinks
  startupBlink();
  
  Serial.println("System initialized and running...");
  Serial.printf("Operating on channel: %d\n", WIFI_CHANNEL);
}

// =============== Main Loop ===============
void loop() {
  // Handle LED blinking
  handleLED();
  
  // Update SSIDs
  if (millis() - lastSSIDUpdate >= SSID_REFRESH_MS) {
    broadcastSSIDs();
    lastSSIDUpdate = millis();
  }
  
  // Send UDP traffic
  if (millis() - lastUDPSend >= UDP_INTERVAL_MS) {
    sendUDPTraffic();
    lastUDPSend = millis();
  }
}

// =============== Function Implementations ===============

void setupWiFi() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  delay(100);
  
  // Set WiFi channel
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
}

String generateRandomSSID() {
  String ssid = "";
  int length = random(8, 21); // Random length between 8 and 20 characters
  
  for (int i = 0; i < length; i++) {
    ssid += charset[random(0, strlen(charset))];
  }
  
  return ssid;
}

void broadcastSSIDs() {
  for (int i = 0; i < MAX_SSIDS; i++) {
    String ssid = generateRandomSSID();
    
    // Create beacon frame
    wifi_config_t ap_config;
    memset(&ap_config, 0, sizeof(wifi_config_t));
    strcpy((char*)ap_config.ap.ssid, ssid.c_str());
    ap_config.ap.ssid_len = ssid.length();
    ap_config.ap.channel = WIFI_CHANNEL;
    ap_config.ap.authmode = WIFI_AUTH_OPEN;
    ap_config.ap.ssid_hidden = 0;
    ap_config.ap.max_connection = 0;
    ap_config.ap.beacon_interval = 100;
    
    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
  }
}

void sendUDPTraffic() {
  IPAddress broadcastIP(255, 255, 255, 255);
  udp.beginPacket(broadcastIP, UDP_PORT);
  udp.write(packetBuffer, UDP_PACKET_SIZE);
  udp.endPacket();
}

void startupBlink() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void handleLED() {
  if (millis() - lastLEDBlink >= LED_BLINK_MS) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastLEDBlink = millis();
  }
}
