#ifdef BMP180_ENABLE
#include <Wire.h>
#include <BMP180advanced.h>

/*
BMP180advanced(resolution)

resolution:
BMP180_ULTRALOWPOWER - pressure oversampled 1 time  & power consumption 3uA
BMP180_STANDARD      - pressure oversampled 2 times & power consumption 5uA
BMP180_HIGHRES       - pressure oversampled 4 times & power consumption 7uA
BMP180_ULTRAHIGHRES  - pressure oversampled 8 times & power consumption 12uA, library default
*/
BMP180advanced myBMP(BMP180_ULTRAHIGHRES);

float coefPressureSeaLevel;

bool status;

void bmp180_init()
{
#ifdef ESP8266
        status = myBMP.begin(D2,D3); //sda, scl
#else
        status = myBMP.begin();
#endif
        //compute coeficien niveau de la mer     pressureSeaLevel =  (pressure / pow(1.0 - (float)trueAltitude / 44330, 5.255));
        // coefPressureSeaLevel = 0,991730   1/coefPressureSeaLevel = 1.008338963225878
        float trueAltitude = 40.0;
        coefPressureSeaLevel =  pow(1.0 - (float)trueAltitude / 44330, 5.255) ;

        if (isReportSerial()){
            if (status != true)
            {
                DbgSerial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
            }
            else
            {
                DbgSerial.println(F("Bosch BMP180/BMP085 sensor is OK ")); //(F()) saves string to flash & keeps dynamic memory free
                DbgSerial.print(" coefPressureSeaLevel ");
                DbgSerial.println(coefPressureSeaLevel,6 );
            }
        }
}

void bmp180_read()
{
    if (status == true)
    {
	    float temp = myBMP.getTemperature()*10;
	    uint32_t pressureInPa = myBMP.getPressure();
	    reportDomoticTempBaro   ("BMP180", 1,    temp, pressureInPa / 100, pressureInPa / coefPressureSeaLevel/100 , 50.0, 1);
    //	reportDomoticTempHumBaro("BMP180", 1, 1, temp, pressureInPa / 100, pressureInPa / coefPressureSeaLevel/100 , 1, 0, 0xff, 0xFF);
    }
    else
    {
        bmp180_init();
    }
	
}

#endif
