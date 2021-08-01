#ifndef TransitionEffect_h
#define TransitionEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>


class TransitionEffect : public EffectsFather{

    public:
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds);
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect);// Constructor
        void run(float value); 
        
    private:

        //Variables del efecto
        bool _direccionEfecto = false;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
};

#endif