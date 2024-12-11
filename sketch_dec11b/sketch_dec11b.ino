// Definindo os pinos
const int LED_1 = 18;     // Pino do LED
const int BUTTON = 23;    // Pino do botão

volatile bool ledState = false; // Variável para alternar o estado do LED
volatile bool buttonState = false; // Variável para alternar o estado do LED

void setup() {
  // Inicializa o LED como saída
  pinMode(LED_1, OUTPUT);
  // Inicializa o botão como entrada com resistor de pull-down interno
  pinMode(BUTTON, INPUT_PULLDOWN);

  // Configura a interrupção para o pino do botão
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, FALLING); // A interrupção é acionada na borda de subida (pressionado)
}

void loop() {
  // O controle do LED é feito pela interrupção
  // Não é necessário mais código no loop
}

// Função chamada pela interrupção para alternar o estado do LED
void buttonISR() {
  digitalWrite(LED_1, digitalRead(BUTTON) ? HIGH : LOW); // Define o estado do LED
}
