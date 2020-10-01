#ifndef DotsDegradableEffect_h
#define DotsDegradableEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "EffectsFather.h"


class DotsDegradableEffect : public EffectsFather{

    public:
        DotsDegradableEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        unsigned long _tiempoColorPuntosDegradables = 0;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
        int _cantidadMaxLeds = 50;//Cantidad de Leds / 10
        byte _divLedsEfectoVoz[2][50];
};

#endif