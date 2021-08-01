#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ShockEffect.h>
#include <EffectsFather.h>


ShockEffect::ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 5;}

ShockEffect::ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ShockEffect::run(float valPico){

    int mitadTira = _numPixel/2;


    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_incrementando == true){

            if(_i < mitadTira){

                _pixels->setPixelColor(_i, _r, _g, _b);
                _pixels->setPixelColor((_numPixel-1)-_i, _r, _g, _b);

                if(_i > 0){_pixels->setPixelColor(_i-1, _r, _g, _b); _pixels->setPixelColor(_numPixel-_i, _r, _g, _b);}
                if(_i > 1){_pixels->setPixelColor(_i-2, _r, _g, _b); _pixels->setPixelColor((_numPixel+1)-_i, _r, _g, _b);}
                if(_i > 2){_pixels->setPixelColor(_i-3, _r, _g, _b); _pixels->setPixelColor((_numPixel+2)-_i, _r, _g, _b);}
            }

            if(_i > 3){_pixels->setPixelColor(_i-4, 0, 0, 0); _pixels->setPixelColor((_numPixel+3)-_i, 0, 0, 0);}
            _i++;
        }
        else{

            if(_i > -1){_pixels->setPixelColor(_i, _r, _g, _b); _pixels->setPixelColor((_numPixel-1)-_i, _r, _g, _b);}
            if((_i > -2) && (_i < (mitadTira-2))){_pixels->setPixelColor(_i+1, _r, _g, _b); _pixels->setPixelColor((_numPixel-2)-_i, _r, _g, _b);}
            if((_i > -3) && (_i < (mitadTira-3))){_pixels->setPixelColor(_i+2, _r, _g, _b); _pixels->setPixelColor((_numPixel-3)-_i, _r, _g, _b);}
            if((_i > -4) && (_i < (mitadTira-4))){_pixels->setPixelColor(_i+3, _r, _g, _b); _pixels->setPixelColor((_numPixel-4)-_i, _r, _g, _b);}

            if((_i > -5) && (_i < (mitadTira-4))){_pixels->setPixelColor(_i+4, 0, 0, 0); _pixels->setPixelColor((_numPixel-5)-_i, 0, 0, 0);}
            _i--;
        }

        if(_i == (mitadTira - 3) && _incrementando == true){
            _delayEfecto = _delayEfecto * 4;
        }
        else if(_i == mitadTira - 3 && _incrementando == false){
            _delayEfecto = _delayEfecto / 4;
        }

        if(_i >= mitadTira + 2){
            _incrementando = false;
            _i = mitadTira - 2;
        }
        else if(_i <= -5 && _incrementando == false){
            _iniciarSecuencia = false;
            _i = 0; 
            _incrementando = true;
        }
        
        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico <= (_pico * _multiplicador) || valPico < _minimoPico){return;}
        
    if(valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico + (valPico * _porcentajePico);
        _iniciarSecuencia = true;
    
        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
    }
    else {

        if (_pico > _minimoPico){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}
