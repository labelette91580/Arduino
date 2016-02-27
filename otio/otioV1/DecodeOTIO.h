class DecodeOTIO {
public:
    byte total_bits, state, MaxTemp , NbTempOk ;
    long T , Temp , tmpTemp, lastTemp;
    long LastReceived ; 
public:
    enum { UNKNOWN, T0, T1, T2, T3, OK, DONE };

    void resetDecoder () {
          total_bits =  0;
          state = UNKNOWN;
          T = 0 ;
    }    
    DecodeOTIO (byte pMaxTemp=5) { Temp = 0 ; NbTempOk=0;MaxTemp=pMaxTemp;tmpTemp=0;lastTemp=0;LastReceived=0;resetDecoder(); }

    /* 0 = short pulse = 2ms */
    /* 1 = long  pulse = 4ms */
    /* 2 = end   pulse = 8ms */
    
    byte getPulseBit(word p)
    {
    if ( p < 2500)
      return 0 ;
    else
    if ( p < 6500)
      return 1 ;
    else 
      return 2 ;
    }
    
    bool nextOnePulse (word width , byte data)   {
       /* 1er bit */ 
       if ( (width>1500)&& (data==1) )   state = T0 ;
      /* bit next  */
      if ( (width>1000)&&(state == T0) )
      {
        total_bits++;
        /*  end of word and correct number of bit  */
        if ( width > 6000)
        {
          if (total_bits==25)
          {
            //update temperature
            tmpTemp = T ;
            resetDecoder ();
            return true;
          }
          else
          {
            resetDecoder ();
            return false;
          }
        } 
        else
        {
          /* add bit to temp */
          T = T << 1;
          T = T | getPulseBit(width);
        }
        if (total_bits>=25)
            resetDecoder ();
      }
      return false;   
  }
  bool nextPulse (word width , byte data)   {
    if (nextOnePulse ( width ,  data) ){
       if (NbTempOk==0) lastTemp = tmpTemp ;
       if (lastTemp == tmpTemp ) NbTempOk ++ ; else NbTempOk -- ;
       if (NbTempOk >= MaxTemp ){
          NbTempOk = 0 ;
          Temp = lastTemp ;
//          if ( (millis()-LastReceived) > 2000)
          {
            LastReceived = millis();
            return true;
          }
//          else
//            return false ;
            
       } 
    }
    return false ;

  }  
  

/*
NB --IDENT-------    SIGN- -----TEMP---    -BAT---   --FRAC-    End Temp
   3 2 1 0 9 8 7 6   5     4 3 2 1 0 9 8   7 6 5 4   3 2 1 0     
25 1 0 0 1 0 1 0 1   1     0 0 0 1 0 1 1   0 0 0 0   0 0 1 0    88  -11.2
25 1 0 0 1 0 1 0 1   1     0 0 0 0 0 0 0   0 0 0 0   0 0 1 0    87  -0.2                                                      
25 1 0 0 1 0 1 0 1   0     0 0 0 0 0 0 1   0 0 0 0   0 0 1 0    88  01.2                                                      
25 1 0 0 1 0 1 0 1   0     0 0 0 1 0 0 0   0 0 0 0   0 0 1 0    88  08.2
25 1 0 0 1 0 1 0 1   0     0 0 0 1 0 1 0   0 0 0 0   0 1 0 1    87  10.5
*/
  /* temperature in Lsb = 0.1 degrec C */
  int getTemperature(){
    int  t = Temp ;
    byte frac = t & 0xF ;
    t = t >>8 ;
    byte signe = t &  0x80 ;
    /* partie entiere */
    t = t & 0x7F;
    /* partie frac */
    t = t*10  ;
    t = t  + frac ;
    if (signe)
      t = -t;
    return t;        
    
  }
  byte getId(){
    return (Temp >> 16) ;        
  }
  byte getBatteryOk(){
    return ( (Temp &  0x80 )!= 0 ) ;
  }
  void ReportSerial(){
    Serial.print ("Otio:");
    Serial.print (Temp,HEX);
    Serial.print (" T:");
    int t = getTemperature();
    Serial.print (t/10);
    Serial.print ('.');
    t=t%10; if (t<0)t=-t;
    Serial.print (t);
    Serial.print (" Id:");
    Serial.print (getId(),HEX);
    Serial.print (" Bat:");
    Serial.println (getBatteryOk());

  }
};






/* 24 bit decodage 
   --IDENT-------    SIGN-   -TEMP---    -BAT---   --FRAC-     DEG
25 1 0 0 1 0 1 0 1   1 0 0   0 1 0 1 1   0 0 0 0   0 0 1 0 88  -11.2
25 1 0 0 1 0 1 0 1   1 0 0   0 1 0 0 1   0 0 0 0   0 0 1 1 88  -9.3
25 1 0 0 1 0 1 0 1   1 0 0   0 1 0 0 0   0 0 0 0   0 0 1 1 87  -8.3
25 1 0 0 1 0 1 0 1   1 0 0   0 0 1 1 1   0 0 0 0   0 0 1 1 87  -7.3
25 1 0 0 1 0 1 0 1   1 0 0   0 0 1 0 0   0 0 0 0   0 1 0 0 87  -4.4                                                      
25 1 0 0 1 0 1 0 1   1 0 0   0 0 0 1 1   0 0 0 0   0 1 0 1 88  -3.5                                                      
25 1 0 0 1 0 1 0 1   1 0 0   0 0 0 0 0   0 0 0 0   0 0 1 0 87  -0.2                                                      
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 0 0   0 0 0 0   0 1 0 1 87   0.5                                                      
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 0 1   0 0 0 0   0 0 1 0 88  01.2                                                      
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 0 1   0 0 0 0   1 0 0 0 87  01.8                                                      
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 1 0   0 0 0 0   0 1 0 0 87  02.4                                                      
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 1 0   0 0 0 0   0 0 1 0 87  02.2
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 1 1   0 0 0 0   0 1 0 0 86  03.4
25 1 0 0 1 0 1 0 1   0 0 0   0 0 0 1 1   0 0 0 0   1 0 0 1 87  03.9
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 0 0   0 0 0 0   0 1 0 0 87  04.4
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 0 1   0 0 0 0   0 0 0 0 89  05.0
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 0 1   0 0 0 0   1 0 0 1 87  05.9
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 1 0   0 0 0 0   0 1 0 0 87  06.4
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 1 0   0 0 0 0   1 0 0 0 88  06.8
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 1 1   0 0 0 0   0 1 0 1 88  07.5
25 1 0 0 1 0 1 0 1   0 0 0   0 0 1 1 1   0 0 0 0   1 0 0 1 86  07.9
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 0 0   0 0 0 0   0 0 1 0 88  08.2
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 0 0   0 0 0 0   0 1 0 1 87  08.5
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 0 0   0 0 0 0   1 0 0 1 87  08.9
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 0 1   0 0 0 0   0 0 1 0 87  09.2
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 0 1   0 0 0 0   0 1 0 1 86  09.5
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 1 0   0 0 0 0   0 1 0 1 87  10.5
25 1 0 0 1 0 1 0 1   0 0 0   0 1 0 1 1   0 0 0 0   0 1 1 0 87  11.6
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 0   0 0 0 0   0 0 0 0 87  12.0
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 0   0 0 0 0   0 0 1 1 87  12.3
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 0   0 0 0 0   0 1 1 0 87  12.6
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 1   0 0 0 0   0 0 1 1 86  13.7
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 1   0 0 0 0   0 1 1 0 87  13.6
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 0 1   0 0 0 0   1 0 0 1 87  13.9
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 1 0   0 0 0 0   0 0 1 0 86  14.2
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 1 1   0 0 0 0   0 0 0 1 88  15.1
25 1 0 0 1 0 1 0 1   0 0 0   0 1 1 1 1   0 0 0 0   0 1 0 0 88  15.4
25 1 0 0 1 0 1 0 1   0 0 0   1 0 0 0 0   0 0 0 0   0 0 0 1 87  16.1
25 1 0 0 1 0 1 0 1   0 0 0   1 0 0 0 0   0 0 0 0   0 1 1 1 87  16.7
25 1 0 0 1 0 1 0 1   0 0 0   1 0 0 1 0   0 0 0 0   0 0 0 0 88  18.0
25 1 0 0 1 0 1 0 1   0 0 0   1 0 0 1 1   0 0 0 0   0 0 0 1 87  19.1
25 1 0 0 1 0 1 0 1   0 0 0   1 0 1 0 1   0 0 0 0   0 0 0 0 87  21.0
*/


/* pulse in 100micros unit 
short : 2000..2200 micros
long  : 4000..4200 micros
end   :8700..8800    

   42 21 20 41 21 41 21 41 21 21 20 42 21 41 41 20 21 41 21 20 42 21 21 40 
87 41 21 20 42 20 42 20 42 21 21 20 42 20 42 41 21 20 42 20 21 41 21 20 40 
87 41 20 21 43 20 41 21 43 20 21 21 42 20 42 41 22 20 41 21 21 41 21 21 40 
87 41 21 20 41 19 42 20 42 20 22 20 42 19 42 41 21 19 42 20 21 41 22 20 39 
88 41 20 21 42 20 41 20 42 21 20 21 42 20 41 42 21 20 58 21 20 42 20 21 40 
87 41 20 21 41 20 41 22 41 20 21 21 41 21 41 42 20 20 41 22 20 42 21 21 40 
87 42 20 21 41 21 41 21 40 21 20 21 41 22 41 42 20 21 41 21 19 42 20 21 39 
87 42 20 21 41 21 41 21 41 21 20 21 41 21 40 42 21 21 41 21 20 42 20 21 40 
87 41 20 21 41 21 41 22 41 21 21 21 41 21 41 42 20 21 41 22 20 42 21 21 40 
87 42 20 21 41 21 41 21 40 21 20 21 41 22 41 42 20 21 41 21 19 42 20 21 39 
87 42 20 21 41 21 41 42 41 22 20 21 41 21 41 41 19 22 41 21 21 43 20 21 40 
87 42 20 21 41 21 40 21 41 21 20 22 41 21 41 42 20 21 40 21 20 42 20 22 40 
87 42 21 21 41 21 41 21 41 21 21 22 40 21 41 43 20 21 41 21 20 42 21 21 39 
87 42 20 21 41 22 41 21 41 22 20 21 41 21 41 41 19 22 41 21 21 43 20 21 40 
87 42 20 21 41 21 40 21 41 21 19 22 41 21 41 42 20 21 40 21 20 41 20 20 40 
87 42 21 21 41 21 41 21 41 21 21 21 40 21 41 43 20 21 41 21 20 42 21 21 56 
87 41 20 21 41 20 41 21 41 20 20 21 42 20 42 42 21 20 41 21 20 41 20 21 39 
87 40 21 20 41 21 42 20 41 20 21 20 41 21 42 41 20 21 42 20 20 40 21 20 40 
87 42 20 20 42 21 41 20 42 21 20 20 42 20 41 41 21 21 41 20 21 42 20 20 41 
87 41 20 21 43 20 41 21 42 20 20 21 43 20 42 41 21 20 41 21 21 41 20 21 40 
87 40 21 20 41 20 42 20 41 20 21 20 41 

*/