int sensorPin = 2;
volatile long pulse;
unsigned long lastTime;

float volume;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,&Wire, -1);


void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(19200);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
 
}


void loop() {
  volume = 8.82 * pulse;
  if (millis() - lastTime > 1000) {
    pulse = 0;
    lastTime = millis();
  }
  Serial.print(volume);
  Serial.println(" mL/s");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print(volume);
  display.print(" ml/s");

  if(volume>1500){
      tone(9, 1000); 
      delay(1000); 
    }
  else{
      noTone(9); 
      delay(1000);
    }

  delay(400);

  }



void increase() {
  pulse++;
}
