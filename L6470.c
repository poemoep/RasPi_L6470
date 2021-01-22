#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <math.h>

// #include <sys/ioctl.h>
// #include <asm/ioctl.h>
 #include <linux/spi/spidev.h>

#include "wiringPi.h"
#include "wiringPiSPI.h"

#define L6470_SPI_MODE SPI_MODE_3 // default

#include "L6470.h"
#include "L6470_user.h"

// uint8_t *REG_SIZE;
union L6470_packet *L6470_setting;


static uint32_t spiSpeeds [2];
static int 	spiFds [2];

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
{ enum_L6470_STEP_MODE    , REG_STEP_MODE,    REG_SIZE_STEP_MODE,     READONLY | WRITABLE_HiZ},
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

static void L6470_ExecCmd(struct L6470_CMD cmd, int orprm, uint32_t arg_param,const char* msg);
static void L6470_ExecCmd_NoArg(struct L6470_CMD cmd, const char* msg);
static union L6470_packet generate_pkt(int enum_param,int32_t val);
static union L6470_packet generate_pkt_with_percentage(int enum_param, int32_t percentage);


#if defined (L6470_PRINT_MESSAGE)
#define L6470_PRINT_HEADER "[L6470 DEBUG]: "
#define L6470_PRINT_CAUTION "Caution"
static void L6470_debug_print(const char *msg,union L6470_packet* send, union L6470_packet* get);
#endif

void L6470_setting_init(void)
{

#ifdef L6470_PRINT_MESSAGE
    printf("%s setting_init start\n",L6470_PRINT_HEADER);
#endif


    L6470_setting = (union L6470_packet*)malloc((PARAM_NUM) * sizeof(union L6470_packet));

    for (int enum_param = 0; enum_param < (PARAM_NUM); enum_param++)
    {
        if(L6470_param[enum_param].rw == RESERVED){
            continue;
        }else if(L6470_param[enum_param].rw == READONLY){
            L6470_GetParam(enum_param);
        }else{
            /* copy to buf from const */
            L6470_setting[enum_param] = L6470_user_setting[enum_param];
            //make temp because wiringPiSPIDataRW rewrite send data
            union L6470_packet pkt_temp;
            pkt_temp = L6470_user_setting[enum_param];

            int len, SPI_res = 0;
            len = L6470_param[enum_param].param_size;
#ifdef L6470_PRINT_MESSAGE
            union L6470_packet send = L6470_user_setting[enum_param];
#endif
            SPI_res = L6470_rw(&(pkt_temp), (int)(bit2byte(len + ADDR_SIZE)), NULL);
#ifdef L6470_PRINT_MESSAGE
            L6470_debug_print("setting_init",&(send),&(pkt_temp));
#endif
        }
    }

#ifdef L6470_PRINT_MESSAGE
    printf("%s setting_init end\n",L6470_PRINT_HEADER);
#endif

}


void L6470_SPI_init(void)
{
    int SPI_res;
    SPI_res = wiringPiSPISetupMode(L6470_SPI_CH,SPI_SPEED,L6470_SPI_MODE);
    // SPI_res = mywiringPiSPISetupMode(SPI_CH,SPI_SPEED,SPI_WMODE, SPI_RMODE);

#ifdef L6470_PRINT_MESSAGE
    printf("%s SPI_init ch:%d\n",L6470_PRINT_HEADER,SPI_res);
#endif
}

void L6470_init(void)
{

    L6470_SPI_init();
    L6470_ResetDevice();
    L6470_setting_init();

#ifdef L6470_PRINT_MESSAGE
    printf("%s init Done\n",L6470_PRINT_HEADER);
#endif
}

int L6470_rw(union L6470_packet *pkt,int len, const char* msg)
{
    //uint8_t *data;
    //data = pkt->value8b;

#ifdef L6470_PRINT_MESSAGE
    union L6470_packet send = *pkt;
#endif


	int i = 0,j = 0;
	for (i = 0; i<len; i++){
	//	j += wiringPiSPIDataRW(L6470_SPI_CH, data,1);
		j += wiringPiSPIDataRW(L6470_SPI_CH, (unsigned char *)(pkt->value8b + i),1);
	//	data++;
	}

#ifdef L6470_PRINT_MESSAGE
    L6470_debug_print(msg,&(send),pkt);
#endif

   return j; 
}

void L6470_nop(int times)
{
    union L6470_packet pkt = {0};
    int SPI_res = 0;
    int size = L6470_cmd[enum_L6470_NOP].send_bit_size;

    L6470_rw(&(pkt),times, "NOP");
}

void L6470_SetParam(int enum_param, uint32_t value)
{
    union L6470_packet pkt;
    int SPI_res = 0;
    int size = L6470_param[enum_param].param_size;
    
    pkt.data.reg_addr = (L6470_param[enum_param].addr | L6470_cmd[enum_L6470_SETPARAM].addr);

    if(8 >= size){
        pkt.value8b[1] = ((value & 0xFF));
    }else if (16 >= size){
        pkt.value8b[1] = ((value & 0xFF00) >> 8);
        pkt.value8b[2] = ((value & 0x00FF));
    }else{
        pkt.value8b[1] = ((value & 0xFF0000) >> 16);
        pkt.value8b[2] = ((value & 0x00FF00) >> 8);
        pkt.value8b[3] = (value & 0x0000FF);
    }
    
    SPI_res = L6470_rw(&(pkt),bit2byte(size + ADDR_SIZE), "SetParam");

}

int32_t L6470_GetParam(int enum_param)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int32_t ret = 100;

    int size = L6470_cmd[enum_L6470_GETPARAM].send_bit_size;
    pkt.data.reg_addr = (L6470_param[enum_param].addr | L6470_cmd[enum_L6470_GETPARAM].addr);

    SPI_res = L6470_rw(&(pkt),bit2byte(size + ADDR_SIZE),"GetParam");

    //rewrite addr
    pkt.data.reg_addr = L6470_param[enum_param].addr;
    L6470_setting[enum_param] = pkt;


    if(8 >= size){
        ret = (pkt.value8b[1]);
    }else if (16 >= size){
        ret = (pkt.value8b[1] << 8) + (pkt.value8b[2]);
    }else{
        ret = (pkt.value8b[1] << 16) + (pkt.value8b[2] << 8) + (pkt.value8b[3]);
    }

    return ret;
}
/*speed = 0 to 15625000 [x0.001 step/s] */
void L6470_MoveCont(uint8_t dir, uint32_t speed)
{
    int32_t speed_val = (int32_t)round((double)speed / SPEED_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)speed_val * SPEED_RESOLUTION) != speed)
        printf("%s %s speed is rounded to %d [x0.001 step/s]\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION, (speed_val) * SPEED_RESOLUTION);
#endif
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVECONT],dir,speed_val, "MoveCont");
}
/* dir = DIR_FWD or DIR_RVS */
void L6470_MoveStepClock(uint8_t dir)
{
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVESTEPCLOCK],dir,0, "MoveStepClock");
}
/* step = 0 to 4194303(2^22) [step] */
void L6470_MoveStep(uint8_t dir,uint32_t step)
{
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVESTEP],dir,step, "MoveStep");
}
/* abs_pos = -2^21 to 2^21 -1 [step]*/
void L6470_MoveGoTo(int32_t abs_pos)
{
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVEGOTO],0,abs_pos, "MoveGoTo");
}
/* dir = DIR_FWD or DIR_RVS, abs_pos = -2^21 to 2^21-1 [step] */
void L6470_MoveGoToDir(uint8_t dir,int32_t abs_pos)
{
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVEGOTODIR],dir,abs_pos,"MoveGoToDir");
}
/* act = ACT_POS_CLEAR or ACT_POS_TO_MARK */
/* dir = DIR_FWD or DIR_RVS */
/*speed = 0 to 15625000 [x0.001 step/s] */
void L6470_MoveGoToUntil(uint8_t act, uint8_t dir,uint32_t speed)
{
    int32_t speed_val = (int32_t)round((double)speed / SPEED_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)speed_val * SPEED_RESOLUTION) != speed)
        printf("%s %s speed is rounded to %d [x0.001 step/s]\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION, (speed_val) * SPEED_RESOLUTION);
#endif

    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVEGOTOUNTIL],act|dir,speed_val, "MoveGoToUntil");
}

/* act = ACT_POS_CLEAR or ACT_POS_TO_MARK */
/* dir = DIR_FWD or DIR_RVS */
void L6470_MoveRelease(uint8_t act, uint8_t dir)
{
    L6470_ExecCmd(L6470_cmd[enum_L6470_MOVERELEASE],act|dir,0,"MoveRelease");
}

void L6470_GoHome(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_GOHOME], "GoHome");

}

void L6470_GoMark(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_GOMARK], "GoMark");
}

void L6470_ResetPos(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_RESETPOS], "ResetPos");

}

void L6470_ResetDevice(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_RESETDEVICE],"ResetDevice");
}

void L6470_StopSoft(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_STOPSOFT], "StopSoft");
}

void L6470_StopHard(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_STOPHARD], "StopHard");
}

void L6470_HiZSoft(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_HIZSOFT],"HiZSoft");
}

void L6470_HiZHard(void)
{
    L6470_ExecCmd_NoArg(L6470_cmd[enum_L6470_HIZHARD],"HIZHard");
}

static void L6470_ExecCmd(struct L6470_CMD cmd, int orprm, uint32_t arg_param,const char* msg)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;

    int size = cmd.send_bit_size;
    pkt.data.reg_addr = (cmd.addr | orprm);

    if(pow(2,cmd.send_bit_size) < abs(arg_param))
    {
        printf("%s AbortCmd size_over cmdsize:2^%d, but arg is %d\n ",L6470_PRINT_HEADER, cmd.send_bit_size,arg_param);
        return;
    }

    if(8 >= size){
        pkt.data.value8b[0] = ((arg_param & 0x0000FF));
    }else if (16 >= size){
        pkt.data.value8b[0] = ((arg_param & 0x00FF00) >> 8);
        pkt.data.value8b[1] = ((arg_param & 0x0000FF));
    }else{
        pkt.data.value8b[0] = ((arg_param & 0xFF0000) >> 16);
        pkt.data.value8b[1] = ((arg_param & 0x00FF00) >> 8);
        pkt.data.value8b[2] = ((arg_param & 0x0000FF));
    }

    SPI_res = L6470_rw(&(pkt),bit2byte(size + ADDR_SIZE),msg);
}

static void L6470_ExecCmd_NoArg(struct L6470_CMD cmd, const char* msg)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
        
    int size = cmd.send_bit_size;
    pkt.data.reg_addr = cmd.addr;

    SPI_res = L6470_rw(&(pkt),bit2byte(size + ADDR_SIZE),msg);

}

int32_t L6470_GetAbsPos(void)
{
    int32_t pos = 0;
    int32_t ret = 0; 
    union L6470_packet pkt;
    pos = L6470_GetParam(enum_L6470_ABS_POS);
 
    if(((pos & 0x200000) >> 21) == 1){
	    pos = (-1) * ((~pos + 1) & 0x3FFFFF);	
    }

#ifdef L6470_PRINT_MESSAGE
	printf("pos: %d\n", pos);
#endif

    return pos;

}


uint16_t L6470_GetStatus(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;

    int size = L6470_param[enum_L6470_GETSTATUS].param_size;
    pkt.data.reg_addr = L6470_cmd[enum_L6470_GETSTATUS].addr;

    SPI_res = L6470_rw(&(pkt),bit2byte(size + ADDR_SIZE),"GetStatus");

    return ((pkt.value8b[2] << 8) & (pkt.value8b[3]));

}

/* (-2^21 <= abs_pos <= +2^21 -1) with the selected step mode */
union L6470_packet gen_ABS_POS(int32_t abs_pos)
{
#if defined (L6470_PRINT_MESSAGE)
    if( (abs_pos > (int32_t)(pow(2,21)-1)) | (abs_pos < (int32_t)((-1)*pow(2,21))) )
        printf("%s %s abs_pos is over/under flow\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION);
#endif
    int32_t val = abs_pos & (int32_t)(pow(2,22)-1);
    union L6470_packet pkt = generate_pkt(enum_L6470_ABS_POS, val);
    return pkt;
}

/* step = 0 to 3, el_step = 0 to 127(masked with selected step mode in IC) */
union L6470_packet gen_EL_POS(int32_t step_u_step)
{
    int32_t step = (step_u_step & STEP_ePOS_MASK);
    int32_t u_step = (step_u_step & STEP_u_STEP_MASK);
#if 0
#if defined (L6470_PRINT_MESSAGE)
    printf("%s %s step is selected STEP_ePOS_%ddeg.\n",
            L6470_PRINT_HEADER, L6470_PRINT_CAUTION, 90 * (step >> STEP_ePOS_ofset));
    printf("%s %s el_step is selected %d\n",L6470_PRINT_HEADER, L6470_PRINT_CAUTION, u_step));
#endif
#endif

    uint32_t val;
    val = (step + u_step);
    union L6470_packet pkt = generate_pkt(enum_L6470_EL_POS, val);
    return pkt;
}

/* (-2^21 <= mark <= +2^21 -1) with the selected step mode */
union L6470_packet gen_MARK(int32_t mark)
{
#if defined (L6470_PRINT_MESSAGE)
    if( (mark > (int32_t)(pow(2,21)-1)) | (mark < (int32_t)((-1)*pow(2,21))) )
        printf("%s %s MARK is over/under flow\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION);
#endif
    int32_t val = ( mark & (int32_t)(pow(2,22) - 1) );
    union L6470_packet pkt = generate_pkt(enum_L6470_MARK, mark);
    return pkt;
}

/* step_per_ss = N x ACC_RESOLUTION [x0.01 step/s^2]*/
union L6470_packet gen_ACC(int32_t step_per_ss)
{
    int32_t val = (int32_t)round((double)step_per_ss / ACC_RESOLUTION) ;
#if defined (L6470_PRINT_MESSAGE)
    if(val == 0){
        printf("%s %s ACC step_per_ss is more than equal %d [x0.01 step/s^2]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, ACC_RESOLUTION);
        printf("%s %s set minumum value.\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION);
        val = 1;
    } else if((int32_t)round((double)val * ACC_RESOLUTION) != step_per_ss){
        printf("%s %s ACC is rounded to %d [x0.01 step/s^2]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * ACC_RESOLUTION));
    } 
#endif

    union L6470_packet pkt = generate_pkt(enum_L6470_ACC, val);
    return pkt;
}

/* step_per_ss = N x DEC_RESOLUTION [0.01 step/s^2] */
union L6470_packet gen_DEC(int32_t step_per_ss)
{
    int32_t val = (int32_t)round((double)step_per_ss / DEC_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(val == 0){
        printf("%s %s DEC step_per_ss is more than equal %d [x0.01 step/s^2]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, DEC_RESOLUTION);
        printf("%s %s set minumum value.\n",L6470_PRINT_HEADER, L6470_PRINT_CAUTION);
        val = 1;
    } else if((int32_t)round((double)val * DEC_RESOLUTION) != step_per_ss){
        printf("%s %s DEC is rounded to %d [x0.01 step/s^2]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * DEC_RESOLUTION));
    } 
#endif

    union L6470_packet pkt = generate_pkt(enum_L6470_DEC, val);
    return pkt;
}

/* step_per_s = N x MAX_SPEED_RESOLUTION [x0.01 step/s^2]*/
union L6470_packet gen_MAX_SPEED(int32_t step_per_s)
{
    int32_t val = (int32_t)round((double)step_per_s / MAX_SPEED_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(val == 0){
        printf("%s %s MAX_SPEED is more than equal %d\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, MAX_SPEED_RESOLUTION);
        printf("%s %s set minumum value.\n",L6470_PRINT_HEADER, L6470_PRINT_CAUTION);
        val = 1;
    } else if((int32_t)round((double)val * MAX_SPEED_RESOLUTION) != step_per_s){
        printf("%s %s MAX_SPEED is rounded to %d [x0.01 step/s]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * MAX_SPEED_RESOLUTION));
    } 
#endif

    union L6470_packet pkt = generate_pkt(enum_L6470_MAX_SPEED, val);
    return pkt;
}

/* step_per_s = M x MIN_SPEED_RESOLUTION, enable_LSPD = ENABLE_LSPD or DISABLE */
union L6470_packet gen_MIN_SPEED(int32_t enable_LSPD_step_per_s)
{
    union L6470_packet pkt = {0};
    if( 0 != (enable_LSPD_step_per_s & 0x7E000000) ) {
#if defined (L6470_PRINT_MESSAGE)
        printf("%s %s MIN_SPEED is over\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION);
#endif
    return pkt;
    } /*check 0b0111 1110 000~ */

    int32_t step_per_s = (enable_LSPD_step_per_s & MIN_SPEED_MASK); /* 20 bits */
    int32_t enable_LSPD = (enable_LSPD_step_per_s & ENABLE_LSPD); /* 25 bit */

    int32_t val = (int32_t)round((double)step_per_s / MIN_SPEED_RESOLUTION);

#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)val * MIN_SPEED_RESOLUTION) != step_per_s){
        printf("%s %s MIN_SPEED is rounded to %d [x0.001 step/s]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * MIN_SPEED_RESOLUTION));
    } 
#endif
    if(DISABLE != enable_LSPD) val |= ENABLE_LSPD_BIT;

    pkt = generate_pkt(enum_L6470_MIN_SPEED, val);
    return pkt;
}

/* percentage = 0 to 10000 [0.01%]*/
union L6470_packet gen_KVAL_HOLD(int32_t percentage)
{
    union L6470_packet pkt = generate_pkt_with_percentage(enum_L6470_KVAL_HOLD, percentage);
    return pkt;
}

/* percentage = 0 to 10000 [0.01%] */
union L6470_packet gen_KVAL_RUN(int32_t percentage)
{
    union L6470_packet pkt = generate_pkt_with_percentage(enum_L6470_KVAL_RUN, percentage);
    return pkt;
}

/* percentage = 0 to 10000 [0.01%] */
union L6470_packet gen_KVAL_ACC(int32_t percentage)
{
    union L6470_packet pkt = generate_pkt_with_percentage(enum_L6470_KVAL_ACC, percentage);
    return pkt;
}

/* percentage = 0 to 10000 [0.01%] */
union L6470_packet gen_KVAL_DEC(int32_t percentage)
{
    union L6470_packet pkt = generate_pkt_with_percentage(enum_L6470_KVAL_DEC, percentage);
    return pkt;
}

/* step_per_s = N x INT_SPEED_RESOLUTION [x0.0001 step/s] */
union L6470_packet gen_INT_SPEED(int32_t step_per_s)
{
    uint32_t val = (int32_t)round((double)step_per_s / INT_SPEED_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)val * INT_SPEED_RESOLUTION) != step_per_s){
        printf("%s %s INT_SPEED is rounded to %d [x0.0001 step/s] \n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * INT_SPEED_RESOLUTION));
    } 
#endif

    union L6470_packet pkt = generate_pkt(enum_L6470_INT_SPEED, val);
    return pkt;
}

/* slp = N x ST_SLP_RESOLUTION [x0.000001]*/
union L6470_packet gen_ST_SLP(int32_t slp)
{
    uint32_t val = (int32_t)round((double)slp / ST_SLP_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)val * ST_SLP_RESOLUTION) != slp){
        printf("%s %s ST_SLP is rounded to %d [x0.000001] \n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * ST_SLP_RESOLUTION));
    } 
#endif
    union L6470_packet pkt = generate_pkt(enum_L6470_ST_SLP, val);
    return pkt;
}

/* slp_acc = N x FN_SLP_ACC_RESOLUTION*/
union L6470_packet gen_FN_SLP_ACC(int32_t slp_acc)
{
    uint32_t val = (int32_t)round((double)slp_acc / FN_SLP_ACC_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)val * FN_SLP_ACC_RESOLUTION) != slp_acc){
        printf("%s %s FN_SLP_ACC is rounded to %d [x0.000001]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * FN_SLP_ACC_RESOLUTION));
    }
#endif
    union L6470_packet pkt = generate_pkt(enum_L6470_FN_SLP_ACC, val);
    return pkt;
}

/* slp_dec = N x FN_SLP_DEC_RESOLUTION [x0.000001]*/
union L6470_packet gen_FN_SLP_DEC(int32_t slp_dec)
{
    uint32_t val = (int32_t)round((double)slp_dec / FN_SLP_DEC_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round((double)val * FN_SLP_DEC_RESOLUTION) != slp_dec){
        printf("%s %s FN_SLP_DEC is rounded to %d [x0.000001]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * FN_SLP_DEC_RESOLUTION));
    } 
#endif
    union L6470_packet pkt = generate_pkt(enum_L6470_FN_SLP_DEC, val);
    return pkt;
}

/* k_therm = N x K_THERM_RESOLUTION */
union L6470_packet gen_K_THERM(int32_t k_therm)
{
    int32_t val = (int32_t)round((double)(k_therm - K_THERM_MIN) / K_THERM_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(((int32_t)round((double)val * K_THERM_RESOLUTION) + K_THERM_MIN) != k_therm){
        printf("%s %s K_THERM is rounded to %d [x0.00001]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * K_THERM_RESOLUTION) + K_THERM_MIN);
    } 
#endif
    union L6470_packet pkt = generate_pkt(enum_L6470_K_THERM, val);
    return pkt;
}

/* ocd_th = 375 to 6000 mA */
union L6470_packet gen_OCD_TH(int32_t ocd_th)
{
    uint32_t val = (int32_t)round((double)(ocd_th - OCD_TH_RESOLUTION) / OCD_TH_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(((int32_t)round((double)val * OCD_TH_RESOLUTION) + OCD_TH_RESOLUTION) != ocd_th){
        printf("%s %s OCD_TH is rounded to %d [mA]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, ((int32_t)round((double)val * OCD_TH_RESOLUTION) + OCD_TH_RESOLUTION));
    } 
#endif
    union L6470_packet pkt = generate_pkt(enum_L6470_OCD_TH, val);
    return pkt;
}

/* stall_th = 31.25 to 4000 mA */
union L6470_packet gen_STALL_TH(int32_t stall_th)
{
    int32_t val = (int32_t)round((double)(stall_th - STALL_TH_RESOLUTION) / STALL_TH_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(((int32_t)round((double)val * STALL_TH_RESOLUTION) + STALL_TH_RESOLUTION) != stall_th){
        printf("%s %s STALL_TH is rounded to %d [x0.01 mA]\n",
                        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, ((int32_t)round((double)val * STALL_TH_RESOLUTION) + STALL_TH_RESOLUTION));
    } 
#endif    
    union L6470_packet pkt = generate_pkt(enum_L6470_STALL_TH, val);
    return pkt;
}
/* fs_spd = 7.63(FS_SPD_MIN) to 15625 [step/s] */
union L6470_packet gen_FS_SPD(int32_t fs_spd)
{
    uint32_t val = (int32_t)round((double)(fs_spd - FS_SPD_MIN) / FS_SPD_RESOLUTION);
#if defined (L6470_PRINT_MESSAGE)
    if(((int32_t)round((double)val * FS_SPD_RESOLUTION) + FS_SPD_MIN) != fs_spd){
        printf("%s %s FS_SPD is rounded to %d [x0.01 step/s]\n",
        L6470_PRINT_HEADER, L6470_PRINT_CAUTION, (int32_t)round((double)val * FS_SPD_RESOLUTION) + FS_SPD_MIN);
    } 
#endif   

    union L6470_packet pkt = generate_pkt(enum_L6470_FS_SPD, val);
    return pkt;
}

/* sync_en = SYNC_EN or DISABLE, sync_sel = SYNC_FFS_*, step_sel = STEP_* */
union L6470_packet gen_STEP_MODE(int32_t mode)
{
#if defined (L6470_PRINT_MESSAGE)
    uint8_t sync_en = (mode & SYNC_EN);
    uint8_t sync_sel = (mode & SYNC_SEL_MASK);
    uint8_t step_sel = (mode & STEP_SEL_MASK);
    if( (sync_sel >> SYNC_SEL_ofset) > step_sel)
        printf("%s %s sync_sel is less than equal step_sel.\n",L6470_PRINT_HEADER, L6470_PRINT_CAUTION);    
#endif
    int32_t val = mode;
    union L6470_packet pkt = generate_pkt(enum_L6470_STEP_MODE, val);
    return pkt;
}

/* alm = ALM_* | ALM_* ... */
union L6470_packet gen_ALARM_EN(int32_t alm)
{
    int32_t val = alm;
    union L6470_packet pkt = generate_pkt(enum_L6470_ALARM_EN, val);
    return pkt;
}

/* f_pwm_int, f_pwm_dec, pow_sr, oc_sd, en_vscomp, sw_mode, ext_clk, osc_sel */
union L6470_packet gen_CONFIG(int32_t param)
{
#if 0
#if defined (L6470_PRINT_MESSAGE)
    int32_t f_pwm_int   = (param & F_PWM_INT_MASK);
    int32_t f_pwm_dec   = (param & F_PWM_DEC_MASK);
    int32_t pow_sr      = (param & POW_SR_MASK);
    int32_t oc_sd       = (param & OC_SD_MASK);
    int32_t en_vscomp   = (param & EN_VSCOMP_MASK);
    int32_t sw_mode     = (param & SW_MODE_MASK);
    int32_t ext_clk     = (param & EXT_CLK_MASK);
    int32_t osc_sel     = (param & OSC_SEL_MASK);
#endif
#endif

    int32_t val =  param;
    union L6470_packet pkt = generate_pkt(enum_L6470_CONFIG, val);
    return pkt;
}

static union L6470_packet generate_pkt(int enum_param,int32_t val)
{
    union L6470_packet pkt = {0};
    pkt.data.reg_addr = L6470_param[enum_param].addr;

    int size = L6470_param[enum_param].param_size;

    if(8 >= size){
        pkt.data.value8b[0] = (uint8_t)(val & 0xFF);
    } else if (16 >= size){
        pkt.data.value8b[0] = (uint8_t)((val & 0xFF00) >> 8);
        pkt.data.value8b[1] = (uint8_t)((val & 0x00FF));
    } else {
        pkt.data.value8b[0] = (uint8_t)((val & 0xFF0000) >> 16);
        pkt.data.value8b[1] = (uint8_t)((val & 0x00FF00) >> 8);
        pkt.data.value8b[2] = (uint8_t)((val & 0x0000FF));
    }
    
    return pkt;
}

/* percentage = 0 to 10000 [x0.01%] */
static union L6470_packet generate_pkt_with_percentage(int enum_param, int32_t percentage)
{
    union L6470_packet pkt = {0};
    if( (percentage < 0) | (10000 < percentage) )
    {
#if defined (L6470_PRINT_MESSAGE)
        printf("%s %s percentage = 0 to 10000 [%%]\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION);
#endif
        return pkt; /* 0x00 pkt */  
    } /*0 to 10000*/

    int32_t val = (int32_t)round((255 * (double)percentage) / 10000);
#if defined (L6470_PRINT_MESSAGE)
    if((int32_t)round(((double)val * 10000) / 255) != percentage)
        printf("%s %s percentage is round to %d[0.01%%]\n",L6470_PRINT_HEADER,L6470_PRINT_CAUTION,(int32_t)round((val * 10000)/ 255));
#endif
    pkt = generate_pkt(enum_param,val);
    return pkt;
}

#if defined (L6470_PRINT_MESSAGE)
static void L6470_debug_print(const char *msg,union L6470_packet* send, union L6470_packet* get)
{
    if(msg != NULL)
    {
        printf("%s %s send:0x%02x 0x%02x 0x%02x 0x%02x\n", L6470_PRINT_HEADER, msg, 
				send->value8b[0], 
				send->value8b[1], 
				send->value8b[2], 
				send->value8b[3]);
        if (get != (union L6470_packet*)NULL)
            printf("%s %s  get:0x%02x 0x%02x 0x%02x 0x%02x\n", L6470_PRINT_HEADER, msg,  
			         get->value8b[0], 
			         get->value8b[1], 
			         get->value8b[2], 
			         get->value8b[3]);
    }
}
#endif
