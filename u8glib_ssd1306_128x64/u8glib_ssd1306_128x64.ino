// Programa: Teste Display OLED SSD1306
// Autor: FILIPEFLOP
 
#include "U8glib.h"
 
// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device
 
//U8GLIB_ST7920_192X32_4X u8g(10);      // SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 10, HW SPI
//U8GLIB_ST7920_202X32_1X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_1X u8g(18, 16, 17);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9); // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);     // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_PCF8812 u8g(13, 11, 10, 9, 8);     // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_ILI9325D_320x240 u8g(18,17,19,U8G_PIN_NONE,16 );           // 8Bit Com: D0..D7: 0,1,2,3,4,5,6,7 en=wr=18, cs=17, rs=19, rd=U8G_PIN_NONE, reset = 16
//U8GLIB_SBN1661_122X32 u8g(8,9,10,11,4,5,6,7,14,15, 17, U8G_PIN_NONE, 16);     // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 cs1=14, cs2=15,di=17,rw=16,reset = 16
//U8GLIB_SSD1306_128X64 u8g(10, 9);     // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST); // Fast I2C / TWI 
//U8GLIB_SSD1306_128X64_2X u8g(U8G_I2C_OPT_NONE);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

int temp() {
  // Sensor NTC em 3.5 com resistor de 10k
  double n=0; //numero que o pino A0 le
  double Rt=0; //resistencia calculada
  float t=0; //temperatura
  float v=3.5;//tensao no termistor
  n=analogRead(A0);
  v=5-(analogRead(A0)/1023.0)*5.0;//calculo da tensao no ntc
  Rt=(5*(10000/(5-v)))-10000; //calculo da resistencia do ntc no momento da leitura
  t=(1/(0.001229148+(0.000234125*log(Rt))+(0.0000000876741*pow(log(Rt),3))))-273.15;//equaÃ§Ã£o de Steinhart-Hart
  Serial.print("n= ");
  Serial.print(n);
  Serial.print("Tensao: ");
  Serial.print(v);
  Serial.print("\tResistencia: ");
  Serial.print(Rt);
  Serial.print("\tTemperatura: ");
  Serial.println(t);
  return t;
}

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

void printDigits(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);   
}

void ck() {
  long timeNow = millis();
  int days = timeNow / day; //number of days
  int hours = (timeNow % day) / hour; //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
  int minutes = ((timeNow % day) % hour) / minute ; //and so on...
  int seconds = (((timeNow % day) % hour) % minute) / second;
  
  // digital clock display of current time
 //Serial.print(days,DEC);  
 //printDigits(hours);  
 //printDigits(minutes);
 //printDigits(seconds);
 //Serial.println();
  //Hora
  u8g.setFont(u8g_font_fub30);
  //u8g.drawStr( 10, 57, "09:35");
  u8g.setPrintPos(10, 57);
  u8g.print(minutes);
  u8g.print(":");
  u8g.print(seconds);
  
  //Texto - AM
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr( 115, 33, "AM");
  
  //moldura relogio
  u8g.drawRFrame(0,18, 128, 46, 4);
}

void draw() 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Seleciona a fonte de texto
  u8g.setFont(u8g_font_8x13B);
  
  //Linha superior - temperatura 
  //u8g.drawStr( 5, 15, "23");
  u8g.setPrintPos(5, 15);
  u8g.print(temp());
  u8g.drawCircle(28,8,3);
  u8g.drawStr( 34, 15, "C");

  ck();
  
  //Desenho bateria
  u8g.drawRFrame(105, 3, 20,12 , 0); //box
  u8g.drawBox(125, 6, 2,6); // positivo
  //if (b == 0) {
    u8g.drawBox(107, 5, 4,8); // 1 barra
  //} else if (b == 1) {
    u8g.drawBox(112, 5, 4,8); // 2 barra
  //} else if (b == 2) {
    u8g.drawBox(117, 5, 4,8); // 3 barra
  //} else if (b == 3) {
    u8g.drawBox(122, 5, 2,8); // 1/2 barra
  //} else {
    //b=0;
  //}
    
  //Desenho linhas sinal
  u8g.drawVLine(99,0, 15);
  u8g.drawVLine(98,0, 15);
  u8g.drawVLine(96,4, 11);
  u8g.drawVLine(95,4, 11);
  u8g.drawVLine(93,8, 7);
  u8g.drawVLine(92,8, 7);
  u8g.drawVLine(90,12, 3);
  u8g.drawVLine(89,12, 3);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}
 
void loop() 
{
  u8g.firstPage();  
  do
  {
    draw();
  } while( u8g.nextPage() );
  delay(50);
}

