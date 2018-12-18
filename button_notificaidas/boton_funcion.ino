int pinIN = 5;
int pinOUT = 8;
int lectura;
//int ciclos = 3;
int contador = 0;
int i=0;

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
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinIN, INPUT);
  pinMode(pinOUT, OUTPUT);
  sei();//allow interrupts
  TIMSK1 = 0;
}

int boton(int pin_IN, int ciclos){
  int flag = 0;
  TCNT1 = 0;
  contador = 0;
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  while (contador< ciclos){
    lectura = digitalRead(pin_IN);
    Serial.print(lectura);
    Serial.print("\t");
    Serial.println(contador);
    if (lectura==1){
      TIMSK1 = 0;
      TCNT1 = 0;
      flag = 1;
      break;
    }
  }
  TIMSK1 = 0;
  return flag;
}


ISR(TIMER1_COMPA_vect){
  contador= contador+1;
  TCNT1  = 0;
}


void loop() {
  while (i<3){
    Serial.println("asd");
    int asd = boton(pinIN, 3);
    digitalWrite(pinOUT, ~asd&1);
    delay(1000);
    i = i+1;
    Serial.print("i\t");
    Serial.print(i);
    Serial.print("\t");
    Serial.println(~asd, BIN);
    Serial.println((~asd&1), BIN);
  }
 
  
  
  // put your main code here, to run repeatedly:

}
