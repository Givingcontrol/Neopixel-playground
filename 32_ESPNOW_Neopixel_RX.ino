/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

#include<Adafruit_NeoPixel.h>
#define LED_PIN 23 // WS2812 data pin
#define LED_COUNT 24 // Number of LEDs
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
int sat = 255;
int r =0;
int g =0;
int b =0;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int green ;
 int red ;
 int blue;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

   int g = myData.green;
   int r = myData.red ;
    int b = myData.blue ;
  //int br = myData.brt;
  //int hue = myData.hue;
  
  
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Green: ");
  Serial.println(g);
  Serial.print("Red: ");
  Serial.println(r);
   Serial.print("Blue: ");
  Serial.println(b);
   Serial.println();

  strip.setBrightness(255);
  uint32_t color = strip.Color(r, g, b);
  strip.fill(color, 0, LED_COUNT);
  strip.show(); 
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
 // esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
/*
 //  strip.setBrightness(255);
  uint32_t color = strip.Color(r,g, b);
  strip.fill(color, 0, LED_COUNT);
  strip.show(); 
  delay(100);
  r++;
  g+=4;
  b+=6;
  if (r > 255)r = 0;
  if (g > 255)g = 0;
  if (b > 255)b = 0, r = 150;
  */
}
