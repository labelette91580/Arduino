    #define HEXTODEC(AH) AH = AH-'0'; if (AH>9) AH = AH -( 7 );if (AH>15) AH = AH - 0x20 ;

#define CMD_LIST const char* cmd[]="drwiaxtsma"

byte readCar()
{
    char Ah;
    while (DbgSerial.available() ==0 ); 
    Ah  = Serial.read();
     DbgSerial.print(Ah);
    return Ah;

}
byte readByte()
{
    byte vByte=0;
    char Ah;
           Ah  = readCar();
           if (Ah == ' ') {
            Ah  = readCar();;
           }

           if (Ah == 'n') 
           {
                //numerique decimale
               Ah  = readCar();
               do{
                   vByte = vByte * 10  ;
                   vByte += Ah -'0';
                   Ah  = readCar();

               }while (Ah!=' ');
           }
           else
           if (Ah == 'b') 
           {
            //bin
               Ah  = readCar();
               do{
                   vByte = vByte << 1 ;
                   vByte += Ah -'0';
                   Ah  = readCar();

               }while (Ah!=' ');
           }
           else
           {
                //hexa
               char Al  = readCar();
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
         input = readCar();
        if (input == 'd') //d=dump all register values
        {
            radio.readAllRegs();
        }
        if (input == 'r') // RXX read register number xx 
        {
           byte addr = readByte();
           DbgSerial.print(" Read :");
           printReg( addr);
        }
        if (input == 'R') // RXX read register number xx 
        {
           byte addr = readByte();
           DbgSerial.print(" Read :");
           printReg( addr);
           addr++;
           DbgSerial.print(" Read :");
           printReg( addr);
        }
        if (input == 'w') // WAAVVwrite register number xx 
        {
           byte addr = readByte();
           byte val  = readByte();
       
           DbgSerial.print(" Write Adr:");DbgSerial.print(addr,HEX);
           DbgSerial.print("=");       DbgSerial.println(val,HEX);
           radio.writeReg(addr, val) ;
           printReg( addr);
        }

        if (input == 'W') // WAAVVVV write register number xx 
        {
           byte addr = readByte();
           byte val1  = readByte();
           byte val2  = readByte();
       
           DbgSerial.print(" Write Adr:");DbgSerial.print(addr,HEX);
           DbgSerial.print("=")          ;DbgSerial.println(val1,HEX);
           radio.writeReg(addr, val1) ;
           printReg( addr);

           addr++;
           DbgSerial.print(" Write Adr:");DbgSerial.print(addr,HEX);
           DbgSerial.print("=")          ;DbgSerial.println(val2,HEX);
           radio.writeReg(addr, val2) ;
           printReg( addr);
        }

        if (input == 'i')
        {
          DbgSerial.print(" [RX_RSSI:");DbgSerial.print(radio.readRSSI());DbgSerial.println("]");
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
          DbgSerial.print( "Radio Temp is ");
          DbgSerial.print(temperature);
          DbgSerial.print("C, ");
          DbgSerial.print(fTemp); //converting to F loses some resolution, obvious when C is on edge between 2 values (ie 26C=78F, 27C=80F)
          DbgSerial.println('F');
        }
        if (input == 's')
          {
            easy->setSwitch(true,55,1);    // turn on device 0
            delay(3000);        // wait 3 sec
            easy->setSwitch(false,55,1);    // turn on device 0
            DbgSerial.println("Sent");
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

