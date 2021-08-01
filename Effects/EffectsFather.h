#ifndef EffectsFather_h
#define EffectsFather_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <IEffects.h>


class EffectsFather : public IEffects{

    protected:
        EffectsFather(Adafruit_NeoPixel *pixels, int quantityLeds);
        EffectsFather(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier);
        
        //Variables comunes a todos los efectos
        Adafruit_NeoPixel* _pixels;

        unsigned long _tiempoEfecto = 0;
        int _numPixel = 0;
        int _delayEfecto = 0;
        float _minimoPico = 10;
        float _pico = 10;
        float _porcentajePico = 0.15;
        float _multiplicador = 0.15;
        float _valorDecrementoEntrePicos = 0.05;
        byte _r;
        byte _g;
        byte _b;
};

#endif