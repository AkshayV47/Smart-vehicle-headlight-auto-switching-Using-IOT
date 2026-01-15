#define BLYNK_TEMPLATE_ID "TMPL3K5L-8SZN"
#define BLYNK_TEMPLATE_NAME "Smart vehicle headlight auto switching"
#define BLYNK_AUTH_TOKEN "baj4fAlDYtQa17UQQrslU5cWcmPYWaSJ"

#define BLYNK_PRINT Serial
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>    
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <MQ2_LPG.h>
#include <DHT.h>
#define SWITCH_PIN D6
#define LIGHT D5
#define LDR A0
#define LED_BUILTIN D7
// const char* ssid = "arthanari";
// const char* password ="12345678";
const char* ssid = "OPPOReno8T5G";
const char* password ="OPPO8T5G";
// const char* ssid = "Redmi13C5G";
// const char* password ="latha3844";

LiquidCrystal_I2C lcd(0x27, 16, 2);
bool value;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(SWITCH_PIN, INPUT);
  pinMode(LIGHT, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.begin(115200);
  Wire.begin(D2, D3); 
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Light Intensity :");
}

// Blynk switch widget on Virtual Pin V0
BLYNK_WRITE(V3) {
  int switchState = param.asInt(); // 1 = ON, 0 = OFF
  digitalWrite(LED_BUILTIN, switchState); // LOW = ON for built-in LED
  if (switchState == 1){
    Blynk.virtualWrite(V2, "Light is On");
    analogWrite(LED_BUILTIN, 500);
  }
  else if (switchState == 0){
    Blynk.virtualWrite(V2, "Light is Off");  
    analogWrite(LED_BUILTIN, 0); 
  }
}

// the loop function runs over and over again forever
void loop() {
  int LDR_value = analogRead(LDR);
    delay(100);
  Blynk.virtualWrite(V0, LDR_value);
  if(digitalRead(SWITCH_PIN) == HIGH){
    Serial.println("Engine started");
    Blynk.virtualWrite(V1, "Engine started");
    Serial.println(LDR_value);
    if( LDR_value >= 650){
      analogWrite(LED_BUILTIN, 500); 
      Serial.println("Full - On");
      Blynk.virtualWrite(V2, "Light is Full - On");
    }
    else if(LDR_value > 80 && LDR_value < 750){
      analogWrite(LED_BUILTIN, 150); 
      Serial.println("Mid - On");
      Blynk.virtualWrite(V2, "Light is Mid - On");
    }
    else if(LDR_value > 40 && LDR_value <= 750){
      analogWrite(LED_BUILTIN, 80); 
      Serial.println("Low - On");
      Blynk.virtualWrite(V2, "Light is Low - On");
    }
    else if(LDR_value > 10 && LDR_value <= 40){
      analogWrite(LED_BUILTIN, 0); 
      Serial.println("Off");
      Blynk.virtualWrite(V2, "Light is Off");
    }  
  }
  else if(digitalRead(SWITCH_PIN) == LOW){
    Serial.println("Engine OFF");
    Blynk.virtualWrite(V1, "Engine OFF");
    Blynk.virtualWrite(V2, "Light is OFF");
    analogWrite(LED_BUILTIN, 0); 
    Serial.println("LED - OFF");
    if(digitalRead(LIGHT) == HIGH){
      Serial.println(LDR_value);
      Serial.println("Auto matic light mode ON");
      Blynk.virtualWrite(V4,"Auto matic light mode ON" );
      if( LDR_value >= 650){
        analogWrite(LED_BUILTIN, 500); 
        Serial.println("Full - On");
        Blynk.virtualWrite(V2, "Light is Full - On");
      }
      else if(LDR_value > 80 && LDR_value < 750){
        analogWrite(LED_BUILTIN, 150); 
        Serial.println("Mid - On");
        Blynk.virtualWrite(V2, "Light is Mid - On");
      }
      else if(LDR_value > 40 && LDR_value <= 750){
        analogWrite(LED_BUILTIN, 80); 
        Serial.println("Low - On");
        Blynk.virtualWrite(V2, "Light is Low - On");
      }
      else if(LDR_value > 10 && LDR_value <= 40){
        analogWrite(LED_BUILTIN, 0); 
        Serial.println("Off");
        Blynk.virtualWrite(V2, "Light is Off");
      }
    }
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