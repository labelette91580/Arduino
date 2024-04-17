#ifndef _DecodePortail_
#define _DecodePortail_

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>            //assumes Arduino IDE v1.0 or greater
#else
#include "deftype.h"
#endif

#include "DecodePwm.h"


#define TEST_PULSE(WIDTH,PULSE_LEN,TOL)((WIDTH> (PULSE_LEN-TOL))&&(WIDTH<(PULSE_LEN+TOL)))

class DecodePortail  : public DecodePwm{
public:
public:
    
    DecodePortail (byte pMaxCode=2)  ;
    virtual void report();
    virtual bool isValid();
    virtual byte getCrc();

 };

#endif