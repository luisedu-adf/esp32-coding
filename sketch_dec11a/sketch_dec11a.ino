#define BUTTON 23  // Button on GPIO23
#define LED_1 18 // offboard RED LED on GPIO18

volatile bool buttonState = false; // Declare the button state as volatile

void IRAM_ATTR debounced_button() {
  buttonState = true;  // Set the flag when the button is pressed
}

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);  // Button with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(BUTTON), debounced_button, FALLING);
  Serial.begin(9600);
}

void loop() {
  if (buttonState) {
    // Process button action outside the ISR context
    buttonState = false;  // Reset the flag
    digitalWrite(LED_1, !digitalRead(LED_1));  // Toggle the LED state
    Serial.println("Button Pressed");
  }
  
  // Add other code here, but avoid using functions like delay() or Serial.print() inside interrupts
}
