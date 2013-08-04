#define F_CPU 16000000
#define ARDUINO 100
#include "Arduino.h"

void setup();
void loop();

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	pinMode(11, OUTPUT);
}

void setupStuff(){
	setup();
}

int getLight(){
	return analogRead(0);
}

void printOut(char * str){
	Serial.println(str);
}

void setBuzz(int n){
	analogWrite(10, n);
}