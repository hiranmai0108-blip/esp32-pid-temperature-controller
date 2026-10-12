#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize I2C LCD (address 0x27, 16x2 chars)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int heaterPin = 18;    // PWM output for heater
const int sensorPin = 34;    // Analog input for temperature sensor
const int upButton = 12;     // Button to increase setpoint
const int downButton = 14;   // Button to decrease setpoint

// PID Parameters
double kp = 2.0, ki = 0.5, kd = 1.0;
double setPoint = 50.0;      // Target temperature in Celsius
double input = 25.0;         // Current temperature
double output = 0.0;         // Heater control output

// PID Variables
unsigned long lastTime;
double errSum = 0, lastErr = 0;
int sampleTime = 1000;       // 1 second

void setup() {
  Serial.begin(115200);
  
  pinMode(heaterPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("ESP32 PID Control");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read buttons to adjust setpoint
  if (digitalRead(upButton) == LOW) {
    setPoint += 1.0;
    delay(200);
  }
  if (digitalRead(downButton) == LOW) {
    setPoint -= 1.0;
    delay(200);
  }

  unsigned long now = millis();
  unsigned long timeChange = (now - lastTime);
  
  if (timeChange >= sampleTime) {
    // Read temperature (simulate sensor reading)
    int rawValue = analogRead(sensorPin);
    input = (rawValue / 4095.0) * 100.0; // Scale to 0-100 C

    // Compute PID errors
    double error = setPoint - input;
    errSum += (error * timeChange);
    double dErr = (error - lastErr) / timeChange;

    // Compute PID output
    output = kp * error + ki * errSum + kd * dErr;

    // Constrain output to PWM limits (0 - 255)
    if (output > 255) output = 255;
    if (output < 0) output = 0;

    analogWrite(heaterPin, (int)output);

    // Save values for next loop
    lastErr = error;
    lastTime = now;

    // Print to Serial Monitor
    Serial.print("SetPoint: "); Serial.print(setPoint);
    Serial.print(" | Temp: "); Serial.print(input);
    Serial.print(" | Output: "); Serial.println(output);

    // Update LCD Display
    lcd.setCursor(0, 0);
    lcd.print("SP:"); lcd.print(setPoint); lcd.print("C  ");
    
    lcd.setCursor(0, 1);
    lcd.print("PV:"); lcd.print(input); lcd.print("C  ");
  }
}
