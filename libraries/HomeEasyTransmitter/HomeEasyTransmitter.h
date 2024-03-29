
#ifndef HomeEasyTransmitter_h
#define HomeEasyTransmitter_h

class HomeEasyTransmitter
{

  public:
    //Constructor.
    //arg1 = pin to connected to 434Mhz transmitter
    HomeEasyTransmitter(byte dataPin, byte pclkPin , byte pLed );
    
    HomeEasyTransmitter(byte dataPin,  byte pLed );

    //arg1 = true to turn switch on, false for off
    //arg2 = the 26 bit long transmitter ID as found by the Pete and Banarby's recevier code
    //arg3 = the 4 bit recipient code, seems to be on a dial for mains switches, 1010 (6 in decimal) for my light fittings
    void setSwitch(bool,unsigned long, short);
    //init pin in output
    void initPin();
//  private:
    byte txPin;  // 433mhz transmitter on pin2
    byte clkPin;  // 433mhz transmitter on pin2
    byte  ledPin;

    void transmit(bool, unsigned long, short);
		void transmit(bool blnOn,unsigned long transmitterId, short recipient, byte level );
    void sendBit(bool);
    void sendPair(bool);
    void rfm69_set_data(byte state);
    void rfm69_set_data_without_clk(byte state);
    void rfm69_set_data_with_clk(byte state);
		void deactivatePin();

    void SetTransmitBuffer(word* buffer,bool blnOn,unsigned long transmitterId, short recipient);
    void SetSendBit(word* buffer, bool b);
    void SetSendPair(word* buffer, bool b);
    void transmitRaw(word * pulses  );
    void transmitRawBuffer(word * pulses, byte nbTransmit);
};

#endif


