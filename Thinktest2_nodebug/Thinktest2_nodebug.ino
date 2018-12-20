//Credits: https://www.instructables.com/id/ESP8266-IOT-Using-Arduino-and-ThingSpeak/
//https://www.electronicshub.org/connect-esp8266-to-thingspeak/
// Es recomendable resetear la ESP en cada inicio
#include <SoftwareSerial.h>
#define DEBUG true
#define RX 2
#define TX 3

String HOST = "api.thingspeak.com";
String PORT = "80";
String AP = "Nosellama";
String PASS = "12345678";


String API = "Q23CTI6P3RYKN1XP";
//String API = "CBGALWS23J4ASMR5";
String field = "field1";

int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 0;

SoftwareSerial esp8266(RX,TX);

void setup() {
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  delay(50);
  pinMode(4,INPUT);
  delay(200);
  
  Serial.begin(57600);
  esp8266.begin(9600);
  
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=3",5,"OK");
  sendCommand("AT+CWJAP=""+ AP +"",""+ PASS +""",15,"OK");
  sendCommand("AT+CIPMUX=0",5,"OK");
  countTrueCommand = 0;
  
}

void loop() {
  valSensor = random(0,2); // random value, change with sensor value if using sensor
  sendData(valSensor);
}

void sendData(int data) {
  String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(data);
  switch(countTrueCommand) {

    case 0: sendCommand("AT",5,"OK");break;
    case 1: //sendCommand("AT+RST",10,"invalid");break;
    case 2: sendCommand("AT+CIPMUX?",5,"0"); break;
    //case 2: break;
    case 3: sendCommand("AT+CIPSTART=\"TCP\",\""+ HOST +"\""+","+PORT,15,"OK"); break;
    //case 4: sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">"); break;
    case 4: sendCommand("AT+CIPSEND=51",4,">"); break;
    case 5: esp8266.println(getData);delay(1500);countTrueCommand++; break;
    case 6: sendCommand("AT+CIPCLOSE",5,"OK"); break;
    case 7:

    if(DEBUG){
      Serial.println(data);
      Serial.print(getData);
      Serial.print(",");
      Serial.println(getData.length());
    }
    countTrueCommand = 0;
    delay(13000);
    break;
  }
}


void sendCommand(String command, int maxTime, char readReplay[]) {
  if(DEBUG){
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  }
  while(countTimeCommand < (maxTime*1)){
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay)){//ok
      found = true;
      break;
    }
    
  countTimeCommand++;
  }
  
  if(found == true){
    if(DEBUG){Serial.println("OYI");}
    
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false){
    if(DEBUG){Serial.println("Fail");}
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
}
