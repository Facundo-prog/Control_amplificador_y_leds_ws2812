/* 
*  En este ejemplo basico se controla la temperatura (lm35) y el pin de mute/stand by de un amplificador
*  Tambien se controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo)
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  3(out) -> Pin de mute/stand by del amplificador (a travez de un transistor)
*  4(out) -> Pin de control del ventilador (a travez de un transistor)
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*  A1(in) -> Pin de lectura de temperatura (se tiene que utilizar un LM35)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h

#include "AmplifierControl.h"  //Libreria que controla el amplificador
#include "AudioControl.h"      //Libreria que obtiene el audio
#include <Adafruit_NeoPixel.h> //Libreria necesaria para controlar los leds
#include <Arduino.h>


//-------- Incluyo los efectos que voy a usar -------//
#include "TransitionEffect.h"
#include "WaveEffect.h"
#include "DotsDegradableEffect.h"
#include "WormEffect.h"
#include "RandomEffect.h"
#include "ReboundEffect.h"
#include "ShockEffect.h"
#include "ScrollingDotsEffect.h"


//------Pines Utilizados ------//
byte pinLeds = 2;
byte pinMute = 3;
byte pinVentilador = 4;
byte pinLecturaAudio = A0;
byte pinSensorTemp = A1;


//---------- Variables del programa ---------//
float value = 0;//Guardo temporalmente el valor de audio

int cantidadLeds = 50;//La cantidad de leds se puede modificar (procure que la cantidad sea par)
unsigned long tiempoTemperatura = 0;//Variable donde guardamos el valor de millis para compararlo
unsigned long tiempoCambioEfecto = 0;//Variable donde guardamos el valor de millis para compararlo
bool estadoEfectos = true;//Determina si los efectos estan activos o no
byte efectoActual = 0;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos


//--------- Instancias de Objetos ---------//
AmplifierControl ampli(pinMute, pinSensorTemp, pinVentilador);
AudioControl audio(pinLecturaAudio);
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);


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


void setup() {

    Serial.begin(115200);//Inicializo el puerto serial
    leds.begin();//Inicializo los leds
    leds.clear();//Limpio la tira
}


void loop(){

    value = audio.readAudio();

    if(estadoEfectos == true && value < 20){
        efectos[efectoActual]->run(value);//Actualizo el estado de los leds
    }
    
    if((millis() - tiempoTemperatura) >= 1000)
    {
        Serial.println(ampli.readTemperature());//Actualizo el estado de la temperatura
        estadoEfectos = true;//Enciendo los efectos

        if(ampli.getStateTempVeryHigh() == true){
            leds.clear();//Apago los leds
            estadoEfectos = false;//Apago los efectos
            ampli.mute(true);//Muteo el amplificador
        }
        else{
            if(audio.getStateMute() == true){
                leds.clear();//Apago los leds
                estadoEfectos = false;//Apago los efectos
                ampli.mute(true);//Activo el mute del amplificador
            }
            else{
                ampli.mute(false);//Desactivo el mute del amplificador
            }
        }
        tiempoTemperatura = millis();//Vuelvo a 0 la diferencia de timepo
    }

    if((millis() - tiempoCambioEfecto) >= 10000){
        efectoActual++;//Incremento el efecto
        leds.clear();//Apago los leds

        if(efectoActual >= cantidadEfectos){
            efectoActual = 0;//Vuelvo a 0 el contador
        }

        tiempoCambioEfecto = millis();//Vuelvo a 0 la diferencia de tiempo
    }
}