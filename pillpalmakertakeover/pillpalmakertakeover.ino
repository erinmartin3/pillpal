#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo ContinuousServo;
const int ContinuousServoPin = 19;
const int DispenseLED = 14;
const int DispenseButton = 18;
const int PowerLED = 16;
const int PowerButton = 4;
const int IRSensor = 5;
const int AdjustButton = 32;
const int AdjustButton2 = 26;

int count = 1;
int count2 = 0;
bool powerState = false;


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(DispenseLED, OUTPUT);
  pinMode(DispenseButton, INPUT_PULLUP);
  pinMode(PowerLED, OUTPUT);
  pinMode(PowerButton, INPUT_PULLUP);
  pinMode(IRSensor, INPUT_PULLUP);
  pinMode(AdjustButton, INPUT_PULLUP);
  pinMode(AdjustButton2, INPUT_PULLUP);
  digitalWrite(DispenseLED, HIGH);
  ContinuousServo.attach(ContinuousServoPin);

}
void loop() {

int val = digitalRead(IRSensor);
if (val == 0){
  // column, row
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Happy Maker Takeover");
  lcd.setCursor(3, 2);
  lcd.print("From PillPal!!");
  delay(6000);
} else{
}
delay(1000);
  if (digitalRead(PowerButton) == LOW) {
    powerState = true;
    digitalWrite(PowerLED, HIGH);
    lcd.backlight();
    lcd.clear();
    if (powerState && count == 1) {
      lcd.print("Device is Powered ON");
      count=count+1;
      delay(3000);
      lcd.clear();
    } else {
      lcd.clear();
    }
  } else if (digitalRead(PowerButton) == HIGH) {
    digitalWrite(PowerLED, LOW);
    powerState = false;
  }
  if (powerState==false) {
    digitalWrite(DispenseLED, LOW);
    digitalWrite(PowerLED, LOW);
    lcd.noBacklight();
    //ContinuousServo
    return;
  }

  if (digitalRead(DispenseButton) == LOW) {
    digitalWrite(DispenseLED, LOW);
        ContinuousServo.write(114);
        delay(182);
        ContinuousServo.write(90);
        lcd.setCursor(2, 1);
        lcd.print("Dispensing pills");
        delay(3000);
  } else{
    digitalWrite(DispenseLED, HIGH);
    lcd.setCursor(6, 0);
    lcd.print("Pill Pal");
      lcd.setCursor(0, 2);
      lcd.print("Ready to dispense...");
  }  
  if (digitalRead(AdjustButton)==LOW){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Special thanks to");
    lcd.setCursor(3, 1);
    lcd.print("Kyle Altmann,");
    lcd.setCursor(2, 2);
    lcd.print("Nim Batchelor &");
    lcd.setCursor(3, 3);
    lcd.print("the Maker Hub");
    delay(5000);
  }

  if (digitalRead(AdjustButton2)==LOW){
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("ERROR: 05012024");
    lcd.setCursor(3, 2);
    lcd.print("MaKeRtAkEoVeR");
    delay(5000);
  }
 
}