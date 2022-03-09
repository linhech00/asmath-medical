#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Wifi.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "wifi_symbol.h"

#define SCK     (18)
#define DIN     (23)
#define DC      (4)
#define CE      (5)
#define RST     (32)

Adafruit_PCD8544 display = Adafruit_PCD8544(SCK, DIN, DC, CE, RST);

int	gSysValue = 118;
int	gDiaValue = 78;

typedef enum
{
  WL_STRONG,
  WL_NORMAL,
  WL_POOR,
  WL_UNUSABLE
}WiFiSignalStrength;

String ssid = "B5-107";
String password = "0947656027";

void print_para();
void print_symbol(void);
WiFiSignalStrength getWiFiSignalStrength(void);


void setup()   {
	Serial.begin(9600);

	//Initialize Display
	display.begin();

	// you can change the contrast around to adapt the display for the best viewing!
	display.setContrast(25);

	// Clear the buffer.
	display.clearDisplay();

	WiFi.disconnect();
  	WiFi.mode(WIFI_STA);
  	WiFi.begin(ssid.c_str(), password.c_str());
  	while (WiFi.status() != WL_CONNECTED){
		Serial.print(".");
		delay(50);
	}
	Serial.print("WF CONNECTED");


}

void loop() {
	
	display.clearDisplay();
	print_symbol();
	print_para();
	display.display();

	// test para
	gSysValue++;
	gDiaValue++;
	delay(500);
	Serial.println(gSysValue);
	Serial.println(gDiaValue);

}

void print_para(){

	// SYS display
	display.setTextColor(BLACK);
	display.setCursor(0,27);
	display.setTextSize(1);
	display.print("SYS: ");
	display.setCursor(26,27);
	display.print(gSysValue);
	display.setCursor(60,27);
	display.print("mmHg");
	delay(50);

	// SYS display
	display.setTextColor(BLACK);
	display.setCursor(0,39);
	display.setTextSize(1);
	display.print("DIA: ");
	display.setCursor(26,39);
	display.print(gDiaValue);
	display.setCursor(60,39);
	display.print("mmHg");
	delay(50);
}

void print_symbol(){

	WiFiSignalStrength state = getWiFiSignalStrength();
 
//	if(state > 3){state = 0;}
//	Serial.println(state);
	// Display bitmap
	if(state == WL_STRONG){
		display.drawBitmap(60, 0,  WS1, 24, 16, BLACK);
		delay(10);
	}else if(state == WL_NORMAL){
		display.drawBitmap(60, 0,  WS2, 24, 16, BLACK);
		delay(10);		
	}else if(state == WL_POOR){
		display.drawBitmap(60, 0,  WS3, 24, 16, BLACK);
		delay(10);		
	}else if(state == WL_UNUSABLE){
		display.drawBitmap(60, 0,  WS0, 24, 16, BLACK);
		delay(10);		
	}
//	state++;
	display.drawBitmap(0, 0,  HEART, 30, 25, BLACK);
	delay(10);
	display.drawBitmap(36, 0,  BAT, 27, 16, BLACK);
	delay(50);

}
/* */
WiFiSignalStrength getWiFiSignalStrength()
{
  WiFiSignalStrength result = WL_UNUSABLE;
  int16_t rssi = WiFi.RSSI();
  Serial.println(rssi);
  if (rssi < (-90))
  {
    result = WL_UNUSABLE;
  }
  else if (rssi < (-70))
  {
    result = WL_POOR;
  }
  else if (rssi < (-35))
  {
    result = WL_NORMAL;
  }
  else if (rssi < 0)
  {
    result = WL_STRONG;
  }
  return result;
}

