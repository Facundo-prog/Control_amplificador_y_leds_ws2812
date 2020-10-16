/* 
*  En este ejemplo basico se controlan controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo)
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h

#include <Adafruit_NeoPixel.h>// Libreria necesaria para controlar los leds
#include <AudioControl.h>     // Libreria que controla el audio
#include <Arduino.h>


//-------- Incluyo los efectos que voy a usar -------//
#include <TransitionEffect.h>
#include <WaveEffect.h>
#include <DotsDegradableEffect.h>
#include <WormEffect.h>
#include <RandomEffect.h>
#include <ReboundEffect.h>
#include <ShockEffect.h>
#include <ScrollingDotsEffect.h>


//------ Pines Utilizados ------//
byte pinLeds = 2;
byte pinLecturaAudio = A0;


//---------- Variables del programa ---------//
int cantidadLeds = 50;//Determina la cantidad de leds a controlar
float value = 0;//Guardo temporalmente el valor de audio

long tiempoAnteriorComprobacion = 0;//Variable donde guardamos el valor de millis para compararlo
byte efectoActual = 0;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos
bool estadoEfectos = true;//Determina si los efectos estan activos o no


//--------- Instancias de Objetos ---------//
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);
AudioControl audio(pinLecturaAudio);


//-------- Inicializacion de los efectos -----------//
TransitionEffect effect_1(&leds, cantidadLeds);
WaveEffect effect_2(&leds, cantidadLeds);
DotsDegradableEffect effect_3(&leds, cantidadLeds);// No adaptado a millis
WormEffect effect_4(&leds, cantidadLeds);
RandomEffect effect_5(&leds, cantidadLeds);
ReboundEffect effect_6(&leds, cantidadLeds);
ShockEffect effect_7(&leds, cantidadLeds);
ScrollingDotsEffect effect_8(&leds, cantidadLeds);// No adaptado a millis


//--------- Array de Efectos -----------//
EffectsFather* efectos[] = {&effect_1, &effect_2, &effect_3, &effect_4, &effect_5, &effect_6, &effect_7, &effect_8};


void setup(){

    leds.begin();//Inicializo los leds
    leds.clear();//Limpio la tira

    randomSeed(millis());//Seteo la semilla de la funcion random
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