#include <Wire.h>

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>


ESP8266WiFiMulti g_wifi;
WiFiServer g_server(3017);

struct JoyState
{
	int32_t m_leftRight;
	int32_t m_upDown;
	int32_t m_button;
} s_joystick;
const int MAX_VAL = 512;

void setup()
{
	s_joystick.m_leftRight = -100;
	s_joystick.m_upDown = 444;

	Serial.begin(9600);
	Serial.write("Starting up\n");
	g_wifi.addAP("WIFI NAME", "WIFI PASSWORD");

	Wire.begin(); 
}

void loop()
{
	if(g_wifi.run() == WL_CONNECTED)
	{
		static int connectedBefore = 0;
		if(!connectedBefore)
		{
			Serial.write("CONNECTED\n");
			IPAddress ip = WiFi.localIP();
			Serial.print("[WIFI] IP: ");
			Serial.println(ip);
			g_server.begin();
			connectedBefore = 1;
		}
	}

	const unsigned long UPDATE_THRESHOLD = 1000;
	static unsigned long lastUpdateTime = -UPDATE_THRESHOLD;
	unsigned long curTime = millis();
	if(curTime - lastUpdateTime >= UPDATE_THRESHOLD)
	{
		Wire.beginTransmission(9);
		Wire.write((char*)&s_joystick, sizeof(s_joystick));
		Wire.endTransmission();

		lastUpdateTime = curTime;
	}


	static WiFiClient client;
	if (client)
	{
		if (client.available() > 0)
		{
			int nBytes = client.read((uint8_t*)&s_joystick, sizeof(s_joystick));
			/*
			Serial.write("Got ");
			Serial.print(nBytes);
			Serial.print(" ");
			Serial.print(s_joystick.m_leftRight);
			Serial.print(" ");
			Serial.println(s_joystick.m_upDown);
			*/
		}
		delay(10);
	}
	else
	{
		client = g_server.available();
		if (client.connected())
		{
			Serial.println("Connected to client");   
		}
	}
}
