#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);

void setup() 
{
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kartinizi okutun");
  SPI.begin();      
  mfrc522.PCD_Init();  
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  lcd.clear();
  if (content.substring(1) == "60 9E EC A2") 
  {
    lcd.setCursor(0,0);
    lcd.print("Giris");
    lcd.setCursor(0,1);
    lcd.print("Basarili");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kartinizi okutun");
  }
 else{
    lcd.setCursor(0,0);
    lcd.print("Giris");
    lcd.setCursor(0,1);
    lcd.print("Basarisiz");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kartinizi okutun");
  }
} 
