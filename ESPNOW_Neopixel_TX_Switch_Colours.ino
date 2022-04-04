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

// Mode buttons
const int switch_LED_off = D0;  //Switch off Leds
const int switch_LED_white = D1; //Switch Led's to all white
const int switch_LED_pride = D2; // Switch Led's to pride colours

// Button start up states
 int LED_off = 0;  //Switch off Leds
 int LED_white = 0; //Switch Led's to all white
 int LED_pride = 0;
 int active_mode =0; //store for current mode

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
unsigned long longtimerDelay = 3500;  // send readings timer
unsigned long colour_Change = 2000;

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

void colour_off(){
  Greenchange = 255;
    Redchange = 255;
    Bluechange =255;

    myData.green = 0;
    myData.red = 0;
    myData.blue = 0;

    
}

void colour_White(){
  Greenchange = 255;
    Redchange = 255;
    Bluechange =255;

    myData.green = 255;
    myData.red = 255;
    myData.blue = 255;

    
}

//red, orange,yellow,green,blue,purple
void colour_Pride_red(){
    //red
  Greenchange = 255;
    Redchange = 0;
    Bluechange =0;
    myData.green = 255;
    myData.red = 0;
    myData.blue = 0;
}

void colour_Pride_orange(){
    //orange
  Greenchange = 154;
    Redchange = 247;
    Bluechange =5;
    myData.green = 247;
    myData.red = 124;
    myData.blue = 0;
}

void colour_Pride_yellow(){
    //yellow,
  Greenchange = 243;
    Redchange = 247;
    Bluechange =5;
    myData.green = 254;
    myData.red = 254;
    myData.blue = 0;
}

void colour_Pride_green(){
    //green,
  Greenchange = 0;
    Redchange = 255;
    Bluechange =0;
    myData.green = 0;
    myData.red = 255;
    myData.blue = 0;
}

void colour_Pride_blue(){
    //blue,
  Greenchange = 30;
    Redchange = 155;
    Bluechange = 250;
    myData.green = 3;
    myData.red = 3;
    myData.blue = 250;
}

void colour_Pride_purple(){
    //purple
  Greenchange = 9;
    Redchange = 225;
    Bluechange =240;
    myData.green = 225;
    myData.red = 0;
    myData.blue = 250;
}
 
void setup() {
  //Init Mode buttons
  pinMode(switch_LED_off, INPUT);
  pinMode(switch_LED_white, INPUT);
  pinMode(switch_LED_pride, INPUT);
  
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
  
  // set leds off
     myData.green = 0;
    myData.red = 0;
    myData.blue = 0;

// Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));



}
 
void loop() {


  LED_off = digitalRead(switch_LED_off);
  LED_white = digitalRead(switch_LED_white);
  LED_pride = digitalRead(switch_LED_pride);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (LED_off == HIGH ) {active_mode = 0; }; 
  if (LED_white == HIGH ) {active_mode = 1; }; 
  if (LED_pride == HIGH ) {active_mode = 2; }; 
 

  if (active_mode == 0) {colour_off();};
  if (active_mode == 1) {colour_White();};
  if (active_mode == 2) 
{
  //send pride colours
      //red, orange,yellow,green,blue,purple
     colour_Pride_red();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_Pride_orange();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_Pride_yellow();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_Pride_green();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_Pride_blue();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_Pride_purple();
       // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

    colour_White();
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
  delay(colour_Change);

  colour_off();
  // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    esp_now_send(broadcastAddress2, (uint8_t *) &myData, sizeof(myData));
 
  } 
  
  Serial.print("Green: ");
  Serial.println(Greenchange);
  Serial.print("Red: ");
  Serial.println( Redchange);
   Serial.print("Blue: ");
  Serial.println(Bluechange);
   Serial.println();
}
