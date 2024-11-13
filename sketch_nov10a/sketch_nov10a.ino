#define BUTTON 4  // Pino D4

int buttonState = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(digitalRead(BUTTON))
      buttonState = HIGH;

   
  if (buttonState == LOW) {
        Serial.println("OOO");    // Envia "OOO" para o serial
      } else {
        Serial.println("XXX");    // Envia "XXX" para o serial
      }
}
