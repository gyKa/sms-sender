// Works on Arduino IDE 1.0.6 using this library: http://downloads.arduino.cc/GSM-Arduino-1.0.7-afc368b.zip
// Serial Monitor must be configured to understand that a new line is a line ending symbol.

#include <GSM.h>

#define PIN_NUMBER "4463"
#define LED_GSM_STATUS_PIN A0

#define SMS_SEPARATOR "|"
#define SMS_NUMBER_LIMIT 20
#define SMS_TEXT_LIMIT 160


GSM gsmAccess;
GSM_SMS sms;

void setup() {
    Serial.begin(9600);
    pinMode(LED_GSM_STATUS_PIN, OUTPUT);
    connectGsm();
}

void loop() {
    smsSending();
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

    digitalWrite(LED_GSM_STATUS_PIN, HIGH);
}

void sendSms(char *number, char *text) {
    Serial.println("Sending SMS...");

    Serial.print("Number: ");
    Serial.println(number);

    Serial.print("Text: ");
    Serial.println(text);

    sms.beginSMS(number);
    sms.print(text);
    sms.endSMS();

    Serial.println("SMS is sent!");
}

String readSerial() {
    String content;

    if (Serial.available()) {
        content = Serial.readStringUntil('\n'); // will wait until it receives the character or timeout
    }

    if (content != "") {
        Serial.println("Serial: " + content);
    }

    return content;
}

void smsSending() {
    String input;

    input = readSerial();

    if (input == "") {
        return;
    }

    int separatorIndex =  input.indexOf(SMS_SEPARATOR);

    if (separatorIndex <= 0) {
        return;
    }

    String number = input.substring(0, separatorIndex);
    String text = input.substring(separatorIndex + 1);

    char numberArray[SMS_NUMBER_LIMIT];
    char textArray[SMS_TEXT_LIMIT];

    number.toCharArray(numberArray, SMS_NUMBER_LIMIT);
    text.toCharArray(textArray, SMS_TEXT_LIMIT);

    sendSms(numberArray, textArray);
}
