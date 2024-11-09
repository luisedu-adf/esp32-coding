#define ONBOARD_LED 2  // onboard LED on GPIO02
#define LED_1 18 // offboard LED on GPIO18
#define LED_2 5 // offboard LED on GPIO5

unsigned long previousMillis = 0;  
const unsigned long interval = 3000; 

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  ledcSetup(0, 5000, 8);      // Configura o canal 0 a 5 kHz, com resolução de 8 bits
  ledcAttachPin(LED_2, 0);  // Associa o pino do LED ao canal 0
  Serial.begin(9600);
}

void loop() {
 for (int brilho = 0; brilho <= 255; brilho++) { // Aumenta o brilho
    ledcWrite(0, brilho);  // Define o brilho do LED
    delay(10);             // Aguarda 10 ms
  }

  for (int brilho = 255; brilho >= 0; brilho--) { // Diminui o brilho
    ledcWrite(0, brilho);  // Define o brilho do LED
    delay(10);             // Aguarda 10 ms
  }

}

  
