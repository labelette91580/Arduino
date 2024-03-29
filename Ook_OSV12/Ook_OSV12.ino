#ifdef WIN32
#include "vspde.h"
#else
#define stricmp(a, b) strcasecmp(a, b)
#endif

#include "Config.h"

#include "Domotic.h"
#include "DecodeOOK.h"
#include <HomeEasyTransmitter.h>

#ifdef OOK_ENABLE        
#include "OOKDecoder.h"
#endif

#ifdef HAGER_ENABLE        
#include <HagerDecoder.h>
HagerDecoder    hager;
#endif

#ifdef RUBICSON_ENABLE        
#include "rubicson.h"
#endif

#ifdef HOMEEASY_ENABLE
#include "DecodeHomeEasy.h"
#endif

#ifdef MD230_ENABLE
#include "DecodeMD230.h"
DecodeMD230 MD230(2) ;
#endif

#ifdef OTIO_ENABLE        
#include <DecodeOTIO.h>
DecodeOTIO Otio(3);  
#endif

#ifdef RAIN_ENABLE        
#include "DecodeRain.h"
#endif

#include "fifo.h"
TFifo  fifo;

// #if defined(__AVR_ATmega2560__) 
// #define ledPin  13 sur UNO
// #define ledPin  9 sur anarduino
// #define ledPin  2 sur 8266

byte ledPin = LED_BUILTIN ;

//1 = dump pulse len to serial
byte dumpPulse=0;     ////format word
byte dumpPulseByte=0; //format hexa byte / 10



#ifdef ESP8266
byte PDATA = 5 ;// GPIO5 = D1 sur la carte wiimos
byte PCLK  = 4 ;// GPIO4 = D2 sur la carte wiimos

#else
byte PDATA = 3 ;//pin for data input/output
byte PCLK  = 4 ;//pin for clk  input/output
#endif

word    NbPulse  ;
word    NbPulsePerSec ;
word    NbPulsePerMin ;
word    NbDecodedPackets ;

//etat du pulse
byte        PulsePinData;
word        Seconds;
word        lastSeconds;
word        lastMinute ;
word        lastHour   ;
word        lastDay   ;

#ifdef RFM69_ENABLE
#include <RFM69.h>
#include <RFM69registers.h>
#include <SPI.h>
RFM69 radio;
#endif

// This is the Home Easy controller
// This example will use a 433AM transmitter on
// pin 3 : data pin
// pin 4 : clk  pin
HomeEasyTransmitter * easy;

#include  "reportSerial.h"

#include "hager.h"

#ifdef HIDEKI_ENABLE        
#include "tfaDecoder.h"
#endif

#ifdef BMP180_ENABLE
#include "bmp180.h"
#endif

//OTIO;OOK;HAGER;HOMEEASY;MD230;RUBICSON;HIDEKI;RAIN;

char DecoderListInit[] = 

#ifdef OTIO_ENABLE        
                          "OTIO"     ";"
#endif
#ifdef OOK_ENABLE         
                          "OOK"      ";"
#endif
#ifdef HAGER_ENABLE       
                          "HAGER"    ";"
#endif
#ifdef HOMEEASY_ENABLE    
                          "HOMEEASY" ";"
#endif
#ifdef MD230_ENABLE       
                          "MD230"    ";"
#endif
#ifdef RUBICSON_ENABLE    
                          "RUBICSON" ";"
#endif
#ifdef HIDEKI_ENABLE      
                          "HIDEKI"   ";"
#endif
#ifdef RAIN_ENABLE        
                          "RAIN"     ";"
#endif
"END;"
;


const char* DecodersName[] = {
"",
"OTIO"     ,
"OOK"      ,
"HAGER"    ,
"HOMEEASY" ,
"MD230"    ,
"RUBICSON" ,
"HIDEKI"   ,
"RAIN"     ,
0

};



DecodeOOK* Decoders [sizeof(DecodersName)/sizeof(char*)] ;


byte getDecoderFromName (char *name)
{
    byte i = 0 ;
    while(DecodersName[i] != 0)
    {
        if (stricmp(name,DecodersName[i])==0)
            return i;
    }
    return 0;
}

void createDecoderList(const char* DecoderList)
{
    byte index = 0 ;
    char name[10];

    const char* ptb = DecoderList ;
    const char* pte = strchr(ptb,';');

    while( (pte) && (* pte != 0))
    {
        Decoders[index]=0;
        strncpy(name,ptb,pte-ptb);
        name[pte-ptb]=0;
        pte++  ;
        ptb = name;
#ifdef OOK_ENABLE         
        if (stricmp(ptb,  "OOK"      )==0) { Decoders[index++] = new   OregonDecoderV2() ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef OTIO_ENABLE        
      if (stricmp(ptb,  "OTIO"     )==0) { Decoders[index++] = new   DecodeOTIO(2);    ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef HAGER_ENABLE       
      if (stricmp(ptb,  "HAGER"    )==0) { Decoders[index++] = new   HagerDecoder()    ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef HOMEEASY_ENABLE    
        if (stricmp(ptb,  "HOMEEASY" )==0) { Decoders[index++] = new   DecodeHomeEasy()  ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef MD230_ENABLE       
      if (stricmp(ptb,  "MD230"    )==0) { Decoders[index++] = new   DecodeMD230(2)    ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef RUBICSON_ENABLE    
        if (stricmp(ptb,  "RUBICSON" )==0) { Decoders[index++] = new   DecodeRubicson()  ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef HIDEKI_ENABLE      
        if (stricmp(ptb,  "HIDEKI"   )==0) { Decoders[index++] = new   Hideki()          ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
#ifdef RAIN_ENABLE        
        if (stricmp(ptb,  "RAIN"     )==0) { Decoders[index++] = new   DecodeRain(1)     ;  reportPrint("add ") ; reportPrint(ptb) ;reportPrint("\n"); };
#endif
        ptb=pte ;
        pte = strchr(ptb,';');
        Decoders[index]=0;
    }
}

int rssiGetAverage();

inline static void write(word w)
{
  static byte nbc = 0;
  if (w>=1000)
  {
  if (w>=9999) 
      w=9998 + (w & 1) ;
  Serial.write((char)(w/1000+'0') ); w = w % 1000; 
  Serial.write((char)(w/100 +'0') ); w = w % 100;  
  Serial.write((char)(w/10  +'0') ); w = w % 10;  
  Serial.write((char)(w     +'0') );              
  }
  else if (w>=100)
  {
  Serial.write((char)(w/100 +'0') ); w = w % 100;  
  Serial.write((char)(w/10  +'0') ); w = w % 10;  
  Serial.write((char)(w     +'0') );              
  }
  else if (w>=10)
  {
  Serial.write((char)(w/10  +'0') ); w = w % 10;  
  Serial.write((char)(w     +'0') );              
  }
  else 
  {
  Serial.write((char)(w     +'0') );              
  }
  nbc++;
  Serial.write(',');
  if ((nbc%16) == 0 )
    Serial.write('\n');

  
}

inline static void writeHexaByte(word w)
{
  static byte nbc = 0;

  byte ww ;
  if (w>=2550) 
    ww = 254 + (w & 1) ;
  else
    ww = w / 10 + (w & 1) ;

  Serial.write((char)DectoHex( ww >> 4  ) );   Serial.write((char)DectoHex( ww  & 0x0F      ) );   Serial.write(',');

  nbc++;
  if ((nbc%16) == 0 )
    Serial.write('\n');

  
}

//le signal du RFM69 entre sur int ext    d3 : int1 
//sur 8266 : interrupt shall be in IRAM
#ifdef ESP8266
void ICACHE_RAM_ATTR ext_int_1(void) {
#else
void ext_int_1(void) {
#endif

    static unsigned long  last;
    byte            pinData;
    word pulse;
    unsigned long  micro ;

    // determine the pulse length in microseconds, for either polarity
    micro = micros() ;
    pulse = (word )(micro - last);
    last  = micro ;

    pinData = digitalRead(PDATA);
        
    //calcul etat du pulse que l'on mesure
    if (pinData == 1)
        //tranistion 0--1 : etat pulse = 0 : bit 0 = 0
        pulse &=0xFFFE ;
    else
        //tranistion 1--0 : etat pulse = 1 : bit 0 = 1
        pulse |= 1 ;

    if(pulse>130)
        fifo.put(pulse);
}

#ifdef RFM69_ENABLE
#include "SerialRfmCmd.h"
#endif

void Setup (byte pData, byte pClk, byte pLed, const char* DecoderList  ) ;

void setup () {
    setReportType(REPORT_TYPE);
    Setup ( PDATA, PDATA, ledPin, DecoderListInit  );

}
void RadioInit()
{
#ifdef RFM69_ENABLE
    reportPrint("RFM69 Init");
    bool ok = radio.initialize(RF69_433MHZ,1,100);
    if (ok)
        reportPrint("ok ");
    else
        reportPrint("ko ");

    delay(10);
    radio.setMode(RF69_MODE_RX);
    if (isReportSerial())
    {
        Serial.print("READY:");
	    //Serial.println(wait);
    }
    //2400 bauds bit rate 3,4
    radio.writeReg(REG_BITRATEMSB,RF_BITRATEMSB_2400);
    radio.writeReg(REG_BITRATELSB,RF_BITRATELSB_2400);
    radio.writeReg(REG_OOKPEAK,RF_OOKPEAK_THRESHTYPE_PEAK +RF_OOKPEAK_PEAKTHRESHDEC_000);
    //lna 50 h    
    radio.writeReg(REG_LNA, RF_LNA_ZIN_50);
#endif     

}
void Setup (byte rxPin, byte txPin, byte pLed, const char* pDecoderList  ) {

    PDATA = rxPin;
    PCLK  = -1 ;
    ledPin = pLed;
    NbPulsePerMin = 0;
    NbDecodedPackets=0;

if (isReportSerial() )
    Serial.begin(2000000);
    //Serial.begin(115200);
else
    Serial.begin(38400);

createDecoderList(pDecoderList);

// initialize the LED pin as an output:
    if(ledPin)
        pinMode(ledPin, OUTPUT);       
    pinMode(PDATA, INPUT);
   
    attachInterrupt(digitalPinToInterrupt(PDATA) , ext_int_1, CHANGE);

#ifdef RFM69_ENABLE
RadioInit();
#endif     

#ifdef BMP180_ENABLE
        bmp180_init();
#endif

easy = new HomeEasyTransmitter (txPin,ledPin);

HagerSetPin(txPin,  pLed );

delay(100);
if (isReportSerial() )
{
    Serial.print("Version ");
    Serial.println(VERSION);

    Serial.print("Rx:");
    
#ifdef ESP8266
     Serial.print(Serial.getRxBufferSize());
#else
//     Serial.print(SERIAL_RX_BUFFER_SIZE);
#endif
}

DomoticInit();

registerStdout();

}


/*
void sendRfxCount2()
{
    int rssi = rssiGetAverage();
    rfxCmd.CEENCODER.packettype = pTypeCARTELECTRONIC;
    rfxCmd.CEENCODER.subtype    = sTypeCEencoder;
    rfxCmd.CEENCODER.packetlength = sizeof(rfxCmd.CEENCODER)-1;
    rfxCmd.CEENCODER.rssi = rssi >> 8;
    rfxCmd.CEENCODER.id1 = 0 ;
    rfxCmd.CEENCODER.id2 = 0;
    rfxCmd.CEENCODER.id3 = 0;
    rfxCmd.CEENCODER.id4 = 1;
    rfxCmd.CEENCODER.counter1_0 = 0 ;
    rfxCmd.CEENCODER.counter1_1 = 0;
    rfxCmd.CEENCODER.counter1_2 = NbPulsePerMin >> 8;
    rfxCmd.CEENCODER.counter1_3 = NbPulsePerMin & 0x00ff;
    rfxCmd.CEENCODER.counter2_0 = 0 ;
    rfxCmd.CEENCODER.counter2_1 = 0;
    rfxCmd.CEENCODER.counter2_2 = NbDecodedPackets >> 8;
    rfxCmd.CEENCODER.counter2_3 = NbDecodedPackets & 0x00ff;
    Serial.write((byte*)&rfxCmd.CEENCODER, rfxCmd.CEENCODER.packetlength + 1);

}
*/

//2 : toogle pin 1!0 set
void PulseLed(int Level)
{
    static int ledPinLevel = 0;

	if (Level == 2)
		ledPinLevel = !ledPinLevel;
	else
		ledPinLevel = Level;
#ifdef RASPBERRY_PI
//	if (ledPinLevel)
//		system("echo 1 | sudo tee /sys/class/leds/led0/brightness > /dev/null");
//	else
//		system("echo 0 | sudo tee /sys/class/leds/led0/brightness > /dev/null");

#else
    digitalWrite(ledPin, ledPinLevel);  
#endif
}

 void managedDecoder(DecodeOOK* Decoder , word p , byte  PinData )
 {
    {
      if (Decoder->nextPulse(p,PinData))
      {
        if (Decoder->newPacket())
        {// ce sont bien nos sondes (signature, identification dans le 1er octet du header
            PulseLed(2);
            
            Decoder->report();
            NbDecodedPackets++;
        }
        Decoder->resetDecoder(); 
      }
    }
 }
void ManagePulseReception ( word p) {
    byte i=0;
    DecodeOOK* Decoder ;
        if (p > 00 ) {
            if (dumpPulse)
                if (p>00)
                {       
                        write(p);
                }
            if (0)
            {
            char n = fifo.PWr-fifo.PRd;
            if (n<0)n+= SIZE_FIFO ;
            if(n>0)
                write(n);
            }

            //get pinData
            PulsePinData = p & 1;
            if (PulsePinData) {
                NbPulse++;
                NbPulsePerMin++;
            }
            if (dumpPulseByte)
                if (p>00)
                {       
                   writeHexaByte(p);
                }


#if   OFFSET_DURATION_HIGH
            //offset sur pulse high for RFM69
            if(PulsePinData)
                p+= OFFSET_DURATION_HIGH;
#endif

            Seconds = millis() / 1000;
            //every seconds
            if (Seconds != lastSeconds)
            {
                    lastSeconds = Seconds ;
                    NbPulsePerSec = NbPulse;
                    NbPulse = 0;
//          Serial.print(".");
            }
            //every minute
            if ((Seconds/60)!= lastMinute )
            {
                if (!DomoticReceptionInProgress())
                {
                    lastMinute = Seconds / 60;
#ifdef BMP180_ENABLE
                    bmp180_read();
#endif
                }
                lastMinute = Seconds/60;

				if (lastMinute & 1 )
					reportDomoticRfxCount(1,NbPulsePerMin);
				else
					reportDomoticRfxCount(2,NbDecodedPackets);
			    NbPulsePerMin = 0;
				
                //every hours
                if((lastMinute/60)!= lastHour)
                {
                    lastHour = lastMinute/60 ;

                    if((lastHour/24)!= lastDay)
                    {
                        lastDay = lastHour/24 ;
                        DomoticSaveToEEP();
                    }



                }

            }

            while ( (Decoder=Decoders[i++]) != 0 )
            {
                  managedDecoder(Decoder,p,PulsePinData);
            }

#ifdef OTIO_ENABLE        
            if (Otio.nextPulse(p, PulsePinData)) {
                //dumpPulse=0;
                if (isReportSerial())
                    Otio.ReportSerial();
                else
                    reportDomoticTemp("OTIO",Otio.getTemperature(), Otio.getId(), 0, Otio.getBatteryLevel());
                PulseLed(2);
                Otio.resetDecoder();
            }
#endif          

#ifdef MD230_ENABLE
            if (MD230.nextPulse(p, PulsePinData)) {
                if (isReportSerial())
                    MD230.ReportSerial();
                else
                    reportDomoticMD230(MD230.getData(), MD230.getBytes());
                PulseLed(2);
            }
#endif

#ifdef HAGER_ENABLE        
            //si pulse bas on enleve 100micros sinon on ajoute 100micros
            //pour compenser etat haut tronquer
            if (PulsePinData == 1) p -= 100; else p += 100;

            if (hager.nextPulse(p)) {
            if (isReportSerial())
                hager.reportSerial();
            else
                reportHagerDomotic(hager.getData(), hager.pos);
                hager.resetDecoder();
                PulseLed(2);
            }
#endif        

    }
}
void ManageDomoticCmdEmission() {
    byte i = 0 ;
    DecodeOOK* Decoder ;

    //check domotic send command reception
    //attente une secone max pour emetre si emission en cours -80--> -70
    //pas de reception en cours

    if ( DomoticPacketReceived == 0 )
        return ;

    while ( (Decoder=Decoders[i++]) != 0 )
    {
            //si reception en cours , ne traite pas la commande
            if (Decoder->total_bits != 0 )
                return ;
    }

    if (   (DomoticPacketReceived)
#ifdef RFM69_ENABLE
          && (radio.canSend(-70)   )
#endif
        )
  {
    PulseLed(HIGH);

     if (isReportSerial()) 
     {
         Serial.print("Cmd:");
         printHexa(&Cmd.ICMND.packetlength, Cmd.ICMND.packetlength+1 );
         Serial.println();
     }
    //start receive cmd
    if ( (Cmd.ICMND.packettype == pTypeInterfaceControl)&& (Cmd.ICMND.cmnd==cmdStartRec) ) {  
        DomoticStartReceive();
    }
    else if ( (Cmd.ICMND.packettype == pTypeInterfaceControl)&& (Cmd.ICMND.cmnd==cmdSTATUS) ) {  
        DomoticStatus();
    }
    else if ( (Cmd.ICMND.packettype == pTypeInterfaceControl)&& (Cmd.ICMND.cmnd==cmdRESET) ) {  
    }
    else if ( (Cmd.ICMND.packettype == pTypeInterfaceControl)&& (Cmd.ICMND.cmnd==cmdSETMODE) ) {  

        if (Cmd.IRESPONSE.UNDECODEDenabled )
            setReportType(getReportType() | REPORT_SERIAL);
        else
            setReportType(getReportType() & ~REPORT_SERIAL);
        
    }
    else
    {
        detachInterrupt(digitalPinToInterrupt(PDATA));

#ifndef RASPBERRY_PI
        easy->initPin();
#endif
#ifdef RFM69_ENABLE
        radio.setMode(RF69_MODE_TX);
#endif
        delay(10);
            
        if (Cmd.LIGHTING2.packettype==pTypeLighting2) 
        {  //
                if (Cmd.LIGHTING2.subtype == sTypeHEU)           //if home easy protocol : subtype==1
                {
#ifdef RASPBERRY_PI
                    extern void sendBuffer(word* transmitBuffer);
                    word transmitBuffer[256];
                    easy->SetTransmitBuffer(transmitBuffer,Cmd.LIGHTING2.cmnd, getLightingId(), Cmd.LIGHTING2.unitcode);    // turn on device 0
                    sendBuffer(transmitBuffer);
#else
                 if (isReportSerial()) 
                 {
                     Serial.print("cmd:");Serial.print(Cmd.LIGHTING2.cmnd);
                     Serial.print("id:");Serial.print(getLightingId());
                     Serial.print("cmd:");Serial.print(Cmd.LIGHTING2.unitcode);
                     Serial.println();
                 }
                 easy->setSwitch(Cmd.LIGHTING2.cmnd, getLightingId(), Cmd.LIGHTING2.unitcode);    // turn on device 0
                 //easy->SetTransmitBuffer( lbuffer,Cmd.LIGHTING2.cmnd,getLightingId(), Cmd.LIGHTING2.unitcode);
                 //easy->transmitRawBuffer(lbuffer,5);
                 

#endif
                    Cmd.LIGHTING2.subtype = 1;
                }
                else if (Cmd.LIGHTING2.subtype == sTypeAC)           //if hager protocol : subtype==0
                {
                    ManageHager(Cmd.LIGHTING2.id4, Cmd.LIGHTING2.unitcode, Cmd.LIGHTING2.cmnd);
                    Cmd.LIGHTING2.subtype = 0;
                }
                else
                    Cmd.LIGHTING2.subtype = 2;
        }
        else
        if (Cmd.RAW.packettype==pTypeRAW ) 
        {
            byte Nbrepeat = Cmd.RAW.repeat ;
            byte NbPulse  = (Cmd.RAW.packetlength - 4 ) / 2 ;
            for (byte ii = 0 ; ii<NbPulse;ii++){
                word wd = Cmd.Buffer[ii*2+5];
                wd = wd *256 ;
                wd = wd + Cmd.Buffer[ii*2+1+5] ;
                Cmd.Word[ii] = wd ;
            }
            Cmd.Word[NbPulse] = 0 ;
//            NbPulse = sizeof(pulses)/sizeof(word) ;
            if (isReportSerial()) 
            {
                Serial.print("Raw:");Serial.print(Nbrepeat);Serial.print(" ");Serial.print(NbPulse);Serial.print(" ");
                for (byte ii = 0 ; ii<NbPulse;ii++){
                    Serial.print(Cmd.Word[ii]) ;
                    Serial.print(" ");
//                    Serial.print(Cmd.Word[ii],16) ;
//                    Serial.print(" ");
                }
                Serial.println();
            }
///---------------
            easy->transmitRawBuffer(Cmd.Word,Nbrepeat);
        }
        else
                Cmd.LIGHTING2.subtype = 3;

        //acknoledge 
        {
            int rssi = rssiGetAverage()  ;
            Cmd.LIGHTING2.packettype = pTypeUndecoded;
            Cmd.LIGHTING2.packetlength = 7;
            Cmd.LIGHTING2.id1 = rssi >> 8;
            Cmd.LIGHTING2.id2 = rssi & 0x00ff ;
            Cmd.LIGHTING2.id3 = NbPulsePerSec >> 8;
            Cmd.LIGHTING2.id4 = NbPulsePerSec & 0x00ff;
            Serial.write((byte*)&Cmd.LIGHTING2, Cmd.LIGHTING2.packetlength + 1);
//            reportDomoticRfxCount(1,NbPulsePerSec);
        }
#ifndef RASPBERRY_PI
        pinMode(PDATA, INPUT);
#endif

        attachInterrupt(digitalPinToInterrupt(PDATA) , ext_int_1, CHANGE);
#ifdef RFM69_ENABLE
        radio.setMode(RF69_MODE_STANDBY);
        delay(10);
        radio.setMode(RF69_MODE_RX);
#endif
    }
    PulseLed(LOW);
        DomoticPacketReceived = false;
    
  }
}
void Loop ( word p) {
    ManagePulseReception ( p);
    //read serial input & fill receive buffe(
    ReadDomoticCmdFromSerial();
#ifdef RFM69_ENABLE
    //readKbdCmd();
#endif
    ManageDomoticCmdEmission();
}

void loop ( ) {
    word p = fifo.get();
    Loop(p);
}

#ifndef RASPBERRY_PI
int rssiGetAverage()
{
#ifdef RFM69_ENABLE
      return (radio.readRSSI());
#else
        return 0;
#endif
}
#endif
void printRSSI()
{
    static long int LastPrintRSSI ;
//print RSSI
//if ((millis() - LastPrintRSSI ) > 5000 ) 
{
#ifdef RFM69_ENABLE
      Serial.print(" rssi:");  
      Serial.print(rssiGetAverage());  
#endif
      LastPrintRSSI = millis() ;
}
}

void reportTemperatureToDomotic()
{
#ifdef RFM69_ENABLE
      // -1 = user cal factor, adjust for correct ambient
      byte temperature =  radio.readTemperature(-1); 

        if (isReportSerial()){
           Serial.print  ("T:");
           Serial.println(temperature,DEC);
        }
        else
        reportDomoticTemp ( "RFM69",temperature , 0x45  , 0 ,15 );
#endif
}
