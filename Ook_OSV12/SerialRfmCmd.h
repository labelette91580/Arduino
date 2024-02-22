    #define HEXTODEC(AH) AH = AH-'0'; if (AH>9) AH = AH -( 7 );if (AH>15) AH = AH - 0x20 ;

#define CMD_LIST const char* cmd[]="drwiaxtsma"

byte readByte()
{
    byte vByte=0;
    char Ah;
           while (Serial.available() ==0 ); 
           Ah  = Serial.read();
           if (Ah == ' ') {
            while (Serial.available() ==0 ); 
            Ah  = Serial.read();
           }

           if (Ah == 'n') 
           {
                //numerique decimale
               while (Serial.available() ==0 );
               Ah  = Serial.read();
               do{
                   vByte = vByte * 10  ;
                   vByte += Ah -'0';
                   while (Serial.available() ==0 );
                   Ah  = Serial.read();

               }while (Ah!=' ');
           }
           else
           if (Ah == 'b') 
           {
            //bin
               while (Serial.available() ==0 );
               Ah  = Serial.read();
               do{
                   vByte = vByte << 1 ;
                   vByte += Ah -'0';
                   while (Serial.available() ==0 );
                   Ah  = Serial.read();

               }while (Ah!=' ');
           }
           else
           {
                //hexa
               while (Serial.available() ==0 );
               char Al  = Serial.read();
               HEXTODEC(Ah);
               HEXTODEC(Al);
               vByte = Ah*16+ Al ; 
           }

           return vByte ;
}

void printReg(byte addr)
{
    byte regVal = radio.readReg(addr);
    radio.PrintReg( addr , regVal);    
}
void readKbdCmd()
{
    byte input;
    if (Serial.available() )
    {
         input = Serial.read();
        if (input == 'd') //d=dump all register values
        {
            radio.readAllRegs();
        }
        if (input == 'r') // RXX read register number xx 
        {
           byte addr = readByte();
           Serial.print(" Read :");
           printReg( addr);
        }
        if (input == 'R') // RXX read register number xx 
        {
           byte addr = readByte();
           Serial.print(" Read :");
           printReg( addr);
           addr++;
           Serial.print(" Read :");
           printReg( addr);
        }
        if (input == 'w') // WAAVVwrite register number xx 
        {
           byte addr = readByte();
           byte val  = readByte();
       
           Serial.print(" Write Adr:");Serial.print(addr,HEX);
           Serial.print("=");       Serial.println(val,HEX);
           radio.writeReg(addr, val) ;
           printReg( addr);
        }

        if (input == 'W') // WAAVVVV write register number xx 
        {
           byte addr = readByte();
           byte val1  = readByte();
           byte val2  = readByte();
       
           Serial.print(" Write Adr:");Serial.print(addr,HEX);
           Serial.print("=")          ;Serial.println(val1,HEX);
           radio.writeReg(addr, val1) ;
           printReg( addr);

           addr++;
           Serial.print(" Write Adr:");Serial.print(addr,HEX);
           Serial.print("=")          ;Serial.println(val2,HEX);
           radio.writeReg(addr, val2) ;
           printReg( addr);
        }

        if (input == 'i')
        {
          Serial.print(" [RX_RSSI:");Serial.print(radio.readRSSI());Serial.println("]");
        }
        if (input == 'a')
        {
          attachInterrupt(digitalPinToInterrupt(PDATA) , ext_int_1, CHANGE);
          pinMode(PDATA, INPUT);
          radio.setMode(RF69_MODE_RX);
        }
        if (input == 'x')
        {
          detachInterrupt(digitalPinToInterrupt(PDATA));
          easy->initPin();
          radio.setMode(RF69_MODE_TX);
        }
        if (input == 't')
        {
          byte temperature =  radio.readTemperature(-1); // -1 = user cal factor, adjust for correct ambient
          byte fTemp = 1.8 * temperature + 32; // 9/5=1.8
          Serial.print( "Radio Temp is ");
          Serial.print(temperature);
          Serial.print("C, ");
          Serial.print(fTemp); //converting to F loses some resolution, obvious when C is on edge between 2 values (ie 26C=78F, 27C=80F)
          Serial.println('F');
        }
        if (input == 's')
          {
            easy->setSwitch(true,55,1);    // turn on device 0
            delay(3000);        // wait 3 sec
            easy->setSwitch(false,55,1);    // turn on device 0
            Serial.println("Sent");
          }
        if (input == 'm')
          {
            easy->setSwitch(true,55,1);    // turn on device 0
          }
        if (input == 'a')
          {
            easy->setSwitch(false,55,1);    // turn on device 0
          }
        if (input == 'p')//dump pulse serial
          {
            if (dumpPulse==0) dumpPulse=1;else dumpPulse=0;
          }
    }
}

