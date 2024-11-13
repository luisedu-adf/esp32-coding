#define POT_PIN 4       // Potentiometer on GPIO 4
#define LED_2 5         // LED on GPIO 5
#define POT_THRESHOLD 100 // Minimum change in potentiometer value to switch control

bool potentiometerControl = true; // Flag to determine control source
int lastPotValue = 0;             // Stores last potentiometer value

void setup() {
  Serial.begin(9600);
  pinMode(LED_2, OUTPUT);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int intensity = map(potValue, 0, 4095, 0, 255);

  // Check if the potentiometer value has changed significantly
  if (abs(potValue - lastPotValue) > POT_THRESHOLD) {
    potentiometerControl = true; // Switch to potentiometer control
    lastPotValue = potValue;     // Update last potentiometer value
  }

  // If potentiometer control is active, set LED based on potentiometer
  if (potentiometerControl) {
    Serial.print("Valor do potenciômetro: ");
    Serial.println(potValue);
    Serial.print("Intensidade: ");
    Serial.println(intensity);

    analogWrite(LED_2, intensity);
  }

  // Check for Serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    
    // If a valid intensity value is received, switch to serial control
    if (input.toInt() >= 0 && input.toInt() <= 255) {
      potentiometerControl = false;            // Switch to serial monitor control
      analogWrite(LED_2, input.toInt());       // Set LED intensity based on serial input
    }
  }
}
