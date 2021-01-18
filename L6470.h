#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>


#ifndef __L6470_HEADER
#define __L6470_HEADER

//----define debug message function ON/OFF----
#define L6470_PRINT_MESSAGE 

//----define inline function----
#define bit2byte(x) ( ( x + 8 - 1 ) / 8 ) 

//----define const value----

#define ADDR_SIZE    (8 )
#define L6470_TICK   (250) // ns
#define ACC_RESOLUTION    (14.55) //[step/s^2]
#define DEC_RESOLUTION     ACC_RESOLUTION
#define MAX_SPEED_RESOLUTION (14.55) //[step/s]
#define MIN_SPEED_RESOLUTION (0.238) //[step/s]
#define INT_SPEED_RESOLUTION (0.0596) //[step/s]
#define ST_SLP_RESOLUTION    (0.000015) //
#define FN_SLP_ACC_RESOLUTION (0.000015) //
#define FN_SLP_DEC_RESOLUTION (0.000015) //
#define K_THERM_RESOLUTION ( 0.03125) //
#define OCD_TH_RESOLUTION (375) // [mA]
#define STALL_TH_RESOLUTION (31.25) // [mA]
#define FS_SPD_RESOLUTION (15.25) // [step/s]
#define FS_SPD_MIN        (FS_SPD_RESOLUTION/2) // [step/s]

#define ENABLE  (1)
#define DISABLE (0)
#define ENABLE_LSPD (ENABLE << 12)

// define for STEP_MODE
#define SYNC_EN     (ENABLE << 7) //Output sync_clock from ^BUSY/SYNC
#define STEP_FULL   (0b000)
#define STEP_HALF   (0b001)
#define STEP_4DIV   (0b010)
#define STEP_8DIV   (0b011)
#define STEP_16DIV  (0b100)
#define STEP_32DIV  (0b101)
#define STEP_64DIV  (0b110)
#define STEP_128DIV (0b111)
#define SYNC_FFS_2DIV   (0b000 << 4) // EL_POS[7]
#define SYNC_FFS        (0b001 << 4) // EL_POS[6]
#define SYNC_FFS_2TIMES (0b010 << 4) // EL_POS[5]
#define SYNC_FFS_4TIMES (0b011 << 4) // EL_POS[4]
#define SYNC_FFS_8TIMES (0b100 << 4) // EL_POS[3]
#define SYNC_FFS_16TIMES (0b101 << 4) // EL_POS[2]
#define SYNC_FFS_32TIMES (0b110 << 4) // EL_POS[1]
#define SYNC_FFS_64TIMES (0b111 << 4) // EL_POS[0]

// define for ALARM
#define ALM_NOTHING          (0b00000000)
#define ALM_OVERCURRENT      (0b00000001)
#define ALM_THERMAL_SHUTDOWN (0b00000010)
#define ALM_THERMAL_WARNING  (0b00000100)
#define ALM_UDERVOLTAGE      (0b00001000)
#define ALM_STALL_A          (0b00010000)
#define ALM_STALL_B          (0b00100000)
#define ALM_SW_TURNON        (0b01000000)
#define ALM_CMD_WRONG        (0b10000000)


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

#define RESERVED  (0x00)
#define READONLY	(0x01)
#define WRITABLE	(0x10)
#define WRITABLE_HiZ	(WRITABLE | 0x02)
#define WRITABLE_MStop	(WRITABLE | 0x04)
#define WRITABLE_Always (WRITABLE | 0x08)
//----define L6470 parametor as userful number----

enum enum_L6470_PARAM {
  enum_L6470_ABS_POS ,
  enum_L6470_EL_POS ,
  enum_L6470_MARK,
  enum_L6470_SPEED, //readonly
  enum_L6470_ACC ,
  enum_L6470_DEC,
  enum_L6470_MAX_SPEED,
  enum_L6470_MIN_SPEED,
  enum_L6470_KVAL_HOLD,
  enum_L6470_KVAL_RUN,
  enum_L6470_KVAL_ACC,
  enum_L6470_KVAL_DEC,
  enum_L6470_INT_SPEED,
  enum_L6470_ST_SLP,
  enum_L6470_FN_SLP_ACC,
  enum_L6470_FN_SLP_DEC,
  enum_L6470_K_THERM,
  enum_L6470_ADC_OUT, //readonly
  enum_L6470_OCD_TH,
  enum_L6470_STALL_TH,
  enum_L6470_FS_SPD,
  enum_L6470_STEP_MODE,
  enum_L6470_ALARM_EN,
  enum_L6470_CONFIG,
  enum_L6470_STATUS, //readonly
//  enum_L6470_RESERVED_h1A,
//  enum_L6470_RESERVED_h1B,
  enum_L6470_PARAM_FIN
};
#define PARAM_NUM (enum_L6470_PARAM_FIN)

//----define L6470 command as userful number----
enum enum_L6470_CMD{
  enum_L6470_NOP,
  enum_L6470_SETPARAM, 
  enum_L6470_GETPARAM,
  enum_L6470_MOVECONT,
  enum_L6470_MOVESTEPCLOCK,
  enum_L6470_MOVESTEP,
  enum_L6470_MOVEGOTO,
  enum_L6470_MOVEGOTODIR,
  enum_L6470_MOVEGOTOUNTIL,
  enum_L6470_MOVERELEASE,
  enum_L6470_GOHOME,
  enum_L6470_GOMARK,
  enum_L6470_RESETPOS,
  enum_L6470_RESETDEVICE,
  enum_L6470_STOPSOFT,
  enum_L6470_STOPHARD,
  enum_L6470_HIZSOFT,
  enum_L6470_HIZHARD,
  enum_L6470_GETSTATUS,
  enum_L6470_CMD_FIN
};
#define CMD_NUM		  (enum_L6470_CMD_FIN)

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
#define CMD_NOP           0b00000000
#define CMD_SETPARAM      0b00000000
#define CMD_GETPARAM      0b00100000
#define CMD_MOVECONT      0b01010000
#define CMD_MOVESTEPCLOCK 0b01011000
#define CMD_MOVESTEP      0b01000000
#define CMD_MOVEGOTO      0b01100000
#define CMD_MOVEGOTODIR   0b01101000
#define CMD_MOVEGOTOUNTIL 0b10000010
#define CMD_MOVERELEASE   0b10010010
#define CMD_GOHOME        0b01110000
#define CMD_GOMARK        0b01111000
#define CMD_RESETPOS      0b11011000
#define CMD_RESETDEVICE   0b11000000
#define CMD_STOPSOFT      0b10110000
#define CMD_STOPHARD      0b10111000
#define CMD_HIZSOFT       0b10100000
#define CMD_HIZHARD       0b10101000
#define CMD_GETSTATUS     0b11010000





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
//#define REG_SIZE_RESERVED_h1A     (0) //dummy
//#define REG_SIZE_RESERVED_h1B     (0) //dummy

#define CMD_SIZE_NOP        (1 ) // test
#define CMD_SIZE_SETPARAM   (24) //MAX
#define CMD_SIZE_GETPARAM   (24) //MAX
#define CMD_SIZE_MOVECONT   (20)
#define CMD_SIZE_MOVESTEPCLOCK   (0 )
#define CMD_SIZE_MOVESTEP    (22)  
#define CMD_SIZE_MOVEGOTO    (22)
#define CMD_SIZE_MOVEGOTODIR (22)
#define CMD_SIZE_MOVEGOTOUNTIL (20)
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

#define SPI_BPW   8
#define SPI_DELAY  0

extern union L6470_packet *L6470_setting;

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
{ enum_L6470_ABS_POS      , REG_ABS_POS,      REG_SIZE_ABS_POS,       READONLY | WRITABLE_MStop },
{ enum_L6470_EL_POS       , REG_EL_POS ,      REG_SIZE_EL_POS ,       READONLY | WRITABLE_MStop},
{ enum_L6470_MARK         , REG_MARK,         REG_SIZE_MARK,          READONLY | WRITABLE_Always},
{ enum_L6470_SPEED        , REG_SPEED,        REG_SIZE_SPEED,         READONLY }, //readonly
{ enum_L6470_ACC          , REG_ACC,          REG_SIZE_ACC,           READONLY | WRITABLE_MStop},
{ enum_L6470_DEC          , REG_DEC,          REG_SIZE_DEC,           READONLY | WRITABLE_MStop},
{ enum_L6470_MAX_SPEED    , REG_MAX_SPEED,    REG_SIZE_MAX_SPEED,     READONLY | WRITABLE_Always},
{ enum_L6470_MIN_SPEED    , REG_MIN_SPEED,    REG_SIZE_MIN_SPEED,     READONLY | WRITABLE_MStop},
{ enum_L6470_KVAL_HOLD    , REG_KVAL_HOLD,    REG_SIZE_KVAL_HOLD,     READONLY | WRITABLE_Always},
{ enum_L6470_KVAL_RUN     , REG_KVAL_RUN,     REG_SIZE_KVAL_RUN,      READONLY | WRITABLE_Always},
{ enum_L6470_KVAL_ACC     , REG_KVAL_ACC,     REG_SIZE_KVAL_ACC,      READONLY | WRITABLE_Always},
{ enum_L6470_KVAL_DEC     , REG_KVAL_DEC,     REG_SIZE_KVAL_DEC,      READONLY | WRITABLE_Always},
{ enum_L6470_INT_SPEED    , REG_INT_SPEED,    REG_SIZE_INT_SPEED,     READONLY | WRITABLE_HiZ},
{ enum_L6470_ST_SLP       , REG_ST_SLP,       REG_SIZE_ST_SLP,        READONLY | WRITABLE_HiZ},
{ enum_L6470_FN_SLP_ACC   , REG_FN_SLP_ACC,   REG_SIZE_FN_SLP_ACC,    READONLY | WRITABLE_HiZ},
{ enum_L6470_FN_SLP_DEC   , REG_FN_SLP_DEC,   REG_SIZE_FN_SLP_DEC,    READONLY | WRITABLE_HiZ},
{ enum_L6470_K_THERM      , REG_K_THERM,      REG_SIZE_K_THERM,       READONLY | WRITABLE_Always},
{ enum_L6470_ADC_OUT      , REG_ADC_OUT,      REG_SIZE_ADC_OUT,       READONLY }, //readonly
{ enum_L6470_OCD_TH       , REG_OCD_TH,       REG_SIZE_OCD_TH,        READONLY | WRITABLE_Always},
{ enum_L6470_STALL_TH     , REG_STALL_TH,     REG_SIZE_STALL_TH,      READONLY | WRITABLE_Always},
{ enum_L6470_FS_SPD       , REG_FS_SPD,       REG_SIZE_FS_SPD,        READONLY | WRITABLE_Always},
{ enum_L6470_STEP_MODE    , REG_STEP_MODE,    REG_STEP_MODE,          READONLY | WRITABLE_HiZ},
{ enum_L6470_ALARM_EN     , REG_ALARM_EN,     REG_SIZE_ALARM_EN,      READONLY | WRITABLE_MStop},
{ enum_L6470_CONFIG       , REG_CONFIG,       REG_SIZE_CONFIG,        READONLY | WRITABLE_HiZ},
{ enum_L6470_STATUS       , REG_STATUS,       REG_SIZE_STATUS,        READONLY }, //readonly
//{ enum_L6470_RESERVED_h1A , REG_RESERVED_h1A, REG_SIZE_RESERVED_h1A,  RESERVED }, //dummy
//{ enum_L6470_RESERVED_h1B , REG_RESERVED_h1B, REG_SIZE_RESERVED_h1B,  RESERVED }  //dummy
};

const struct L6470_CMD L6470_cmd[CMD_NUM] =
{	
{  enum_L6470_NOP,            CMD_NOP,            CMD_SIZE_NOP},
{  enum_L6470_SETPARAM,       CMD_SETPARAM,       CMD_SIZE_SETPARAM},
{  enum_L6470_GETPARAM,       CMD_GETPARAM,       CMD_SIZE_GETPARAM},
{  enum_L6470_MOVECONT,       CMD_MOVECONT,       CMD_SIZE_MOVECONT},
{  enum_L6470_MOVESTEPCLOCK,  CMD_MOVESTEPCLOCK,  CMD_SIZE_MOVESTEPCLOCK},
{  enum_L6470_MOVESTEP,       CMD_MOVESTEP,       CMD_SIZE_MOVESTEP},
{  enum_L6470_MOVEGOTO,       CMD_MOVEGOTO,       CMD_SIZE_MOVEGOTO},
{  enum_L6470_MOVEGOTODIR,    CMD_MOVEGOTODIR,    CMD_SIZE_MOVEGOTODIR},
{  enum_L6470_MOVEGOTOUNTIL,  CMD_MOVEGOTOUNTIL,  CMD_SIZE_MOVEGOTOUNTIL},
{  enum_L6470_MOVERELEASE,    CMD_MOVERELEASE,    CMD_SIZE_MOVERELEASE},
{  enum_L6470_GOHOME,         CMD_GOHOME,         CMD_SIZE_GOHOME},
{  enum_L6470_GOMARK,         CMD_GOMARK,         CMD_SIZE_GOMARK},
{  enum_L6470_RESETPOS,       CMD_RESETPOS,       CMD_SIZE_RESETPOS},
{  enum_L6470_RESETDEVICE,    CMD_RESETDEVICE,    CMD_SIZE_RESETDEVICE},
{  enum_L6470_STOPSOFT,       CMD_STOPSOFT,       CMD_SIZE_STOPSOFT},
{  enum_L6470_STOPHARD,       CMD_STOPHARD,       CMD_SIZE_STOPHARD},
{  enum_L6470_HIZSOFT,        CMD_HIZSOFT,        CMD_SIZE_HIZSOFT},
{  enum_L6470_HIZHARD,        CMD_HIZHARD,        CMD_SIZE_HIZHARD},
{  enum_L6470_GETSTATUS,      CMD_GETSTATUS,      CMD_SIZE_GETSTATUS}
};


//----prottype declaration---
void L6470_SPI_init(void);
void L6470_reg_size_init(void);
void L6470_setting_init(void);
void L6470_init(void);
int  L6470_rw(union L6470_packet *pkt,int len,const char* msg);
void L6470_nop(int times);
void L6470_SetParam(int enum_param,uint32_t value);
int32_t L6470_GetParam(int param);
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
static void L6470_ExecCmd(struct L6470_CMD cmd, int orprm, uint32_t arg_param,const char* msg);
static void L6470_ExecCmd_NoArg(struct L6470_CMD cmd, const char* msg);

union L6470_packet gen_ABS_POS(int32_t abs_pos);
union L6470_packet gen_EL_POS(uint8_t step, uint8_t el_step);
union L6470_packet gen_MARK(int32_t mark);
union L6470_packet gen_ACC(float step_per_ss);
union L6470_packet gen_DEC(float step_per_ss);
union L6470_packet gen_MAX_SPEED(float step_per_s);
union L6470_packet gen_MIN_SPEED(float step_per_s, int16_t enable_LSPD);
union L6470_packet gen_KVAL_HOLD(uint8_t kval);
union L6470_packet gen_KVAL_RUN(uint8_t kval);
union L6470_packet gen_KVAL_ACC(uint8_t kval);
union L6470_packet gen_KVAL_DEC(uint8_t kval);
union L6470_packet gen_INT_SPEED(float step_per_s);
union L6470_packet gen_ST_SLP(float slp);
union L6470_packet gen_FN_SLP_ACC(float slp_acc);
union L6470_packet gen_FN_SLP_DEC(float slp_dec);
union L6470_packet gen_K_THERM(float k_therm);
union L6470_packet gen_OCD_TH(uint16_t ocd_th);
union L6470_packet gen_STALL_TH(float stall_th);
union L6470_packet gen_FS_SPD(float fs_spd);
union L6470_packet gen_STEP_MODE(uint8_t sync_en, uint8_t sync_sel, uint8_t step_sel);
union L6470_packet gen_ALARM_EN(uint8_t alm);
union L6470_packet gen_CONFIG(uint8_t f_pwm_int, uint8_t f_pwm_dec, uint8_t pow_sr, uint8_t oc_sd, uint8_t en_vscomp, uint8_t sw_mode, uint8_t ext_clk, uint8_t osc_sel);


static union L6470_packet generate_pkt(int enum_param,int32_t val);



#if defined (L6470_PRINT_MESSAGE)
#define L6470_PRINT_HEADER "[L6470 DEBUG]: "
#define L6470_PRINT_CAUTION "Caution"
static void L6470_debug_print(const char *msg,union L6470_packet* send, union L6470_packet* get);
#endif

#endif

