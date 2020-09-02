/* 
*  En este ejemplo basico se controlan controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo)
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h en el mismo directorio que Effects.h


#include <Adafruit_NeoPixel.h>// Libreria necesaria para controlar los leds
#include "AudioControl.h"     // Libreria que controla el audio
#include "EffectsFather.h"    // Libreria padre de Effects.h
#include "Effects.h"          // Libreria que controla los efectos
#include <Arduino.h>


//------Pines Utilizados ------//
byte pinLeds = 3;
byte pinLecturaAudio = A0;


//---------- Variables del programa ---------//
int cantidadLeds = 40;//Determina la cantidad de leds a controlar
float valorPico = 1;
float valorDecremento = 0.50;
byte brilloLeds = 255;//Determina el brillo de los leds. El minimo es 0 y el maximo 255

long tiempoAnteriorComprobacion = 0;//Variable donde guardamos el valor de millis para compararlo
byte efectoActual = 7;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos
bool estadoEfectos = true;//Determina si los efectos estan activos o no

float value = 0;//Guardo temporalmente el valor de audio


//--------- Instancias de Objetos ---------//
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);
AudioControl audio(pinLecturaAudio);


//-------- Inicializacion de los efectos -----------//
TransitionEffect effect_1(&leds, cantidadLeds, valorPico, valorDecremento, 15);
WaveEffect effect_2(&leds, cantidadLeds, valorPico, valorDecremento, 15);
DotsDegradableEffect effect_3(&leds, cantidadLeds, valorPico, (valorDecremento*2), 40);// No adaptado a millis
WormEffect effect_4(&leds, cantidadLeds, valorPico, valorDecremento, 20);
RandomEffect effect_5(&leds, cantidadLeds, valorPico, valorDecremento, 5);
ReboundEffect effect_6(&leds, cantidadLeds, valorPico, valorDecremento, 40);
ShockEffect effect_7(&leds, cantidadLeds, valorPico, valorDecremento, 5);
ScrollingDotsEffect effect_8(&leds, cantidadLeds, valorPico, (valorDecremento*2), 35);// No adaptado a millis


//--------- Array de Efectos -----------//
EffectFather* efectos[] = {&effect_1, &effect_2, &effect_3, &effect_4, &effect_5, &effect_6, &effect_7, &effect_8};


void setup(){

    audio.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    audio.setDetectionFrequency(5000);//Seteo la frecuencia de deteccion. Leer propiedades.txt

    leds.begin();//Inicializo los leds
    leds.clear();//Apago los leds
    leds.setBrightness(brilloLeds);//Seteo el brillo

    randomSeed(millis());
}   


void loop(){

    value = audio.readAudio();//Actualizo el valor de audio

    if(estadoEfectos == true){
        efectos[efectoActual]->run(value);//Actualizo el estado de los leds
    }

    if((millis() - tiempoAnteriorComprobacion) >= 10000){
        efectoActual++;//Incremento el efecto
        estadoEfectos = true;//Activo los efectos
        leds.clear();//Apago los leds

        if(audio.getStateMute() == true){
            estadoEfectos = false;//Desactivo los efectos
        }

        if(efectoActual >= cantidadEfectos){
            efectoActual = 0;//Vuelvo a 0 los efectos
        }

        tiempoAnteriorComprobacion = millis();//Vuelvo a 0 la diferencia de timepo
    }
}