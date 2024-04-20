//#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>            //assumes Arduino IDE v1.0 or greater

#include "DecodePortail.h"

#include "util.h"
#include "Domotic.h"


uint16_t getRaw16bValue(uint8_t* data, uint8_t offset, uint8_t size);
uint8_t getRaw08bValue(uint8_t* data, uint8_t offset, uint8_t size);


    DecodePortail::DecodePortail (byte pMaxCode) { 
        SetPulseDuration(1100,400,400,1100,0,0, 200);
        PacketCountSeuil=pMaxCode;
        Name ="R";
        max_bits =24;

    }
 
  void DecodePortail::report(){

        byte id1 = data[0];
        byte id2 = data[1];
        byte id3 = data[2];
        byte id4 = 0;

    reportDomoticHomeEasy(  id1   , id2   , id3   , id4   , 0 , 1   , 1,   data, pos);  
  }

  bool DecodePortail::isValid()      		 
  {	  
        return true  ;
  }    

  byte DecodePortail::getCrc()         
  {	  
      return (0);  
  }

