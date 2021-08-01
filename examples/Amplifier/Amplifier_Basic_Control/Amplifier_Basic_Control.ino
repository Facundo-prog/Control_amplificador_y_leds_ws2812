/* En este ejemplo basico se controla la temperatura, un ventilador y el pin de mute de un Amplificador
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin ventilador
*  3(out) -> Pin mute
*  A0(in) -> Pin de lectuta de temperatura (LM35)
*/

#include "AmplifierControl.h" //Libreria que controla el amplificador
#include <Arduino.h>


//------Pines Utilizados ------//
byte pinMute = 3;
byte pinVentilador = 2;
byte pinSensorTemp = A0;


//---------- Variables del programa ---------//
long tiempoTemperatura = 0;//Variable donde guardamos el valor de millis para compararlo


//--------- Instancias de Objetos ---------//
AmplifierControl ampli(pinMute, pinSensorTemp, pinVentilador);


void setup() {
    Serial.begin(115200);//Inicializo el puerto serial
}


void loop(){

    if((millis() - tiempoTemperatura) >= 1000){
        Serial.println(ampli.readTemperature());//Actualizo el estado de la temperatura

        if(ampli.getStateTempVeryHigh() == true){
            ampli.mute(true);//Habilito el mute del amplificador
        }
        else{
            ampli.mute(false);//Deshabilito el mute del amplificador
        }
        
        tiempoTemperatura = millis();//Vuelvo a 0 la diferencia de timepo
    }
}