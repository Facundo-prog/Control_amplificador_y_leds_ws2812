#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <DotsDegradableEffect.h>
#include <EffectsFather.h>


DotsDegradableEffect::DotsDegradableEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, float multiplier, int delayEffect) : EffectsFather(pixels, quantityLeds, sensibilityPeak, decrementValue, multiplier){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void DotsDegradableEffect::run(float valPico){

    byte divisorTemporal = 0;
    byte posicionTemporal = 0;
    byte posicion = 0;
    int delayCambioColor = 3000;
    byte valorDeIncremento = 1;


    if(millis() > _tiempoColorPuntosDegradables + delayCambioColor){
        
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
        
        _tiempoColorPuntosDegradables = millis();
    }
    

    if(millis() > _tiempoEfecto + _delayEfecto){

        for(int i=0;i < _cantidadMaxLeds;i++){

            if(_divLedsEfectoVoz[0][i] >= 20){
            
                _divLedsEfectoVoz[0][i] = 0;
                _divLedsEfectoVoz[1][i] = 0;
            }
            else if(_divLedsEfectoVoz[0][i] > 0){

                divisorTemporal = _divLedsEfectoVoz[0][i];
                posicionTemporal = _divLedsEfectoVoz[1][i];
                _pixels->setPixelColor(posicionTemporal, round(_r/divisorTemporal), round(_g/divisorTemporal), round(_b/divisorTemporal));
                _pixels->setPixelColor(posicionTemporal + 1, round(_r/divisorTemporal+2), round(_g/divisorTemporal+2), round(_b/divisorTemporal+2));
                _pixels->setPixelColor(posicionTemporal - 1, round(_r/divisorTemporal+2), round(_g/divisorTemporal+2), round(_b/divisorTemporal+2));
                _divLedsEfectoVoz[0][i] += valorDeIncremento;
            }
        }
        _pixels->show();
        _tiempoEfecto = millis();
    }


    if(valPico <= _sensibilidadPico){return;}

    
    if(valPico > _pico){

        _pico = valPico * _multiplicador;

        for(int i=0;i < _cantidadMaxLeds;i++){
            if(_divLedsEfectoVoz[0][i] == 0){

                posicion = random(1, _numPixel);
                _divLedsEfectoVoz[0][i] = 1;
                _divLedsEfectoVoz[1][i] = posicion;
                break;
            }
        }
    }
    else {

        if (_pico > 1){
            _pico -= _valorDecrementoEntrePicos;
        }
    }
}