#define BLYNK_TEMPLATE_ID "TMPL2X-Dwe0dT"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitor"
#define BLYNK_AUTH_TOKEN "MlvW-ihqxg2MbZ0PvS8CF7UwX2HXf-XD"

#define BLYNK_PRINT Serial
#include <WiFi.h>    //esp32 wifi connection header file
#include <BlynkSimpleEsp32.h> //Blynk esp32 header file

#include <DHT.h>    
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
byte degree_symbol[8] = {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
            
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "<GOATY>";
char pass[] = "Nyai_the_lion99";

BlynkTimer timer;

int gas = A0;   //mq2 pin no
int sensorThreshold = 100;

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void sendSensor() {

float t =  dht.readTemperature();
float h = dht.readHumidity();

if(isnan(t) || isnan(h)){
  Serial.println("Failed to read from DHT sensor!"); 
  return;
}

int analogSensor = analogRead(gas);
Blynk.virtualWrite(V2, analogSensor);
Serial.print("Gas value: ");
Serial.print(analogSensor);

Blynk.virtualWrite(V0, t);
Blynk.virtualWrite(V1, h);

}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //pinMode(gas, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setTimer(30000, sendSensor, 30);

  Wire.begin();
  lcd.begin(16, 2); // Initialize the LCD

  //lcd.backlight();
  //lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Air Monitoring");
  lcd.setCursor(3,1);
  lcd.print("Monitor");
  delay(2000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int gasValue = analogRead(gas);

  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.setCursor(6,1);
  lcd.write(1);
  lcd.createChar(1, degree_symbol);
  lcd.setCursor(7,1);
  lcd.print("C");
  delay(3000);

  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  delay(4000);
  lcd.clear();

  if (gasValue < 600){
    lcd.setCursor(0,0);
    lcd.print("Gas Value: ");
    lcd.print(gasValue);
    lcd.setCursor(0,1);
    lcd.print("Fresh Air");
    Serial.println("Fresh Air");
    delay(4000);
    lcd.clear();
  } else{
    lcd.setCursor(0,0);
    lcd.print("Gas Value: ");
    lcd.print(gasValue);
    lcd.setCursor(0,1);
    lcd.print("Bad Air");
    Serial.println("Bad Air");
    delay(4000);
    lcd.clear();
  }

  if(gasValue > 600){
    Blynk.logEvent("pollution_alert", "Bad Air");
  }

}




















