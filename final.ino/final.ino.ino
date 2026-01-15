#define BLYNK_TEMPLATE_ID "*******************"
#define BLYNK_TEMPLATE_NAME "Smart vehicle headlight auto switching"
#define BLYNK_AUTH_TOKEN "*****************"

#define BLYNK_PRINT Serial
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>    
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <MQ2_LPG.h>
#include <DHT.h>
//Input pin
#define Engine_switch D7
#define light_switch D8
#define LDR A0
//OUT pin 
#define Hazard_light D6
#define Light_pin D5

const char* ssid = "******************";
const char* password ="**********";

LiquidCrystal_I2C lcd(0x27, 16, 2);
bool value;

void setup() {
  pinMode(Hazard_light, OUTPUT);
  pinMode(Light_pin, OUTPUT);  
  pinMode(Engine_switch, INPUT);
  pinMode(light_switch, INPUT);
  pinMode(LDR, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.begin(9600);
  Wire.begin(D2, D3); //SDA , SCL
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Light Intensity :");
}

// Blynk switch widget on Virtual Pin V0
BLYNK_WRITE(V3) {
  int switchState = param.asInt(); // 1 = ON, 0 = OFF
  digitalWrite(Hazard_light, switchState); // LOW = ON for built-in LED
  if (switchState == 1){
    // Blynk.virtualWrite(V2, "Light is On");
    analogWrite(Hazard_light, 500);
  }
  else if (switchState == 0){
    // Blynk.virtualWrite(V2, "Light is Off");  
    analogWrite(Hazard_light, 0); 
  }
}

// the loop function runs over and over again forever
void loop() {
  int LDR_value = analogRead(LDR);
  delay(100);
  Blynk.virtualWrite(V0, LDR_value);
  delay(100);
  if(digitalRead(Engine_switch) == HIGH){
    Serial.println("Engine started");
    Blynk.virtualWrite(V1, "Engine started");
    Serial.println(LDR_value);
    delay(100);
    if(digitalRead(light_switch) == HIGH){
      analogWrite(Hazard_light, 0); 
      Serial.println("Hazard light OFF");
      if( LDR_value >= 650){
        analogWrite(Light_pin, 500); 
        Serial.println("Full - On");
        Blynk.virtualWrite(V2, "Light is Full - On");
      }
      else if(LDR_value > 80 && LDR_value < 750){
        analogWrite(Light_pin, 150); 
        Serial.println("Mid - On");
        Blynk.virtualWrite(V2, "Light is Mid - On");
     }
      else if(LDR_value > 10 && LDR_value <= 750){
        analogWrite(Light_pin, 80); 
        Serial.println("Low - On");
        Blynk.virtualWrite(V2, "Light is Low - On");
      }
      // else if(LDR_value > 10 && LDR_value <= 40){
      //   analogWrite(Light_pin, 0); 
      //   Serial.println("Off");
      //   Blynk.virtualWrite(V2, "Light is Off");
      // }
    }
    else if(digitalRead(light_switch) == LOW){
      analogWrite(Hazard_light, 0); 
      Serial.println("Hazard light OFF");
      analogWrite(Light_pin, 0); 
      Serial.println("Light Off");
      Blynk.virtualWrite(V2, "Light is Off"); 
    }  
  }
  else if(digitalRead(Engine_switch) == LOW){
    Serial.println("Engine OFF");
    Blynk.virtualWrite(V1, "Engine OFF");
    analogWrite(Hazard_light, 500); 
    Serial.println("Hazard light ON");
    delay(3000);
    Blynk.virtualWrite(V2, "Light is OFF");
    analogWrite(Light_pin, 0); 
    Serial.println("LED - OFF");

  }
  Blynk.run();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light Intensity :");  
  lcd.print("                "); 
  lcd.setCursor(0, 1);
  lcd.print("LDR Value: ");
  lcd.print(LDR_value);
  delay(1000);
}
