#define ONBOARD_LED 2  // onboard LED on GPIO02
#define LED_1 18 // offboard RED LED on GPIO18
#define LED_2 5 // offboard YELLOW LED on GPIO5
#define POT_PIN 4 // Potentiometer on GPIO 4
#define BUTTON 23  // Button on GPIO23

#define INTERVAL 100 // Blink Onboard Interval 
#define POT_THRESHOLD 400 // Minimum change in potentiometer value to switch control
#define DEBOUNCE_DELAY 10 // Button Debounce Delay

int lastPotValue = 0;             // Stores last Potentiometer value
bool potentiometerControl = true; // Control Flag for Potentiometer

bool monitorControl = false;  // Control Flag for Monitor

bool debugMode = true;

bool cargaMode = false;

bool lastButtonState = 0; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Tempo da última mudança do botão
bool buttonState = 0; // Variável para armazenar o estado do botão

unsigned long previousMillis = 0; // Onboard blink delay

void menu() {
  Serial.println("\n===== Equipment Status =====");

  Serial.print("Onboard LED: ");
  Serial.println(digitalRead(ONBOARD_LED) ? "ON" : "OFF");

  Serial.print("Red LED: ");
  Serial.println(digitalRead(LED_1) ? "ON" : "OFF");

  Serial.print("Yellow LED PWM: ");
  Serial.println(ledcRead(LED_2));

  Serial.print("Button State: ");

  Serial.print("Potentiometer State: ");
  Serial.println(analogRead(POT_PIN));

  Serial.print("Carga: ");
  Serial.println(cargaMode == 1 ? "On" : "Off");


  Serial.println("===========================");
}


void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  ledcAttach(LED_2, 5000, 8); // ledcAttach(LED_2, pwmFrequency, pwmResolution);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void onboard_blink() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
    if(debugMode) Serial.println(digitalRead(ONBOARD_LED) ? "OnBoard LED ON" : "OnBoard LED OFF");
  }
}



void monitor_control() {

  if (Serial.available()) {
    
    String input = Serial.readStringUntil('\n');
    //int input = Serial.parseInt();
    int op;
    
    if(input=="debug")
      op = 0;
    else if(input=="red")
      op = 1;
    else if(input.toInt() >= 0 and input.toInt() <= 255)
      op = 2;
    else if(input.toInt() == 777)
      op = 3;
    else  // invalid
      op = -1; 
    

    switch(op){
      case 0:
          debugMode = !debugMode;
          break;
      case 1:
          monitorControl = true;
          digitalWrite(LED_1, !digitalRead(LED_1));
          break;
      case 2:
          potentiometerControl = false;
          ledcWrite(LED_2, input.toInt());
          break;
      case 3:
          cargaMode = !cargaMode;
          break;
      default:
          Serial.println("Invalid Input");
          break;
    }

   
  }

}

#define NUM_READINGS 10  // Number of readings to average

int potValues[NUM_READINGS];  // Array to store potentiometer values
int potIndex = 0;  // Index to keep track of where to store the next reading
int potValue = 0;  // Variable to store the current potentiometer value

void potentiometer() {
  int rawValue = analogRead(POT_PIN);

  potValues[potIndex] = rawValue;
  
  potIndex = (potIndex + 1) % NUM_READINGS;

  int sum = 0;
  for (int i = 0; i < NUM_READINGS; i++) {
    sum += potValues[i];
  }
  int averageValue = sum / NUM_READINGS;

  int intensity = map(averageValue, 0, 4095, 0, 255);

  if (abs(averageValue - lastPotValue) > POT_THRESHOLD) {
    potentiometerControl = true; // Switch to potentiometer control
    lastPotValue = averageValue; // Update last potentiometer value
    if(debugMode) Serial.printf("Valor do potenciômetro: %d, Intensidade: %d\n", averageValue, intensity);
  }

  if (potentiometerControl) {
    ledcWrite(LED_2, intensity);
  }
}

void debounced_button() {

  int reading = digitalRead(BUTTON); // Lê o estado do botão
      
  if (reading != lastButtonState) { // Verifica se o estado do botão mudou
    lastDebounceTime = millis(); // Reseta o tempo de debounce
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) { // Se já passou o tempo de debounce
    if (reading != buttonState) { // Se o estado do botão mudou
      buttonState = reading;
      button();
    }
  }
  
  lastButtonState = reading; // Atualiza o estado anterior do botão
  
}

void button() {

  buttonState = digitalRead(BUTTON);

  // Se o botão for pressionado liga o LED Vermelho
  if (buttonState == HIGH) {
    monitorControl = false;
    digitalWrite(LED_1, HIGH);  
    if(debugMode) menu();
  } 
  else if(!monitorControl) { // Botão solto desliga se o monitor não controla
    digitalWrite(LED_1, LOW);   
    if(debugMode) menu();
  }

}


void carga(){ 
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcsljvnflamddklsm42km2l3l");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcsljv5mg3i02m0gi5mfnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcsljvn0im40imf0i2m0iwsmiwm2dflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcslj0im40im230iem032imvnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcslj809182039810983vnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkc0980291820390921sljvnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&092092129s0ksaoidmo)#%ldkfamslkcsljvnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcisojaijxoiajoisjsljvnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslk09jassxoasxnjdcsljvnflamdl");
  Serial.println("!@#(!*$)(@%*)%(*%#(&)#%ldkfamslkcsljvnf080880808lamdl");
}
// attachinterrupt ( por tempo ou por evento ) 
// blink se torna função com attachinterrupt time
// attachinterrupt evento butao
// após essas mudanças a carga não deve afetar o sistema
// sem variaveis nas funções de interrupt

void loop() {

  monitor_control();

  debounced_button(); //

  onboard_blink(); //
  
  potentiometer();

  if(cargaMode){
    carga();
  }

  delay(42);

}
