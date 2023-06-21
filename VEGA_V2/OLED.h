#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oledPrint(String text, int fontSize=1, bool clear=false, bool newLine=false, bool refresh=false){
  if(clear)display.clearDisplay();
  display.setTextSize(fontSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(text);
  if(newLine)display.print("\n");
  if(refresh)display.display();
//  Serial.println(micros() - lastDisplay);
//  if(refresh && (micros() - lastDisplay > 250*1000)){
//    display.display();
//    lastDisplay = micros();
//  }else{
//    delayMicroseconds(250*1000 - (micros() - lastDisplay));
//    display.display();
//  }
//  lastDisplay = micros();
}

void SetupOLED(){
  Serial.print("SETTING UP OLED... ");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    return;
  }
  oledTimer = micros();
  oledPrint(" BLACK\nFALCON",2,true,true,true);
  Serial.println("DONE");
}

void LoopOLED(){
  
}
