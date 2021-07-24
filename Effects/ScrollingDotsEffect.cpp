#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ScrollingDotsEffect.h>
#include <EffectsFather.h>


ScrollingDotsEffect::ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds) : EffectsFather(pixels, quantityLeds){
    _delayEfecto = 30;
    
    for(int i=0;i < _cantidadLedsDesplazables;i++){
        _ledsDesplazables[i] = 0;
    }
}

ScrollingDotsEffect::ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float decrementValue, float minimumPeakValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, decrementValue, minimumPeakValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}

    for(int i=0;i < _cantidadLedsDesplazables;i++){
        _ledsDesplazables[i] = 0;
    }
}

void ScrollingDotsEffect::run(float valPico){

    byte posMaxima = (_numPixel / 2) + 1;
    int delayCambioColor = 3000;


    if(millis() > _tiempoColorPuntosDesplazables + delayCambioColor){

        _tiempoColorPuntosDesplazables = millis();

        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
    }


    if(millis() > _tiempoEfecto + _delayEfecto){

        for(int i=0;i < _cantidadLedsDesplazables;i++)
        {
            if(_ledsDesplazables[i] > posMaxima){
                _ledsDesplazables[i] = 0;
                _pixels->setPixelColor(_ledsDesplazables[i], 0, 0, 0);
            }
            else if(_ledsDesplazables[i] > 0){
                _pixels->setPixelColor(_ledsDesplazables[i]-1, _r, _g, _b);
                _pixels->setPixelColor((_numPixel - _ledsDesplazables[i]), _r, _g, _b);
                _pixels->setPixelColor(_ledsDesplazables[i]-2, 0, 0, 0);
                _pixels->setPixelColor(((_numPixel + 1) - _ledsDesplazables[i]), 0, 0, 0);
                _ledsDesplazables[i] += 1;
            }
        }
        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico <= (_pico * _multiplicador) || valPico < _minimoPico){return;}
        
    if(valPico > _pico){
        _pico = valPico + (valPico * _porcentajePico);
    
        for(int i=0;i < _cantidadLedsDesplazables;i++){
            if(_ledsDesplazables[i] == 0){
                _ledsDesplazables[i] = 1;
                break;
            }
        }
    }
    else {

        if (_pico > _minimoPico){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}