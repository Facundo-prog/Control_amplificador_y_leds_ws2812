#ifndef ShockEffect_h
#define ShockEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

class ShockEffect : public EffectsFather{

    public:
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds);
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        bool _incrementando = true;
        int _i = 0;
};

#endif