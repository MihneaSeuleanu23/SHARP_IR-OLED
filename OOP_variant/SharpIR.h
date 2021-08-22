
#ifndef SharpIR_h
#define SharpIR_h

#include <Arduino.h>

class SharpIR
{
    private:
        byte _pin;
        //float distanta;
        int count;
        float *AverageBuffer;
        float weight;
    public:
        SharpIR(const byte pin);
        ~SharpIR();
        float getDistance();
        float getDistanceAverage();
        float getDistanceExp();
        int constrain_analog(const int);     
};

#endif
