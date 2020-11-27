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
float valorPico = 0.9;//Valor por encima del cual se considera un pico de audio
float minimoPico = 0.9;//Valor de diferencia entre lecturas que se toma como un pico de audio
float valorDecremento = 0.05;//Valor que se descuenta cuando no se detecta un pico
float multiplicador = 6;//Valor por el cual se multiplica cuando se detecta un pico de audio
float value = 0;//Guardo temporalmente el valor de audio
byte brilloLeds = 255;//Determina el brillo de los leds. El minimo es 0 y el maximo 255

long tiempoAnteriorComprobacion = 0;//Variable donde guardamos el valor de millis para compararlo
byte efectoActual = 0;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos
bool estadoEfectos = true;//Determina si los efectos estan activos o no


//--------- Instancias de Objetos ---------//
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);
AudioControl audio(pinLecturaAudio);


//-------- Inicializacion de los efectos -----------//
TransitionEffect effect_1(&leds, cantidadLeds, valorPico, valorDecremento, multiplicador, 10);
WaveEffect effect_2(&leds, cantidadLeds, valorPico, valorDecremento, multiplicador, 15);
DotsDegradableEffect effect_3(&leds, cantidadLeds, valorPico, round(valorDecremento*2), multiplicador, 35);// No adaptado a millis
WormEffect effect_4(&leds, cantidadLeds, valorPico, valorDecremento, multiplicador, 20);
RandomEffect effect_5(&leds, cantidadLeds, valorPico, round(valorDecremento*2), multiplicador, 5);
ReboundEffect effect_6(&leds, cantidadLeds, valorPico, valorDecremento, multiplicador, 40);
ShockEffect effect_7(&leds, cantidadLeds, valorPico, valorDecremento, multiplicador, 5);
ScrollingDotsEffect effect_8(&leds, cantidadLeds, valorPico, round(valorDecremento*2), multiplicador, 30);// No adaptado a millis


//--------- Array de Efectos -----------//
EffectsFather* efectos[] = {&effect_1, &effect_2, &effect_3, &effect_4, &effect_5, &effect_6, &effect_7, &effect_8};


void setup(){

    audio.setDetectionSilence(true, 10000, 10, minimoPico);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    audio.setDetectionFrequency(2500);//Seteo la frecuencia de deteccion. Leer propiedades.txt

    leds.begin();//Inicializo los leds
    leds.clear();//Limpio la tira
    leds.setBrightness(brilloLeds);//Seteo el brillo
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