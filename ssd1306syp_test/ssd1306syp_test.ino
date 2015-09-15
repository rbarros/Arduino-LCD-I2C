#include <Adafruit_ssd1306syp.h>
#define SDA_PIN 8
#define SCL_PIN 9
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
void setup()
{
  delay(1000);
  display.initialize();
}
void loop()
{
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("25C    y:0      v1.0");
  /*
  u8g.drawVLine(99,0, 15);
  u8g.drawVLine(98,0, 15);
  u8g.drawVLine(96,4, 11);
  u8g.drawVLine(95,4, 11);
  u8g.drawVLine(93,8, 7);
  u8g.drawVLine(92,8, 7);
  u8g.drawVLine(90,12, 3);
  u8g.drawVLine(89,12, 3);
  */
  //display.drawLine(120, 0, 0, 0,WHITE);
  //display.drawLine(98, 0, 15, 1,WHITE);
  //display.drawLine(96, 4, 11, 1,WHITE);
  //display.drawLine(95, 4, 11, 1,WHITE);
  //display.drawLine(93, 8, 7, 1,WHITE);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.println("|||");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.update();
  delay(2000);
  display.clear();
}
