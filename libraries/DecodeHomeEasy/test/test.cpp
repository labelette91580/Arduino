#if _MSC_VER 

#include "VSPDE.h"
#endif


#include "fifo.h"
TFifo fifo;

#include "DecodeHomeEasy.h"

DecodeHomeEasy orscV2(1);



#define PORT 2

#define ledPin  13

volatile word pulse;

long int 	LastReceive ;
int 		NbReceive;
word 		Dt;
long int 	NbPulse  ;

int HexDec1digit(char  hexV)
{
  if ((hexV >= '0') && (hexV <= '9')) return (hexV - '0');
  if ((hexV >= 'A') && (hexV <= 'F')) return (hexV - 'A' + 10);
  return 0;
}

int HexDec(char * hexv, int nbdigit)
{

  int res = 0;
  for (int i = 0; i < nbdigit; i++)
  {
    res *= 16;
    res += HexDec1digit(*hexv++);
  }
  return res;
}

void setup () {

/*	fifo.Clear();
	fifo.Put(10,(byte*)"toto");
	fifo.Put(10,(byte*)"toto1");
	fifo.Put(10,(byte*)"toto2");
	while (!fifo.Empty())
	{
  			char message[100];
        byte len;

				//rc->getOokCode(message);
        strncpy((char*) message,(const char*)fifo.Get(len),90 ) ;
				printf("%s",message);
	}
	
*/	
  char * pt = "3A8B0001000000000055";

//unit code     data[3] 
  int UnitCode = HexDec(&pt[3 * 2], 2);

  //switch value     data[4] 
  int OnOff = HexDec(&pt[4 * 2], 2);
  //group value     data[5] 
  int Group = HexDec(&pt[5 * 2], 2);

  // ID data[6..9]
  int CodeId = HexDec(&pt[6 * 2], 8);

	
	  LastReceive = 0 ;
	  NbReceive   = 0;
    
    Serial.begin(38400);
//    Serial.println("\n[ookDecoder]");
    
   // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);       
    
    pulse=0;
}

#define    BIT_0  300 , 300 ,
#define    BIT_1  300 , 1300 ,
#define    BITS   300 , 2300 ,

#define    BIT0  300 , 300  , 300 , 1300 ,
#define    BIT1  300 , 1300 ,300 , 300 ,


int result[] = {
	0,
0x55555555,
0x1551,
0,
0,
0,
0,
0,
0,
};

int ConfZ1[]  =  {  BITS BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 
                         BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 
                         BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 
                         BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 
                    BITS
0,
    };

 int ConfZ2[]  = {
 284  ,
10010,
277  ,
2721 ,
278  ,
278  ,
278  ,
1271 ,
279  ,
279  ,
278  ,
1255 ,
280  ,
279  ,
278  ,
1264 ,
278  ,
321  ,
278  ,
1262 ,
280  ,
279  ,
278  ,
1261 ,
279  ,
279  ,
278  ,
1332 ,
279  ,
277  ,
277  ,
1265 ,
279  ,
282  ,
283  ,
1298 ,
290  ,
277  ,
277  ,
1266 ,
279  ,
294  ,
277  ,
1264 ,
279  ,
286  ,
277  ,
1261 ,
279  ,
278  ,
281  ,
1296 ,
280  ,
279  ,
278  ,
1278 ,
279  ,
277  ,
301  ,
1291 ,
279  ,
276  ,
277  ,
1272 ,
279  ,
276  ,
340  ,
1262 ,
279  ,
280  ,
279  ,
1264 ,
279  ,
278  ,
295  ,
1264 ,
279  ,
278  ,
287  ,
1272 ,
278  ,
1261 ,
279  ,
301  ,
286  ,
277  ,
277  ,
1291 ,
280  ,
1269 ,
279  ,
333  ,
278  ,
278  ,
286  ,
1269 ,
279  ,
1261 ,
279  ,
280  ,
277  ,
278  ,
277  ,
1264 ,
294  ,
1262 ,
280  ,
278  ,
284  ,
313  ,
279  ,
1280 ,
279  ,
1264 ,
279  ,
278  ,
326  ,
277  ,
276  ,
1279 ,
279  ,
278  ,
277  ,
1263 ,
285  ,
278  ,
277  ,
1277 ,
279  ,
1274 ,
279  ,
278  ,
272  ,
12942,
0
 };
 int ConfZ3[]  = {
	 50000,
	 10000,
	 100,
	 2800,
	 100,
	 300,
	 300,
	 1300,
	 99,
	 400,
	 200,
	 1400,
	 99,
	 400,
	 100,
	 1500,
	 99,
	 500,
	 100,
	 1200,
	 200,
	 400,
	 99,
	 1400,
	 100,
	 400,
	 200,
	 1400,
	 99,
	 400,
	 99,
	 1600,
	 99,
	 300,
	 200,
	 1300,
	 100,
	 400,
	 99,
	 1500,
	 99,
	 400,
	 200,
	 1300,
	 200,
	 500,
	 99,
	 1400,
	 99,
	 400,
	 200,
	 1300,
	 100,
	 500,
	 99,
	 1400,
	 200,
	 200,
	 200,
	 1500,
	 100,
	 200,
	 200,
	 1500,
	 99,
	 400,
	 300,
	 1300,
	 99,
	 600,
	 99,
	 1300,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1400,
	 300,
	 1200,
	 100,
	 500,
	 400,
	 200,
	 1300,
	 100,
	 1400,
	 99,
	 400,
	 200,
	 300,
	 300,
	 1300,
	 99,
	 1300,
	 200,
	 300,
	 200,
	 400,
	 100,
	 1400,
	 100,
	 1400,
	 100,
	 300,
	 200,
	 300,
	 100,
	 1400,
	 99,
	 1300,
	 200,
	 400,
	 100,
	 400,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 1300,
	 100,
	 400,
	 200,
	 1300,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 12700,
	 200,
	 9900,
	 100,
	 2700,
	 200,
	 400,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 1300,
	 200,
	 300,
	 300,
	 1200,
	 100,
	 400,
	 200,
	 1400,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 400,
	 100,
	 1400,
	 200,
	 200,
	 300,
	 1200,
	 200,
	 300,
	 300,
	 1200,
	 100,
	 400,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 1400,
	 200,
	 200,
	 200,
	 1400,
	 100,
	 300,
	 100,
	 1300,
	 100,
	 400,
	 200,
	 1200,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 400,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 1400,
	 200,
	 300,
	 200,
	 1400,
	 99,
	 500,
	 100,
	 1300,
	 200,
	 1300,
	 100,
	 500,
	 100,
	 300,
	 200,
	 1300,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 1400,
	 100,
	 400,
	 200,
	 300,
	 100,
	 1400,
	 99,
	 1300,
	 200,
	 300,
	 200,
	 300,
	 100,
	 1300,
	 200,
	 1400,
	 100,
	 400,
	 200,
	 300,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 99,
	 99,
	 1300,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 1300,
	 100,
	 400,
	 100,
	 12800,
	 100,
	 10100,
	 100,
	 2900,
	 100,
	 400,
	 100,
	 1300,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1400,
	 300,
	 300,
	 100,
	 1400,
	 200,
	 300,
	 200,
	 1300,
	 200,
	 300,
	 200,
	 1300,
	 100,
	 400,
	 200,
	 1300,
	 100,
	 500,
	 100,
	 1300,
	 200,
	 400,
	 100,
	 1400,
	 200,
	 200,
	 200,
	 1400,
	 200,
	 300,
	 200,
	 1300,
	 100,
	 400,
	 200,
	 1300,
	 100,
	 300,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 400,
	 100,
	 1400,
	 100,
	 400,
	 200,
	 1300,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 300,
	 100,
	 1400,
	 200,
	 200,
	 300,
	 1300,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 500,
	 100,
	 1200,
	 200,
	 1300,
	 200,
	 400,
	 100,
	 300,
	 200,
	 1400,
	 100,
	 1300,
	 100,
	 400,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 1400,
	 100,
	 400,
	 200,
	 300,
	 100,
	 1400,
	 99,
	 1300,
	 200,
	 300,
	 200,
	 300,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 1300,
	 200,
	 300,
	 200,
	 1400,
	 100,
	 1300,
	 200,
	 400,
	 100,
	 12800,
	 100,
	 10100,
	 100,
	 2800,
	 100,
	 500,
	 1400,
	 200,
	 300,
	 100,
	 1400,
	 100,
	 300,
	 200,
	 1300,
	 200,
	 300,
	 200,
	 1300,
	 100,
	 400,
	 200,
	 1200,
	 100,
	 500,
	 100,
	 1300,
	 200,
	 500,
	 100,
	 1300,
	 300,
	 300,
	 100,
	 1400,
	 100,
	 300,
	 200,
	 1300,
	 100,
	 400,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1300,
	 100,
	 500,
	 100,
	 1300,
	 200,
	 300,
	 100,
	 1400,
	 100,
	 400,
	 200,
	 1200,
	 200,
	 300,
	 100,
	 1400,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 500,
	 99,
	 1300,
	 100,
	 400,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 1300,
	 100,
	 1300,
	 200,
	 300,
	 200,
	 200,
	 200,
	 1300,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 400,
	 300,
	 1200,
	 200,
	 1300,
	 200,
	 300,
	 100,
	 300,
	 200,
	 1300,
	 200,
	 1300,
	 100,
	 400,
	 200,
	 300,
	 200,
	 1400,
	 99,
	 1400,
	 100,
	 400,
	 200,
	 300,
	 100,
	 1400,
	 99,
	 400,
	 200,
	 1200,
	 200,
	 400,
	 100,
	 1300,
	 200,
	 1400,
	 100,
	 400,
	 100,
	 30600,
	 600,
	 700,
	 200,
	 1100,
	 700,
	 1100,
	 800,
	 1100,
	 300,
	 600,
	 800,
	 500,
	 400,
	 1100,
	 100,
	 700,
	 700,
	 1200,
	 700,
	 600,
	 200,
	 1200,
	 200,
	 700,
	 700,
	 700,
	 200,
	 1200,
	 700,
	 1100,
	 800,
	 1100,
	 700,
	 1100,
	 600,
	 1300,
	 200,
	 600,
	 700,
	 1200,
	 700,
	 1100,
	 800,
	 600,
	 200,
	 1200,
	 200,
	 600,
	 800,
	 700,
	 100,
	 1200,
	 700,
	 1100,
	 300,
	 600,
	 800,
	 1100,
	 700,
	 600,
	 200,
	 1100,
	 800,
	 1100,
	 700,
	 1100,
	 800,
	 1100,
	 800,
	 1000,
	 700,
	 1100,
	 700,
	 1200,
	 700,
	 1100,
	 800,
	 1100,
	 700,
	 1100,
	 700,
	 1100,
	 300,
	 600,
	 700,
	 600,
	 300,
	 1200,
	 300,
	 500,
	 700,
	 600,
	 400,
	 1000,
	 700,
	 1100,
	 800,
	 1100,
	 800,
	 1100,
	 800,
	 1100,
	 200,
	 600,
	 700,
	 1100,
	 700,
	 1100,
	 700,
	 600,
	 300,
	 1100,
	 200,
	 800,
	 600,
	 1000,
	 800,
	 600,
	 400,
	 1000,
	 700,
	 1100,
	 200,
	 700,
	 700,
	 1100,
	 800,
	 1100,
	 800,
	 600,
	 400,
	 1100,
	 100,
	 700,
	 800,
	 1200,
	 700,
	 600,
	 200,
	 1200,
	 200,
	 600,
	 800,
	 54000,
	 800,
	 1100,
	 700,
	 1100,
	 700,
	 1100,
	 800,
	 1100,
	 700,
	 1100,
	 700,
	 1100,
	 700,
	 1200,
	 700,
	 1200,
	 500,
	 1300,
	 500,
	 1200,
	 700,
	 1200,

000, 	
 	
 	
 	};
 int Z2Eco []  = {0};
 int Z2Conf[]  = {0};
 int Z3Eco []  = {0};
 int Z3Conf[]  = {0};


/*
0704FA00	02208B4E	03827D00	011045A7
0704FA00	02208851	03827D00	01104428
			
0704FA00	02209346	03827D00	011049A3
0704FA00	02209049	03827D00	01104824
			
0704FA00	0220A336	03827D00	0110519B
0704FA00	0220A039	03827D00	0110501C
			
0704FA00	0220CC0D	03827D00	01106606
0704FA00	0220D405	03827D00	01106A02
			
0704FA00	020501F3	03827D00	010280F9
0704FA00	020502F2	03827D00	01028179
0704FA00	020504F0	03827D00	01028278

*/

int i=0;
int j=1;
int * conf = ConfZ1;
byte data = 0;
void setPulse()
{

if ( conf[i]!=0)  
{
  pulse = conf[i++]  ;
  if (data==0) data=1;else data=0;
}
else 
{
  orscV2.resetDecoder();		
  data = 0;
  i=0;
  j++;
       if (j==1)
    conf = ConfZ1;
  else if (j==2)
    conf = ConfZ2;
  else if (j==3)
    conf = ConfZ3;
  else if (j==4)
    conf=Z2Eco ;    
  else if (j==5)
    conf=Z2Conf;    
  else if (j==6)
    conf=Z3Eco ;    
  else if (j==7)
    conf=Z3Conf;    
    
}
}

char * state [] = {
"UN",
"T0", 
"T1", 
"T2", 
"T3", 
"OK", 
"DO" };

void printState()
{
  Serial.print("NbPulse ");
  Serial.print(NbPulse,10);

  Serial.print(" state ");
  Serial.print(state[orscV2.state]); 

  Serial.print(" data:");
  Serial.print(data,10);

  Serial.print(" Bits ");
  Serial.print(orscV2.total_bits,10);

  Serial.print(" code:");
  Serial.print(orscV2.CurCode,HEX);

  Serial.print(" p:");
  Serial.print(conf[i-1],10);

  Serial.println();
    

}
void loop () {
    setPulse();
    word p = pulse;
    pulse = 0;
      
    if (p != 0) {
        NbPulse++;
        if (orscV2.nextPulse(p,data))
        {
					for (int i = 0; i < orscV2.getBytes(); i++)
						printf("%02X ", orscV2.getData()[i]);

					  printf (" Home: %08x \n",orscV2.Code);
						Serial.println();
						if (result[	j]== orscV2.Code )
							Serial.println(" OK");
						else
						Serial.println(" KO");

						NbReceive ++ ;
            NbPulse=0 ;
           orscV2.resetDecoder();		
                
        }
        printState();    
    }

}



int Main(int, char**);


int main(int, char**)
{
    
    Main(0,0);

}