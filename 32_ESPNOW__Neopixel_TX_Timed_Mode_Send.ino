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
int Greenchange = 0;
int Redchange = 0;
int Bluechange = 0;

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress1[] = {0x34, 0x94, 0x54, 0x34, 0xF5, 0xF0};//34:94:54:34:F5:F0
uint8_t broadcastAddress2[] = {0x34, 0x94, 0x54, 0x35, 0x29, 0x58};//34:94:54:35:29:58
uint8_t broadcastAddress3[] = {0x34, 0x94, 0x54, 0x35, 0x29, 0x30};// 34:94:54:35:29:30
uint8_t broadcastAddress4[] = {0x34, 0x94, 0x54, 0x35, 0x39, 0x8C};//34:94:54:35:39:8C
uint8_t broadcastAddress5[] = {0x34, 0x94, 0x54, 0x36, 0x0F, 0xF8};//34:94:54:36:0F:F8


// Mode buttons
const int switch_LED_off = 15;  //Switch off Leds
const int switch_LED_white = 23; //Switch Led's to all white
const int switch_LED_pride = 22; // Switch Led's to pride colours

// Button start up states
 int LED_off = 0;  //Switch off Leds
 int LED_white = 0; //Switch Led's to all white
 int LED_pride = 0;
 int active_mode = 0; //store for current mode

//Timer variables
int time_now;
int time_change = 120000 ;// seconds X 1000
 
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
 int green = Greenchange;
 int red = Redchange;
 int blue = Bluechange;
 int sent_mode = 0;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

unsigned long lastTime = 0;  
unsigned long timerDelay = 500;  // send readings timer
unsigned long longtimerDelay = 3500;  // send readings timer
unsigned long colour_Change = 2000;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 

void colour_off(){
  Greenchange = 255;
    Redchange = 255;
    Bluechange =255;

    myData.green = 0;
    myData.red = 0;
    myData.blue = 0;
    myData.sent_mode = 0;

    
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
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  //esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
 // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
     /// register fourth peer
  memcpy(peerInfo.peer_addr, broadcastAddress4, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
     /// register fifth peer
  memcpy(peerInfo.peer_addr, broadcastAddress5, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  // set leds off
     myData.green = 0;
    myData.red = 0;
    myData.blue = 0;

// Send message via ESP-NOW
    //esp_err_t result = 
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));

}
 
void loop() {

 LED_off = digitalRead(switch_LED_off);
  LED_white = digitalRead(switch_LED_white);
  LED_pride = digitalRead(switch_LED_pride);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (LED_off == HIGH )  {active_mode = 1; }; 
  if (LED_white == HIGH ) {active_mode = 2; }; 
  if (LED_pride == HIGH )  {active_mode = 3;};
       
       
       // Send message via ESP-NOW
   //esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));// {active_mode = 3; }; 
 

  if (active_mode == 1) {
    Serial.print("currentMode: ");
    Serial.println("Off" );
  
   
    colour_off();
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
   
    };
    
  if (active_mode == 2) {
    Serial.print("currentMode: ");
    Serial.println("White");
    time_now = millis();
    colour_White();
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
      if (time_now > time_change) {
        int sent_mode = 3;  
        esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
        }
      else {colour_White();}  
    };
    
  if (active_mode == 3) 
{
   Serial.print("currentMode: ");
    Serial.println("Pride");

     
    myData.sent_mode = 3;
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
}
   /*
   delay(200);
  //send pride colours
      //red, orange,yellow,green,blue,purple
  
     colour_Pride_red();
  
       // Send message via ESP-NOW
   esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);
  
 
  colour_Pride_orange();
  
       // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);
  
  
  colour_Pride_yellow();
  
       // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);
  
  
  colour_Pride_green();
  
       // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);
  
 
  colour_Pride_blue();
  
       // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);

 
  colour_Pride_purple();
  
       // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(struct_message));
  delay(colour_Change);

   
  
  }; 
  /*
  Serial.print("Mode: ");
  Serial.println(active_mode);
  Serial.print("Green: ");
  Serial.println(Greenchange);
  Serial.print("Red: ");
  Serial.println( Redchange);
   Serial.print("Blue: ");
  Serial.println(Bluechange);
   Serial.println();
 */  
   delay(100);

}
