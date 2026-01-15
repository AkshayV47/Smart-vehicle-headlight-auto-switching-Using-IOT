#include <ESP8266WiFi.h>
#define SWITCH_PIN D6
#define LDR A0
#define LED_BUILTIN D7
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(SWITCH_PIN, INPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  int LDR_value = analogRead(LDR);
  if(digitalRead(SWITCH_PIN) == HIGH){
    Serial.println("Engine started");
    Serial.println(LDR_value);
    if( LDR_value >= 800){
      analogWrite(LED_BUILTIN, 500); 
      Serial.println("Full - On");
    }
    else if(LDR_value > 80 && LDR_value < 800){
      analogWrite(LED_BUILTIN, 150); 
      Serial.println("Mid - On");
    }
    else if(LDR_value > 40 && LDR_value <= 80){
      analogWrite(LED_BUILTIN, 80); 
      Serial.println("Low - On");
    }
    else if(LDR_value > 10 && LDR_value <= 40){
      analogWrite(LED_BUILTIN, 0); 
      Serial.println("Off");
    }  
  }
  else if (digitalRead(SWITCH_PIN) == LOW){
    Serial.println("Engine OFF");
    delay(5000);
    analogWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}