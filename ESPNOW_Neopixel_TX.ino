/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
int Greenchange = 0;
int Redchange = 0;
int Bluechange = 0;

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x5C, 0xCF, 0x7F, 0xB8, 0x59, 0xD3};
uint8_t broadcastAddress2[] = {0x84, 0xF3, 0xEB, 0x8E, 0x57, 0xCD};//84:F3:EB:8E:57:CD

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
 int green = Greenchange;
 int red = Redchange;
 int blue = Bluechange;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 500;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    
    myData.green = Greenchange;
    myData.red = Redchange;
    myData.blue = Bluechange;
   

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
    
  }
  Greenchange += 22;
    Redchange += 48;
    Bluechange +=4;
    if (Redchange > 255)Redchange = 0;
    if (Greenchange > 255)Greenchange = 0;
    if (Bluechange > 255)Bluechange = 0 ;

    Serial.print("Green: ");
  Serial.println(Greenchange);
  Serial.print("Red: ");
  Serial.println( Redchange);
   Serial.print("Blue: ");
  Serial.println(Bluechange);
   Serial.println();
}
