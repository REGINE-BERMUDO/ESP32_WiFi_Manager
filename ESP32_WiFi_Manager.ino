// Functions that live in wifi.cpp
void wifi_Setup();
void bootpin_Setup();
void wifi_reset_on_bootpressed();
void wifi_keep_alive();

void setup() {
  Serial.begin(115200);
  delay(500);
  bootpin_Setup();
  wifi_Setup();          // connects to saved Wi-Fi, or opens the setup portal
}

void loop() {
  wifi_reset_on_bootpressed();  // hold BOOT 3 s = forget Wi-Fi
  wifi_keep_alive();            // reconnect / re-open portal if Wi-Fi is lost

  // ---- Put your own project code below ----
}