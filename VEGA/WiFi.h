#include <esp8266.h>
//#include <Adafruit_ESP8266.h>

ESP8266Class esp(1);
//Adafruit_ESP8266 wifi(&esp, &Serial, -1);

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};
char payload[250]={0,};
int timeout=3;

void sendCommand(String cmd, long int timeoutSeconds){
  esp.print(cmd);esp.print("\r\n");
  long int now = micros();
  while(now+(timeoutSeconds*1000000) > micros()){
    if(esp.available()){
      Serial.print((char)esp.read());
    }
  }
}

 void SetupWifi(){
#ifdef ENABLE_WIFI
#else
  return;
#endif
  Serial.println("SETTING UP WIFI");
  esp.begin(9200);
  delay(500);
  sendCommand("AT+RST", 1); // OK
//  sendCommand("AT+");
//  sendCommand("AT", 1); // OK
//  sendCommand("AT+GMR", 1); // Board details
//  sendCommand("AT+CWAUTOCONN=0\", 1);
  sendCommand("AT+CWMODE=2", 1); // 3 -> bo90zth AP and Station mode, 2 -> hotspot
  sendCommand("AT+CWSAP=\"DEESHA - VEGA\",\"yametekudasai\",5,4",3);
//  sendCommand("AT+CWLAP", 5); // List APs
//  sendCommand("AT+CWJAP=\"VEGA_DRONE\",\"BlackFalcon69\"", 10); // Connect
  sendCommand("AT+CIFSR", 2); // IP
  sendCommand("AT+CIPMUX=1", 2); // Enable multiple connections
//  sendCommand("AT+CIPSTART=0,\"UDP\",\"0.0.0.0\",4445,4445,2", 5);
sendCommand("AT+CIPSERVER=1,8080\r\n",3);
delay(1000);
}


//void checkForRequest()
//{
//  if (esp.available())
//  {
//    Serial.write(esp.read());
//    
//    String request;
//    while (esp.available()) {
//      char c = esp.read();
//      request += c;
//  
//      // Check for the end of the request
//      if (request.endsWith("\r\n")) {
//        break;
//      }
//    }
//
//    if (request.indexOf("GET /data") != -1) // Check if the request is for "/data" endpoint
//    {
//      String jsonResponse = "{\"message\":\"Hello, world!\"}"; // JSON response
//      String response = "HTTP/1.1 200 OK\r\n";
//      response += "Content-Type: application/json\r\n";
//      response += "Connection: close\r\n\r\n";
//      response += jsonResponse;
//  
//      sendCommand("AT+CIPSEND=0," + String(response.length()), 2); // Send response length to client
//      delay(500);
//      sendCommand(response, 2); // Send the response
//      delay(500);
//      sendCommand("AT+CIPCLOSE=0", 2); // Close the connection
//    }
//  }
//  if (Serial.available())
//  {
//    esp.write(Serial.read());
//  }
//}
//
//void TalkToESP(){
//  if(Serial.available()){
//    String cmd = "";
//    while(Serial.available()){
//      char c = (char)Serial.read();
//      cmd += c;
//    }
//    Serial.print(cmd);
//    esp.print(cmd);
//  }
//  if(esp.available()){
//    while(esp.available()){
//      char c = (char)esp.read();
//      Serial.write(c);
//    }
//  }
//}
