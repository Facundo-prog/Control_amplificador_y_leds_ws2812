#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ReboundEffect.h>
#include <EffectsFather.h>


ReboundEffect::ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 40;}

ReboundEffect::ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
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


    if(valPico < _minimoPico){return;}
 
    if(valPico > _pico && _iniciarSecuencia == false){
        
        _pico = valPico + (valPico * _porcentajePico);
        _iniciarSecuencia = true;
    }
    else {

        if (_pico > _minimoPico){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}