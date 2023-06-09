#include <esp8266.h>

ESP8266Class esp(1);

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};
char payload[250]={0,};
int timeout=3;

void sendCommand(String cmd, long int timeoutSeconds){
  esp.print(cmd);
  long int now = micros();
  while(now+(timeoutSeconds*1000000) > micros()){
    if(esp.available()){
      Serial.print((char)esp.read());
    }
  }
}

 void SetupWifi(){
  Serial.println("-> SETTING UP WIFI");
  esp.begin(9200);
  delay(500);
  sendCommand("AT+RST\r\n", 1); // OK
  delay(500);
//  sendCommand("AT\r\n", 1); // OK
//  delay(500);
//  sendCommand("AT+GMR\r\n", 1); // Board details
//  delay(500);
//  sendCommand("AT+CWAUTOCONN=0\r\n", 1);
//  delay(500);
//  sendCommand("AT+CWMODE=1\r\n", 1); // 3 -> bo90zth AP and Station mode
//  delay(500);
//  sendCommand("AT+CWLAP\r\n", 5); // List APs
  sendCommand("AT+CWJAP=\"VEGA_DRONE\",\"BlackFalcon69\"\r\n", 10); // Connect
  delay(500);
  sendCommand("AT+CIFSR\r\n", 2); // IP
  delay(500);
  sendCommand("AT+CIPMUX=1\r\n", 2); // Enable multiple connections
  delay(500);
  sendCommand("AT+CIPSTART=0,\"UDP\",\"0.0.0.0\",4445,4445,2\r\n", 5);
}

// 9056766001

void parseInput(String inputString) {
  int separatorPos = inputString.indexOf(';');  // Find the first separator (;)
  
  if (separatorPos != -1) {
    String rollString = inputString.substring(0, separatorPos);  // Extract the substring before the first separator
    input_ROLL = rollString.toInt();  // Convert the substring to a double value and assign it to the 'roll' variable
    
    int separatorPos2 = inputString.indexOf(';', separatorPos + 1);  // Find the second separator (;)
    
    if (separatorPos2 != -1) {
      String pitchString = inputString.substring(separatorPos + 1, separatorPos2);  // Extract the substring between the first and second separators
      input_PITCH = pitchString.toInt();  // Convert the substring to a double value and assign it to the 'pitch' variable
      
      String throttleString = inputString.substring(separatorPos2 + 1);  // Extract the substring after the second separator
      input_THROTTLE = map(throttleString.toInt(), 0, 100, 1100, 2000);  // Convert the substring to a double value and assign it to the 'throttle' variable
    }
  }
}

void CheckUDP(){
  if(esp.available()){
    String espIn = "";
    while(esp.available()){
      char c = (char)esp.read();
      if(c=='\n')break;
      espIn = espIn + c;
    }
    Serial.println(espIn);
    parseInput(espIn);
    Serial.print(input_PITCH);Serial.print("\t");
    Serial.print(input_ROLL);Serial.print("\t");
    Serial.print(input_THROTTLE);Serial.print("\t");
  }
}

//void loop() { 
//  sendCommand("AT+CIPMUX=1",3,"OK");  // This AT Command is used to enable or disable multiple TCP Connections. (0: Single connection, 1: Multiple connections)
//  memset(atcommand,0,250);
//  sprintf(atcommand,"AT+CIPSTART=0,\"TCP\",\"%s\",%d", HOST, PORT);    // to establish one of the three connections: TCP, UDP or SSL. 
//  sendCommand(atcommand,3,"OK");
//  memset(atcommand,0,250);
//   memset(data,0,250);
//  sprintf(data,"{\"value\": %d}",getSensorData());
//  sprintf(payload,"POST %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nX-AIO-Key: %s\r\nContent-Length: %d\r\n\r\n%s",URL, HOST, KEY, strlen(data),data);
//  sprintf(atcommand,"AT+CIPSEND=0,%d",strlen(payload));  //  to start sending data in transparent transmission mode.
//  sendCommand(atcommand,4,">");
//  esp8266.println(payload);
//  countTrueCommand++;
//  delay(2000);
//  sendCommand("AT+CIPCLOSE=0",5,"OK");  // Closes TCP/UDP/SSL connection 
//}
