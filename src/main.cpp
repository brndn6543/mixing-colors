#include <Arduino.h>
#include <map>

int redPin = 11;
int bluePin = 10;
int greenPin = 6;
int baudRate = 9600;

String inputString = "";
String promptColor = "[+] Please provide a color (red, green, blue, cyan, magenta, white, orange, yellow), or off: ";
String promptBrightness = "[+] Please input your desired brightness (1-10): ";
char receivedChar;

std::map<String, std::tuple<int, int, int>> colorMap = {
	{"red", {255, 0, 0}},
	{"green", {0, 255, 0}},
	{"blue", {0, 0, 255}},
	{"cyan", {0, 255, 255}},
	{"magenta", {255, 0, 255}},
	{"white", {255, 255, 255}},
	{"orange", {255, 165, 0}},
	{"yellow", {255, 255, 0}}
};

void setColor(int r, int g, int b, int brightness) {
	int pwmRed = map(r * brightness, 0, 2550, 0, 255);
	int pwmGreen = map(g * brightness, 0, 2550, 0, 255);
	int pwmBlue = map(b * brightness, 0, 2550, 0, 255);

	analogWrite(redPin, pwmRed);
	analogWrite(greenPin, pwmGreen);
	analogWrite(bluePin, pwmBlue);
}

void handleInput(String& inputString) {
	inputString.toLowerCase();

	if (colorMap.count(inputString)) {
		Serial.print(promptBrightness);
		String brightnessInput = "";

		while (true) {
			if (Serial.available()) {
				receivedChar = Serial.read();

				if (receivedChar == '\n' || receivedChar == '\r') {
					if (brightnessInput.length() > 0) break;
				}
				else if (receivedChar >= '0' && receivedChar <= '9') {
					brightnessInput += receivedChar;
					Serial.print(receivedChar);
				}
			}
		}
		Serial.println();

		int brightness = brightnessInput.toInt();
		brightness = constrain(brightness, 1, 10);

		auto [r, g, b] = colorMap[inputString];
		setColor(r, g, b, brightness);

	} else if (inputString == "off") {
		setColor(0, 0, 0, 0);
	} else {
		Serial.println("[-] You entered an invalid value, try again.");
	}
}

void setup() {
	Serial.begin(baudRate);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	while (!Serial) {};
}

void loop() {
	Serial.print(promptColor);
	inputString = "";

	while (true) {
		if (Serial.available()) {
			receivedChar = Serial.read();

			if (receivedChar == '\n' || receivedChar == '\r') {
				if (inputString.length() > 0) break;
			}
			else if (receivedChar == 8 || receivedChar == 127) {
				if (inputString.length() > 0) {
					inputString.remove(inputString.length() - 1);
					Serial.print("\b \b");
				}
			}
			else if (receivedChar >= 32 && receivedChar < 126) {
				inputString += receivedChar;
				Serial.print(receivedChar);
			}
		}
	}
	Serial.println();
	handleInput(inputString);
}