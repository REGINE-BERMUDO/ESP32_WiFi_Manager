#include <Arduino.h>
#include <WiFiManager.h>   // by tzapu

#define BOOTPIN      0           // BOOT button
#define HELD         3000        // hold time (ms) to erase saved Wi-Fi
#define PORTAL_NAME  "ESP32-Setup"
#define PORTAL_PASS  ""          // "" = open hotspot, or 8+ characters

WiFiManager manager;

static void connectOrOpenPortal() {
  bool ok;
  if (strlen(PORTAL_PASS) == 0) ok = manager.autoConnect(PORTAL_NAME);
  else                          ok = manager.autoConnect(PORTAL_NAME, PORTAL_PASS);

  if (ok) {
    Serial.println("Connected to Wi-Fi!");
    Serial.print("Network : "); Serial.println(WiFi.SSID());
    Serial.print("IP      : "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("Could not connect. Restarting...");
    delay(1000);
    ESP.restart();
  }
}

void wifi_Setup() {
  WiFi.mode(WIFI_STA);
  manager.setConnectTimeout(20);
  manager.setConfigPortalTimeout(0);   // portal stays open until configured
  manager.setConnectRetries(2);
  connectOrOpenPortal();
}

void bootpin_Setup() {
  pinMode(BOOTPIN, INPUT_PULLUP);
}

void wifi_reset_on_bootpressed() {
  bool pressed = !digitalRead(BOOTPIN);
  static unsigned long pressedTime = 0;
  static bool counting = false;

  if (pressed && !counting) {
    pressedTime = millis();
    counting = true;
  }
  if (!pressed) counting = false;

  if (counting && millis() - pressedTime >= HELD) {
    counting = false;
    Serial.println("BOOT held 3 s: erasing saved Wi-Fi, restarting...");
    manager.resetSettings();
    delay(500);
    ESP.restart();
  }
}

void wifi_keep_alive() {
  static unsigned long lastCheck = 0;
  static uint8_t fails = 0;

  if (millis() - lastCheck < 10000) return;
  lastCheck = millis();

  if (WiFi.status() == WL_CONNECTED) { fails = 0; return; }

  fails++;
  Serial.printf("Wi-Fi lost (attempt %u/3)\n", fails);
  WiFi.reconnect();

  if (fails >= 3) {
    fails = 0;
    Serial.println("Opening setup portal so you can pick a new network...");
    connectOrOpenPortal();
  }
}