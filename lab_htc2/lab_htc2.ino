//------------------- Include the NodeMCU ESP8266 Library ---------------------------------
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
//-----------------------------------------------------------------------------------------
#define ON_Board_LED 14           //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define time_delay 120
#define button1 5
#define button2 4
#define button3 0
#define led1 12
#define led2 13
#define led3 15
const int buzzer = 16;

//----------------------------------------SSID dan Password wifi mu gan.-------------------
const char* ssid = "TP-Link_BFF2";            //--> Name Wifi / SSID.
const char* password = "39497680";            //-->  Password wifi .
//----------------------------------------Host & httpsPort---------------------------------
const char* host = "script.google.com";
const int httpsPort = 443;
//-----------------------------------------------------------------------------------------
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
//================== spreadsheet script ID ================================================
 
String GAS_ID = "AKfycbzH_RqUrnOlx3qjvoqss2_QSvl0jlUDqdv9So5YT7aC4e1eL-A4_XMBSpLOPZhhs9nucA"; // test v1

//==================== void setup =========================================================

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> 

  //------------------Botton Setup-----------------------------
 
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  pinMode(buzzer,OUTPUT);

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  client.setInsecure();
}

//========================== Loop ==============================
void loop() {
    String id = "1179900468705";
    String hsts = "0";
    String help = "%E0%B8%A3%E0%B8%AD"; 
//==============================================================
  if(digitalRead(button1) == LOW){
    Serial.println("button 1 is pressed");
    digitalWrite(led1, HIGH);
    tone(buzzer, 2000); 
    delay(100);
    tone(buzzer, 0);
        
        hsts = "%E0%B8%82%E0%B8%AD%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%8A%E0%B9%88%E0%B8%A7%E0%B8%A2%E0%B9%80%E0%B8%AB%E0%B8%A5%E0%B8%B7%E0%B8%AD"; 
        //ขอความช่วยเหลือ
        
        sendData(id,hsts,help);
        delay(time_delay);
        tone(buzzer, 1000); 
        delay(100);
        tone(buzzer, 0);
        
  }else{
    digitalWrite(led1, LOW);
    delay(time_delay);
  }
//==============================================================  
  if(digitalRead(button2) == LOW){
    Serial.println("button 2 is pressed");
    digitalWrite(led2, HIGH);
    tone(buzzer, 2000); 
    delay(100);
    tone(buzzer, 0);
        
        hsts = "%E0%B8%82%E0%B8%AD%E0%B8%84%E0%B8%B3%E0%B9%81%E0%B8%99%E0%B8%B0%E0%B8%99%E0%B8%B3";
        //ขอคำแนะนำ
        
        sendData(id,hsts,help);
        delay(time_delay);
        tone(buzzer, 1000); 
        delay(100);
        tone(buzzer, 0);

  }else{
    digitalWrite(led2, LOW);
    delay(time_delay);
  }
//==============================================================    
  if(digitalRead(button3) == LOW){
    Serial.println("button 3 is pressed");
    digitalWrite(led3, HIGH);
    tone(buzzer, 2000); 
    delay(100);
    tone(buzzer, 0);
    
        hsts = "%E0%B8%82%E0%B8%AD%E0%B8%A3%E0%B8%B1%E0%B8%9A%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%80%E0%B8%9D%E0%B9%89%E0%B8%B2%E0%B8%A3%E0%B8%B0%E0%B8%A7%E0%B8%B1%E0%B8%87";
        //ขอรับการเฝ้าระวัง 
         
        sendData(id,hsts,help);
        delay(time_delay);
        tone(buzzer, 1000); 
        delay(100);
        tone(buzzer, 0);
        
  }else{
    digitalWrite(led3, LOW);
    delay(time_delay);
  }
//============================================================== 
//---------------Send Data---------------=--------
//    sendData(id,hsts,help);
  
//  }
}
//*****
//======== [Function] Send Data to Google Sheet============================

void sendData(String value1,String value2,String value3) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //------------------Connect to Google host -------------------------------
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //-------------------------------------------------------------------------

  //------------------------- Proses dan kirim data ------------------------- 

  String string_id = value1; 
  String string_hsts = value2;
  String string_help = value3;
  String url = "/macros/s/" + GAS_ID + "/exec?idmember=" + string_id + "&hsts="+ string_hsts +"&help=" + string_help; //  3 variables 
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------
  
  //---------------------------------------
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();

  //----------------------------------------
} 
/*
AKfycbynlnUT3d0UylxfsNThdFc9mk159hf3DLd9Qe3Ehj0maCRm3RenYDEkU9ZdSDhFckvQDQ
https://script.google.com/macros/s/AKfycbynlnUT3d0UylxfsNThdFc9mk159hf3DLd9Qe3Ehj0maCRm3RenYDEkU9ZdSDhFckvQDQ/exec
*/
