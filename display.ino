
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <ctype.h>  



const char* ssid = "DDNETWORK";
const char* password = "DD95dd95DD";
const char* addres= "http://ddani.ddns.net/";

Adafruit_ST7735 tft = Adafruit_ST7735(16, 5, 4);//TFT_CS,  TFT_DC, TFT_RST);


void setup()
{
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(tft.getRotation()+2);
  
    tft.setTextColor(ST7735_BLUE);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(16, 60);
  tft.print("Booting"); // Start Print text to Line 1
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(17, 80);      
  
  
  WiFi.begin(ssid, password);
  tft.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    tft.print(".");
    delay(1000);
    
  }
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(17,80);
  tft.print("connected");


ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
  });
}


void loop()
{
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http1;  //Declare an object of class HTTPClient
    HTTPClient http2;
    HTTPClient httpH; 
    HTTPClient httpUpdate;
    HTTPClient httpM;
    HTTPClient httpDate;
    HTTPClient httpConds;
    HTTPClient httpFore;
    HTTPClient httpSky;
    HTTPClient httpRain;
    HTTPClient httpTodo;

    httpUpdate.begin("http://192.168.0.96/update/");
    httpUpdate.GET();
    
    http1.begin("http://192.168.0.96/display1/");  //Specify request destination
    int httpCode = http1.GET();                                                                  //Send the request

    http2.begin("http://192.168.0.96/display2/");  //Specify request destination
    int httpCode2 = http2.GET();
    
    httpH.begin("http://192.168.0.96/hour/");  //Specify request destination
    httpH.GET();

    httpM.begin("http://192.168.0.96/minute/");  //Specify request destination
    httpM.GET();
    httpDate.begin("http://192.168.0.96/date/");  //Specify request destination
    httpDate.GET();
    httpConds.begin("http://192.168.0.96/conds/");  //Specify request destination
    httpConds.GET();
    httpFore.begin("http://192.168.0.96/fore/");  //Specify request destination
    httpFore.GET();
    httpSky.begin("http://192.168.0.96/sky/");  //Specify request destination
    httpSky.GET();
    httpRain.begin("http://192.168.0.96/rain/");  //Specify request destination
    httpRain.GET();
    httpTodo.begin("http://192.168.0.96/todo/");  //Specify request destination
    httpTodo.GET();
 
    if (httpCode > 0) { //Check the returning code
      while(1 == atoi(httpUpdate.getString().c_str()) ){
        
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(17, 80);
        tft.print("UPDATE");
        
        ArduinoOTA.handle();
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(17, 80);
        tft.print("fail or wtf");
        delay(30);
      }
      //if(10 > atoi(httpH.getString().c_str()))
        //tft.noBacklight();
       //else
        //tft.backlight();
      tft.setCursor(0,0);
      tft.fillScreen(ST7735_BLACK);
      tft.print(http1.getString());   
      tft.setCursor(30,30);
      tft.setTextSize(2);
      tft.print(httpH.getString());
      tft.print(":");
      tft.print(httpM.getString());
      tft.setTextSize(1);
      tft.setCursor(0,10);
      printMid(httpDate.getString(),10);
      tft.setCursor(0,20);
      printMid(httpConds.getString(),20);
      
      tft.setCursor(0,47);
      tft.print("B");
      tft.setCursor(4,47);
      tft.print(":");
      
      drawDiag(httpFore.getString(), ST7735_BLUE, 144);

      tft.setCursor(0,61);
      tft.print("S");
      tft.setCursor(4,61);
      tft.print(":");

      tft.drawLine(0,57,128,57,ST7735_BLUE);

      drawDiag(httpSky.getString(), ST7735_BLUE, 116);

      tft.setCursor(0,75);
      tft.print("R");
      tft.setCursor(4,75);
      tft.print(":");
      
      tft.drawLine(0,71,128,71,ST7735_BLUE);
      
      drawDiag(httpRain.getString(), ST7735_BLUE, 130);

      tft.setCursor(0,89);
      tft.print("T");
      tft.setCursor(4,89);
      tft.print(":");

      tft.drawLine(0,85,128,85,ST7735_BLUE);
      
      drawDiag(http2.getString(), ST7735_BLUE, 102);//Print the response payload

      tft.setCursor(0,102);
      tft.print("Todo: ");
      tft.print(httpTodo.getString());

      tft.drawLine(0,99,128,99,ST7735_BLUE);
    }
 
    http1.end();
    http2.end();//Close connection
    httpH.end();
    httpUpdate.end();
    httpM.end();
    httpDate.end();
    httpConds.end();
    httpFore.end();
    httpSky.end();
    httpRain.end();
    httpFore.end();
 
  }
 
  //delay(300000);
for(int j=0;5000>j;j++){
  for( int i=0; 30>i ;i++)
    {
      tft.drawLine(0,120,128,120, ST7735_BLUE /30 *i);
      tft.drawLine(0,121,128,121, ST7735_BLUE /30 *i);
      tft.drawLine(0,122,128,122, ST7735_BLUE /30 *i);
      tft.drawLine(0,123,128,123, ST7735_BLUE /30 *i);
      tft.drawLine(0,124,128,124, ST7735_BLUE /30 *i);
      tft.drawLine(0,125,128,125, ST7735_BLUE /30 *i);
      tft.drawLine(0,126,128,126, ST7735_BLUE /30 *i);
      tft.drawLine(0,127,128,127, ST7735_BLUE /30 *i);
      delay(3000/30);
    }
    for( int i=30; i>0 ;i--)
    {
      tft.drawLine(0,120,128,120, ST7735_BLUE /30 *i);
      tft.drawLine(0,121,128,121, ST7735_BLUE /30 *i);
      tft.drawLine(0,122,128,122, ST7735_BLUE /30 *i);
      tft.drawLine(0,123,128,123, ST7735_BLUE /30 *i);
      tft.drawLine(0,124,128,124, ST7735_BLUE /30 *i);
      tft.drawLine(0,125,128,125, ST7735_BLUE /30 *i);
      tft.drawLine(0,126,128,126, ST7735_BLUE /30 *i);
      tft.drawLine(0,127,128,127, ST7735_BLUE /30 *i);
      delay(3000/30);
    }
}
  
}
//one char 6 pix wide 8 pix height
void drawDiag(String numbers, int16_t color, int y){
  if(3>numbers.length())
  {
    tft.setCursor(10,y-int('8'));
    tft.print("No Data");
    return;
  }
  int stp = 120/(numbers.length()-2);
  for(int i=0;numbers.length()-2>i;i++){
    
    tft.drawLine(8+i*stp, y-int(numbers.charAt(i)),8+(i+1)*stp, y-int(numbers.charAt(i+1)), color);
    tft.drawLine(8+i*stp, 1+y-int(numbers.charAt(i)),8+(i+1)*stp, 1+y-int(numbers.charAt(i+1)), color);
  }
}
void printMid(String str, int y){
  int space= (128-str.length()*6)/2;
  tft.setCursor(space,y);
  tft.print(str);
  //tft.print(space);
  
}

