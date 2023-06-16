#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeSerif12pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void writeText(String txt){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(txt);
  display.display();
//  display.startscrollleft(0x00, 0x0F);
}

void SetupOLED(){
  LOG Serial.println("INITIALISING OLED");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    LOG Serial.println(F("SSD1306 allocation failed"));
    display = false;
  }
//  display.setFont(&FreeSerif12pt7b);
  display.display();
  display.clearDisplay();
  LOG Serial.println("DONE!");
  writeText("BLACK\nFALCON");
}

long int prevDisp = micros();

int x = 20;
int y = 7;

void displayESCVals(){
  if(killed || crashed || !armed)return;
  if((prevDisp - micros()) > 250){
    display.clearDisplay();
    display.setCursor(x,y);
    display.print(ESCout_3);
    display.setCursor(x+70,y);
    display.print(ESCout_1);
    display.setCursor(x,y+15);
    display.print(ESCout_2);
    display.setCursor(x+70,y+15);
    display.print(ESCout_4);
    prevDisp = micros();
    display.display();
  }
}
