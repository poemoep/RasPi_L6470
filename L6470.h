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

#define STATUS_MASK_HiZ		0b0000000000000001
#define STATUS_MASK_BUSY	0b0000000000000010 //Constant speed / positioning / motion command
#define STATUS_MASK_SW_F	0b0000000000000100 //SW input status
#define STATUS_MASK_SW_EVN	0b0000000000001000 //Normaly L, SW turn-on event
#define STATUS_MASK_DIR		0b0000000000010000 //1: FWD, 0: RVS
#define STATUS_MASK_MOT_sTATUS 	0b0000000001100000 //00: Stop, 01: Acceleration, 10: Deceleration, 11: Constant speed
#define STATUS_MASK_NOTPERF_CMD	0b0000000010000000 //Normaly L
#define STATUS_MASK_WRONG_CMD	0b0000000100000000 //Normaly L
#define STATUS_MASK_UVLO	0b0000001000000000 //Normaly H
#define STATUS_MASK_TH_WRN	0b0000010000000000 //Normaly H
#define STATUS_MASK_TH_SD	0b0000100000000000 //Normaly H
#define STATUS_MASK_OCD		0b0001000000000000 //Normaly H
#define STATUS_MASK_STEP_LOSS_A	0b0010000000000000 //Normaly H
#define STATUS_MASK_STEP_LOSS_B	0b0100000000000000 //Normaly H
#define STATUS_MASK_SCK_MOD	0b1000000000000000 //Normaly L

#define MOTOR_STATUS_STOP	0b00
#define MOTOR_STATUS_ACC	0b01
#define MOTOR_STATUS_DEC	0b10
#define MOTOR_STATUS_CONST	0b11

#define READONLY	(0x00)
#define WRITABLE	(0x10)
#define WRITABLE_HiZ	(Writable | 0x01)
#define WRITABLE_MStop	(Writable | 0x02)
#define WRITABLE_Always (Writable | 0x04)
//----define L6470 parametor as userful number----

#define PARAM_ofset 	  0

#define L6470_ABS_POS     (PARAM_ofset + 0)
#define L6470_EL_POS      (PARAM_ofset + 1) 
#define L6470_MARK        (PARAM_ofset + 2)
#define L6470_SPEED       (PARAM_ofset + 3) //readonly
#define L6470_ACC         (PARAM_ofset + 4) 
#define L6470_DEC         (PARAM_ofset + 5)
#define L6470_MAX_SPEED   (PARAM_ofset + 6)
#define L6470_MIN_SPEED   (PARAM_ofset + 7)
#define L6470_KVAL_HOLD   (PARAM_ofset + 8)
#define L6470_KVAL_RUN    (PARAM_ofset + 9)
#define L6470_KVAL_ACC    (PARAM_ofset + 10)
#define L6470_KVAL_DEC    (PARAM_ofset + 11)
#define L6470_INT_SPEED   (PARAM_ofset + 12)
#define L6470_ST_SLP      (PARAM_ofset + 13)
#define L6470_FN_SLP_ACC  (PARAM_ofset + 14)
#define L6470_FN_SLP_DEC  (PARAM_ofset + 15)
#define L6470_K_THERM     (PARAM_ofset + 16)
#define L6470_ADC_OUT     (PARAM_ofset + 17) //readonly
#define L6470_OCD_TH      (PARAM_ofset + 18)
#define L6470_STALL_TH    (PARAM_ofset + 19)
#define L6470_FS_SPD      (PARAM_ofset + 20)
#define L6470_STEP_MODE   (PARAM_ofset + 21)
#define L6470_ALARM_EN    (PARAM_ofset + 22)
#define L6470_CONFIG      (PARAM_ofset + 23)
#define L6470_STATUS      (PARAM_ofset + 24) //readonly
#define L6470_RESERVED_h1A    (PARAM_ofset + 25)
#define L6470_RESERVED_h1B    (PARAM_ofset + 26)

#define PARAM_NUM	(L6470_RESERVED_h1B + 1 - PARAM_ofset)

//----define L6470 command as userful number----
#define CMD_ofset	  100

#define L6470_NOP (CMD_ofset + 0) /0x00
#define L6470_SETPARAM    (CMD_ofset + 1) 
#define L6470_GETPARAM    (CMD_ofset + 2)
#define L6470_MoveCont    (CMD_ofset + 3)
#define L6470_MoveStepClock (CMD_ofset + 4)
#define L6470_MoveStep    (CMD_ofset + 5)
#define L6470_MoveGoTo    (CMD_ofset + 6)
#define L6470_MoveGoToDir (CMD_ofset + 7)
#define L6470_MoveGoToUntil (CMD_ofset + 8)
#define L6470_MoveRelease (CMD_ofset + 9)
#define L6470_GoHome      (CMD_ofset + 0)
#define L6470_GoMark      (CMD_ofset + 1)
#define L6470_ResetPos    (CMD_ofset + 2)
#define L6470_ResetDevice (CMD_ofset + 13)
#define L6470_StopSoft    (CMD_ofset + 14)
#define L6470_StopHard    (CMD_ofset + 15)
#define L6470_HiZSoft     (CMD_ofset + 16)
#define L6470_HiZHard     (CMD_ofset + 17)
#define L6470_GetStatus   (CMD_ofset + 18)

#define CMD_NUM		  (L6470_GetStatus + 1 - CMD_ofset)

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
#define CMD_NOP 0b00000000 //0x00
#define CMD_SETPARAM    0b00000000 
#define CMD_GETPARAM    0b00100000
#define CMD_MoveCont    0b01010000
#define CMD_MoveStepClock 0b01011000
#define CMD_MoveStep    0b01000000
#define CMD_MoveGoTo    0b01100000
#define CMD_MoveGoToDir 0b01101000
#define CMD_MoveGoToUntil 0b10000010
#define CMD_MoveRelease 0b10010010
#define CMD_GoHome      0b01110000
#define CMD_GoMark      0b01111000
#define CMD_ResetPos    0b11011000
#define CMD_ResetDevice 0b11000000
#define CMD_StopSoft    0b10110000
#define CMD_StopHard    0b10111000
#define CMD_HiZSoft     0b10100000
#define CMD_HiZHard     0b10101000
#define CMD_GetStatus   0b11010000

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
struct L6470_CMD{
	uint8_t self_num;
	uint8_t addr;
	uint8_t send_bit_size;
};

struct L6470_REG{
	uint8_t self_num;
	uint8_t addr;
	uint8_t param_size;
	uint8_t rw;
}

struct L6470_Data{
  uint8_t reg_addr;
  uint8_t value8b[3];
};

union L6470_packet{
  struct L6470_Data data;
  uint8_t value8b[4];
  uint32_t value32b;
};

const struct L6470_CMD[CMD_NUM] =
{	},




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

