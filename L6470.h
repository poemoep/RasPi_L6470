#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>


#ifndef __L6470_HEADER
#define __L6470_HEADER

//----define debug message function ON/OFF----
#define L6470_PRINT_MESSAGE 

//----define const value----

#define DIR_RVS 0x00
#define DIR_FWD 0x01

#define DIR_CCW 0x00
#define DIR_CW 0x01

#define ACT_POS_CLEAR 0b00000000
#define ACT_POS_TO_MARK 0b00001000

//----define L6470 registers----

#define REG_ABS_POS     0x01
#define REG_EL_POS      0x02
#define REG_MARK        0x03
#define REG_SPEED       0x04 //readonly
#define REG_ACC         0x05
#define REG_DEC         0x06
#define REG_MAX_SPEED   0x07
#define REG_MIN_SPEED   0x08
#define REG_KVAL_HOLD   0x09
#define REG_KVAL_RUN    0x0A
#define REG_KVAL_ACC    0x0B
#define REG_KVAL_DEC    0x0C
#define REG_INT_SPEED   0x0D
#define REG_ST_SLP      0x0E
#define REG_FN_SLP_ACC  0x0F
#define REG_FN_SLP_DEC  0x10
#define REG_K_THERM     0x11
#define REG_ADC_OUT     0x12 //readonly
#define REG_OCD_TH      0x13
#define REG_STALL_TH    0x14
#define REG_FS_SPD      0x15
#define REG_STEP_MODE   0x16
#define REG_ALARM_EN    0x17
#define REG_CONFIG      0x18
#define REG_STATUS      0x19 //readonly
//#define REG_RESERVED_h1A    0x1A
//#define REG_RESERVED_h1B    0x1B

//----define L6470 registers for functions----
#define REG_NOP 0x00
#define REG_SETPARAM    0b00000000
#define REG_GETPARAM    0b00100000
#define REG_MoveCont    0b01010000
#define REG_MoveStepClock 0b01011000
#define REG_MoveStep    0b01000000
#define REG_MoveGoTo    0b01100000
#define REG_MoveGoToDir 0b01101000
#define REG_MoveGoToUntil 0b10000010
#define REG_MoveRelease 0b10010010
#define REG_GoHome      0b01110000
#define REG_GoMark      0b01111000
#define REG_ResetPos    0b11011000
#define REG_ResetDevice 0b11000000
#define REG_StopSoft    0b10110000
#define REG_StopHard    0b10111000
#define REG_HiZSoft     0b10100000
#define REG_HiZHard     0b10101000
#define REG_GetStatus   0b11010000



//#define REG_NUM  43

//const uint8_t REG_SIZE[REG_NUM];
extern uint8_t *REG_SIZE;

#define ADDR_SIZE                (8 )

#define REG_SIZE[REG_ABS_POS]    (22)
#define REG_SIZE[REG_EL_POS]     (9 )
#define REG_SIZE[REG_MARK]       (22)
#define REG_SIZE[REG_SPEED]      (20) //readonly
#define REG_SIZE[REG_ACC]        (12)
#define REG_SIZE[REG_DEC]        (12)
#define REG_SIZE[REG_MAX_SPEED]  (10)
#define REG_SIZE[REG_MIN_SPEED]  (13)
#define REG_SIZE[REG_KVAL_HOLD]  (8 )
#define REG_SIZE[REG_KVAL_RUN]   (8 )
#define REG_SIZE[REG_KVAL_ACC]   (8 )
#define REG_SIZE[REG_KVAL_DEC]   (8 )
#define REG_SIZE[REG_INT_SPEED]  (14)
#define REG_SIZE[REG_ST_SLP]     (8 )
#define REG_SIZE[REG_FN_SLP_ACC] (8 )
#define REG_SIZE[REG_FN_SLP_DEC] (8 )
#define REG_SIZE[REG_K_THERM]    (4 )
#define REG_SIZE[REG_ADC_OUT]    (5 ) //readonly
#define REG_SIZE[REG_OCD_TH]     (4 )
#define REG_SIZE[REG_STALL_TH]   (7 )
#define REG_SIZE[REG_FS_SPD]     (10)
#define REG_SIZE[REG_STEP_MODE]  (8 )
#define REG_SIZE[REG_ALARM_EN]   (8 )
#define REG_SIZE[REG_CONFIG]     (16)
#define REG_SIZE[REG_STATUS]     (16) //readonly

#define REG_SIZE[REG_NOP]        (1 ) // test
#define REG_SIZE[REG_SETPARAM]   (24)
#define REG_SIZE[REG_GETPARAM]   (24)
#define REG_SIZE[REG_MoveCont]   (24)
#define REG_SIZE[REG_MoveStepClock]   (0 )
#define REG_SIZE[REG_MoveStep]    (24)  
#define REG_SIZE[REG_MoveGoTo]    (24)
#define REG_SIZE[REG_MoveGoToDir] (24)
#define REG_SIZE[REG_MoveGoToUntil] (24)
#define REG_SIZE[REG_MoveRelease] (0 )
#define REG_SIZE[REG_GoHome]      (0 )
#define REG_SIZE[REG_GoMark]      (0 )
#define REG_SIZE[REG_ResetPos]    (0 )
#define REG_SIZE[REG_ResetDevice] (0 )
#define REG_SIZE[REG_StopSoft]    (0 )
#define REG_SIZE[REG_StopHard]    (0 )
#define REG_SIZE[REG_HiZSoft]     (0 )
#define REG_SIZE[REG_HiZHard]     (0 )
#define REG_SIZE[REG_GetStatus]   (16)

static const uint8_t spiBPW  8;
static const uint16_t spiDelay  0;

//----define struct/union----

struct L6470_Data{
#define  uint8_t reg_addr;
#define  uint8_t value8b[3];
};

union L6470_packet{
#define  struct L6470_Data data;
#define  uint8_t value8b[4];
#define  uint32_t value32b;
};

//----prottype declaration---
void L6470_SPI_init(void);
int mywiringPiSPISetupMode (int channel, int speed, int wmode, int rmode);
int mywiringPiSPIDataRW(int channel, unsigned char *data,int len);
void L6470_reg_size_init(void);
void L6470_setting_init(void);
void L6470_init(void);
int L6470_rw(uint8_t *data,int len);
void L6470_nop(int times);
void L6470_SetParam(uint8_t param,uint32_t value);
union L6470_packet L6470_GetParam(uint8_t param);
void L6470_MoveCont(uint8_t dir,uint32_t value);
void L6470_MoveStepClock(uint8_t dir);
void L6470_MoveStep(uint8_t dir, uint32_t step);
void L6470_MoveGoTo(int32_t abs_pos);
void L6470_MoveGoToDir(uint8_t dir, int32_t abs_pos);
void L6470_MoveGoToUntil(uint8_t act, uint8_t dir,uint32_t speed);
void L6470_MoveRelease(uint8_t act, uint8_t dir);
void L6470_GoHome(void);
void L6470_GoMark(void);
void L6470_ResetPos(void);
void L6470_ResetDevice(void);
void L6470_StopSoft(void);
void L6470_StopHard(void);
void L6470_HiZSoft(void);
void L6470_HiZHard(void);
int32_t L6470_GetAbsPos(void);
uint16_t L6470_GetStatus(void);

#if defined (L6470_PRINT_MESSAGE)
#define L6470_PRINT_HEADER "[L6470 DEBUG]: "
static void L6470_debug_print(const char *msg,union L6470_packet send, union L6470_packet get)
#endif

#endif

