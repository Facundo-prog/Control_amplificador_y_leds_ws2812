#ifndef AmplifierControl_h
#define AmplifierControl_h

#include <Arduino.h>

class AmplifierControl
{
    public:
        AmplifierControl(byte pinMute, byte pinSensorTemp, byte pinFan);
        void setTemperatureRange(int tempLow, int tempHigh, int tempVeryHigh);
        void setSetingsAdc(float maximumVoltajeAdc, int resolution);
        void mute(bool value);
        float readTemperature();
        bool getStateTempVeryHigh();

    private:
        byte _pinMute;
        byte _pinFan;
        byte _pinSensorTemp;
        bool _muteState = false;
        bool _stateTempVeryHigh = false;
        int _tempLow;
        int _tempHigh;
        int _tempVeryHigh;
        float _maximumVoltajeAdc = 5.0;
        int _resolution = 1024;
};

#endif