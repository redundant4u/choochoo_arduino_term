#include <SoftwareSerial.h>

void initBluetooth()
{
    Serial1.begin(9600);
}

int receiveDataFromBluetooth()
{
    int result = -1;

    if(Serial1.available())
    {
        char data = Serial1.read();
        
        if(data == 'r')
        {
            result = 1;
        }

        else if(data == 'y')
        {
            result = 2;
        }

        else if(data == 'g')
        {
            result = 3;
        }
    }

    return result;
}