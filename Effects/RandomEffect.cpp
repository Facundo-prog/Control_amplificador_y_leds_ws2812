#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <RandomEffect.h>
#include <EffectsFather.h>


RandomEffect::RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){_delayEfecto = 5;}

RandomEffect::RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, sensibilityPeak, decrementValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void RandomEffect::run(float valPico){
    
    int avanceMaximo = round(_numPixel/3);


    if((millis() - _tiempoEfecto) >= _delayEfecto && _iniciarSecuencia == true){

        if(_i < _numPixel){_pixels->setPixelColor(_i,_r,_g,_b);}
        if(_a >= 0){_pixels->setPixelColor(_a,_r,_g,_b);}

        _pixels->show();

        _i++;
        _a--;

        if(_i >= _pixelElegido + _avance){
            _iniciarSecuencia = false;
        }

        _tiempoEfecto = millis();
    }


    if(valPico <= _sensibilidadPico){return;}

        
    if(valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico * _multiplicador;
        _iniciarSecuencia = true;

        _pixelElegido = random(0,_numPixel);
        _avance = random(4, avanceMaximo);
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
        _i = _pixelElegido;
        _a = _pixelElegido;
    }
    else {
    
        if(_pico > 1){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}