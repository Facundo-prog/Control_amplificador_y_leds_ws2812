#ifndef Effects_h
#define Effects_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class IEffects{

    public:
        virtual void run(float value) = 0;
};



class EffectFather : public IEffects{

    public:
        EffectFather(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue);// Constructor comun para todos los efectos
        void run(float value) override;// Funcion heredada de IEffects

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



class TransitionEffect : public EffectFather{

    public:
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);// Constructor
        void run(float value);// Implementacion de la clase EffectFather 
        
    private:

        //Variables del efecto
        bool _direccionEfecto = false;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
};


class WaveEffect : public EffectFather{

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



class DotsDegradableEffect : public EffectFather{

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



class WormEffect : public EffectFather{

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



class RandomEffect : public EffectFather{

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



class ReboundEffect : public EffectFather{

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



class ShockEffect : public EffectFather{

    public:
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value);
        
    private:

        //Variables del efecto
        bool _iniciarSecuencia = false;
        bool _incrementando = true;
        int _i = 0;
};



class ScrollingDotsEffect : public EffectFather{

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