#define LED 18  //  LED on GPIO18

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, !digitalRead(LED));
  delay(100);
}
