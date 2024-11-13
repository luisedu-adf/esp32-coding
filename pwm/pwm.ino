// Define parameters
#define PWM_PIN 5

const int pwmChannel = 0;           // PWM channel (0-15)
const int pwmFrequency = 5000;       // Frequency in Hz
const int pwmResolution = 8;         // Resolution in bits (8 bits = 0-255)

// Setup function
void setup() {
  // Attach and configure the PWM pin with frequency and resolution
  ledcAttach(PWM_PIN, pwmFrequency, pwmResolution);
}

// Loop function
void loop() {
  // Set PWM duty cycle (0 - 255 for 8-bit resolution)
  //int dutyCycle = 128;  // 50% duty cycle
  ledcWrite(PWM_PIN, 255);
}
