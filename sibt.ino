#include <TinyGPS.h>
#include<SoftwareSerial.h>
SoftwareSerial Serial1(10,11);//GPS
TinyGPS gps;
unsigned long chars;
unsigned short sentences, failed_checksum;
char new1[15];
char new2[15]; 
String a;
void setup() {
Serial.begin(9600);
//Serial2.begin(9600);
Serial1.begin(9600);
}
//float olat=24.916571, olon=67.078946; 
//float lati=24.920733,lon=67.088162;
//float lati=24.951729,lon=67.002272;
float olat=0, olon=0; 
float lati,lon;
float b,c;
String o,z,u,j;
void loop() {
    GPS();
    b=abs(lati-olat);//abs for ignor -ve sign
    c=abs(lon-olon);
   olat=lati;
   olon=lon;
 if(b!=0 && c!=0)
  { 
    Serial.println(lati,6);
    Serial.println(lon,6);
  Serial.println("AT+CGATT=1");
  delay(2000);  
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//For connect GPRS
  delay(2000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"www\"");
  delay(2000);
  Serial.println("AT+SAPBR=1,1");//open GSM context
  delay(8000);
  Serial.println("AT+HTTPINIT");//Start session
  delay(2000);
  Serial.println("AT+HTTPPARA=\"URL\",\"http://blind-guide.000webhostapp.com/welcome.php?abcid=2340&loclat="+String(lati,6)+"&loclon="+String(lon,6)+"\"");
  delay(2000);
  Serial.println("AT+HTTPACTION=1");//Action completion
  delay(5000);
  Serial.println("AT+HTTPTERM");//For disconnect GPRS
  delay(5000);
  
 } 
 }
 void GPS(){ 
while(Serial1.available()>0){
 // Serial.println("hi");
byte  c=Serial1.read();
          if (gps.encode(c))
                  {
                   gps.f_get_position(&lati,&lon);
                   gps.stats(&chars, &sentences, &failed_checksum);
                  dtostrf(lati,7, 6, new1);
                  dtostrf(lon,7, 6, new2);
//                  a="CURRENT LOCATION\n""LATITUDE:"+(String)new1+"\n"+"LONGITUDE:"+(String)new2;
                    //lcd.setCursor(0,0);
                    Serial.print("LAT: ");
                    Serial.println(lati,6);
                    //lcd.print("LAT: ");
                    //lcd.print(lat,6);
                    //lcd.setCursor(0,1);
                    Serial.print("LONG:");
                    Serial.println(lon,6);  
                    //lcd.print("LONG:");
                    //lcd.print(lon,6);   
                    delay(5000);
                    //lcd.clear();
                   
                  } }}               
