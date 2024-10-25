// Pin Definitions
#define SOIL_SENSOR_PIN A0  // Soil moisture sensor analog input
#define PUMP_PIN 3          // Relay or pump control pin
#define LED_PIN 4           // LED to indicate low moisture
#define THRESHOLD 500       // Threshold value for dry soil (adjustable)

void setup() {
  pinMode(PUMP_PIN, OUTPUT);  // Set pump pin as output
  pinMode(LED_PIN, OUTPUT);   // Set LED pin as output
  Serial.begin(9600);         // Initialize serial communication
}

void loop() {
  int moistureLevel = analogRead(SOIL_SENSOR_PIN);  // Read soil moisture value

  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureLevel);

  // Check if moisture level is below the threshold
  if (moistureLevel < THRESHOLD) {
    digitalWrite(PUMP_PIN, HIGH);  // Turn on water pump
    digitalWrite(LED_PIN, HIGH);   // Light up LED to indicate dryness
    Serial.println("Soil is dry. Pump activated.");
  } else {
    digitalWrite(PUMP_PIN, LOW);   // Turn off water pump
    digitalWrite(LED_PIN, LOW);    // Turn off LED
    Serial.println("Soil is sufficiently moist. Pump off.");
  }

  delay(2000);  // Wait 2 seconds before the next reading
}
