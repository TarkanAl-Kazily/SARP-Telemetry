/*
  leo_usb2serial
  Allows to use an Arduino Leonardo as an usb to serial converter.
 */


// this pin will output the DTR signal (as set by the pc)
#define DTR_PIN 13

//SimpleSerial commands
#define SET_CALLSIGN 'c'
#define SEND_RAW_PACKET '!'
#define SEND_LOCATION '@'
#define SEND_APRS_MSG '#'
#define SET_LATITUDE "lla"
#define SET_LONGITUDE "llo"
#define SHOW_CONFIG 'H'

static long baud = 9600;
static String callsign = "KI7AFR";

int num = 90;

void setup() {
  //pinMode(DTR_PIN, OUTPUT);
  //digitalWrite(DTR_PIN, LOW);
  Serial.begin(baud);
  Serial1.begin(baud);
  setCallSign(callsign);
  delay(100);
}

void loop() {
    
    // copy from virtual serial line to uart and vice versa
    if (Serial.available()) {
        char c = (char)Serial.read();
        String str = "";
        for (int i = 0; i < 30; i++)
        {
            str += c;
            c = (char) Serial.read();
        }
        Serial1.print(str);
        //digitalWrite(DTR_PIN, HIGH);
        delay(100);
    }
    Serial.println(num);
    sendMessage(String(num));
    delay(2000);
    num++;
    //displaySettings();
    //digitalWrite(DTR_PIN, LOW);
    while (Serial1.available()) {
        char c = (char)Serial1.read();
        Serial.write(c);
    }
}

void setCallSign(String call)
{
    String str = "";
    str += SET_CALLSIGN;
    str += call;

    Serial1.print(str);
    //Serial1.print(str);

    //digitalWrite(DTR_PIN, HIGH);
}

void displaySettings()
{
   String str = "";
   str += SHOW_CONFIG;
   
   Serial1.print(str); 
   //Serial1.print(str);
   //digitalWrite(DTR_PIN, HIGH);

}

void sendMessage(String message)
{
    String str = "";
    str += SEND_RAW_PACKET;
    //str += SEND_APRS_MSG;
    str += message;

    Serial1.print(str);
    //delay(50);
    //Serial1.print(str);
}

void setLatitude(String latitude)
{
    String str = "";
    str += SET_LATITUDE;
    str += latitude;

    Serial1.print(str);
    //Serial1.print(str);
}

void setLongitude(String longitude)
{
    String str = "";
    str += SET_LONGITUDE;
    str += longitude;

    Serial1.print(str);
    //Serial1.print(str);
}
