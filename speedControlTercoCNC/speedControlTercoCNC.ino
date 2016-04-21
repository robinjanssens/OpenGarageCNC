const byte interruptPin = 2;
volatile int pulses = 0;
int ppr = 4;    //pulses per revolution
int startTime = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), counter, RISING);
  Serial.begin(9600);
}

void loop() {
  pulses = 0;   // reset cycle counter
  while( millis()-startTime >= 100 ) {}
  startTime = millis();
  int rps = (pulses/ppr)*10;      // revolutions per second
  int rpm = rps * 60;             // revolutions per minute
  Serial.println(rpm);
}

void counter() {
  pulses++;
}
