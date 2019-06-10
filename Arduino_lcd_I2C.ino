//incase if there is an error (syntax or library not founded downloaded in the ardiono application 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//two types of lcds, the I2C has an adaptor with 4 cables just talk a llok online 
//connect GND ro ground 
// connect VCC to the 5V pin in any arduino Board 
//connect SCL to A5 
//connect SDA to A4 
LiquidCrystal_I2C lcd(0x27,20,4);  // the address ranges should be specified in manaual of the screen. 
void setup()
{
  lcd.init();                      // initialize the lcd 
  //lcd.begin();
  // Print a message to the LCD.
  lcd.backlight();
 lcd.setCursor(1,0);
  lcd.print("Bier her! Oder");
  //lcd.setCursor(1,1);
  //lcd.print("print second row here ");
}


void loop()
{
  lcd.setCursor(1,1);
  lcd.print("ich fall um...");
  //delay(500);
}
//try to delete some comments to check the changes. 
//dont forget to adjust the contrast potentiometer in the adaptor to see the test. 
