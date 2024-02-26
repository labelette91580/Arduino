#pragma once

#define VERSION 16


#define BYTE byte

typedef union tRBUF {
//domotic structure
	struct T_TEMP {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	temperatureh : 7;
		byte	tempsign : 1;
		byte	temperaturel;
		byte	battery_level : 4;
		byte	rssi : 4;
	} Temp;
	struct T_TEMP_HUM{
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	temperatureh : 7;
		byte	tempsign : 1;
		byte	temperaturel;
		byte	humidity; 
		byte	humidity_status;
		byte	battery_level : 4;
		byte	rssi : 4;
	} Temp_Hum;
struct  T_LIGHTING2{
		byte	packetlength;   /* == 11 : longueur a partir de packettype */
		byte	packettype;     /* 17    */
		byte	subtype;
		byte	seqnbr;
		byte	id1;            /* id emetteur 0..3  */
		byte	id2;            /* id emetteur 0..FF */
		byte	id3;            /* id emetteur 0..FF */
		byte	id4;            /* id emetteur 0..FF */
		byte	unitcode;       /* unit 0.0xF        */
		byte	cmnd;           /* 0 : off 1:On      */
		byte	level;          /* dim level 0..15   */
		byte	rssi ;
//		byte	data[2] ;
		
	} LIGHTING2;

struct {
		byte	packetlength; // = 13
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	cmnd;
		byte	msg1;
		byte	msg2;
		byte	msg3;
		byte	msg4;
		byte	msg5;
		byte	msg6;
		byte	msg7;
		byte	msg8;
		byte	msg9;
	} ICMND;


struct {	//response on a mode command from the application
		BYTE	packetlength;
		BYTE	packettype;
		BYTE	subtype;
		BYTE	seqnbr;
		BYTE	cmnd;
		BYTE	msg1;	//receiver/transceiver type
		BYTE	msg2;	//firmware version

#ifdef IS_BIG_ENDIAN
		//BYTE	msg3;
		BYTE	UNDECODEDenabled : 1;
		BYTE	IMAGINTRONIXenabled : 1;
		BYTE	SXenabled : 1;
		BYTE	RSLenabled : 1;
		BYTE	LIGHTING4enabled : 1;
		BYTE	FINEOFFSETenabled : 1;
		BYTE	RUBICSONenabled : 1;
		BYTE	AEenabled : 1;

		//BYTE	msg4;
		BYTE	BLINDST1enabled : 1;
		BYTE	BLINDST0enabled : 1;
		BYTE	MSG4Reserved5 : 1;
		BYTE	LEGRANDenabled : 1;
		BYTE	LACROSSEenabled : 1;
		BYTE	HIDEKIenabled : 1;
		BYTE	LWRFenabled : 1;
		BYTE	MERTIKenabled : 1;

		//BYTE	msg5;
		BYTE	VISONICenabled : 1;
		BYTE	ATIenabled : 1;
		BYTE	OREGONenabled : 1;
		BYTE	MEIANTECHenabled : 1;
		BYTE	HEEUenabled : 1;
		BYTE	ACenabled : 1;
		BYTE	ARCenabled : 1;
		BYTE	X10enabled : 1; //note: keep this order

		//BYTE    msg6;
        BYTE    MSG6Reserved7 : 1;
        BYTE    MSG6Reserved6 : 1;
        BYTE    MSG6Reserved5 : 1;
        BYTE    MSG6Reserved4 : 1;
        BYTE    MSG6Reserved3 : 1;
        BYTE    MSG6Reserved2 : 1;
		BYTE    HCEnabled : 1;
        BYTE    KEELOQenabled : 1;
#else
		//BYTE	msg3;
		BYTE	AEenabled : 1;
		BYTE	RUBICSONenabled : 1;
		BYTE	FINEOFFSETenabled : 1;
		BYTE	LIGHTING4enabled : 1;
		BYTE	RSLenabled : 1;
		BYTE	SXenabled : 1;
		BYTE	IMAGINTRONIXenabled : 1;
		BYTE	UNDECODEDenabled : 1;

		//BYTE	msg4;
		BYTE	MERTIKenabled : 1;
		BYTE	LWRFenabled : 1;
		BYTE	HIDEKIenabled : 1;
		BYTE	LACROSSEenabled : 1;
		BYTE	LEGRANDenabled : 1;
		BYTE	MSG4Reserved5 : 1;
		BYTE	BLINDST0enabled : 1;
		BYTE	BLINDST1enabled : 1;

		//BYTE	msg5;
		BYTE	X10enabled : 1; //note: keep this order
		BYTE	ARCenabled : 1;
		BYTE	ACenabled : 1;
		BYTE	HEEUenabled : 1;
		BYTE	MEIANTECHenabled : 1;
		BYTE	OREGONenabled : 1;
		BYTE	ATIenabled : 1;
		BYTE	VISONICenabled : 1;

        //BYTE	msg6;
        BYTE    KEELOQenabled : 1;
		BYTE    HCEnabled : 1;
        BYTE    DDenabled : 1;
        BYTE    MSG6Reserved3 : 1;
        BYTE    MSG6Reserved4 : 1;
        BYTE    MSG6Reserved5 : 1;
        BYTE    MSG6Reserved6 : 1;
        BYTE    MSG6Reserved7 : 1;
#endif

		BYTE	msg7;	//major version
		BYTE	msg8;	//minor version
		BYTE	msg9;	//RF power
		BYTE	msg10;	//FW type
        BYTE	msg11;	//noise level
        BYTE	msg12;
        BYTE	msg13;
        BYTE	msg14;
        BYTE	msg15;
        BYTE	msg16;
	} IRESPONSE;


struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	msg[17];
	} UNDECODED;
struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	count;
		byte	ch1h;
		byte	ch1l;
		byte	ch2h;
		byte	ch2l;
		byte	ch3h;
		byte	ch3l;
		byte	rssi : 4;
		byte	battery_level : 4;
	} CURRENT;
struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	count;
		byte	instant1;
		byte	instant2;
		byte	instant3;
		byte	instant4;
		byte	total1;
		byte	total2;
		byte	total3;
		byte	total4;
		byte	total5;
		byte	total6;
		byte	battery_level : 4;
		byte	rssi : 4;
	} ENERGY;
struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	count;
		byte	ch1h;
		byte	ch1l;
		byte	ch2h;
		byte	ch2l;
		byte	ch3h;
		byte	ch3l;
		byte	total1;
		byte	total2;
		byte	total3;
		byte	total4;
		byte	total5;
		byte	total6;
		byte	rssi : 4;
		byte	battery_level : 4;
	} CURRENT_ENERGY;
struct 
{
	uint8_t len;
	uint8_t type;
	uint8_t subtype;
	uint8_t id1;
	float   temp;
	float   baro;
	float   altitude;
	uint8_t forecast;

} _tTempBaro;
struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
#ifdef IS_BIG_ENDIAN
		byte	tempsign : 1;
		byte	temperatureh : 7;
#else
		byte	temperatureh : 7;
		byte	tempsign : 1;
#endif
		byte	temperaturel;
		byte	humidity;
		byte	humidity_status;
		byte	baroh;
		byte	barol;
		byte	forecast;
#ifdef IS_BIG_ENDIAN
		byte	rssi : 4;
		byte	battery_level : 4;
#else
		byte	battery_level : 4;
		byte	rssi : 4;
#endif
	} TEMP_HUM_BARO;
struct {
		byte	packetlength;
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	id1;
		byte	id2;
		byte	rainrateh;
		byte	rainratel;
		byte	raintotal1;
		byte	raintotal2;
		byte	raintotal3;
#ifdef IS_BIG_ENDIAN
		BYTE	rssi : 4;
		BYTE	battery_level : 4;
#else
		byte	battery_level : 4;
		byte	rssi : 4;
#endif
	} RAIN;
byte Buffer[1] ; //for reception by char

struct {
		BYTE	packetlength;
		BYTE	packettype;
		BYTE	subtype;
		BYTE	seqnbr;
		BYTE	id1;
		BYTE	id2;
		BYTE	count1;
		BYTE	count2;
		BYTE	count3;
		BYTE	count4;
#ifdef IS_BIG_ENDIAN
		BYTE	rssi : 4;
		BYTE	filler : 4;
#else
		BYTE	filler : 4;
		BYTE	rssi : 4;
#endif
	} RFXMETER;

// 	struct {
// 		BYTE	packetlength;
// 		BYTE	packettype;
// 		BYTE	subtype;
// 		BYTE	seqnbr;
// 		BYTE	id1;
// 		BYTE	id2;
// 		BYTE	id3;
// 		BYTE	id4;
// 		BYTE	counter1_0;
// 		BYTE	counter1_1;
// 		BYTE	counter1_2;
// 		BYTE	counter1_3;
// 		BYTE	counter2_0;
// 		BYTE	counter2_1;
// 		BYTE	counter2_2;
// 		BYTE	counter2_3;
// 		BYTE	state;
// #ifdef IS_BIG_ENDIAN
// 		BYTE	rssi : 4;
// 		BYTE	battery_level : 4;
// #else
// 		BYTE	battery_level : 4;
// 		BYTE	rssi : 4;
// #endif
// 	} CEENCODER;

}_tRBUF;	

typedef union tRecBUF {
//domotic structure
struct  T_LIGHTING2{
		byte	packetlength;   /* == 11 : longueur a partir de packettype */
		byte	packettype;     /* 17    */
		byte	subtype;
		byte	seqnbr;
		byte	id1;            /* id emetteur 0..3  */
		byte	id2;            /* id emetteur 0..FF */
		byte	id3;            /* id emetteur 0..FF */
		byte	id4;            /* id emetteur 0..FF */
		byte	unitcode;       /* unit 0.0xF        */
		byte	cmnd;           /* 0 : off 1:On      */
		byte	level;          /* dim level 0..15   */
		byte	rssi ;
//		byte	data[2] ;
		
	} LIGHTING2;
struct {	//response on a mode command from the application
		BYTE	packetlength;
		BYTE	packettype;
		BYTE	subtype;
		BYTE	seqnbr;
		BYTE	cmnd;
		BYTE	msg1;	//receiver/transceiver type
		BYTE	msg2;	//firmware version

#ifdef IS_BIG_ENDIAN
		//BYTE	msg3;
		BYTE	UNDECODEDenabled : 1;
		BYTE	IMAGINTRONIXenabled : 1;
		BYTE	SXenabled : 1;
		BYTE	RSLenabled : 1;
		BYTE	LIGHTING4enabled : 1;
		BYTE	FINEOFFSETenabled : 1;
		BYTE	RUBICSONenabled : 1;
		BYTE	AEenabled : 1;

		//BYTE	msg4;
		BYTE	BLINDST1enabled : 1;
		BYTE	BLINDST0enabled : 1;
		BYTE	MSG4Reserved5 : 1;
		BYTE	LEGRANDenabled : 1;
		BYTE	LACROSSEenabled : 1;
		BYTE	HIDEKIenabled : 1;
		BYTE	LWRFenabled : 1;
		BYTE	MERTIKenabled : 1;

		//BYTE	msg5;
		BYTE	VISONICenabled : 1;
		BYTE	ATIenabled : 1;
		BYTE	OREGONenabled : 1;
		BYTE	MEIANTECHenabled : 1;
		BYTE	HEEUenabled : 1;
		BYTE	ACenabled : 1;
		BYTE	ARCenabled : 1;
		BYTE	X10enabled : 1; //note: keep this order

		//BYTE    msg6;
        BYTE    MSG6Reserved7 : 1;
        BYTE    MSG6Reserved6 : 1;
        BYTE    MSG6Reserved5 : 1;
        BYTE    MSG6Reserved4 : 1;
        BYTE    MSG6Reserved3 : 1;
        BYTE    MSG6Reserved2 : 1;
		BYTE    HCEnabled : 1;
        BYTE    KEELOQenabled : 1;
#else
		//BYTE	msg3;
		BYTE	AEenabled : 1;
		BYTE	RUBICSONenabled : 1;
		BYTE	FINEOFFSETenabled : 1;
		BYTE	LIGHTING4enabled : 1;
		BYTE	RSLenabled : 1;
		BYTE	SXenabled : 1;
		BYTE	IMAGINTRONIXenabled : 1;
		BYTE	UNDECODEDenabled : 1;

		//BYTE	msg4;
		BYTE	MERTIKenabled : 1;
		BYTE	LWRFenabled : 1;
		BYTE	HIDEKIenabled : 1;
		BYTE	LACROSSEenabled : 1;
		BYTE	LEGRANDenabled : 1;
		BYTE	MSG4Reserved5 : 1;
		BYTE	BLINDST0enabled : 1;
		BYTE	BLINDST1enabled : 1;

		//BYTE	msg5;
		BYTE	X10enabled : 1; //note: keep this order
		BYTE	ARCenabled : 1;
		BYTE	ACenabled : 1;
		BYTE	HEEUenabled : 1;
		BYTE	MEIANTECHenabled : 1;
		BYTE	OREGONenabled : 1;
		BYTE	ATIenabled : 1;
		BYTE	VISONICenabled : 1;

        //BYTE	msg6;
        BYTE    KEELOQenabled : 1;
		BYTE    HCEnabled : 1;
        BYTE    DDenabled : 1;
        BYTE    MSG6Reserved3 : 1;
        BYTE    MSG6Reserved4 : 1;
        BYTE    MSG6Reserved5 : 1;
        BYTE    MSG6Reserved6 : 1;
        BYTE    MSG6Reserved7 : 1;
#endif

		BYTE	msg7;	//major version
		BYTE	msg8;	//minor version
		BYTE	msg9;	//RF power
		BYTE	msg10;	//FW type
        BYTE	msg11;	//noise level
        BYTE	msg12;
        BYTE	msg13;
        BYTE	msg14;
        BYTE	msg15;
        BYTE	msg16;
	} IRESPONSE;

struct {
		byte	packetlength; // = 13
		byte	packettype;
		byte	subtype;
		byte	seqnbr;
		byte	cmnd;
		byte	msg1;
		byte	msg2;
		byte	msg3;
		byte	msg4;
		byte	msg5;
		byte	msg6;
		byte	msg7;
		byte	msg8;
		byte	msg9;
	} ICMND;
byte Buffer[1] ; //for reception by char
word Word  [1] ; //for reception by char

	struct  {
	BYTE	packetlength;
	BYTE	packettype;
	BYTE	subtype;
	BYTE	seqnbr;
	BYTE	repeat;
//	struct{
//		BYTE	uint_msb;
//		BYTE	uint_lsb;
//	} pulse[124];
	byte pulse[124*2];
    } RAW;

}_tRecBUF;	



#define pTypeTEMP_BARO 0xF7
#define sTypeBMP085 0x01

//types for Interface Control
#define pTypeInterfaceControl 0x00
#define sTypeInterfaceCommand 0x00
#define cmdRESET	0x00 // reset the receiver/transceiver
#define cmdSTATUS	0x02 // return firmware versions and configuration of the interface
#define cmdSETMODE	0x03 // set configuration of the interface

#define cmdSAVE		0x06 // save receiving modes of the receiver/transceiver in non-volatile memory
#define cmdStartRec	0x07 // start RFXtrx receiver

#define pTypeInterfaceMessage 0x01
#define sTypeInterfaceResponse 0x00

#define trxType43392 0x53

#define FWtyperec 0x0
#define FWtype1 0x1
#define FWtype2 0x2
#define FWtypeExt 0x3
#define FWtypeExt2 0x4
#define FWtypePro1 0x5
#define FWtypePro2 0x6
#define FWtypeProXL1 0x10
#define FWtypeProXL2 0x13
#define FWtypeRFX433 0x14 //RFM69 433 firmware
#define FWtypeRFX868 0x15 //RFM69 868 firmware
#define FWtypeProXL95 0x16 //RFM95 firmware
#define FWtypeRFX433XXL 0x17 //RFU
#define FWtypeRFX310 0x18 //RFXusb with 310MHz receiver module


#define pTypeLighting2 0x11
#define sTypeAC 0x0
#define sTypeHEU 0x1
#define sTypeANSLUT 0x2
#define sTypeKambrook 0x03

#define pTypeUndecoded 0x03


//types for current
#define pTypeCURRENT 0x59
#define sTypeELEC1 0x1   //CM113,Electrisave

//types for energy
#define pTypeENERGY 0x5A
#define sTypeELEC2 0x1   //CM119/160
#define sTypeELEC3 0x2   //CM180

//types for current-energy
#define pTypeCURRENTENERGY 0x5B
#define sTypeELEC4 0x1   //CM180i

//types for power
#define pTypePOWER 0x5C
#define sTypeELEC5 0x1   //revolt

//types for temperature+humidity
#define pTypeTEMP_HUM 0x52
#define sTypeTH1_OREGON 0x1  //THGN122/123,THGN132,THGR122/228/238/268
#define sTypeTH2 0x2  //THGR810,THGN800
#define sTypeTH3 0x3  //RTGR328
#define sTypeTH4 0x4  //THGR328
#define sTypeTH5 0x5  //WTGR800
#define sTypeTH6 0x6  //THGR918,THGRN228,THGN500
#define sTypeTH7 0x7  //TFA TS34C, Cresta
#define sTypeTH8 0x8  //WT450H
#define sTypeTH9 0x9  //Viking 02035,02038 (02035 has no humidity), TSS320
#define sTypeTH10_RUBiCSON 0xA   //Rubicson
#define sTypeTH11_TFA 0xB   //EW109
#define sTypeTH12 0xC   //Imagintronix
#define sTypeTH13 0xD   //Alecto WS1700 and compatibles
#define sTypeTH14 0xE   //Alecto

//types for temperature
#define pTypeTEMP 0x50
#define sTypeTEMP1 0x1  //THR128/138,THC138, Davis
#define sTypeTEMP2 0x2  //THC238/268,THN132,THWR288,THRN122,THN122,AW129/131
#define sTypeTEMP3 0x3  //THWR800
#define sTypeTEMP4 0x4	//RTHN318
#define sTypeTEMP5 0x5  //LaCrosse TX3
#define sTypeTEMP6 0x6  //TS15C
#define sTypeTEMP7 0x7  //Viking 02811,TSS330
#define sTypeTEMP8 0x8  //LaCrosse WS2300
#define sTypeTEMP9 0x9  //RUBiCSON
#define sTypeTEMP10_TFA 0xA  //TFA 30.3133
#define sTypeTEMP11 0xB  //WT0122

#define pTypeTEMP_HUM_BARO 0x54
#define sTypeTHB1 0x1   //BTHR918,BTHGN129
#define sTypeTHB2 0x2   //BTHR918N,BTHR968
#define sTypeTHBFloat 0x10	    // Weather Station

#define HOMESWITCH_ID0 0x3B
#define HOMESWITCH_ID1 0x80

//types for rain
#define pTypeRAIN 0x55
#define sTypeRAIN9 0x9   //TFA 30.3233.01 

//RFXMeter
#define pTypeRFXMeter 0x71
#define sTypeRFXMeterCount 0x0
#define sTypeRFXMeterInterval 0x1
#define sTypeRFXMeterCalib 0x2
#define sTypeRFXMeterAddr 0x3
#define sTypeRFXMeterCounterReset 0x4
#define sTypeRFXMeterCounterSet 0xB
#define sTypeRFXMeterSetInterval 0xC
#define sTypeRFXMeterSetCalib 0xD
#define sTypeRFXMeterSetAddr 0xE
#define sTypeRFXMeterIdent 0xF

//types for CARTELECTRONIC
#define pTypeCARTELECTRONIC 0x60
#define sTypeTIC 0x1
#define sTypeCEencoder 0x2
#define sTypeLinky 0x3

//RAW transit/receive
#define pTypeRAW 0x7F
#define sTypeRAW1 0x0
#define sTypeRAW2 0x1
#define sTypeRAW3 0x2
#define sTypeRAW4 0x3

extern  tRecBUF Cmd ;
extern bool DomoticPacketReceived;

bool DomoticReceptionInProgress();

extern void ReadDomoticCmdFromSerial();
extern unsigned long getLightingId ();
extern void  DomoticInit();
extern void reportDomoticTemp ( const char* Name,int temp , byte id1 , byte id2 , byte bateryLevel,  byte* data=0, byte pos = 0);
extern void reportDomoticTempHum ( const char* Name, int temp , byte hum , byte id1 , byte id2, byte bateryLevel, byte subType,  byte* data=0, byte pos = 0);
void reportDomoticPower(const char* Name,byte* data, int size);
extern void DomoticStartReceive();
extern void DomoticStatus();
void reportHagerDomotic ( const byte* data, byte pos );
void reportDomoticHomeEasy(byte id1, byte id2, byte id3, byte id4, byte group, byte cmd, byte unitcode,  byte* data, byte pos);
void resetLastSensorValue();
void reportDomoticTempBaro(const char* Name, byte id1, float temp, float baro, float PressureSeaLevel, float altitude, uint8_t forecast,  byte* data=0, byte pos = 0);
void reportDomoticTempHumBaro(const char* Name, byte id1, byte unit, float temperature, float pressure, float PressureSeaLevel, uint8_t forecast, byte humidity, byte BatteryLevel, byte RssiLevel,  byte* data=0, byte pos = 0);
void reportDomoticMD230(const byte* data, byte pos);
void reportDomoticRfxCount(byte id, word value);


