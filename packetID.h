//
//  packetID.h
//  
//

#ifndef _packetID_h
#define _packetID_h

// A1900 IDs
unsigned const short A1900_PACKET          = 0x1900;
unsigned const short A1900_PACKET_VERSION  = 0x1001;

unsigned const short A1900_FP_PPAC0_PACKET = 0x1910;
unsigned const short A1900_FP_PPAC1_PACKET = 0x1911;
unsigned const short A1900_FP_PIN_PACKET   = 0x1920;
unsigned const short A1900_XF_PIN_B_PACKET = 0x1921;
unsigned const short A1900_XF_PIN_D_PACKET = 0x1922;
unsigned const short A1900_XF_PIN_F_PACKET = 0x1923;
unsigned const short A1900_FP_SCI_PACKET   = 0x1930;
unsigned const short A1900_XF_SCI_PACKET   = 0x1931;
unsigned const short A1900_FP_IC_PACKET    = 0x1940;
unsigned const short A1900_FP_STACK_PACKET = 0x1950;
unsigned const short A1900_I2_SCI_PACKET   = 0x1960;
unsigned const short A1900_TOF_RF_PACKET   = 0x1990;
unsigned const short A1900_TOF_I2_PACKET   = 0x1991;
unsigned const short A1900_TOF_DL_PACKET   = 0x1992;

unsigned const short A1900_I2_PPAC0_SAMPLE_PACKET   = 0x1970;
unsigned const short A1900_I2_PPAC0_STRIP_PACKET    = 0x1971;
unsigned const short A1900_I2_PPAC0_POS_PACKET      = 0x1972;
unsigned const short A1900_I2_PPAC0_XSAMPLE_PACKET  = 0x1973;
unsigned const short A1900_I2_PPAC1_SAMPLE_PACKET   = 0x1980;
unsigned const short A1900_I2_PPAC1_STRIP_PACKET    = 0x1981;
unsigned const short A1900_I2_PPAC1_POS_PACKET      = 0x1982;
unsigned const short A1900_I2_PPAC1_XSAMPLE_PACKET  = 0x1983;
unsigned const short A1900_FP_GE_PACKET             = 0x19a0;

unsigned const short test    = 0x8;

// Other IDs
unsigned const short HIRA_PACKET   = 0x3100;
unsigned const short S800_PACKET   = 0x5800;
unsigned const short FOURPI_PACKET = 0x4000;
unsigned const short VMEADC_PACKET = 0xabcd;
unsigned const short SISADC_PACKET = 0xabce;
unsigned const short XLM80_PACKET  = 0xabcf;
unsigned const short CLAS_PACKET   = 0x3200;

#define VMEADC      0xADC0
#define VMETDC      0xADC1
#define VMEIGQDC    0xADC3
#define VMEQDC      0xADC2
#define TOWER_0     0xA001
#define TOWER_1     0xA002
#define TOWER_2     0xA003
#define TOWER_3     0xA004
#define TOWER_4     0xA005
#define TOWER_5     0xA006
#define MCP_PACK    0x3CB0
#define CSI_PACK    0xC510
#define DE_PACK     0xC1A5

#endif
