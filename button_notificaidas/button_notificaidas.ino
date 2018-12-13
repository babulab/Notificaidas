int pinIN = 5;
int pinOUT = 8;
int lectura;


void setup() {
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 65536;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinIN, INPUT);
  pinMode(pinOUT, OUTPUT);
  sei();//allow interrupts

}

void loop() {
  //digitalWrite(pinOUT, HIGH);
  lectura = digitalRead(pinIN);
  Serial.println(lectura);
  if(lectura==1){
    TIMSK1 = 0;
    TCNT1 = 0;
  }
  // put your main code here, to run repeatedly:
}


ISR(TIMER1_COMPA_vect){
  digitalWrite(pinOUT, HIGH);  
  while(1){
    Serial.println("asd");
  }
}




