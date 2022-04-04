#include <ESP8266WiFi.h>
#include <espnow.h>

#include<Adafruit_NeoPixel.h>
#define LED_PIN D4 // WS2812 data pin
#define LED_COUNT 16 // Number of LEDs
Adafruit_NeoPixel strip= Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
int sat = 255;
int r =0;
int g =0;
int b =0;


void setup() {
  // put your setup code here, to run once:
 // Initialize Serial Monitor
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  Serial.print("Green: ");
  Serial.println(g);
  Serial.print("Red: ");
  Serial.println(r);
   Serial.print("Blue: ");
  Serial.println(b);
  // put your main code here, to run repeatedly:
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
  
}
