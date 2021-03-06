#ifndef Feedbacks_Handler_h
#define Feedbacks_Handler_h

#include "Haptic.h"
#include "RGB_LED.h"
#include "NEO_STRIP.h"
#include "MATRIX.h"
#include "DRV2605.h"
#include "BUZZER.h"

class Feedbacks_Handler
{
    public:
      Feedbacks_Handler();   //default constructor
      
      String UpdateFeedback();
      void HandleTime(unsigned int ElapsedTime);

      // Haptic
      void setHapticMotor(Haptic *pHapticMotor);
      void setHapticMotor(DRV2605 *pHapticIC);
      void Vibrate(String Type);
      void burst();
      void shortv();
      void longv();
      void raise();
      void fall();
      void raiseFall();

      // RGB Led
      void setRGB_LED(RGB_LED *pLED);

      // RGB Strip
      void setNEO_STRIP(NEO_STRIP *pSTRIP);
      void setColor(String color);
      void blink(String color);
      void fade(String color);

      // MATRIX
      void setMATRIX(MATRIX *pMATRIX);
      void startGazing();
      void stopGazing();
      void showFace(String type);

      // BUZZER
      void setBuzzer(BUZZER *pBuzzer);
      void buzz(char *song);
      
    private:
      Haptic *HapticMotor;
      bool HapticAvailable;

      DRV2605 *HapticIC;
      bool HapticICAvailable;

      RGB_LED *LED;
      bool RGB_LEDAvailable;

      NEO_STRIP *STRIP;
      bool NEO_STRIPAvailable;

      MATRIX *MATRIXX;
      bool MATRIX_Available;

      BUZZER *Buzz;
      bool BUZZER_Available;
     
};

#endif
