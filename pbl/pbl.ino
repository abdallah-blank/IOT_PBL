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
#define RST_PIN 49
#define SS_PIN 53
int wrongAttempts = 3;



//create MFRC522 instance.
MFRC522 rfid(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;  


void setup() {
  Serial.begin(9600);
  SPI.begin(); //initialize SPI bus
  oledDebut();
  rfid.PCD_Init(); //initialize MFRC522 card
  pinMode(buzzerPin, OUTPUT);
  lockedDoor();
  
}

void loop() {
  //RFID startup part (From example code)
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
  return;  
  // Verify if the NUID has been read
  if ( ! rfid.PICC_ReadCardSerial())
  return; 
  String tag = getHexString(rfid.uid.uidByte, rfid.uid.size);
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  rfid.PICC_HaltA(); // Halt PICC
  
  
  


  //Door unlocking/locking. Logic
  bool isUnlocked = keyChecker(tag);
  //When RFID reading matches, unlocks door for 5 seconds
  if(isUnlocked){
    oledscr.setCursor(0,0);
    oledDisplay(3, WHITE, "Door");
    oledscr.setCursor(0, 25);
    oledDisplay(3,WHITE,"Open");
    oledscr.display();
    delay(300);
    for (int i = 5; i > 0; i--) { //Loop for timer (how long door stays unlocked)
      Serial.println("Door closing in: ");
      Serial.println(i);
      delay(1000);
    }
    //Sets everything to default (Locked, 3 attempts, no buzzer)
    oledscr.setCursor(0, 0);
    oledscr.clearDisplay();
    isUnlocked = false;
    wrongAttempts=3;
    digitalWrite(buzzerPin, LOW);  
  }
    //When Card read is wrong, buzzes a little, after 3 wrong readings starts buzzing until correct key is used + displays intruder alert)
  if(!keyChecker(tag)){
    wrongAttempts--;
    Serial.print("You have ");
    Serial.print(wrongAttempts);
    Serial.println(" attempts left");
    oledscr.clearDisplay();

    digitalWrite(buzzerPin, 1);
    delay(150);
    digitalWrite(buzzerPin,0);

   if(wrongAttempts == 0){
    Serial.println("No attempts Left");
    delay(200);
    oledDisplay(2, WHITE, "INTRUDER");
    oledscr.setCursor(0, 25);
    oledDisplay(2,WHITE,"ALERT!!!");
    oledscr.display();
    delay(100);
    digitalWrite(buzzerPin, 1);
   }
  }
  else{
    lockedDoor();
  }
 

}



//Displays "DOOR LOCKED" on OLED display
void lockedDoor(){
    oledscr.setCursor(0,0);
    oledDisplay(3, WHITE ,"Door");
    oledscr.setCursor(0, 25);
    oledDisplay(3,WHITE,"Locked");
    oledscr.display();
    oledscr.clearDisplay();
    oledscr.setCursor(0, 0);
}


//Prints text to the OLED display
void oledDisplay(int size,char color,char text[]){
  oledscr.setTextSize(size);
  oledscr.setTextColor(color);
  oledscr.println(text);

}

//Starts the OLED display
void oledDebut(){
  oledscr.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Address 0x3C for 128x64
  oledscr.display();
  delay(1000);
  oledscr.clearDisplay();
}


//Get the RFID card tag in a Hex String format (BY CHATGPT)
String getHexString(byte *buffer, byte bufferSize) {
  String hexString = "";

  for (byte i = 0; i < bufferSize; i++) {
    if (buffer[i] < 0x10) {
      hexString += "0"; // leading zero
    }
    hexString += String(buffer[i], HEX);
  }

  hexString.toUpperCase(); // optional
  return hexString;

}

//Check if the correct key is used
bool keyChecker(String tagged){
  if(tagged == "6C7D3A5C"){
    oledscr.clearDisplay();
    return true;
  }
  else{
    oledscr.clearDisplay();
    return false;
  }
}


