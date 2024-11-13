#define ONBOARD_LED 2  // onboard LED on GPIO02
#define LED_1 18 // offboard LED on GPIO18
#define LED_2 5 // offboard LED on GPIO5
#define INTERVAL 3000 // blink onboard interval 

unsigned long previousMillis = 0;  

void setup() {
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  Serial.begin(9600);
}

void onboard_blink(){

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= INTERVAL) { 
    previousMillis = currentMillis; 
    digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED)); 
  }
   
  if(digitalRead(ONBOARD_LED))
    Serial.println("OOO");
  else 
    Serial.println("XXX");
}

void loop() {
  
  
  onboard_blink();
  
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

  
