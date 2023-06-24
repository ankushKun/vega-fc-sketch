#include <UARTClass.h>

UARTClass esp(1);

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};
char payload[250]={0,};
int timeout=3;

void sendCommand(String cmd, long int timeoutSeconds){
  Serial.print("CMD: ");Serial.println(cmd);
  esp.print(cmd);esp.print("\r\n");
  long int now = micros();
  while(now+(timeoutSeconds*1000000) > micros()){
    if(esp.available()){
      Serial.print((char)esp.read());
    }
  }
}

 void SetupWIFI(){
#ifdef ENABLE_WIFI
#else
  return;
#endif
  Serial.println("SETTING UP WIFI");
  oledPrint("SETTING UP WIFI...",1,true,true,true);
  esp.begin(115200);
  delay(500);
//  sendCommand("AT+RST", 1); // OK
  sendCommand("AT", 1); // OK
  sendCommand("ATE0", 1); // echo
//  sendCommand("AT+GMR", 1); // Board details
//  sendCommand("AT+CWAUTOCONN=0", 1); // Disable autoconnect
  sendCommand("AT+CWMODE=2", 1); // 3 -> both AP and Station mode, 2 -> hotspot
  sendCommand("AT+CIPMUX=1", 2); // Enable multiple connections
//  sendCommand("AT+CWLAP", 5); // List APs
//  sendCommand("AT+CWJAP=\"Redmi Note 11T 5G\",\"123456789\"", 10); // Connect to AP
  sendCommand("AT+CWSAP=\"DEESHA - VEGA\",\"yametekudasai\",1,4",3); // Setup AP
  sendCommand("AT+CIPSERVER=1,80",3);// Open server on port 80
  sendCommand("AT+CIFSR", 2); // IP
  oledPrint("DONE...",1,true,true,true);
  delay(1000);
}

long lastUpdate = micros();
void LoopWIFI(){
  if(micros() - lastUpdate > 50*1000){
    char data[256];
    // rollAngle, pitchAngle, yawAngle
    // throttleIN, rollIN, pitchIN, yawIN
    // ESC1, ESC2, ESC3, ESC4
    // armed, killed, crashed;
    sprintf(data, "HTTP/1.1 200 OK\r\n\r\n>%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;\n",
      (int)AngleRoll, (int)AnglePitch, (int)AngleYaw,
      input_THROTTLE, input_ROLL, input_PITCH, input_YAW,
      ESCout_1, ESCout_2, ESCout_3, ESCout_4,
      (int)armed, (int)killed, (int)crashed
    );

    char command[256];
    sprintf(command, "AT+CIPSEND=0,%d\r\n", strlen(data));

//  Serial.println(command);
  esp.print(command);
  delay(1);
//  Serial.println(data);
  esp.print(data);
  delay(1);
  esp.print("AT+CIPCLOSE=0\r\n");
  delay(1);
  }
}
