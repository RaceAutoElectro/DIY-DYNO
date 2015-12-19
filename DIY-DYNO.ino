// test software for DIY DYNO Hardware ------------12bit adc  , weader station , Map4 Bar, opto OUT ( Power Module for Retarder )---- works schematic is good ----

#define RELAY1 7
#define RELAY2 8
#define SELPIN 10 //Selection Pin 
#define DATAOUT 11//MOSI 
#define DATAIN  12//MISO 
#define SPICLOCK  13//Clock 
int readvalue;
int lm35;
int rh;
int mpx;
int hihv;


void setup(){ 
 //set pin modes 
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
 pinMode(SELPIN, OUTPUT); 
 pinMode(DATAOUT, OUTPUT); 
 pinMode(DATAIN, INPUT); 
 pinMode(SPICLOCK, OUTPUT); 
 //disable device to start with 
 digitalWrite(SELPIN,HIGH); 
 digitalWrite(DATAOUT,LOW); 
 digitalWrite(SPICLOCK,LOW); 

 int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
   int sensorValue2 = analogRead(A2);
  lm35 = ((5.0 * analogRead(A0) * 100.0) / 1024);
  mpx = ( analogRead(A1)  / 4);   
  hihv = (analogRead(A2)  ) ;
 Serial.begin(115200); 
} 
boolean relay1State = false; // Assume off to start with
boolean relay2State = false;
int read_adc(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}


void loop() { 
  {
  static int relayVal = 0;
  int cmd;

  while (Serial.available() > 0)
  {
    cmd = Serial.read();

    switch (cmd)
    {
   case '1':
{
   relay1State = !relay1State; // If true, make false. If false, make true
   digitalWrite(RELAY1, relay1State);
   break;
} 
   case '2':
{
   relay2State = !relay2State; // If true, make false. If false, make true
   digitalWrite(RELAY2, relay2State);
   break;

    case '3':
{ 
  
 
   Serial.print(" temp: "); 
 Serial.print(lm35,DEC);
 Serial.print(" "); 
 Serial.print(" kpa: ");
  Serial.print(mpx,DEC);
  Serial.print(" "); 
  Serial.print(" rh: ");
   Serial.print(hihv,DEC);
    Serial.println(" "); 
   Serial.println( '\n' );
   
   
   
   
          case '5':
{ 
   Serial.print("5"); 
 readvalue = read_adc(1); 
 Serial.print(readvalue,DEC);
  Serial.print(","); 
   
       case '?':
{ 
   Serial.print("?"); 
 readvalue = read_adc(1); 
 Serial.print(readvalue,DEC);
  Serial.print(","); 
 readvalue = read_adc(2); 
 Serial.print(readvalue,DEC);
  Serial.print(","); 
 readvalue = read_adc(3); 
 Serial.print(readvalue,DEC);
 Serial.print(",");  
 readvalue = read_adc(4); 
 Serial.print(readvalue,DEC); 
 Serial.print(","); 
 readvalue = read_adc(5); 
 Serial.print(readvalue,DEC); 
 readvalue = read_adc(6);
 Serial.print(",");  
 Serial.print(readvalue,DEC); 
 readvalue = read_adc(7); 
  Serial.print(","); 
 Serial.print(readvalue,DEC); 
 readvalue = read_adc(8); 
  Serial.print(","); 
 Serial.print(readvalue,DEC);
 Serial.print( '\n' );
 
   
  break;
} 



} 
   default:
        {
          Serial.println("There are only 2 options Relay 1 or Relay 2");
      }
    }
  }
  } 

 
 delay(10); 
}   } }
