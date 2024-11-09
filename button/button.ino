// Define os pinos
#define BUTTON 4  // Pino D4
#define LED 18  // Pino GPIO 18 (LED)

// Variável para armazenar o estado do botão
int buttonState = 0;

void setup() {
  // Configura o pino do botão como entrada com pull-down
  pinMode(BUTTON, INPUT);
  // Configura o pino do LED como saída
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lê o estado do botão
  buttonState = digitalRead(BUTTON);
  
  // Se o botão for pressionado (estado LOW devido ao pull-down)
  if (buttonState == HIGH) {
    digitalWrite(LED, HIGH);  // Acende o LED
    Serial.println("OOO");
  } else {
    digitalWrite(LED, LOW);   // Apaga o LED
    Serial.println("XXX");
  }

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
