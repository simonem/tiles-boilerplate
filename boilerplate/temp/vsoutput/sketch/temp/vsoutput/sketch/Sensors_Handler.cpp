#include "Sensors_Handler.h"

Sensors_Handler::Sensors_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventString = String();

    //Accelerometer
    _Accelerometer = NULL;
    Accelerometer_Timing = 0;

    //InertialCentral
    _InertialCentral = NULL;
    InertialCentral_Timing = 0;

    //TouchController
    _TouchSensor = NULL;
    TouchSensor_Timing = 0;

    states = 1;
}


void Sensors_Handler::HandleTime(unsigned int ElapsedTime)
{
    Accelerometer_Timing += ElapsedTime;  
    InertialCentral_Timing += ElapsedTime;
    TouchSensor_Timing += ElapsedTime;
    _InertialCentral->HandleTime(ElapsedTime);
}

String Sensors_Handler::pollEvent()    // If an event has occured returns the event code
{
   EventString = "";

    if(_AccelerometerAvailable == true && Accelerometer_Timing >= ACCELEROMETER_UPDATE)
    {
        Serial.println("ACC UPDATE");
        Accelerometer_Timing = 0;
        
        _Accelerometer->RefreshValues();
        
        if (_Accelerometer->isTapped())
        EventString = String("tap,single");
        
        else if (_Accelerometer->isDoubleTapped())
        EventString = String("tap,double");
        
        else if (_Accelerometer->isShaked())
        EventString = String("shake");
        
        //else if (_Accelerometer->isTilted())
        //    EventString = String("tilt");
    }

    if(_InertialCentralAvailable == true && InertialCentral_Timing >= ACCELEROMETER_UPDATE)
    {
        InertialCentral_Timing = 0;
        short isRotated = _InertialCentral->isRotated();
        
        _InertialCentral->RefreshValues();
        
        if (_InertialCentral->isTapped())
            EventString = String("tap");
        
        else if (_InertialCentral->isDoubleTapped())
            EventString = String("doubletap");
        
        else if (_InertialCentral->isShaked()){}
           // EventString = String("shake");
        
        else if (_InertialCentral->isTilted())
            EventString = String("tilt");
        
        else if(isRotated != 0)
        {
            if(isRotated == 1)
                EventString = String("clockrot");
            else if(isRotated == -1)
                EventString = String("cclockrot");
        }
    }

     if(_TouchSensorAvailable == true && TouchSensor_Timing >= TOUCHSENSOR_UPDATE)
    {
        TouchSensor_Timing = 0;
        short touchpin = _TouchSensor->isTouched();
        if(touchpin == 2)
        {
            String temp = String(touchpin);
            EventString = String("touched," + temp);
            //Serial.print("Touched");
            //Serial.println(touchpin);
            //state_change();
        } else if(touchpin == 1){
            Serial.println("quiquiqui");
           BLE->shoutdown();
        }
    } 
    

    if(EventString != String(""))
    {  
        Token Event;
        Event.set(EventString);
        BLE->SendEvent(&Event);        
    }  
    return EventString;
}


void Sensors_Handler::setAccelerometer(ADXL345 *Acc)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _Accelerometer = Acc;
    _AccelerometerAvailable = Acc->SensorAvailable;
}

void Sensors_Handler::setInertialCentral(LSM9DS0 *InC)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _InertialCentral = InC;
    _InertialCentralAvailable = InC->SensorAvailable;
}

void Sensors_Handler::setTouchSensor(CAP1188 *Touch)  
{
    _TouchSensor = Touch;
    _TouchSensorAvailable = true;
}

void Sensors_Handler::state_change()
{
    extern Feedbacks_Handler feedback_handle;
    switch(states){
        case 1:
        feedback_handle.showFace("happy1");
        states++;
        break;
        case 2:
        feedback_handle.showFace("dollar");
        states++;
        break;
        case 3:
        feedback_handle.showFace("puzzled");
        states++;
        break;
        case 4:
        feedback_handle.showFace("sad1");
        states++;
        break;
        case 5:
        feedback_handle.showFace("sad2");
        states++;
        break;
        case 6:
        feedback_handle.showFace("sad3");
        states++;
        break;
        case 7:
        feedback_handle.showFace("x");
        states++;
        break;
        case 8:
        feedback_handle.startGazing();
        states=1;
        break;
    }
    
}
