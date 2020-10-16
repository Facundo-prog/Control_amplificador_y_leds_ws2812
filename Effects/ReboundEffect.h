#ifndef ReboundEffect_h
#define ReboundEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

class ReboundEffect : public EffectsFather{

    public:
        ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds);
        ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _p = 0;
        int _i = 0;
        int _a = 7;
};

#endif