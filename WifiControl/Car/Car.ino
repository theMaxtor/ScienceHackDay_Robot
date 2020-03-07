#include <Wire.h>

struct JoyState
{
	int32_t m_leftRight;
	int32_t m_upDown;
	int32_t m_button;
} s_joystick;
const int MAX_VAL = 512;

void setup()
{
	Serial.begin(9600);
	Serial.write("Starting up\n");

	Wire.begin(9); 
	Wire.onReceive(receiveEvent);
}

void loop()
{
}

void receiveEvent(int count) {

	char* js = (char*)&s_joystick;

	for(int c = 0; c < count; c++)
	{
		js[c] = Wire.read();
	}
#if 0
	Serial.print("Got ");
	Serial.print(count);
	Serial.print(" bytes: ");
	Serial.print(s_joystick.m_leftRight);
	Serial.print("/");
	Serial.print(s_joystick.m_upDown);
	Serial.print("/");
	Serial.println(s_joystick.m_button);
#endif
}
