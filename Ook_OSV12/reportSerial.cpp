#include <stdio.h>
#include <Arduino.h>
#include  "reportSerial.h"
#include "Config.h"

void printRSSI();

#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega2560__)


static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void registerStdout() {
  fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &uartout ;
}
long getTimeInSec()
{
    return millis()/1000;
}
#else
void registerStdout() {};
#include<time.h>

long getTimeInSec()
{
//    clock_t start;
//    start = clock();
//    return start ;
    time_t begin = time( NULL );
  return begin;
}
#endif

static T_REPORTTYPE ReportType =  REPORT_DOMOTIC ;

void setReportType(T_REPORTTYPE pReportType )
{
    ReportType = pReportType ;
}

T_REPORTTYPE getReportType()
{
    return ReportType;
}
bool isReportSerial()
{
    return ReportType >= REPORT_SERIAL ;
}
static inline bool isReportDebugSerial()
{
    return ReportType >= SERIAL_DEBUG ;
}
bool isReportDomotic()
{
    return ( (ReportType & REPORT_DOMOTIC ) == REPORT_DOMOTIC ) ;
}


char DectoHex(byte v)
{
    if (v<=9)
        return (v+'0');
    else
        return (v+'A'-10);
}

void printBinary ( byte * data , byte pos, byte space  )
{
    register byte bl = 0;
	for (byte i = 0; i < pos; ++i)
	{
		byte bt = data[i];
		for (byte b = 0; b < 8; b++)
		{
            if ( (bl++%space) == 0 )DbgSerial.print(' ');
			if (bt & 0x80)
				DbgSerial.print('1');
			else
				DbgSerial.print('0');
			bt = bt << 1;
			//if (b == 3) DbgSerial.print(' ');
			//if (b == 7) DbgSerial.print(' ');
		}
	}
}

//sump hex
void printHexaByte ( byte data )
{

    DbgSerial.print(DectoHex( data >> 4   ));
    DbgSerial.print(DectoHex( data  & 0x0F));
}

void printHexa ( byte * data, byte pos)
{

for (byte i = 0; i < pos; ++i) {
	DbgSerial.print(DectoHex( data[i] >> 4 ));
	DbgSerial.print(DectoHex(data[i] & 0x0F));
}
}

void printTab(byte tab, byte n)
{
	tab = tab - n;
	while (tab>0 ) {
		DbgSerial.print(' ');
		tab--;
	}

}

extern word 	NbPulsePerSec ;;

void reportPrintHeader()
{
    unsigned int secs =getTimeInSec();
    byte sec = secs % 60 ;
    secs /= 60 ;
    byte min = secs % 60 ;
    secs /= 60 ;
    byte heure = secs % 24 ;
    secs /= 24 ;
    secs %= 31 ;

    DbgSerial.print(' ');
    DbgSerial.print(secs);
    DbgSerial.print(':');
    DbgSerial.print(heure);
    DbgSerial.print(':');
    DbgSerial.print(min);
    DbgSerial.print(':');
    DbgSerial.print(sec);

    DbgSerial.print(" Np:");
    byte nb = DbgSerial.print(NbPulsePerSec);
    printTab(6, nb);
    DbgSerial.print(' ');
}
void reportPrint(const char * mes)
{
     if (isReportSerial()) DbgSerial.print(mes); 
}
void reportSerial(const char* Name, byte id1, byte id2, byte bateryLevel, int temp, byte hum, word power, unsigned long totalpower, word pressure, word PressureSeaLevel, word Rain ,  byte* data, byte pos,word counter  ) {

    extern byte dumpPulse;
    if (dumpPulse) DbgSerial.println();

    printTab(TAB,DbgSerial.print(Name)) ;
    reportPrintHeader();

    DbgSerial.print(" Id1:");
    DbgSerial.print(id1, HEX);
    DbgSerial.print(" Id2:");
    DbgSerial.print(id2,HEX);
    DbgSerial.print(" Bat:");
    DbgSerial.print(bateryLevel);

    if (temp != INVALID_TEMP)
    {
        DbgSerial.print(" T:");
        DbgSerial.print(temp/10);
        DbgSerial.print(".");
        DbgSerial.print(temp%10);
    }

    if (hum != INVALID_HUM)
    {
        DbgSerial.print(" Hum:");
        DbgSerial.print(hum);
        DbgSerial.print('%');
    }
    if (pressure != INVALID_PRESSURE)
    {
        DbgSerial.print(" Baro:");
        DbgSerial.print(pressure);
    }
    if (PressureSeaLevel != INVALID_PRESSURE)
    {
        DbgSerial.print(" BaroSea:");
        DbgSerial.print(PressureSeaLevel);
    }
    if (power != INVALID_POWER)
    {
        DbgSerial.print(" Power:");
        DbgSerial.print(power);
        DbgSerial.print(" Total Power:");
        DbgSerial.print(totalpower);
    }
    if (Rain != INVALID_RAIN)
    {
        DbgSerial.print(" Rain:");
        DbgSerial.print(Rain);
    }
    if (counter != INVALID_BYTE )
    {
        DbgSerial.print(" Counter:");
        DbgSerial.print(counter);
    }

    printRSSI();
//     DbgSerial.print(" RSSI:");DbgSerial.print(radio.readRSSI());

    if (getReportType() >= SERIAL_DEBUG) {
        if (data) {
            DbgSerial.print(' ');
//            printBinary(data, pos, 8);
            printHexa(data, pos );
            DbgSerial.print(',');
        }
    }
    DbgSerial.println();
}

