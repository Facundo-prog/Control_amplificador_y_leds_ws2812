#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TransitionEffect.h>
#include <EffectsFather.h>


TransitionEffect::TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 10;}

TransitionEffect::TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void TransitionEffect::run(float valPico){

    byte mitadLeds = _numPixel/2;
    byte limite = _numPixel-1;
    int i = _posicionLed;


    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_direccionEfecto == false){
    
            if(i < mitadLeds){_pixels->setPixelColor(i+1, 0, 0, 0);}
            _pixels->setPixelColor(i, _r, _g, _b);
            _pixels->setPixelColor((_numPixel-1)-i, _r, _g, _b);
            if(i < (mitadLeds-1)){_pixels->setPixelColor((_numPixel-2)-i, 0, 0, 0);}

            _pixels->show();

            if(_posicionLed == mitadLeds){
                _direccionEfecto = true;
                _iniciarSecuencia = false;
            }

            _posicionLed++;
        }
        else{

            if(i > 0){_pixels->setPixelColor(i-1, 0, 0, 0);}
            if(i < (_numPixel/2)){_pixels->setPixelColor(i, _r, _g, _b);}
            if(i < (_numPixel/2)){_pixels->setPixelColor((_numPixel-1)-i, _r, _g, _b);}
            if(i > 0){_pixels->setPixelColor(_numPixel-i, 0, 0, 0);}

            _pixels->show();

            if(_posicionLed == 0){
                _direccionEfecto = false;
                _iniciarSecuencia = false;
            }

            _posicionLed--;
        }

        _tiempoEfecto = millis();
    }


    if(valPico < _minimoPico){return;}
 
    if(valPico > _pico && _iniciarSecuencia == false){
        _pico = valPico + (valPico * _porcentajePico);
        _iniciarSecuencia = true;

        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
    }
    else {
    
        if(_pico > _minimoPico){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}
