#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define THERMISTORPIN A0
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000 
// temp. for nominal resistance 
#define TEMPERATURENOMINAL 23
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3900
// the value of the 'other' resistor the added one as a voltage devider 
#define SERIESRESISTOR 10000

int samples[NUMSAMPLES];
int LED=11;
LiquidCrystal_I2C lcd(0x27,20,4);
void setup(void) {
Serial.begin(9600);
analogReference(EXTERNAL);
//lcd.begin(16, 2);
//lcd.print(" Welcome in ");
lcd.init();
lcd.backlight();
//lcd.setCursor(1,0);
//lcd.print("HEV Abteilung");
pinMode(LED,OUTPUT);
}
void loop(void) {
uint8_t i;
float average;
// take N samples in a row, with a slight delay
for (i=0; i< NUMSAMPLES; i++) {
samples[i] = analogRead(THERMISTORPIN);
delay(10);
}
// average all the samples out
average = 0;
for (i=0; i< NUMSAMPLES; i++) {
average += samples[i];
}
average /= NUMSAMPLES;
Serial.print("Average analog reading ");
Serial.println(average);
// convert the value to resistance
average = 1023 / average - 1;
average = SERIESRESISTOR / average;
Serial.print("Thermistor resistance ");
Serial.println(average);
float T;
T = average / THERMISTORNOMINAL;
// (R/Ro)
T = log(T);
// ln(R/Ro)
T /= BCOEFFICIENT;
// 1/B * ln(R/Ro)
T += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
T = 1.0 / T;
// Invert to c 
T -= 273.15;
  //condition if the temp get higher than a specific value 
if (T >=27)
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}
// showed test on the screen 
Serial.print("Temperature ");
Serial.print(T);
Serial.println(" *C");
lcd.setCursor(1,1);
lcd.print("Temp:");
lcd.print(T);
lcd.print(" *C");
lcd.setCursor(1,0);
lcd.print("HEV Abteilung");
delay(1000);

}
