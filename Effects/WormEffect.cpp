#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "WormEffect.h"
#include "EffectsFather.h"


WormEffect::WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect) : EffectsFather(pixels, quantityLeds, sensibilityPeak, decrementValue){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WormEffect::run(float valPico){

    int i = _posicionLed;

    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_incrementando == true){

            _pixels->setPixelColor(_pixel, _r, _g, _b);

            if(i > 0){
                _pixels->setPixelColor(_pixel+1, round(_r/1.5), round(_g/1.5), round(_b/1.5));
                _pixels->setPixelColor(_pixel-1, round(_r/1.5), round(_g/1.5), round(_b/1.5));
            }
            
            if(i > 1){
                _pixels->setPixelColor(_pixel+2, round(_r/2), round(_g/2), round(_b/2));
                _pixels->setPixelColor(_pixel-2, round(_r/2), round(_g/2), round(_b/2));
            }
            
            if(i > 2){
                _pixels->setPixelColor(_pixel+3, round(_r/3), round(_g/3), round(_b/3));
                _pixels->setPixelColor(_pixel-3, round(_r/3), round(_g/3), round(_b/3));
            }
            
            if(i > 3){
                _pixels->setPixelColor(_pixel+4, round(_r/6), round(_g/6), round(_b/6));
                _pixels->setPixelColor(_pixel-4, round(_r/6), round(_g/6), round(_b/6));
            }
        }
        else{

            if(i <= 0){
                _pixels->setPixelColor(_pixel, 0, 0, 0);
            }

            if(i <= 1){
                _pixels->setPixelColor(_pixel+1, 0, 0, 0);
                _pixels->setPixelColor(_pixel-1, 0, 0, 0);
            }
            
            if(i <= 2){
                _pixels->setPixelColor(_pixel+2, 0, 0, 0);
                _pixels->setPixelColor(_pixel-2, 0, 0, 0);
            }
            
            if(i <= 3){
                _pixels->setPixelColor(_pixel+3, 0, 0, 0);
                _pixels->setPixelColor(_pixel-3, 0, 0, 0);
            }
            
            if(i <= 4){
                _pixels->setPixelColor(_pixel+4, 0, 0, 0);
                _pixels->setPixelColor(_pixel-4, 0, 0, 0);
            }
        }


        if(_incrementando == true){
            _posicionLed++;
        }
        else{
            _posicionLed--;
        }


        if(_posicionLed == 5 && _incrementando == true){
            _incrementando = false;
            _delayEfecto = _delayEfecto * 2;
        }
        else if(_posicionLed == -1 && _incrementando == false){
            _delayEfecto = _delayEfecto / 2;
            _iniciarSecuencia = false;
            _posicionLed = 0;
            _incrementando = true;
        }

        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico * valPico;
        _iniciarSecuencia = true;

        _pixel = random(0, _numPixel);
        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
    }
    else {

        if (_pico > 1){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}