#define ONBOARD_LED 2  // onboard LED on GPIO02
#define LED_1 18 // offboard RED LED on GPIO18
#define LED_2 5 // offboard YELLOW LED on GPIO5
#define POT_PIN 4       // Potentiometer on GPIO 4
#define BUTTON 23  // Button on GPIO23
#define INTERVAL 3000 // blink onboard interval 
#define POT_THRESHOLD 400 // Minimum change in potentiometer value to switch control


bool potentiometerControl = true; // Flag to determine control source
int lastPotValue = 0;             // Stores last potentiometer value

int lastButtonState = 0; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Tempo da última mudança do botão
unsigned long debounceDelay = 10; // debounce time em mili (mover pra define)

unsigned long previousMillis = 0;

int buttonState = 0; // Variável para armazenar o estado do botão
bool monitor_controlled = false;

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void onboard_blink() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
    Serial.println(digitalRead(ONBOARD_LED) ? "OnBoard LED ON" : "OnBoard LED OFF");
  }


}

void monitor_control() {

  if (Serial.available()) {
    
    String input = Serial.readStringUntil('\n');

    if (input == "on" || input == "off") {
      monitor_controlled = true;
      digitalWrite(LED_1, (input == "on") ? HIGH : LOW);
    }
    else if (input.toInt() >= 0 and input.toInt() <= 255){
      potentiometerControl = false; // Switch to serial monitor control
      analogWrite(LED_2, input.toInt()); 
    }
    
  }

}

void potentiometer() {

  int potValue = analogRead(POT_PIN);
  int intensity = map(potValue, 0, 4095, 0, 255);

  // Check if the potentiometer value has changed significantly
  if (abs(potValue - lastPotValue) > POT_THRESHOLD) {
    potentiometerControl = true; // Switch to potentiometer control
    lastPotValue = potValue;     // Update last potentiometer value
    Serial.printf("Valor do potenciômetro: %d, Intensidade: %d\n", potValue, intensity);
  }

  // If potentiometer control is active, set LED based on potentiometer
  if (potentiometerControl) {
    analogWrite(LED_2, intensity);
  }
  
}

void debounced_button() {

  int reading = digitalRead(BUTTON); // Lê o estado do botão
      
  if (reading != lastButtonState) { // Verifica se o estado do botão mudou
    lastDebounceTime = millis(); // Reseta o tempo de debounce
  }

  if ((millis() - lastDebounceTime) > debounceDelay) { // Se já passou o tempo de debounce
    if (reading != buttonState) { // Se o estado do botão mudou
      buttonState = reading;
      button();
    }
  }
  
  lastButtonState = reading; // Atualiza o estado anterior do botão
  
}


void button() {

  buttonState = digitalRead(BUTTON);

  // Se o botão for pressionado (estado LOW devido ao pull-down)
  if (buttonState == HIGH) {
    monitor_controlled = false;
    digitalWrite(LED_1, HIGH);  // Acende o LED
    Serial.println("Botão Pressionado");
  } 
  else if(!monitor_controlled) {
    digitalWrite(LED_1, LOW);   // Apaga o LED
    Serial.println("Botão Solto");
  }

}

void loop() {

  potentiometer();

  monitor_control();

  debounced_button();

  onboard_blink();

  delay(42);

}
