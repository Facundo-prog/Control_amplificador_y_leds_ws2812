#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "ReboundEffect.h"
#include "EffectsFather.h"


ReboundEffect::ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, sensibilityPeak, decrementValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ReboundEffect::run(float valPico){


    if(_iniciarSecuencia == true){

        _pixels->setPixelColor(_i+_p, _r, _g, _b);
        _pixels->setPixelColor(_a+_p, _r, _g, _b);
        if((_i != 4) && (_i > 0)){_pixels->setPixelColor((_i+_p)-1, 0, 0, 0);}
        if((_a != 3) && (_i > 0)){_pixels->setPixelColor((_a+_p)+1, 0, 0, 0);}

        if(_p < _numPixel){
            _p += 8;
        }
        else{
            _p = 0;
        }
    }

    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        _a--;_i++;

        if(_i == 3){
            _r = random(0, 255);
            _g = random(0, 255);
            _b = random(0, 255);
        }
        else if(_i == 8){
            _iniciarSecuencia = false;
            _i = 0;
            _a = 7;
            _p = 0;
        }

        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico <= _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico * _multiplicador;
        _iniciarSecuencia = true;
    }
    else {

        if (_pico > 1){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}