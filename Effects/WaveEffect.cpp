#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WaveEffect.h>
#include <EffectsFather.h>


WaveEffect::WaveEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 15;}

WaveEffect::WaveEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WaveEffect::run(float valPico){

    int topeMaximoLeds = _numPixel + 6;
    int i = _posicionLed;


    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_varAscendente < topeMaximoLeds){
            _pixels->setPixelColor(_varAscendente, _r, _g, _b);
            if(_varAscendente > _ledArranque){_pixels->setPixelColor(_varAscendente-1, round(_r/1.5), round(_g/1.5), round(_b/1.5));}
            if(_varAscendente > (_ledArranque+1)){_pixels->setPixelColor(_varAscendente-2, round(_r/2), round(_g/2), round(_b/2));}
            if(_varAscendente > (_ledArranque+2)){_pixels->setPixelColor(_varAscendente-3, round(_r/3), round(_g/3), round(_b/3));}
            if(_varAscendente > (_ledArranque+3)){_pixels->setPixelColor(_varAscendente-4, round(_r/6), round(_g/6), round(_b/6));}
            if(_varAscendente > (_ledArranque+4)){_pixels->setPixelColor(_varAscendente-5, round(_r/10), round(_g/10), round(_b/10));}
            if(_varAscendente > (_ledArranque+5)){_pixels->setPixelColor(_varAscendente-6, 0, 0, 0);}

            _varAscendente++;
        }
        else{
            _topeAscentente = true;
        }

        if(_varDescendente >= -6){
            _pixels->setPixelColor(_varDescendente, _r, _g, _b);
            if(_varDescendente < _ledArranque){_pixels->setPixelColor(_varDescendente+1, round(_r/1.5), round(_g/1.5), round(_b/1.5));}
            if(_varDescendente < (_ledArranque-1)){_pixels->setPixelColor(_varDescendente+2, round(_r/2), round(_g/2), round(_b/2));}
            if(_varDescendente < (_ledArranque-2)){_pixels->setPixelColor(_varDescendente+3, round(_r/3), round(_g/3), round(_b/3));}
            if(_varDescendente < (_ledArranque-3)){_pixels->setPixelColor(_varDescendente+4, round(_r/6), round(_g/6), round(_b/6));}
            if(_varDescendente < (_ledArranque-4)){_pixels->setPixelColor(_varDescendente+5, round(_r/10), round(_g/10), round(_b/10));}
            if(_varDescendente < (_ledArranque-5)){_pixels->setPixelColor(_varDescendente+6, 0, 0, 0);}
            _varDescendente--;
        }
        else{
            _topeDescentente = true;
        }

        if(_topeAscentente == true && _topeDescentente == true){
            _iniciarSecuencia = false;
            _posicionLed = 0;
            _topeAscentente = false;
            _topeDescentente = false;
            _varAscendente = 0;
            _varDescendente = 0;
        }
        
        _posicionLed++;
        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico < _minimoPico){return;}
 
    if(valPico > _pico && _iniciarSecuencia == false){
        _pico = valPico + (valPico * _porcentajePico);
        _iniciarSecuencia = true;

        _ledArranque = random(3, (_numPixel - 3));
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);

        _varAscendente = _ledArranque;
        _varDescendente = _ledArranque;
    }
    else {

        if (_pico > _minimoPico){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}