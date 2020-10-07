#ifndef RandomEffect_h
#define RandomEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

class RandomEffect : public EffectsFather{

    public:
        RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _pixelElegido = 0;
        int _avance = 0;
        int _i;
        int _a;
};

#endif