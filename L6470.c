#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wiringPi.h"
#include "wiringPiSPI.h"

#include "L6470.h"
#include "L6470_user.h"


void L6470_SPI_init(void)
{
    int SPI_res;
    SPI_res = wiringPiSPISetupMode(SPI_CH,SPI_SPEED,SPI_MODE);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:SPI_init ch:%d\n",SPI_res);
#endif
}

void L6470_setting_init(void)
{
    
    int itr_row,itr_col;
    
    itr_row =  sizeof(L6470_setting) / sizeof(L6470_setting[0]);
    itr_col = sizeof(L6470_setting[0]) / sizeof(L6470_setting[0][0]);

    for (int itr = 0; itr < itr_row; itr++){
        int SPI_res;
        SPI_res = L6470_rw(L6470_setting[itr][L6470_setting_reg_addr],(REG_SIZE[L6470_setting[itr][L6470_setting_reg_addr]] + 8 - 1)/8);
            //切り上げ処理 (roundup(x%8) = (x+8-1)/8
#ifdef L6470_PRINT_MESSAGE
            printf("[L6470 DEBUG]:setting_init res:%d,\treg:0x%2x,\tvalue:0x%2x,\t0x%2x,\t0x%2x\n",
                    SPI_res,
                    L6470_setting[itr][L6470_setting_reg_addr] & 0xFF,
                    L6470_setting[itr][L6470_setting_reg_addr + 1] %0xFF,
                    L6470_setting[itr][L6470_setting_reg_addr + 2] %0xFF,
                    L6470_setting[itr][L6470_setting_reg_addr + 3] %0xFF);
#endif
      }
}

void L6470_init(void)
{
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:init Start\n");
#endif

    L6470_SPI_init();
    L6470_setting_init();

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:init Done\n");
#endif
}
int L6470_rw(uint8_t *data,int len)
{
   return wiringPiSPIDataRW(SPI_CH, data, len); 
}

void L6470_nop(int times)
{
    uint8_t * data;

    data = (uint8_t*)malloc(times * sizeof(uint8_t));

    for (int itr = 0; itr < times; itr++){
        data[itr] = REG_NOP;
    }

    L6470_rw(data,times);
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:nop send %d times\n",times);
#endif
}

void L6470_SetParam(uint8_t param_addr, uint32_t value)
{
    union L6470_packet pkt;
    int SPI_res;
    int size = REG_SIZE[param_addr];
    
    pkt.data.reg_addr = (param_addr & REG_SETPARAM);

    if(8 >= size){
        pkt.data.value32b = ((value & 0xFF) << 16);
    }else if (16 >= size){
        pkt.data.value32b = ((value & 0xFFFF) << 8);
    }else{
        pkt.data.value32b = ((value & 0xFFFFFF));

    }


    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:SetParam res:%d\n",SPI_res);
#endif
}

union L6470_packet L6470_GetParam(uint8_t param_addr)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[param_addr];

    pkt.data.reg_addr = (param_addr & REG_GETPARAM);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetParam res:%d,\taddr:0x%2x\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif

    return pkt;
}

void L6470_MoveCont(uint8_t dir, uint32_t value)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveCont];


    pkt.data.reg_addr = (REG_MoveCont & dir);
    pkt.data.value32b = (value & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveCont res:%d,\tDIR:0x%2x\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif

}

void L6470_MoveStepClock(uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveStepClock];


    pkt.data.reg_addr = (REG_MoveStepClock & dir);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStepClock res:%d,\tDIR:0x%2x\n",SPI_res,pkt.data.reg_addr);
#endif
}

void L6470_MoveStep(uint8_t dir,uint32_t step)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveStep];


    pkt.data.reg_addr = (REG_MoveStep & dir);
    pkt.data.value32b = (step & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStepClock res:%d,\tDIR:0x%2x\n",SPI_res,pkt.data.reg_addr);
#endif
}

void L6470_MoveGoTo(uint32_t abs_pos)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveGoTo];

    pkt.data.reg_addr = (REG_MoveGoTo);
    pkt.data.value32b = (abs_pos & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoTo res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_MoveGoToDir(uint8_t dir,uint32_t abs_pos)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveGoToDir];

    pkt.data.reg_addr = (REG_MoveGoToDir & dir);
    pkt.data.value32b = (abs_pos & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToDir res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_MoveGoToUntil(uint8_t act, uint8_t dir,uint32_t speed)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveGoToUntil];

    pkt.data.reg_addr = (REG_MoveGoToUntil & dir & act);
    pkt.data.value32b = (speed & 0xFFFFFF);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToUntil res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_MoveRelease(uint8_t act, uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_MoveRelease];

    pkt.data.reg_addr = (REG_MoveRelease & dir & act);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveRelease res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_GoHome(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_GoHome];

    pkt.data.reg_addr = (REG_GoHome);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GoHome res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_GoMark(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_GoMark];

    pkt.data.reg_addr = (REG_GoMark);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GoMark res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_ResetPos(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_ResetPos];

    pkt.data.reg_addr = (REG_ResetPos);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetPos res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_ResetDevice(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_ResetDevice];

    pkt.data.reg_addr = (REG_ResetDevice);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetDevice res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_StopSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_StopSoft];

    pkt.data.reg_addr = (REG_StopSoft);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopSoft res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_StopHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_StopHard];

    pkt.data.reg_addr = (REG_StopHard);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopHard res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_HiZSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_HiZSoft];

    pkt.data.reg_addr = (REG_HiZSoft);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZSoft res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

void L6470_HiZHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_HiZHard];

    pkt.data.reg_addr = (REG_HiZHard);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZHard res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif
}

uint16_t L6470_GetStatus(void)
{
    union L6470_packet pkt={0};
    int SPI_res;
    int size = REG_SIZE[REG_GetStatus];

    pkt.data.reg_addr = (REG_GetStatus);

    SPI_res = L6470_rw((pkt.value8b),((size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetStatus res:%d,\tDIR:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.data.value32b);
#endif

    return (pkt.value8b[2] << 8) & (pkt.value8b[3]);

}
