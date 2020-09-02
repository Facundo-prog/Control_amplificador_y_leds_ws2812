#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Effects.h"


EffectFather::EffectFather(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue){
    _pixels = pixels;
    if(quantityLeds > 0){_numPixel = quantityLeds;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue > 0){_valorDecrementoEntrePicos = decrementValue;}
}