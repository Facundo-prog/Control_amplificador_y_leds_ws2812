#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EffectsFather.h>

EffectsFather::EffectsFather(Adafruit_NeoPixel *pixels, int quantityLeds){
    _pixels = pixels;
    if(quantityLeds > 0){_numPixel = quantityLeds;}
}

EffectsFather::EffectsFather(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier){
    _pixels = pixels;
    if(quantityLeds > 0){_numPixel = quantityLeds;}
    if(decrementValue > 0){_valorDecrementoEntrePicos = decrementValue;}
    if(minimumPeakValue > 0){_minimoPico = minimumPeakValue;}
    if(multiplier >= 0){_multiplicador = multiplier;}
}