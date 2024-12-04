// Set CorrectionFactor from calibration
const float correctionFactor = 1.039492908; //CorrectionFactor

#include <LiquidCrystal.h>
// Initialize the LCD pins and connect to Arduino
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Pin definitions
const int trigPin = 12;
const int echoPin = 13;
const int pumpPin = 11;
const int buttonPin1 = 8;  // Button to set min/max
const int buttonPin2 = 9;  // Button to switch modes

// Define float pin numbers
const int overfillPin = A0;  // High-level float switch pin (overfill)
const int underfillPin = A1; // Low-level float switch pin (underfill)

// Variables
int minLevel = 0;  // Minimum level
int maxLevel = 0;  // Maximum level
int currentLevel = 0;  // Current water level
bool settingMin = false;  // Is in setting min mode
bool settingMax = false;  // Is in setting max mode
bool inSettingMode = false; // Is in setting mode
bool pumpActive = false; // Is the pump currently active

// Timing variables
unsigned long lastReadTime = 0;  // Time of the last ultrasonic reading
unsigned long readInterval = 5000; // 5.0 seconds
unsigned long buttonPressTime = 0;
bool button1Pressed = false;
bool button2Pressed = false; 

void setup() {
  // Setup pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(overfillPin, INPUT_PULLUP); // High-level float switch (overfill)
  pinMode(underfillPin, INPUT_PULLUP); // Low-level float switch (underfill)

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Water Level:");

  // Initialize Serial Monitor
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  unsigned long currentTime = millis();

  // Read the state of the float switches
  bool overfillTriggered = digitalRead(overfillPin) == HIGH; // Active when triggered (assuming HIGH when triggered)
  bool underfillTriggered = digitalRead(underfillPin) == LOW; // Active when triggered (assuming LOW when triggered)
    
  // If the overfill switch is triggered (water is at high level)
  if (overfillTriggered && pumpActive) {
    digitalWrite(pumpPin, LOW); // Turn off the pump
    pumpActive = false;
    lcd.setCursor(0, 1);
    lcd.print("WARNING: Overfill");
    Serial.println("WARNING: Overfill, pump turned off");
  }

  // If the underfill switch is triggered (water is at low level)
  if (underfillTriggered && pumpActive) {
    digitalWrite(pumpPin, LOW); // Turn off the pump
    pumpActive = false;
    lcd.setCursor(0, 1);
    lcd.print("WARNING: Underfill");
    Serial.println("WARNING: Underfill, pump turned off");
  }

  // Read water level based on pump state or interval time if float switches are not triggered
  if (!overfillTriggered && !underfillTriggered) {
    if (pumpActive || (currentTime - lastReadTime >= readInterval)) {
      currentLevel = readUltrasonicDistance();
      lastReadTime = currentTime;

      // Display current water level on LCD
      if (!inSettingMode) {
        lcd.setCursor(0, 0);
        lcd.print("Water Level: ");
        lcd.print(currentLevel);
        lcd.print(" cm    "); // Clear extra characters

        lcd.setCursor(0, 1);
        lcd.print("PUMP: ");
        lcd.print(pumpActive ? "ON " : "OFF");
      }

      // Serial print water level, pump status, and timestamp
      Serial.print("Time: ");
      Serial.print(currentTime);  // Print timestamp in milliseconds
      Serial.print(" ms, Water Level: ");
      Serial.print(currentLevel);
      Serial.print(" cm, Pump: ");
      Serial.println(pumpActive ? "ON" : "OFF");

      // Control the pump based on water level
      if (pumpActive && currentLevel <= minLevel) {
        digitalWrite(pumpPin, LOW);  // Turn off pump
        pumpActive = false;
        Serial.println("Pump turned off: below min level");
      } else if (!pumpActive && currentLevel >= maxLevel) {
        digitalWrite(pumpPin, HIGH); // Turn on pump
        pumpActive = true;
        Serial.println("Pump turned on: above max level");
      }
    }
  }

  // Check button states for setting min/max levels
  if (digitalRead(buttonPin1) == LOW) {
    if (!button1Pressed) {
      button1Pressed = true;
      if (inSettingMode) {
        if (settingMin) {
          minLevel++;
          lcd.setCursor(0, 1);
          lcd.print("Set Min: ");
          lcd.print(minLevel);
          lcd.print(" cm      ");
        } else if (settingMax) {
          maxLevel++;
          lcd.setCursor(0, 1);
          lcd.print("Set Max: ");
          lcd.print(maxLevel);
          lcd.print(" cm      ");
        }
      }
    }
  } else {
    button1Pressed = false;
  }

  if (digitalRead(buttonPin2) == LOW) {
    if (!button2Pressed) {
      button2Pressed = true;
      if (!inSettingMode) {
        inSettingMode = true;
        settingMin = true;
        minLevel = 0;
        lcd.setCursor(0, 1);
        lcd.print("Set Min: 0 cm");
      } else if (settingMin) {
        settingMin = false;
        settingMax = true;
        maxLevel = 0;
        lcd.setCursor(0, 1);
        lcd.print("Set Max: 0 cm");
      } else if (settingMax) {
        settingMax = false;
        inSettingMode = false;
        lcd.setCursor(0, 1);
        lcd.print("Water Level: ");
      }
    }
  } else {
    button2Pressed = false;
  }

  // Reset display if in setting mode
  if (inSettingMode) {
    if (settingMin) {
      lcd.setCursor(0, 1);
      lcd.print("Set Min: ");
      lcd.print(minLevel);
      lcd.print(" cm      ");
    } else if (settingMax) {
      lcd.setCursor(0, 1);
      lcd.print("Set Max: ");
      lcd.print(maxLevel);
      lcd.print(" cm      ");
    }
  }
}

// Function to read the distance from the ultrasonic sensor
int readUltrasonicDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2; // Calculate distance in cm
  return distance * correctionFactor; // Apply correction factor
}
