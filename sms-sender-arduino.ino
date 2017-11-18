// Works on Arduino IDE 1.0.6 using this library: http://downloads.arduino.cc/GSM-Arduino-1.0.7-afc368b.zip
// Serial Monitor must be configured to understand that a new line is a line ending symbol.

#include <GSM.h>

#define PIN_NUMBER "4463"

GSM gsmAccess;
GSM_SMS sms;

void setup() {
    Serial.begin(9600);
    
    connectGsm();
}

void loop() {
    readSerial();
}

void connectGsm() {
    Serial.println("Connecting to GSM network...");

    boolean connected = false;
    
    while (!connected) {
        if (gsmAccess.begin(PIN_NUMBER) == GSM_READY) {
            Serial.println("Connected to GSM network!");
            connected = true;
        } else {
            Serial.println("Connection to GSM network failed, trying again...");
            delay(1000);
        }
    }
}

void sendSms(char *number, char *text) {
    Serial.println("Sending SMS...");
    sms.beginSMS(number);
    sms.print(text);
    sms.endSMS();
    Serial.println("SMS is sent!");
}

String readSerial() {
    String content;

    if (Serial.available()) {
        content = Serial.readStringUntil('\n');
    }

    if (content != "") {
        Serial.println("Got input: " + content);
    }

    return content;
}
