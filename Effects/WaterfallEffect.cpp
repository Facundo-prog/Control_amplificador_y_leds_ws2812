#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WaterfallEffect.h>
#include <EffectsFather.h>


WaterfallEffect::WaterfallEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 15;}

WaterfallEffect::WaterfallEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WaterfallEffect::run(float valPico){

    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_varAscendente < _numPixel + 1){
            _pixels->setPixelColor(_varAscendente, _r, _g, _b);
            if(_varAscendente > _ledArranque){_pixels->setPixelColor(_varAscendente-1, round(_r/3), round(_g/3), round(_b/3));}

            _varAscendente++;
        }
        else{
            _topeAscentente = true;
        }

        if(_varDescendente >= -1){
            _pixels->setPixelColor(_varDescendente, _r, _g, _b);
            if(_varDescendente < _ledArranque){_pixels->setPixelColor(_varDescendente+1, round(_r/3), round(_g/3), round(_b/3));}

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
 
    if(valPico > _pico){
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