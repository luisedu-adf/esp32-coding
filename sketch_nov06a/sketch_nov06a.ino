// 
#define BUTTON 23   // Pino D4 (BOTÂO)
#define LED_1 18    // GPIO 18 (LED VERMELHO)
#define LED_2 5     // GPIO 5 (LED AMARELO)



int buttonState = 0; // Armazenar o estado do botão
int lastButtonState = 0; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Tempo da última mudança do botão
unsigned long debounceDelay = 10; // debounce time em mili (mudar pra define)

void setup() {
  // Configura o pino do botão como entrada com pull-down
  pinMode(BUTTON, INPUT_PULLDOWN);  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lê o estado do botão
  int reading = digitalRead(BUTTON);
      
  // Verifica se o estado do botão mudou
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reseta o tempo de debounce
  }

  // Se já passou o tempo de debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Se o estado do botão mudou
    if (reading != buttonState) {
      buttonState = reading;

      // Se o botão for pressionado (estado LOW devido ao pull-down)
      if (buttonState == LOW) {
        digitalWrite(LED_1, LOW);  
        Serial.println("Botão ");    
      } else {
        digitalWrite(LED_1, HIGH);   
        Serial.println("OOO");    
      }
    }
  }

  // Atualiza o estado anterior do botão
  lastButtonState = reading;

  
  if(Serial.available()){
   String input = Serial.readStringUntil('\n'); 
   if(input == "on")
      digitalWrite(LED_1, HIGH);
   else if(input == "off")
      digitalWrite(LED_1, LOW);
   else if(input.toInt() >= 0 and input.toInt() <= 255)
      analogWrite(LED_2, input.toInt());   
  }

  
}
