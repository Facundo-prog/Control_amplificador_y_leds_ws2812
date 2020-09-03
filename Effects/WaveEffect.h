#ifndef WaveEffect_h
#define WaveEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "EffectsFather.h"


class WaveEffect : public EffectsFather{

    public:
        WaveEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        int _posicionLed = 0;
        int _ledArranque = 0;
        bool _iniciarSecuencia = false;
        bool _topeAscentente = false;
        bool _topeDescentente = false;
        int _varAscendente = 0;
        int _varDescendente = 0;
};


#endif