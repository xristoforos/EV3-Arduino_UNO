#include <Wire.h>
#include <dht.h>
#include "Timer.h" 
dht DHT;
int relay = 10;
int led1 = 13;
int led2 = 12;
int relay2 = 9;
#define DHT11_PIN 7
#define soilPower 6
#define SLAVE_ADDRESS 0x04
const unsigned long PERIOD2 = 120000;   //ten seconds
Timer t;                               //instantiate the timer object

int val2 = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 
//Variable for Soil moisture Power


int st, index=0;
char buf[8];
byte b[2];

byte b2[2];


void setup() 
{
    Serial.begin(9600);         // start serial for output
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
    pinMode(8, OUTPUT);
    pinMode (relay, OUTPUT);
    pinMode (relay2, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    t.oscillate(relay2, PERIOD2, HIGH);
    t.oscillate(led2, PERIOD2, HIGH);
     pinMode(soilPower, OUTPUT);//Set D6 as an OUTPUT
  digitalWrite(soilPower, LOW); 
}
int flag=0; int te;  uint8_t red;
uint8_t  val; int vul;
void loop()
{
  t.update(); 
    
int chk = DHT.read11(DHT11_PIN);
 // Serial.print("Temperature = ");
 // Serial.println(DHT.temperature);
 // Serial.print("Humidity = ");
  //Serial.println(DHT.humidity);
 // Serial.print("\n output3 = ");  
  //Serial.println(readSoil());
 //Serial.print(readSoil()); 


 //b[0]=readSoil();
   // b[1]=DHT.temperature;
   //  Serial.print( b[1]); 
  delay(1000);

 // Wire.write(val);
  if(flag==1)
   {
    // Serial.print(val);
     flag=0;
   }
}

void receiveData(int byteCount)
{int p=0;
       while(Wire.available()>0) 
    {
        //receive and replace all elements of new thisArray
     b2[p] = Wire.read(); 
    
     // val=Wire.read();
      

       p++;

         flag=1;
    }
      if (b2[5]==45){
       // Serial.print("0");
        Serial.print("A");
        Serial.print("\n");
        digitalWrite(8, HIGH);
        digitalWrite (relay, HIGH); 
        digitalWrite(led1, HIGH);
      }else if (b2[5]==0){
        Serial.print("B");
        Serial.print("\n");
        digitalWrite(8, LOW);
        digitalWrite (relay, LOW); 
        digitalWrite(led1, LOW);
      }
    
}

// callback for sending data
void sendData()
{
 // Serial.print("\n ____");  
 b[0]=readSoil();
    b[1]=DHT.temperature;
    // Serial.print( b[0]); 
   //  Serial.print("\n "); 
 //  Serial.print( b[1]); 
 Wire.write(b,2); 
/*val = DHT.temperature;    // read the value from the sensor 
if (DHT.temperature>25 and DHT.temperature<37){
val = DHT.temperature;  
 red = val;
//Serial.print("\n output3 = ");  
// Serial.print(red); 
 Wire.write(red); 
}else{
  Wire.write(28); 
  }*/
 
  //Serial.print("\n output3 = ");   
  
}
byte readSoil()
{

    digitalWrite(soilPower, HIGH);//turn D7 "On"
   // delay(1000);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
}
