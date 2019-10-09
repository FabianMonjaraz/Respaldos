#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial mySerial(2, 3);  //RX,TX

//  Arduino pin 2 (RX) to ESP8266 TX
//  Arduino pin 3 to voltage divider then to ESP8266 RX
//  Connect GND from the Arduiono to GND on the ESP8266
//  Pull ESP8266 CH_PD HIGH

// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the ESP8266

 
int LEDPIN = 13;

void sendCommand(char *cmd){
    mySerial.println(cmd);
    while ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
    delay(250);
}
 
void initConnection(){
    sendCommand("AT+RST");
    sendCommand("ATE0");
    sendCommand("AT+GMR");
    sendCommand("AT+CWJAP_CUR=\"Bastion\",\"#4rt0r14s#\"");
    delay(1000);
}
void setup() 
{
    pinMode(LEDPIN, OUTPUT);
 
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    // Start the software serial for communication with the ESP8266
    mySerial.begin(9600);  
 
    Serial.println("");
    Serial.println("Remember to to set Both NL & CR in the serial monitor.");
    Serial.println("Ready");
    Serial.println("");    
    initConnection();
}
 
void loop() 
{
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
 
    // listen for user input and send it to the ESP8266
    if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
}
