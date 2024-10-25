#include <DHT.h> // Include the DHT library for temperature and humidity

// Pin Definitions
#define PIR_SENSOR_PIN 2    // PIR motion sensor input pin
#define LED_PIN 3           // LED to simulate a light
#define BUZZER_PIN 4        // Buzzer for alerts
#define RELAY_PIN 5         // Relay to control appliances
#define BUTTON_PIN 6        // Push button for manual control
#define DHT_PIN 7           // Temperature sensor pin (DHT11 or DHT22)
#define DHT_TYPE DHT11      // Define your DHT model (DHT11 or DHT22)

// Variables
bool motionDetected = false;
bool applianceState = false;
DHT dht(DHT_PIN, DHT_TYPE); // Initialize DHT sensor

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Using internal pull-up resistor

  dht.begin(); // Start DHT sensor
  Serial.begin(9600); // Initialize serial communication

  // Initial states
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Check for motion detection
  motionDetected = digitalRead(PIR_SENSOR_PIN);
  if (motionDetected) {
    digitalWrite(LED_PIN, HIGH); // Turn on the light
    digitalWrite(BUZZER_PIN, HIGH); // Sound the buzzer for alert
    Serial.println("Motion detected! Light and buzzer activated.");
    delay(5000); // Keep lights and buzzer on for 5 seconds
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off the light if no motion
  }

  // Check temperature and activate appliance if above threshold
  float temperature = dht.readTemperature(); // Read temperature
  if (temperature > 30.0) { // Example threshold: 30°C
    digitalWrite(RELAY_PIN, HIGH); // Turn on appliance
    Serial.println("High temperature detected! Appliance activated.");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off appliance
  }

  // Manual control using push button
  if (digitalRead(BUTTON_PIN) == LOW) {
    applianceState = !applianceState; // Toggle appliance state
    digitalWrite(RELAY_PIN, applianceState ? HIGH : LOW);
    Serial.println(applianceState ? "Appliance turned ON" : "Appliance turned OFF");
    delay(500); // Debounce delay
  }

  delay(1000); // Short delay for stability
}
