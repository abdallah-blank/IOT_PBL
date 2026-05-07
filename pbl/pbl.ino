#include <SSD1306.h> //Library for OLED
#include <SPI.h>
#include <MFRC522.h> //Library for RFID

long buzzerPin = 4;
long buttonPin = 5;
#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN); //create MFRC522 instance.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin(); //initialize SPI bus
  mfrc522.PCD_Init(); //initialize MFRC522 card
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
