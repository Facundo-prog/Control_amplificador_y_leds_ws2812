#ifndef WormEffect_h
#define WormEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

class WormEffect : public EffectsFather{

    public:
        WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds);
        WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _posicionLed = 0;
        bool _incrementando = true;
        byte _pixel;
};

#endif