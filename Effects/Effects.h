#ifndef Effects_h
#define Effects_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "EffectsFather.h"


class TransitionEffect : public EffectsFather{

    public:
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);// Constructor
        void run(float value); 
        
    private:

        //Variables del efecto
        bool _direccionEfecto = false;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
};


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



class DotsDegradableEffect : public EffectsFather{

    public:
        DotsDegradableEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        unsigned long _tiempoColorPuntosDegradables = 0;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
        int _cantidadMaxLeds = 50;//Cantidad de Leds / 10
        byte _divLedsEfectoVoz[2][50];
};



class WormEffect : public EffectsFather{

    public:
        WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _posicionLed = 0;
        bool _incrementando = true;
        byte _pixel;

};



class RandomEffect : public EffectsFather{

    public:
        RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _pixelElegido = 0;
        int _avance = 0;
        int _i;
        int _a;
};



class ReboundEffect : public EffectsFather{

    public:
        ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        int _p = 0;
        int _i = 0;
        int _a = 7;
};



class ShockEffect : public EffectsFather{

    public:
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        bool _incrementando = true;
        int _i = 0;
};



class ScrollingDotsEffect : public EffectsFather{

    public:
        ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        unsigned long _tiempoColorPuntosDesplazables = 0; 
        const int _cantidadLedsDesplazables = 250;//Cantidad de Leds / 2
        int _ledsDesplazables[250];
};


#endif