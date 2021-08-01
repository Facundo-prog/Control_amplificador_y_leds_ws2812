#ifndef WaterfallEffect_h
#define WaterfallEffect_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>


class WaterfallEffect : public EffectsFather{

    public:
        WaterfallEffect(Adafruit_NeoPixel *pixels, int quantityLeds);
        WaterfallEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect);// Constructor
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