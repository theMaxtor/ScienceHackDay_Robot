// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() {
	pinMode(SW_pin, INPUT);
	digitalWrite(SW_pin, HIGH);
	Serial.begin(9600);
}

void loop() {
	int button = digitalRead(SW_pin);
	int x = analogRead(X_pin);
	int y = analogRead(Y_pin);
	const int OFFSET = -512;

	Serial.print(x + OFFSET);
	Serial.print(" ");
	Serial.print(y + OFFSET);
	Serial.print(" ");
	Serial.println(!button);
	delay(500);
}
