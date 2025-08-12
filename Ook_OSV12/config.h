//type de report serie 
//si = REPORT_TYPE  : report serial forma domoticz (binaire)
//si = REPORT_TYPE : report serial format text 
#define REPORT_TYPE  REPORT_DOMOTIC
//#define REPORT_TYPE REPORT_SERIAL 
//#define REPORT_TYPE SERIAL_DEBUG 

//def raspbery pi serial com
#define RaspPiSerial Serial

//def debug  serial com
#define DbgSerial Serial

#ifndef WIN32
#define RFM69_ENABLE
#define  BMP180_ENABLE        
//#define ENABLE_SERIAL_DEBUG 1
#endif 

//#define OTIO_ENABLE        1
  #define OOK_ENABLE         2
//#define HAGER_ENABLE       3
#define HOMEEASY_ENABLE    4
//#define MD230_ENABLE       5
  #define RUBICSON_ENABLE    6
  #define HIDEKI_ENABLE      7
  #define RAIN_ENABLE        8
#define PORTAIL_ENABLE 9

// #define RASPBERRY_PI

//offset in micros for pulse duration for RFM69 : 80Micros
#define OFFSET_DURATION_HIGH 0

#define DUMPPULSE 0
#define SENDRFXPING 0

#define ENABLE_RESET_CMD 1
#define HAVE_EEPROM 1

#define VERSION 17

