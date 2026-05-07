//Author: Abdallah Brahim
//Dawson College - EET
//Date 5/7/2026

//Libaries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //Library to enable graphics
#include <Adafruit_SSD1306.h> //Library for OLED
#include <MFRC522.h> //Library for RFID

//Set screen size
Adafruit_SSD1306 oledscr = Adafruit_SSD1306(128, 64, &Wire); 



//Set Variables
long buzzerPin = 4;
long buttonPin = 5;
#define RST_PIN 9
#define SS_PIN 10

//create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  SPI.begin(); //initialize SPI bus
  oledDebut();
  mfrc522.PCD_Init(); //initialize MFRC522 card
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  oledscr.setTextSize(3);
  oledscr.setTextColor(WHITE);
  oledscr.println("Gay");
  oledscr.display();
}


void oledDebut(){
  oledscr.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Address 0x3C for 128x64
  oledscr.display();
  delay(1000);
  oledscr.clearDisplay();
}