#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
#include <SparkFun_MAG3110.h>


MAG3110 mag = MAG3110(); //Instantiate MAG3110

int signal;
int distance1;
unsigned long pulseduration1=0;
int x, y, z;

void setup() {
  Serial.begin(9600);
  signal=8;
  pinMode(signal, OUTPUT);
  Serial.begin(9600);
  signal=7;
  pinMode(signal, OUTPUT);
  mag.initialize(); //Initializes the mag sensor
  mag.start();      //Puts the sensor in active mode
}

void measureDistance1()
{
 signal=8;
 // set pin as output so we can send a pulse
 pinMode(signal, OUTPUT);
// set output to LOW
 digitalWrite(signal, LOW);
 delayMicroseconds(5);

 // now send the 5uS pulse out to activate Ping)))
 digitalWrite(signal, HIGH);
 delayMicroseconds(5);
 digitalWrite(signal, LOW);

 // now we need to change the digital pin
 // to input to read the incoming pulse
 pinMode(signal, INPUT);
 // finally, measure the length of the incoming pulse
 pulseduration1=pulseIn(signal, HIGH);
}

int distance2;
unsigned long pulseduration2=0;

void measureDistance2()
{
  signal=7;
 // set pin as output so we can send a pulse
 pinMode(signal, OUTPUT);
// set output to LOW
 digitalWrite(signal, LOW);
 delayMicroseconds(5);

 // now send the 5uS pulse out to activate Ping)))
 digitalWrite(signal, HIGH);
 delayMicroseconds(5);
 digitalWrite(signal, LOW);

 // now we need to change the digital pin
 // to input to read the incoming pulse
 pinMode(signal, INPUT);
 // finally, measure the length of the incoming pulse
 pulseduration2=pulseIn(signal, HIGH);
}

void loop() {

   // get the raw measurement data from Ping)))
 measureDistance1();
 measureDistance2();
 // divide the pulse length by half
 pulseduration1=pulseduration1/2;
 pulseduration2=pulseduration2/2;
 // now convert to centimetres. We're metric here people...
 distance1 = int(pulseduration1/29);
 distance2 = int(pulseduration2/29);

 if(mag.dataReady()) {
    //Read the data
    mag.readMag(&x, &y, &z);
  }

 if(distance1<30 and distance2<30 and y > 300 ){
     Serial.println("---Occupe---");
     Serial.println(distance1);
     Serial.println(distance2);
     Serial.println(y);
     delay(1000);
  }
  else if(distance1<30 and distance2<30 and y <= 300 ){
     Serial.println("---Alert---");
     Serial.println(distance1);
     Serial.println(distance2);
     Serial.println(y);
     delay(1000);
  }
  else{
     Serial.println("---Libre----");
     Serial.println(distance1);
     Serial.println(distance2);
     Serial.println(y);
     delay(1000);
  }

}
