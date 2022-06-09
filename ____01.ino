  #define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "";


const char ssid[] = "";
const char pass[] = "";

int logic;
int lockloop;
int cout;
int multiply;

WidgetLED led1(V1);





void setup() {
  
  lcd.begin();
  lcd.display();        //เปิดหน้าจอ
  lcd.backlight();      //เปิดไฟ backlight 
  lcd.clear();          //ล้างหน้าจอ
  
  EEPROM.begin(512);
  //EEPROM.put(0, 0);
  //EEPROM.put(50, 0);
  EEPROM.get(0, cout);
  EEPROM.commit();
  EEPROM.get(50, multiply);
  EEPROM.commit();
  
   Serial.begin(9600);
    WiFi.begin(ssid, pass);
   Blynk.config(auth,);

 pinMode(16, OUTPUT);
 digitalWrite(16, HIGH);
 

}

void loop() {
if(WiFi.status() != WL_CONNECTED) { 
   
    Serial.println("Connecting...  ");  
    
    Serial.printf("Connection Status: %d\n", WiFi.status()); 
    
  }
 else { 
  Serial.print("Wi-Fi connected."); 
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());  // ทำการ Print IP ที่ได้รับมาจาก 
};

  
 int State = analogRead(A0);
 Serial.println(State);
 Serial.print("\n");
int StateV2 = map(State, 0, 1023, 100, 0);
 Serial.println(StateV2);
 Serial.print("\n");


if(StateV2 < 30){
  digitalWrite(16, LOW);
 led1.on();
 Blynk.virtualWrite(V3,"ทำงาน");
 logic = 1; 
  }
  
else{
digitalWrite(16, HIGH);
 Blynk.virtualWrite(V3,"ไม่ทำงาน");
 led1.off();
 logic = 0; 
};
 Blynk.virtualWrite(V0,StateV2);

if(logic == 1){
 if( lockloop == 1 ){
  lockloop = 0;
  cout ++;
  EEPROM.put(0, cout);
  EEPROM.commit();

  };
  }
else{
  lockloop = 1;
  
  };  

  if (cout==250){ //saveระบบ
    EEPROM.put(0, 0);
    EEPROM.commit();
    multiply ++;
    EEPROM.put(50, multiply);
    EEPROM.commit();
    };
    if (multiply==250){ //saveระบบ
    EEPROM.put(0, 0);
    EEPROM.put(50, 0);
    EEPROM.commit();
    };
    
int save = ((multiply*250)+cout);
Serial.println(save);
Blynk.virtualWrite(V4,save);
lcd.clear();

lcd.setCursor(0, 0);
  lcd.print("humidity :");
  lcd.setCursor(11, 0); 
  lcd.print(StateV2);
  lcd.setCursor(14, 0);  
  lcd.print("%"); 
  lcd.setCursor(0, 1);
  lcd.print("Counter  :"); 
  lcd.setCursor(11, 1);
  lcd.print(save);
  
  delay(500);
  


 Blynk.run();
}
