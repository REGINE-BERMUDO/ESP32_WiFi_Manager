# ESP32_WiFi_Manager
# Author
Name: Ma. Regine A. Bermudo

Assigned Number: 28 (BCA188-ESP32-28)

# Description
This project lets an ESP32 connect to any Wi-Fi network without writing the network name or password in the code. The ESP32 creates its own setup hotspot, and the Wi-Fi details are entered once from a phone through a web portal. They are then saved in the ESP32's flash memory, so the board reconnects by itself after every restart. The project uses the **WiFiManager** library by tzapu.

# Features
- No hardcoded Wi-Fi name or password
- Setup portal opens automatically when no saved network is available
- Saved credentials survive restarts and power loss
- Holding the BOOT button for 3 seconds erases the saved Wi-Fi
- Automatically retries when the connection is lost, then reopens the setup portal after about 30 seconds so a new network can be chosen

# Hardware and Software
| Item | Details |
| :--- | :--- |
| Board | ESP32 Dev Module |
| IDE | Arduino IDE 2.x |
| Board package | esp32 by Espressif Systems |
| Library | WiFiManager by tzapu |
| Other | Phone or laptop with Wi-Fi |

# How It Works
1. On startup, the ESP32 tries to connect to the Wi-Fi network saved in its memory.
2. If there is no saved network, or the connection fails, it creates a hotspot called **ESP32-Setup**.
3. The user joins that hotspot on a phone, and the setup page opens at `192.168.4.1`.
4. The user picks a network from the scanned list, enters its password, and saves.
5. The ESP32 connects, stores the credentials, and prints the network name and IP address in the Serial Monitor.
6. In `loop()`, the code watches the BOOT button (GPIO 0). Holding it for 3 seconds erases the saved network and restarts the board.
7. If the Wi-Fi is lost for about 30 seconds, the setup portal opens again.

# How to Use
1. Install the **esp32** board package and the **WiFiManager** library (by tzapu).
2. Open `ESP32_WiFi_Manager.ino` in the Arduino IDE.
3. Select **ESP32 Dev Module** and the correct port, then click **Upload**.
4. Open the Serial Monitor at **115200 baud**.
5. On your phone, connect to the Wi-Fi called **ESP32-Setup**.
6. Open `192.168.4.1` in a browser if the page does not appear by itself.
7. Tap **Configure WiFi**, choose your network, enter the password, and tap **Save**.
8. To use a different network later, hold the BOOT button for 3 seconds and repeat steps 5 to 7.

# Laboratory Report

### Observation

<div align="center">

| Task | What to do | What I have observed |
| :--- | :--- | :--- |
| First boot | Upload the code and open the Serial Monitor | The ESP32 created the **ESP32-Setup** hotspot because no network was saved |
| Configure Wi-Fi | Join the hotspot, choose a network, enter the password | The ESP32 connected and printed the network name and IP address in the Serial Monitor |
| Restart | Press the EN (reset) button | The ESP32 reconnected by itself without opening the portal |
| Wrong password | Enter a wrong password on the setup page | The connection failed and the setup portal opened again |
| Reset settings | Hold the BOOT button for 3 seconds | The saved Wi-Fi was erased and the board restarted into the setup portal |
| Different network | Reset the board, then connect to a phone hotspot | The ESP32 connected to the new network without any change to the code |
| Connection lost | Turn off the router or hotspot | The ESP32 retried, then reopened the setup portal after about 30 seconds |

</div>
### Main Feature of WiFiManager
The WiFiManager library by tzapu handles Wi-Fi connections on ESP32 and ESP8266 boards. Its main feature is that Wi-Fi can be configured or changed through a web portal on a phone, without rewriting or re-uploading any code.

### Limitation
The ESP32 still needs the password of a secured network the first time it connects to it. The portal is how that password is given to the board without writing it in the code. The ESP32 supports 2.4 GHz networks only, and it cannot log in to Wi-Fi that needs a browser sign-in page, such as hotel Wi-Fi.

### Conclusion
The ESP32 can connect to different Wi-Fi networks without changing the code. The credentials are entered once through the setup portal and stored in the board's flash memory. They can be erased with the BOOT button, so the board is easy to move between networks.

### Images
<div align="center">

<img width="828" height="1228" alt="image" src="https://github.com/user-attachments/assets/90043a62-acdf-4299-93d3-7485e07805a4" />

<img width="828" height="1792" alt="image" src="https://github.com/user-attachments/assets/374c2236-81f6-4c5f-8d6f-0b6b82b6bcfc" />

<img width="975" height="530" alt="image" src="https://github.com/user-attachments/assets/0753ec38-9ba2-4ee5-99c7-0695a560493e" />

Pressed boot for 3 seconds:
<img width="975" height="609" alt="image" src="https://github.com/user-attachments/assets/21e230da-d94d-4da3-b971-cca33e73661e" />


</div>

# References

- [WiFiManager library by tzapu](https://github.com/tzapu/WiFiManager)
- [ESP32 Useful Wi-Fi Functions (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/)
