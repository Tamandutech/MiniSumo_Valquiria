#define DECODE_SONY

#include <IRremote.hpp>

#define led 2

void setup()
{
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    IrReceiver.begin(16, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
    printActiveIRProtocols(&Serial);
    while (true)
    {
        if (IrReceiver.decode())
        {
            IrReceiver.resume();
            if (IrReceiver.decodedIRData.command == 0x0)
            {
                Serial.println("1");
                while(true){
                    digitalWrite(led, 1);
                    delay(50);
                    digitalWrite(led, 0);
                    delay(50);
                    if (IrReceiver.decode()){
                        IrReceiver.resume();
                        if (IrReceiver.decodedIRData.command == 0x1){
                            Serial.println("2");
                            break;
                        }
                    }
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x2)
            {
                Serial.println("3");
            }
        }
    }
}

void loop()
{
}
