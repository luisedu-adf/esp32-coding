// Define os pinos
#define BUTTON 4  // Pino D4
#define LED_1 18  // Pino GPIO 18 (LED VERMELHO)
#define LED_2 5  // Pino GPIO 5 (LED)


// Variável para armazenar o estado do botão
int buttonState = 0;

void setup() {
  // Configura o pino do botão como entrada com pull-down
  pinMode(BUTTON, INPUT);
  // Configura o pino do LED como saída
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lê o estado do botão
  buttonState = digitalRead(BUTTON);

  // Se o botão for pressionado (estado LOW devido ao pull-down)
  if (buttonState == HIGH) {
    digitalWrite(LED_1, HIGH);  // Acende o LED
    Serial.println("OOO");
  } else {
    digitalWrite(LED_1, LOW);   // Apaga o LED
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
