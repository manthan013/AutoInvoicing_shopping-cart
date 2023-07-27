#include <Arduino.h>
#include <Wire.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define buttonpin 7

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 6
#define GREEN 5
#define YELLOW 4
MFRC522 mfrc522(SS_PIN,RST_PIN);
LiquidCrystal_I2C lcd(0X27, 16, 2);

char input[12];
int count = 0;

int c=0;
int a=0;
int a2=0;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
int b1=0;
int b2=0;
int b3=0;
int b4=0;
int balance_amt=1000;
int buttonstate=0;


double total = 0;
int count_prod = 0;

void setup ()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

 
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Wire.begin();
  lcd.setCursor(0, 0);
  lcd.print("AUTOMATIC BILLING");
  delay (2000);
  lcd.setCursor(0, 1);
  lcd.print("SHOPPING CART ");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  delay (2000);
  lcd.setCursor(3, 1);
  lcd.print("SUPER MARKET");
  delay (2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ADD MASTER CARD");
 
 
}
  void loop()
{
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    String content= "";                                                        //to store UID od RFID tags
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));    //extract UID from data blocks of RFID tags
        content.concat(String(mfrc522.uid.uidByte[i], HEX));                   //convert UID to hexadecimal values
    }
    content.toUpperCase();                                                     //convert hexadecimal UID to uppercase
if (content.substring(1) == "ED 1A 68 89" && a==0 && c==0)                         //to check if user checks in with his master card
 
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Name:RAHUL");                                               //print customer data
        lcd.setCursor(0,1);
        lcd.print("Blance=");                                                 //print customers balance amount in the master card
        lcd.setCursor(8,1);
        lcd.print(balance_amt);
        Serial.println("Name:RAHUL");
        Serial.println("Balance=");
        Serial.print(balance_amt);
        Serial.println();
        a=1;
        //to indicate master card is detected
        delay(3000);
    }
  if(content.substring(1) == "82 AE 68 89" && a==1 && b1==0)             //to check if item is added

    {
        Serial.println("MILK ADDED");
        Serial.println("Price=Rs.60");
        Serial.println();
        Serial.println();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MILK ADDED");                                                 //to print details of added item
        lcd.setCursor(0,1);
        lcd.print("Price=Rs.60");
        delay(1000);
        digitalWrite(GREEN,HIGH);
        digitalWrite(BUZZER,HIGH);
        digitalWrite(YELLOW,LOW);
         delay(1000);
        digitalWrite(BUZZER,LOW);
        digitalWrite(GREEN,LOW);
    
        total=total+60;                                                        //adding item price to total amount
        b1=1;                                                                   //to indicate item is added
        delay(3000);
          c=1;                                             //adding item's weight to total weight
    }
    else if(content.substring(1) == "82 AE 68 89" && a==1 && b1==1)             //to check if item is removed
    {
        Serial.println("MILK REMOVED");
        Serial.println("Price = Rs.60");
        Serial.println();
        Serial.println();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MILK REMOVED");                                              //to print details of removed item
        lcd.setCursor(0,1);
        lcd.print("Price=Rs.60");
        delay(1000);
        digitalWrite(GREEN,LOW);
        digitalWrite(BUZZER,HIGH);
        digitalWrite(YELLOW,HIGH);
         delay(1000);
        digitalWrite(BUZZER,LOW);
        digitalWrite(YELLOW,LOW);
        total=total-60;                                                       //subtracting item price from total amount
        b1=0;                                                                  //to indicate item is removed
        delay(3000);
         c=1;                                          //subtracting item's weight from total weight
    }
else if(content.substring(1) == "04 80 18 5A 64 66 84" && a2==0 && b2==0)             //to check if item is added
    {
        Serial.println("Butter milk ADDED");
        Serial.println("Price = Rs.20");
        Serial.println();
        Serial.println();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Butter milk");                                                 //to print details of added item
        lcd.setCursor(0,1);
        lcd.print("Price=Rs.20");
        delay(1000);
        digitalWrite(GREEN,HIGH);
        digitalWrite(BUZZER,HIGH);
        digitalWrite(YELLOW,LOW);
         delay(1000);
        digitalWrite(BUZZER,LOW);
        digitalWrite(GREEN,LOW);
        total=total+20;                                                        //adding item price to total amount
        b2=1;                                                                   //to indicate item is added
        delay(3000);
          c=1;                                             //adding item's weight to total weight
    }
    else if(content.substring(1) == "04 80 18 5A 64 66 84" && a2==0 && b2==1)             //to check if item is removed
    {
        Serial.println("Butter milk removed");
        Serial.println("Price = Rs.20");
        Serial.println();
        Serial.println();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Butter milk removed");                                              //to print details of removed item
        lcd.setCursor(0,1);
        lcd.print("Price=Rs.20");
        delay(1000);
        digitalWrite(GREEN,LOW);
        delay(1000);
        digitalWrite(BUZZER,HIGH);
        digitalWrite(YELLOW,HIGH);
        delay(1000);
        digitalWrite(BUZZER,LOW);
        digitalWrite(YELLOW,LOW);
        total=total-20;                                                       //subtracting item price from total amount
        b2=0;
        //to indicate item is removed
        delay(3000);
         c=1;
    }

         if (content.substring(1) == "ED 1A 68 89" && a==1 && c==1)
          {
        if(total<=balance_amt)                                                  //Check if customer has enough balance in master card
        {
            balance_amt=1000-total;                                                 //Sutracting the total amount from the balance
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("THANKS FOR");
            lcd.setCursor(0,1);
            lcd.print(" SHOPPING ");
            Serial.println("THANKS FOR SHOPpiNG");
            Serial.println();   
            Serial.println();   
            delay(3000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Total Bill =");
            lcd.setCursor(0,1);
            lcd.print(total);
            delay(3000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Balance =");
            lcd.setCursor(0,1);
            lcd.print(balance_amt);                                           //Printing the balance amount for customer's reference
            Serial.println("TOTAL BILL AMOUNT = ");
            Serial.print(total);
            Serial.println();   
            Serial.println();   
            Serial.println("BALANCE AMOUNT = ");
            Serial.print(balance_amt);
            Serial.println();   
            Serial.println();   
        }
        else
       
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("INSUFFICIENT");
            lcd.setCursor(0,1);
            lcd.print("  BALANCE   ");
            Serial.println("INSUFFICIENT BALANCE");
            Serial.println();   
            Serial.println();  
           
           
        }
    }   
   
}

