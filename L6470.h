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

const enum enum_L6470_PARAM {
  L6470_ABS_POS = PARAM_ofset,
  L6470_EL_POS ,
  L6470_MARK,
  L6470_SPEED, //readonly
  L6470_ACC ,
  L6470_DEC,
  L6470_MAX_SPEED,
  L6470_MIN_SPEED,
  L6470_KVAL_HOLD,
  L6470_KVAL_RUN,
  L6470_KVAL_ACC,
  L6470_KVAL_DEC,
  L6470_INT_SPEED,
  L6470_ST_SLP,
  L6470_FN_SLP_ACC,
  L6470_FN_SLP_DEC,
  L6470_K_THERM,
  L6470_ADC_OUT, //readonly
  L6470_OCD_TH,
  L6470_STALL_TH,
  L6470_FS_SPD,
  L6470_STEP_MODE,
  L6470_ALARM_EN,
  L6470_CONFIG,
  L6470_STATUS, //readonly
  L6470_RESERVED_h1A,
  L6470_RESERVED_h1B
} enum_L6470_param;
#define PARAM_NUM (L6470_RESERVED_h1B + 1)

//----define L6470 command as userful number----
const enum enum_L6470_CMD{
  L6470_NOP,
  L6470_SETPARAM, 
  L6470_GETPARAM,
  L6470_MOVECONT,
  L6470_MOVESTEPCLOCK,
  L6470_MOVESTEP,
  L6470_MOVEGOTO,
  L6470_MOVEGOTODIR,
  L6470_,
  L6470_MoveRelease,
  L6470_GoHome,
  L6470_GoMark,
  L6470_ResetPos,
  L6470_ResetDevice,
  L6470_StopSoft,
  L6470_StopHard,
  L6470_HiZSoft,
  L6470_HiZHard,
  L6470_GetStatus
} enum_L6470_cmd;
#define CMD_NUM		  (L6470_GetStatus + 1))

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

#define REG_SIZE_ABS_POS    (22)
#define REG_SIZE_EL_POS     (9 )
#define REG_SIZE_MARK       (22)
#define REG_SIZE_SPEED      (20) //readonly
#define REG_SIZE_ACC        (12)
#define REG_SIZE_DEC        (12)
#define REG_SIZE_MAX_SPEED  (10)
#define REG_SIZE_MIN_SPEED  (13)
#define REG_SIZE_KVAL_HOLD  (8 )
#define REG_SIZE_KVAL_RUN   (8 )
#define REG_SIZE_KVAL_ACC   (8 )
#define REG_SIZE_KVAL_DEC   (8 )
#define REG_SIZE_INT_SPEED  (14)
#define REG_SIZE_ST_SLP     (8 )
#define REG_SIZE_FN_SLP_ACC (8 )
#define REG_SIZE_FN_SLP_DEC (8 )
#define REG_SIZE_K_THERM    (4 )
#define REG_SIZE_ADC_OUT    (5 ) //readonly
#define REG_SIZE_OCD_TH     (4 )
#define REG_SIZE_STALL_TH   (7 )
#define REG_SIZE_FS_SPD     (10)
#define REG_SIZE_STEP_MODE  (8 )
#define REG_SIZE_ALARM_EN   (8 )
#define REG_SIZE_CONFIG     (16)
#define REG_SIZE_STATUS     (16) //readonly

#define CMD_SIZE_NOP        (1 ) // test
#define CMD_SIZE_SETPARAM   (24)
#define CMD_SIZE_GETPARAM   (24)
#define CMD_SIZE_MOVECONT   (24)
#define CMD_SIZE_MOVESTEPCLOCK   (0 )
#define CMD_SIZE_MOVESTEP    (24)  
#define CMD_SIZE_MOVEGOTO    (24)
#define CMD_SIZE_MOVEGOTODIR (24)
#define CMD_SIZE_MOVEGOTOUNTIL (24)
#define CMD_SIZE_MOVERELEASE (0 )
#define CMD_SIZE_GOHOME      (0 )
#define CMD_SIZE_GOMARK      (0 )
#define CMD_SIZE_RESETPOS    (0 )
#define CMD_SIZE_RESETDEVICE (0 )
#define CMD_SIZE_STOPSOFT    (0 )
#define CMD_SIZE_STOPHARD    (0 )
#define CMD_SIZE_HIZSOFT     (0 )
#define CMD_SIZE_HIZHARD     (0 )
#define CMD_SIZE_GETSTATUS   (16)

static const uint8_t spiBPW  8;
static const uint16_t spiDelay  0;

//----define struct/union----
struct L6470_CMD{
	uint8_t self_num;
	uint8_t addr;
	uint8_t send_bit_size;
};

struct L6470_PARAM{
	uint8_t self_num;
	uint8_t addr;
	uint8_t param_size;
	uint8_t rw;
};

struct L6470_Data{
  uint8_t reg_addr;
  uint8_t value8b[3];
};

union L6470_packet{
  struct L6470_Data data;
  uint8_t value8b[4];
  uint32_t value32b;
};

const struct L6470_PARAM L6470_param[PARAM_NUM] =
{
  L6470_ABS_POS ,
  L6470_EL_POS ,
  L6470_MARK,
  L6470_SPEED, //readonly
  L6470_ACC ,
  L6470_DEC,
  L6470_MAX_SPEED,
  L6470_MIN_SPEED,
  L6470_KVAL_HOLD,
  L6470_KVAL_RUN,
  L6470_KVAL_ACC,
  L6470_KVAL_DEC,
  L6470_INT_SPEED,
  L6470_ST_SLP,
  L6470_FN_SLP_ACC,
  L6470_FN_SLP_DEC,
  L6470_K_THERM,
  L6470_ADC_OUT, //readonly
  L6470_OCD_TH,
  L6470_STALL_TH,
  L6470_FS_SPD,
  L6470_STEP_MODE,
  L6470_ALARM_EN,
  L6470_CONFIG,
  L6470_STATUS, //readonly
  L6470_RESERVED_h1A,
  L6470_RESERVED_h1B
}

};
const struct L6470_CMD L6470_cmd[CMD_NUM] =
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

