#ifndef AudioControl_h
#define AudioControl_h

#include <Arduino.h>

class AudioControl{

    public:
        AudioControl(byte pinAudio);
        float readAudio();
        void setDetectionFrequency(int frequency);
        void setDetectionSilence(bool value, int readingFrequency, int ruinValue, float minimumPeakValue);
        bool getStateMute();
        
    private:
        //Funciones internas
        void deteccionDeSilencio();
        float getAudio();

        //Pines
        byte _pinAudio;

        //Deteccion de audio
        float _valorAudioAnterior;
        float _valorMute = 0.0;
        float _valorMinimoPico = 1;
        bool _estadoMute = false;
        bool _deteccionMute = true;
        int _frecuenciaDeteccion = 2500;
        int _frecuenciaDeteccionSilencio = 10000;
        int _valorDeRuido = 10;

        //Variables de tiempo
        unsigned long _tiempoMute = 0;
        unsigned long _timpoDeteccionAudio = 0;

};

#endif