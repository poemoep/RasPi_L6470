#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
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


void L6470_setting_init(void)
{

#ifdef L6470_PRINT_MESSAGE
    printf("%s setting_init start\n",L6470_PRINT_HEADER);
#endif


    L6470_setting = (union L6470_packet*)malloc((PARAM_NUM) * sizeof(union L6470_packet));

    for (int reg = 0; reg < (PARAM_NUM); reg++){
        if(L6470_param[reg].rw == RESERVED){
            continue;
        }else if(L6470_param[reg].rw == READONLY){
            L6470_setting[reg] = L6470_GetParam(L6470_param[reg].addr);
        }else{
            L6470_setting[reg] = L6470_user_setting[reg];
            //make temp because wiringPiSPIDataRW rewrite send data
            union L6470_packet pkt_temp;
            pkt_temp = L6470_user_setting[reg];

            int len, SPI_res = 0;
            len = L6470_param[reg].param_size;
#ifdef L6470_PRINT_MESSAGE
            union L6470_packet send = L6470_setting[reg];
#endif
            SPI_res = L6470_rw(pkt_temp, (int)(bit2byte(len + ADDR_SIZE)), NULL);
#ifdef L6470_PRINT_MESSAGE
            L6470_debug_print("setting_init",send,L6470_setting[reg]);
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
    L6470_setting_init();

#ifdef L6470_PRINT_MESSAGE
    printf("%s init Done\n",L6470_PRINT_HEADER);
#endif
}

int L6470_rw(union L6470_packet pkt,int len, const char* msg)
{
    uint8_t *data;
    data = pkt.value8b;

#ifdef L6470_PRINT_MESSAGE
    union L6470_packet send = pkt;
#endif


	int i = 0,j = 0;
	for (i = 0; i<len; i++){
		j += wiringPiSPIDataRW(L6470_SPI_CH, data,1);
		data++;
	}

#ifdef L6470_PRINT_MESSAGE
    L6470_debug_print(msg,send,pkt);
#endif

   return j; 
}

void L6470_nop(int times)
{
    union L6470_packet pkt = {0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_NOP];

    L6470_rw(pkt.value8b,times, "NOP");
}

void L6470_SetParam(uint8_t param_addr, uint32_t value)
{
    union L6470_packet pkt;
    int SPI_res = 0;
    int size = REG_SIZE[param_addr];
    
    pkt.data.reg_addr = (param_addr | REG_SETPARAM);

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
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "SetParam");

}

union L6470_packet L6470_GetParam(uint8_t param_addr)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[param_addr];

    pkt.data.reg_addr = (param_addr | REG_GETPARAM);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8),"GetParam");

    return pkt;
}

void L6470_MoveCont(uint8_t dir, uint32_t value)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveCont];

    pkt.data.reg_addr = (REG_MoveCont | dir);
    pkt.data.value8b[0] = (uint8_t)((value & 0xFF0000) >> 16);
    pkt.data.value8b[1] = (uint8_t)((value & 0x00FF00) >> 8);
    pkt.data.value8b[2] = (uint8_t)(value & 0x0000FF);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveCont");
}

void L6470_MoveStepClock(uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveStepClock];

    pkt.data.reg_addr = (REG_MoveStepClock | dir);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveStepClock");
}

void L6470_MoveStep(uint8_t dir,uint32_t step)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveStep];

    pkt.data.reg_addr = (REG_MoveStep | dir);
    pkt.data.value8b[0] = ((step & 0xFF0000) >> 16);
    pkt.data.value8b[1] = ((step & 0x00FF00) >> 8);
    pkt.data.value8b[2] = ((step & 0x0000FF));

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveStep");

}

void L6470_MoveGoTo(int32_t abs_pos)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveGoTo];
    
    pkt.data.reg_addr = (REG_MoveGoTo);
    pkt.data.value8b[0] = ((abs_pos & 0x3F0000) >> 16);
    pkt.data.value8b[1] = ((abs_pos & 0x00FF00) >> 8);
    pkt.data.value8b[2] = ((abs_pos & 0x0000FF));

   SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveGoTo");

}

void L6470_MoveGoToDir(uint8_t dir,int32_t abs_pos)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveGoToDir];

    printf("%x\n",abs_pos);
    
    pkt.data.reg_addr = (REG_MoveGoToDir | dir);
    pkt.data.value8b[0] = ((abs_pos & 0x3F0000) >> 16);
    pkt.data.value8b[1] = ((abs_pos & 0x00FF00) >> 8);
    pkt.data.value8b[2] = ((abs_pos & 0x0000FF));

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveGoToDir");
}

void L6470_MoveGoToUntil(uint8_t act, uint8_t dir,uint32_t speed)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveGoToUntil];

    pkt.data.reg_addr = (REG_MoveGoToUntil | dir | act);
    pkt.data.value8b[0] = ((speed & 0xFF0000) >> 16);
    pkt.data.value8b[1] = ((speed & 0xFFFFFF) >> 8);
    pkt.data.value8b[2] = (speed & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveGoToUntil");

}

void L6470_MoveRelease(uint8_t act, uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveRelease];

    pkt.data.reg_addr = (REG_MoveRelease | dir | act);
    
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveRelease");


}

void L6470_GoHome(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_GoHome];

    pkt.data.reg_addr = (REG_GoHome);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveGoHome");

}

void L6470_GoMark(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_GoMark];

    pkt.data.reg_addr = (REG_GoMark);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "MoveGoMark");

}

void L6470_ResetPos(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_ResetPos];

    pkt.data.reg_addr = (REG_ResetPos);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "ResetPos");

}

void L6470_ResetDevice(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_ResetDevice];

    pkt.data.reg_addr = (REG_ResetDevice);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8),"ResetDevice");

}

void L6470_StopSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_StopSoft];

    pkt.data.reg_addr = (REG_StopSoft);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "StopSoft");
}

void L6470_StopHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_StopHard];

    pkt.data.reg_addr = (REG_StopHard);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "StopHard");

}

void L6470_HiZSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_HiZSoft];

    pkt.data.reg_addr = (REG_HiZSoft);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8), "HiZSoft");

}

void L6470_HiZHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_HiZHard];

    pkt.data.reg_addr = (REG_HiZHard);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8),"HIZHard");

}

int32_t L6470_GetAbsPos(void)
{
    int32_t pos = 0;
    
    union L6470_packet pkt;
    pkt = L6470_GetParam(REG_ABS_POS);
    pos = ((pkt.value8b[1] & 0x3F) << 16);
    pos += ((pkt.value8b[2] & 0xFF) << 8);
    pos += ((pkt.value8b[3] & 0xFF));
    
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
    int size = REG_SIZE[REG_GetStatus];

    pkt.data.reg_addr = (REG_GetStatus);

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8),"GetStatus");
    return (pkt.value8b[2] << 8) & (pkt.value8b[3]);

}

#if defined (L6470_PRINT_MESSAGE)
static void L6470_debug_print(const char *msg,union L6470_packet send, union L6470_packet get)
{
    printf("%s %s send:%8x \t len:%d\n", L6470_PRINT_HEADER, msg, send.value32b, REG_SIZE[send.data.reg_addr]);
    if (get != NULL)
        printf("%s %s  get:%8x \t len:%d\n", L6470_PRINT_HEADER, msg,  get.value32b, REG_SIZE[ get.data.reg_addr]);

}
#endif
