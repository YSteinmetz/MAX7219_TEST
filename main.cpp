/*
    SPI Master Demo Sketch
    Connect the SPI Master device to the following pins on the esp8266:

    GPIO    NodeMCU   Name  |   Uno
   ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

    Note: If the ESP is booting at a moment when the SPI Master has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!
    See SPISlave_SafeMaster example for possible workaround

*/
#include <SPI.h>

class ESPMaster
{
private:
    uint8_t _ss_pin;

public:
    ESPMaster(uint8_t pin):_ss_pin(pin) {}
    void begin()
    {
        pinMode(D8, OUTPUT);
        digitalWrite(_ss_pin, HIGH);
    }
    void sendData(uint8_t data){
        digitalWrite(D8, LOW);
        SPI.transfer(data);
        digitalWrite(D8, HIGH);
    }
    void onMode(void){
        digitalWrite(D8, LOW);
        SPI.transfer(0xC);
        digitalWrite(D8, HIGH);
        digitalWrite(D8, LOW);
        SPI.transfer(0x1);
        digitalWrite(D8, HIGH);
        delay(100);
    }
    void offMode(void){
        digitalWrite(D8, LOW);
        SPI.transfer(0xC);
        digitalWrite(D8, HIGH);
        digitalWrite(D8, LOW);
        SPI.transfer(0x0);
        digitalWrite(D8, HIGH);
        delay(100);
    }

};

ESPMaster esp(SS);


void setup()
{
    Serial.begin(9600);
    SPI.begin();
    esp.begin();
    esp.onMode();
    esp.sendData(0xA);
    esp.sendData(0x7);
    delay(1000);
    
}

void loop()
{
    esp.offMode();
    delay(250);
    esp.onMode();
    delay(250);
}