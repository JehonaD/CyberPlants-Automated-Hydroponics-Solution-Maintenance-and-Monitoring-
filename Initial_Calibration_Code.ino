#define TRIG_PIN 2  // Define Trig pin
#define ECHO_PIN 4  // Define Echo pin


void setup() {
  pinMode(TRIG_PIN, OUTPUT);  // Set Trig pin as output
  pinMode(ECHO_PIN, INPUT);   // Set Echo pin as input
  Serial.begin(9600);         // Initialize serial communication at 9600 baud
}


void loop() {
  long duration;
  float distance;


  // Send a 10-microsecond pulse to Trig pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  // Measure the duration of the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);


  // Calculate the distance (cm)
  distance = duration * 0.034 / 2;  // Speed of sound = 0.034 cm/us


  // Print the duration
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" microseconds");


  // Print the calculated distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  delay(1000);  // Wait 500ms before next measurement
}

