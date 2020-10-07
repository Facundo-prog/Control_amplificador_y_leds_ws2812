#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>


EffectsFather::EffectsFather(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier){
    _pixels = pixels;
    if(quantityLeds > 0){_numPixel = quantityLeds;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue > 0){_valorDecrementoEntrePicos = decrementValue;}
    if(multiplier >= 0){_multiplicador = multiplier;}
}