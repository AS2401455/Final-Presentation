#include "DC_Motor.h"
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

unsigned char MotorArray[][2] = {
  {2, 3}
  };

void DC_Init(){
    DDRD |=  (1 << MotorArray[0][0]);
    DDRD |=  (1 << MotorArray[0][1]);
}


void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed){

    if (Direction == DIRECTION_CW)
    {
      PORTD |=  (1 << MotorArray[MotorID][0]);
      PORTD &=  ~(1 << MotorArray[MotorID][1]);
    } else{
      PORTD &=  ~(1 << MotorArray[MotorID][0]);
      PORTD |=  (1 << MotorArray[MotorID][1]);
    }

}

void DC_Stop(unsigned char MotorID){
    PORTD |=  (1 << MotorArray[MotorID][0]);
    PORTD |=  (1 << MotorArray[MotorID][1]);
}