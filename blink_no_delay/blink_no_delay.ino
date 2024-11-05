#define LED1_PIN 18  // First LED on GPIO18
#define LED2_PIN 5  // Second LED on GPIO05
#define INTERVAL_1 500 // Interval for LED1
#define INTERVAL_2 800 // Interval for LED2

unsigned long previousMillis1 = 0;  // Stores the last time LED1 was toggled
unsigned long previousMillis2 = 0;  // Stores the last time LED2 was toggled

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= INTERVAL_1) {   // Check if it's time to toggle LED1
    previousMillis1 = currentMillis; // Update time
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN)); // Toggle LED1
  }

  if (currentMillis - previousMillis2 >= INTERVAL_2) {   // Check if it's time to toggle LED2
    previousMillis2 = currentMillis; // Update time
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN)); // Toggle LED2
  }
}
