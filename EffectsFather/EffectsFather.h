#ifndef EffectsFather_h
#define EffectsFather_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class IEffects{

    public:
        virtual void run(float value) = 0;
};


class EffectFather : public IEffects{

    public:
        // Constructor comun para todos los efectos
        EffectFather(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue);

    protected:

        //Variables comunes a todos los efectos
        Adafruit_NeoPixel* _pixels;

        unsigned long _tiempoEfecto = 0;
        int _numPixel = 0;
        int _delayEfecto = 0;
        float _pico = 0;
        float _sensibilidadPico = 1;
        float _valorDecrementoEntrePicos = 0.15;
        byte _r;
        byte _g;
        byte _b;
};

#endif