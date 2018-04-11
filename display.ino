
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>



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

    httpUpdate.begin("http://ddani.ddns.net/update/");
    httpUpdate.GET();
    
    http1.begin("http://ddani.ddns.net/display1/");  //Specify request destination
    int httpCode = http1.GET();                                                                  //Send the request

    http2.begin("http://ddani.ddns.net/display2/");  //Specify request destination
    int httpCode2 = http2.GET();
    
    httpH.begin("http://ddani.ddns.net/hour/");  //Specify request destination
    httpH.GET();

    httpM.begin("http://ddani.ddns.net/minute/");  //Specify request destination
    httpM.GET();
    httpDate.begin("http://ddani.ddns.net/date/");  //Specify request destination
    httpDate.GET();
 
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
      String payload = http1.getString();   //Get the request response payload
      tft.setCursor(0,0);
      tft.fillScreen(ST7735_BLACK);
      tft.print(payload);   
      tft.setCursor(50,10);
      tft.print(httpH.getString());
      tft.print(":");
      tft.print(httpM.getString());
      tft.setCursor(0,20);
      tft.print(httpDate.getString());
      drawDiag(http2.getString(), ST7735_CYAN, 175);//Print the response payload
 
    }
 
    http1.end();
    http2.end();//Close connection
    httpH.end();
    httpUpdate.end();
    httpM.end();
    httpDate.end();
 
  }
 
  delay(300000);
  
}

void drawDiag(String numbers, int16_t color, int y){
  int stp = 128/numbers.length();
  for(int i=0;numbers.length()-1>i;i++)
    tft.drawLine(i*stp, y-int(numbers.charAt(i)),(i+1)*stp, y-int(numbers.charAt(i+1)), color);
}
