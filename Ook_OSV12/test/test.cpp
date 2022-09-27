//--------------------------------------------------------------------
// Arduino Console Stub
//--------------------------------------------------------------------

#if _MSC_VER 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <string>

#include <vector>
#include "VSPDE.h"

 typedef std::vector<int> TPulses ;

/// PulseString = "541 1890 541  " or "541;1890;541 "
 // lit les valeur de pulse a partir chaine 
 void readPulse( char* PulseString ,  TPulses* Pulse  )
{
  int nb=0;

  std::string list[1000];
  Split ( PulseString  , " ;" , "" , true , list ) ;
  while (list[nb]!="")
  {
    int pulse = atoi (list[nb].c_str())  ;
    Pulse->push_back ( pulse );
    nb++;
  }
}

 void convertdPulse( TPulses* Pulse , float coefA = 1 , float coefB=0  )
{
  int nb=0;

  for (unsigned int i = 0 ; i<Pulse->size() ;i++ )
  {
    int pulse =(*Pulse)[i] * coefA + coefB ;
    (*Pulse)[i] =  ( pulse );
  }
}

//--------------------------------------------------------------------
// Main
//--------------------------------------------------------------------
 
char * RubicsonPulse  = "541 1890 541 3780 541 1890 541 3780 541 3780 541 3780 541 3780 541 3780 541 1890 541 1890 541 3780 541 4050 541 3780 541 1890 541 1890 541 1890 541 1890 541 1890 541 1890 541 1890 541 3780 541 3780 541 1890 541 1890 541 4050 541 3780 541 1890 541 4050 541 1890 541 1890 541 4050 541 1890 541 3780 541 1890 541 3780 541 3780 541 9180";

TPulses TfaPulse= {
0  ,
0  ,
1  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
1  ,
1  ,
1  ,
1  ,
1  ,
0  ,
0  ,
0  ,
0  ,
1  ,
1  ,
1  ,
1  ,
1  ,
0  ,
0  ,
1  ,
0  ,
0  ,
1  ,
1  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
1  ,
1  ,
1  ,
1  ,
0  ,
0  ,
1  ,
1  ,
1  ,
1  ,
1  ,
0  ,
0  ,
1  ,
1  ,
1  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
0  ,
1  ,
1  ,
0  ,
0  ,
1  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,
0  ,
1  ,
0  ,
0  ,
0  ,


0xFFFF
};

TPulses TfaPulse2= {

2000,441,2040,421,3980,421,3960,419,9998,460,481,520,461,560,421,540,
421,560,401,580,441,520,441,520,481,540,421,520,441,1040,921,1040,
941,1000,461,520,441,520,939,1040,941,520,441,520,421,600,421,1040,
421,520,441,520,941,580,381,1060,459,520,441,520,941,1040,901,1058,
441,520,441,518,461,540,901,580,421,1038,441,500,461,500,961,1020,
439,520,941,520,461,560,421,1040,441,520,941,1020,441,520,441,520,
501,518,901,1060,441,520,941,1020,441,520,441,520,439,580,881,578,
441,520,441,520,421,600,421,520,441,520,461,560,421,540,421,580,
381,580,441,1020,941,980,941,                                             //BADCHK T0145E3FFFFFFF5
1020,441,580,439,520,941,1020,881,600,
421,540,421,520,441,1020,501,520,439,520,941,520,441,1040,421,520,
499,520,881,1060,921,1020,441,540,459,520,441,520,941,540,421,1040,
461,540,439,520,941,1040,441,520,939,520,441,538,401,1040,481,540,
901,1000,499,520,421,540,421,580,881,1040,441,540,921,1020,441,580,
441,520,441,520,941,520,421,600,421,540,421,580,381,580,441,520,
441,540,401,580,441,520,441,520,461,1000,941,1040,921,1040,441,520,
441,540,921,1018,941,540,421,580,441,520,441,1020,441,520,461,560,
881,580,441,1020,441,520,441,520,941,1020,941,1040,421,540,421,580,
441,520,941,520,441,1020,461,500,441,580,881,1040,481,520,921,560,
421,540,421,1040,421,580,901,1020,441,540,461,520,441,520,941,1040,
421,540,921,                                                                 //TFA        169 Np:816     Id1:E3 Id2:2 Bat:15 T:19.6 Hum:57%-62 0145E314313909

};

/* pulse in 100micros unit 
short : 2000..2200 micros
long  : 4000..4200 micros
end   :8700..8800    
*/
char* OtioPulse = 
"   42 21 20 41 21 41 21 41 21 21 20 42 21 41 41 20 21 41 21 20 42 21 21 40 "
"87 41 21 20 42 20 42 20 42 21 21 20 42 20 42 41 21 20 42 20 21 41 21 20 40 "
"87 41 20 21 43 20 41 21 43 20 21 21 42 20 42 41 22 20 41 21 21 41 21 21 40 "
"87 41 21 20 41 19 42 20 42 20 22 20 42 19 42 41 21 19 42 20 21 41 22 20 39 "
"88 41 20 21 42 20 41 20 42 21 20 21 42 20 41 42 21 20 58 21 20 42 20 21 40 "
"87 41 20 21 41 20 41 22 41 20 21 21 41 21 41 42 20 20 41 22 20 42 21 21 40 "
"87 42 20 21 41 21 41 21 40 21 20 21 41 22 41 42 20 21 41 21 19 42 20 21 39 "
"87 42 20 21 41 21 41 21 41 21 20 21 41 21 40 42 21 21 41 21 20 42 20 21 40 "
"87 41 20 21 41 21 41 22 41 21 21 21 41 21 41 42 20 21 41 22 20 42 21 21 40 "
"87 42 20 21 41 21 41 21 40 21 20 21 41 22 41 42 20 21 41 21 19 42 20 21 39 "
"87 42 20 21 41 21 41 42 41 22 20 21 41 21 41 41 19 22 41 21 21 43 20 21 40 "
"87 42 20 21 41 21 40 21 41 21 20 22 41 21 41 42 20 21 40 21 20 42 20 22 40 "
"87 42 21 21 41 21 41 21 41 21 21 22 40 21 41 43 20 21 41 21 20 42 21 21 39 "
"87 42 20 21 41 22 41 21 41 22 20 21 41 21 41 41 19 22 41 21 21 43 20 21 40 "
"87 42 20 21 41 21 40 21 41 21 19 22 41 21 41 42 20 21 40 21 20 41 20 20 40 "
"87 42 21 21 41 21 41 21 41 21 21 21 40 21 41 43 20 21 41 21 20 42 21 21 56 "
"87 41 20 21 41 20 41 21 41 20 20 21 42 20 42 42 21 20 41 21 20 41 20 21 39 "
"87 40 21 20 41 21 42 20 41 20 21 20 41 21 42 41 20 21 42 20 20 40 21 20 40 "
"87 42 20 20 42 21 41 20 42 21 20 20 42 20 41 41 21 21 41 20 21 42 20 20 41 "
"87 41 20 21 43 20 41 21 42 20 20 21 43 20 42 41 21 20 41 21 21 41 20 21 40 "
"87 40 21 20 41 20 42 20 41 20 21 20 41                                     "
;


//OSV2 6 Np:1349   1A2D405E302350463E9C[THGR228N] Id:5E Ch:3 T:23.3 233 65% bat:15
char* OregonTempPulse = 

//"1551 28 26 332 32 21 217 25 21 34 29 22 20 24 34 134        "
//"29 65 27 87 95 51 27 317 21 667 24 20 26 102 62 44          "
//"40 29 38 37 174 22 64 1564 25 32 27 20 34 56 29 28          "
//"34 36 37 31 41 26 31 24 32 38 31 42 26 31 23 23             "
//"53 36 31 110 20 65 73 23 52 97 456 23 183 30 24 63          "
//"20 45 59 27 28 24 67 71 59 68 756 37 864 22 80 26           "
//"21 26 369 24 62 36 44 38 24 23 41 40 23 31 52 162           "
//"33 22 32 280 24 427 72 29 27 58 56 25 75 82 84 74           "
//"43 32 25 671 34 670 25 22 344 26 32 28 24 93 23 27          "
//"20 46 61 36 49 42 162 64 39 32 24 572 23 24 22 30           "
//"89 24 86 24 26 30 66 34 47 171 46 57 60 1210 38 32          "
//"26 20 29 20 21 20 22 27 22 24 379 48 42 36 20 37            "
//"28 100 34 46 139 62 59 29 653 28 33 47 32 34 50 36          "
//"38 35 60 96 32 38 33 1323 29 37 72 22 32 45 20 28           "
//"30 35 26 30 27 32 32 21 32 302 38 105 90 20 292 22          "
//"596 34 30 199 119 67 160 31 46 832 28 26 23 147 24 148      "
//"557 26 27 26 26 168 49 188 26 108 21 23 317 61 20 61        "
//"76 28 23 691 24 172 58 194 29 29 32 496 26 48 227 27        "
//"27 24 30 27 46 173 21 24 35 163 32 33 578 135 22 335        "
//"54 33 33 20 38 22 26 838 21 61 20 367 116 78 37 73          "
//"175 72 1070 38 63 35 22 37 21 451 25 35 34 30 23 28         "
//"34 46 28 32 48 34 38 22 32 59 26 40 29 162 37 20            "
//"53 27 368 21 290 83 74 27 39 55 50 60 64 1122 32 220        "
//"61 36 22 396 26 24 33 25 28 32 34 29 60 22 31 27            "
//"28 52 35 88 21 28 78 30 36 32 75 24 1204 27 31 54           "
//"88 48 38 43 20 40 116 34 21 34 55 185 420 21 986 42         "
//"26 26 70 23 104 40 35 28 20 34 20 133 38 61 50 31           "
"39 81 128 30 41 34 26 497 114 81 111 83 112 83 111 84       "
"109 86 108 87 107 88 106 88 106 89 106 88 106 89 106 89     "
"105 90 105 89 105 89 105 41 56 90 56 41 104 41 56 90        "
"55 41 104 91 104 42 55 91 103 91 104 91 54 42 103 43        "
"54 92 54 43 102 92 102 44 53 93 52 44 101 44 52 94          "
"100 94 100 96 99 96 98 97 97 98 96 100 94 101 45 52         "
"92 55 42 104 90 104 42 55 91 103 92 101 93 101 94 52        "
"45 100 46 51 94 52 46 100 95 99 95 99 96 99 96 99           "
"47 50 96 99 95 50 47 99 96 98 47 50 96 99 96 50             "
"47 98 97 98 96 98 47 50 96 50 47 98 96 98 96 98             "
"97 98 96 98 96 98 48 50 96 49 48 98 48 49 96 50             "
"47 98 96 98 48 49 96 98 96 50 48 98 96 98 96 98             "
"48 49 96 49 48 98 97 98 48 49 96 98 96 98 96 98             "
"96 98 97 49 47 98 96 98 96 98 96 98 48 49 96 98             "
"96 98 96 49 48 98 96 98 48 49 96                            " 
;


//OSV2 16 Np:552    3A80018201000000801F00[CMR180,...] Id:3A80 ,power:386 ,total:-2147483648 ,total kWh:-596
char* OregonPowerPulse = 
"23 34 158 21 232 29 33 256 20 37 92 138 22 21 133 21             "
"29 20 294 24 24 20 383 26 24 39 38 22 24 30 52 23                "
"117 96 111 97 110 98 108 99 108 100 108 100 107 100 107 100      "
"107 101 106 101 106 101 106 101 106 102 106 102 106 102 105 50   "
"54 101 54 49 105 50 54 102 54 49 105 102 105 102 105 50          "
"53 102 105 102 105 102 105 102 105 102 104 103 104 103 103 104   "
"103 105 51 53 101 107 100 55 48 107 99 109 98 110 96 112         "
"95 112 95 113 95 111 97 110 45 58 97 58 46 109 98 109            "
"98 109 99 108 100 107 48 57 98 109 98 57 47 107 100 107          "
"100 107 100 107 100 107 100 107 100 107 100 107 100 108 99 108   "
"100 107 101 106 101 107 100 107 101 108 100 107 100 107 100 107  "
"100 108 100 106 101 107 100 107 100 107 101 107 100 107 100 106  "
"101 107 100 108 100 107 100 106 101 106 101 106 101 107 100 107  "
"101 107 100 107 100 107 100 107 48 56 100 108 100 108 99 108     "
"100 108 100 108 100 56 48 107 101 107 100 107 100 108 100 107    "
"100 107 100 107 101 107 100 107 100 107 100 107                  "
;


// OTIO 29 921C89 T:28.9 Id:92 Bat:15
char * OtioPulse2 = "\
941 1004 485 476 993 484 477 984 481 488 993 484 461 1008 485 480 993 468 477 1000                                                                                                                                                    \
8216 361 2048 397 2028 413 2040 393 4224 425 2016 425 2004 437 4068 453                                                                                                                                                               \
7948 469 3932 473 1980 477 1968 469 3916 473 1968 473 1972 465 3928 481 1956 481 1964 477 1964 473 1976 481 3900 489 4160 485 3900 493 1944 493 1948 489 4156 493 1948 489 1948 489 1964 493 4136 497 1940 497 1960 493 4004 497      \
7904 513 3912 513 1924 505 1936 509 3896 505 1936 501 1940 497 3888 505 1948 505 1936 501 1944 497 1940 493 3908 501 4128 501 3900 501 1940 501 1940 497 4148 497 1948 493 1940 497 1944 489 4152 497 1944 493 1948 493 4020 497      \
7904 513 3908 513 1932 497 1940 501 3888 505 1940 493 1960 497 4132 497 1944 493 1960 493 1948 489 1952 485 3900 493 4152 493 3888 501 1956 497 1944 497 4132 497 1960 493 1944 493 1948 493 4152 493 1944 497 1940 497 4004 497 7908 \
";


char * RubicsonPulse2 = "\
 593 2377 1424 553 3836 561 3836 573 1872 557 3832 573 3820 573 3816 573 \
 1872 577 1868 569 1880 557 1872 565 1880 561 3844 549 1892 557 1876 581 \
 1860 565 1884 557 3832 561 3840 565 3824 569 1876 569 1880 545 1884 565 \
 3836 569 3820 569 1880 565 3824 569 3832 565 1868 565 9156 633 1864 557 \
 3832 577 1872 553 3836 569 1876 553 1892 553 3836 569 3824 565 3824 569 \
 3836 553 1880 565 3840 565 3828 565 3820 569 1880 565 1880 561 1884 545 \
 1900 545 1884 561 3844 545 1900 545 1884 557 1888 557 1888 557 3832 561 \
 3844 545 3844 561 1884 561 1884 545 1884 561 3844 545 3844 565 1884 557 \
 3832 561 3828 561 1884 561 9148 625 1868 573 3836 553 1876 565 3844 545 \
 1884 561 1884 561 3828 561 3844 565 3828 561 3828 565 1884 557 3832 561 \
 3844 545 3848 561 1884 545 1884 557 1892 553 1892 553 1892 553 3836 553 \
 1892 553 1892 537 1908 533 1896 549 3856 537 3852 553 3836 557 1892 553 \
 1892 549 1896 533 3856 553 3836 553 1896 549 3840 549 3840 553 1896 549 \
 9156 613 1884 557 3848 545 1888 553 3856 533 1896 549 1896 545 3848 541 \
 3864 529 3860 549 3844 545 1904 537 3852 541 3852 537 3868 525 1908 533 \
 1912 533 1916 525 1920 509 1924 517 3888 521 1924 501 1932 513 1936 505 \
 1940 505 3884 505 3900 493 3896 513 1936 489 1944 501 1944 497 3892 501 \
 3904 489 1944 501 3900 493 3900 509 1940 485 9212 581 1920 505 3884 521 \
 1932 493 3896 513 1936 489 1944 501 3904 489 3900 509 3880 509 3884 509 \
 1940 505 3884 509 3896 493 3896 497 1940 505 1940 501 1944 501 1948 497 \
 1948 481 3904 505 1944 485 1944 501 1944 501 1944 501 3888 505 3900 493 \
 3896 513 1936 489 1944 501 1944 501 3884 509 3896 497 1936 509 3896 497 \
 3896 509 1940 489 9212 581 1916 505 3888 521 1928 497 3896 509 1924 505 \
 1940 505 3900 493 3896 497 3896 509 3880 513 1936 509 3880 513 3880 509 \
 3880 513 1936 509 1940 505 1940 505 1940 489 1944 501 3900 493 1940 505 \
 1940 505 1940 501 1944 489 3900 509 3880 509 3880 513 1940 505 1940 505 \
 1940 505 3884 509 3880 513 1936 505 3884 509 3880 513 1936 509 9196 577 \
 1924 517 3872 517 1932 509 3880 513 1936 509 1940 505 3884 509 3880 513 \
 3880 509 3896 501 1932 509 3896 497 3896 497 3892 517 1936 489 1940 505 \
 1940 505 1944 501 1944 485 3900 509 1940 505 1944 485 1944 501 1944 501 \
 3884 509 3900 493 3896 513 1936 489 1944 501 1944 501 3884 513 3896 493 \
 1940 505 3884 509 3896 497 1936 509 9084 461 j176 257 B312 257 277 2096 \
 341 325 413 349 456 349 401 201 1392 269 281 269 417 1513 677 1677      \
";


//home easy bit value : pulse High pulse low
#define    BIT_0  301 , 300 ,
#define    BIT_1  301 , 1300 ,
#define    BITS   301 , 2300 ,

#define    BIT0  301 , 300  , 301 , 1300 ,
#define    BIT1  301 , 1300 , 301 , 300  ,

// value 0x55555555
TPulses HomeEasyPulse55555555= {
    BITS    BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1    BITS
    BITS    BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1    BITS
    BITS    BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1    BITS
    BITS    BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1    BITS
    BITS    BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1    BITS

};
TPulses HomeEasyPulseAAAAAAAA= {
    BITS    BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0    BITS
    BITS    BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0    BITS
    BITS    BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0    BITS
    BITS    BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0    BITS
    BITS    BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1  BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0 BIT1 BIT0    BITS

};

char * HomeEasyPulse = "\
357 9998  393 9828  405 2612  397 172                                     \
 393 1248 389 180 385 1256 381 188 381 1260 373 192 377 1264 373 196      \
 373 1268 369 196 369 1272 365 200 369 1272 365 204 361 1276 361 204      \
 365 1276 361 204 361 1276 361 208 361 1276 357 208 361 1276 357 212      \
 357 1276 361 208 357 1280 357 208 357 1280 357 208 357 1280 353 212      \
 357 1276 357 212 357 1276 357 212 353 1280 353 1272 357 216 353 216      \
 353 1276 357 1272 353 220 353 216 349 1280 353 1276 349 220 353 216      \
 349 1280 353 1276 349 220 349 216 353 1276 349 1280 349 220 349 220      \
 349 1280 349 216 349 1284 349 216 349 1280 349 1280 345 220 349 9998     \
  385 9836  393 2624  385 184 381 1260 377 192 373 1268 369 200 365 1276  \
 365 204 361 1276 361 208 361 1280 357 208 357 1284 353 216 349 1288      \
 349 220 349 1288 349 220 345 1292 345 224 341 1296 341 228 337 1296      \
 341 228 337 1300 333 236 333 1304 329 240 325 1308 329 240 325 1312      \
 321 248 317 1316 321 248 317 1320 313 256 309 1324 309 260 305 1332      \
 297 1328 301 276 293 276 289 1344 289 1336 289 288 281 288 277 1352      \
 281 1348 281 292 277 296 269 1356 277 1348 281 292 273 296 269 1356      \
 273 1356 273 300 269 300 269 1356 277 292 273 1348 285 288 277 1348      \
 285 1340 289 280 285 9998  349 9872  361 2656  353 216 345 1300 337 232  \
 333 1308 325 248 317 1324 313 256 309 1332 309 260 305 1336 301 268      \
 297 1340 297 276 293 1344 293 276 293 1340 297 272 297 1340 297 272      \
 293 1340 297 272 297 1340 297 272 293 1340 297 272 297 1336 301 268      \
 297 1336 301 272 293 1336 301 268 297 1336 301 268 297 1336 301 268      \
 297 1336 297 272 297 1332 301 1328 297 276 297 272 297 1332 301 1324     \
 301 272 301 268 297 1332 301 1328 297 272 301 268 297 1332 301 1328      \
 297 272 301 268 297 1328 301 1328 297 276 293 276 293 1328 305 268       \
 297 1332 297 272 297 1328 301 1324 305 264 301 9998  873 9998  385 76    \
 145 84 253 120 309 72 197 3796  241 92 349 88 373 76 97 52               \
";


//pwm

//pwm  bit value : pulse High pulse low
#define    PWMSYNHRO 751 , 750 ,
#define    B0 251 , 500 ,
#define    B1  501 , 250 ,

#define P0 B0 B0 B0 B0 
#define P1 B0 B0 B0 B1 
#define P2 B0 B0 B1 B0 
#define P3 B0 B0 B1 B1 
#define P4 B0 B1 B0 B0 
#define P5 B0 B1 B0 B1 
#define P6 B0 B1 B1 B0 
#define P7 B0 B1 B1 B1 
#define P8 B1 B0 B0 B0
#define P9 B1 B0 B0 B1
#define PA B1 B0 B1 B0
#define PB B1 B0 B1 B1
#define PC B1 B1 B0 B0
#define PD B1 B1 B0 B1
#define PE B1 B1 B1 B0
#define PF B1 B1 B1 B1


TPulses PwmPulsec240aaff09550021c= {
    PWMSYNHRO PWMSYNHRO  PC P2 P4 P0 PA PA PF PF P0 P9 P5 P5 P0 P0 P2 P1 PC 
};

// count = FFF6 = -10 = 0 il faut ajouter 10 --> 0 
// FFF6 = 0
// FFF7 = 1
// FFF8 = 2
// FFF9 = 3
// FFFA = 4
// FFFB = 5
// FFFC = 6
// FFFD = 7
// FFFE = 8
// FFFF = 9
// 0000 = 10


TPulses PwmPulsec3DBF5500F6AAFFDE3 = {
    PWMSYNHRO PWMSYNHRO  P3 PD PB PF P5 P5 P0 P0 PF P6 PA PA PF PF PD PE P3
};

TPulses RainPulsec1 = {

513,220,265,472,261,472,261,472,261,476,257,476,497,240,493,244,1672,
729,744,717,756,221,512,221,512,461,284,445,296,429,320,560,417,324,409,324,556,425,308,425,304,433,300,540,536,201,532,201,532,201,528,209,524,209,524,453,280,209,520,461,272,461,272,461,272,217,516,221,512,221,512,221,508,225,512,225,508,225,508,225,504,473,264,469,264,469,264,469,264,229,504,473,260,473,260,229,504,473,260,229,504,473,260,229,504,477,256,237,496,477,256,233,500,477,256,477,260,477,252,477,256,477,256,481,256,477,256,477,256,233,500,477,256,233,496,237,500,237,496,237,496,237,496,481,252,481,1944,
729,740,725,744,233,496,237,496,481,252,485,248,485,252,237,496,481,252,481,252,237,496,481,252,481,252,481,252,241,492,241,492,237,496,237,496,241,492,241,492,241,492,485,252,237,492,485,252,481,252,481,256,233,496,241,496,237,492,241,492,241,492,241,492,241,492,245,488,485,252,481,252,481,252,481,252,237,496,481,252,481,256,237,492,481,252,241,496,481,252,237,496,481,252,237,496,481,252,237,496,481,256,477,256,481,252,481,252,481,252,481,252,481,252,481,252,237,496,481,252,241,492,241,492,241,492,237,500,233,500,477,256,481,1946,
725,744,725,740,237,492,241,492,485,248,485,248,485,248,241,492,485,252,481,252,237,496,481,252,481,252,481,252,237,496,241,492,241,492,241,492,241,492,241,496,237,496,481,252,237,496,481,252,485,248,485,252,237,492,241,496,237,492,241,492,241,492,241,496,237,496,241,492,481,252,481,252,481,252,481,252,245,492,481,252,481,252,237,496,481,252,237,496,481,252,241,492,481,252,241,492,485,248,241,492,481,256,481,252,481,252,481,252,481,252,481,252,481,252,481,252,237,496,481,252,237,496,241,496,237,496,237,496,237,496,481,252,481,1948,
729,740,725,744,233,496,241,492,485,248,485,252,481,248,241,492,481,252,469,264,241,492,485,252,481,252,481,252,237,496,237,496,237,496,241,492,241,492,241,496,237,496,481,252,237,496,481,252,485,248,485,248,241,492,241,492,241,492,241,492,241,492,241,492,241,492,241,492,485,252,481,252,481,252,481,252,237,496,481,256,477,252,237,496,485,252,237,496,481,252,237,496,481,252,237,496,481,252,237,496,485,248,485,248,481,252,481,252,481,256,477,256,481,252,481,252,237,496,481,256,233,496,237,496,237,500,237,492,241,496,481,252,481,1950,
725,740,729,744,233,488,245,492,485,248,481,252,485,248,241,492,485,252,481,252,237,496,481,252,481,252,485,252,237,496,237,492,241,496,237,496,237,496,237,496,237,496,485,244,245,488,485,252,481,252,481,252,237,496,241,492,241,496,237,496,237,496,237,496,237,496,237,496,481,252,481,256,477,256,481,252,237,496,481,248,485,248,241,496,481,252,237,496,481,252,237,496,481,252,237,496,481,252,237,496,485,248,481,252,481,256,481,252,481,252,481,252,481,252,481,252,237,496,481,256,233,496,241,496,237,496,237,496,237,496,481,252,481,2892,
9998,2084,1516,313,548,
3996,3100,217,316,2756,2160,7064,325,840,237,2760,261,936,209,705,1112,
};

TPulses RainPulsec = {
 241,2180,681,780,681,780,241,520,181,520,
461,300,441,260,439,320,181,520,241,520,441,260,501,260,201,520,
241,518,441,260,239,520,439,260,501,260,181,520,499,260,441,258,
501,258,441,300,459,260,441,300,221,520,181,520,241,520,179,520,
241,520,241,520,439,280,421,320,441,260,221,540,201,520,201,520,
461,280,181,580,179,520,241,518,441,260,241,520,441,260,241,520,
441,280,221,540,419,280,241,520,441,260,241,518,181,518,241,520,
181,520,241,520,181,520,241,520,201,500,261,500,461,260,241,520,
181,520,501,260,441,260,241,520,181,520,241,520,181,2220,
701,780,
701,760,181,520,181,520,441,320,441,280,421,320,201,520,201,520,
461,280,441,320,181,520,241,520,441,260,241,520,441,260,441,320,
201,520,481,280,421,280,461,300,441,260,461,300,441,260,241,520,
181,520,241,520,181,520,261,500,201,500,501,260,461,260,481,280,
181,520,241,520,181,520,501,260,181,520,241,520,181,580,441,260,
181,560,461,260,201,540,481,260,181,520,501,260,181,580,441,260,
241,520,181,520,241,520,181,540,201,540,201,520,201,560,181,520,
181,580,441,260,241,520,181,520,441,320,441,260,241,540,181,520,
221,540,181,2220,
701,760,701,760,201,500,261,520,441,260,481,280,
441,260,239,520,181,520,501,260,441,320,181,520,181,580,441,260,
201,540,461,258,461,280,221,520,441,260,501,260,441,260,501,260,
441,320,441,280,201,540,179,540,201,540,201,520,181,540,221,520,
441,320,441,260,441,320,181,520,241,520,201,500,441,320,201,520,
201,560,181,520,461,300,181,520,461,300,181,520,441,320,181,520,
501,260,201,500,501,260,201,540,221,520,181,520,241,520,181,520,
241,520,181,518,241,520,181,580,441,260,181,578,181,520,441,300,
481,240,201,540,221,520,181,580,179,2220,
701,738,721,780,181,520,
181,580,441,260,441,320,441,260,241,520,201,520,421,318,441,280,
241,500,199,520,461,300,181,520,461,300,441,258,241,518,441,260,
501,260,441,260,501,260,461,260,481,280,181,520,239,520,181,520,
241,520,181,520,241,520,441,260,501,258,441,300,221,500,201,540,
221,520,441,260,241,520,181,580,181,520,441,318,181,520,441,320,
201,520,421,318,201,520,421,300,219,520,461,300,181,520,241,520,
181,520,241,520,201,500,241,520,201,520,221,540,181,520,481,260,
199,520,241,520,441,260,461,300,181,520,241,520,179,520,261,2158,
681,780,721,740,241,520,181,518,501,260,441,300,459,260,201,540,
221,520,441,260,501,260,181,520,241,520,439,320,181,520,441,320,
439,260,221,540,441,280,461,260,461,278,441,320,441,258,441,320,
179,520,241,520,181,520,239,520,199,520,221,538,421,280,461,300,
421,280,239,520,179,520,241,520,441,260,241,518,181,520,241,520,
441,300,219,520,441,260,241,520,441,260,241,520,441,260,241,520,
441,260,241,520,181,580,181,520,221,520,221,500,201,540,221,520,
181,520,241,520,441,320,181,520,241,520,441,280,421,320,201,520,
201,540,201,520,201,9998,381,4180,261,1140,261,1058,141,201,2080,361,
};

#include "Fifo.h"
extern TFifo  fifo;

//duree = coefA * duree + float coefB 
void testOOK (TPulses* TestPulse, float coefA=1.0 , float coefB=0   )
{
    unsigned int PulseNb=0;

	setup();
	for(;;)
	{
		if (_kbhit())
		{
			Serial._append((char)_getch());
		}
		loop();
        if (PulseNb<TestPulse->size())
        {
            int pulse =(*TestPulse)[PulseNb] * coefA + coefB ;
            fifo.put(pulse);
            PulseNb++;
        }
        else
            break;
	}
}

void testOOK (char* TestString , float coefA=1.0 , float coefB=0   )
{
    TPulses Pulse ;

    readPulse(TestString,&Pulse);
    testOOK (&Pulse, coefA , coefB   );

}
void reportDomoticPower(char* Name, byte* data, int size ) ;

int main(int, char**)
{
//    testOOK (RubicsonPulse  ) ;
//    testOOK (RubicsonPulse2  ) ;

//    testOOK (&TfaPulse , 500 , 500 ) ;
    testOOK (&TfaPulse2 , 1 , 0 ) ;
    


//    testOOK (OtioPulse2 ,  1 , 0   ) ;
//    testOOK (OregonTempPulse ,  10 , 1   ) ;
//for (int i=0;i<10;i++)
//    testOOK (OregonPowerPulse ,  10 , 1   ) ;
    
    
//    testOOK (HomeEasyPulse   ) ;

//    testOOK (&HomeEasyPulse55555555 ,  1 , 0   ) ;
//    testOOK (&HomeEasyPulseAAAAAAAA ,  1 , 0   ) ;

//    testOOK (&PwmPulsec3DBF5500F6AAFFDE3 ,  1 , 0   ) ;
    
    testOOK (&RainPulsec ,  1 , 0   ) ;

byte data[10];
data[4]=1;
 data[3]=130;
for (int i=0;i<10;i++)
 reportDomoticPower( "power",data, 10 ) ;
    
    
}

#endif


 byte Header[] = {
21 ,	//0 : 1 / 208
22 ,	//1 : 0 / 212
0 };


