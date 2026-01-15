// Automatic Street Light with PWM on ESP8266
// LDR on A0, LED on D2 (GPIO4) — change pin if needed

const int LDR_PIN = A0;     // LDR connected to analog pin
const int LED_PIN = D7;     // LED or LED strip control pin (PWM)

int sensorValue = 0;
int brightness = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  sensorValue = analogRead(LDR_PIN); // 0 = dark, 1023 = bright
  Serial.print("LDR Value: ");
  Serial.println(sensorValue);

  // Map LDR value to PWM brightness
  // Invert because low light => high brightness
  brightness = map(sensorValue, 1023, 0, 0, 1023); 

  // Limit brightness for LED safety (optional)
  if (brightness > 1023) brightness = 1023;
  if (brightness < 0) brightness = 0;

  // Apply PWM brightness
  analogWrite(LED_PIN, brightness);

  delay(50); // smooth update
}