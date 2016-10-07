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

int num = 0;

void setup() {
  //pinMode(DTR_PIN, OUTPUT);
  //digitalWrite(DTR_PIN, LOW);
  Serial.begin(baud);
  Serial.println("Starting");
  Serial2.begin(baud);
  while (!Serial2)
    {
        Serial.println("AAAH");
    }
  Serial2.println('H');
  while (Serial2.available())
  {
    Serial.println("available");
    char c = (char)Serial2.read();
    Serial.write(c);
  }
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
        Serial2.print(str);
        //digitalWrite(DTR_PIN, HIGH);
        delay(100);
    }
    //Serial.println(num);
    //sendMessage(String(num));
    delay(2000);
    //num++;
    //displaySettings();
    //digitalWrite(DTR_PIN, LOW);
    while (Serial2.available()) {
            Serial.println("available");

        char c = (char)Serial2.read();
        Serial.write(c);
    }
}

void setCallSign(String call)
{
    String str = "";
    str += SET_CALLSIGN;
    str += call;

    Serial2.print(str);
    //Serial2.print(str);

    //digitalWrite(DTR_PIN, HIGH);
}

void displaySettings()
{
   String str = "";
   str += SHOW_CONFIG;
   
   Serial2.print(str); 
   //Serial2.print(str);
   //digitalWrite(DTR_PIN, HIGH);

}

void sendMessage(String message)
{
    String str = "";
    str += SEND_RAW_PACKET;
    //str += SEND_APRS_MSG;
    str += message;

    Serial2.print(str);
    //delay(50);
    //Serial2.print(str);
}

void setLatitude(String latitude)
{
    String str = "";
    str += SET_LATITUDE;
    str += latitude;

    Serial2.print(str);
    //Serial2.print(str);
}

void setLongitude(String longitude)
{
    String str = "";
    str += SET_LONGITUDE;
    str += longitude;

    Serial2.print(str);
    //Serial2.print(str);
}
