#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "wiringPi.h"
#include "wiringPiSPI.h"

#include "L6470.h"
#include "L6470_user.h"

uint8_t *REG_SIZE;
union L6470_packet *L6470_setting;

void L6470_reg_size_init(void){

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:reg_size_init start\n");
#endif

    //REG_SIZE initialize
    REG_SIZE = (uint8_t*)malloc(256* sizeof(uint8_t));

    REG_SIZE[REG_ABS_POS]   = 22;
    REG_SIZE[REG_EL_POS]    = 9;
    REG_SIZE[REG_MARK]      = 22;
    REG_SIZE[REG_SPEED]     = 20; //readonly
    REG_SIZE[REG_ACC]       = 12;
    REG_SIZE[REG_DEC]       = 12;
    REG_SIZE[REG_MAX_SPEED] = 10;
    REG_SIZE[REG_MIN_SPEED] = 13;
    REG_SIZE[REG_KVAL_HOLD] = 8;
    REG_SIZE[REG_KVAL_RUN]  = 8;
    REG_SIZE[REG_KVAL_ACC]  = 8;
    REG_SIZE[REG_KVAL_DEC]  = 8;
    REG_SIZE[REG_INT_SPEED] = 14;
    REG_SIZE[REG_ST_SLP]    = 8;
    REG_SIZE[REG_FN_SLP_ACC]= 8;
    REG_SIZE[REG_FN_SLP_DEC]= 8;
    REG_SIZE[REG_K_THERM]   = 4;
    REG_SIZE[REG_ADC_OUT]   = 5; //readonly
    REG_SIZE[REG_OCD_TH]    = 4;
    REG_SIZE[REG_STALL_TH]  = 7;
    REG_SIZE[REG_FS_SPD]    = 10;
    REG_SIZE[REG_STEP_MODE] = 8;
    REG_SIZE[REG_ALARM_EN]  = 8;
    REG_SIZE[REG_CONFIG]    = 16;
    REG_SIZE[REG_STATUS]    = 16; //readonly

    REG_SIZE[REG_NOP]       = 0;
    REG_SIZE[REG_SETPARAM]  = 24;
    REG_SIZE[REG_GETPARAM]  = 24;
    REG_SIZE[REG_MoveCont]  =  24;
    REG_SIZE[REG_MoveStepClock]  = 0;
    REG_SIZE[REG_MoveStep]  =  24;  
    REG_SIZE[REG_MoveGoTo]  =  24;
    REG_SIZE[REG_MoveGoToDir]= 24;
    REG_SIZE[REG_MoveGoToUntil]= 24;
    REG_SIZE[REG_MoveRelease]= 0;
    REG_SIZE[REG_GoHome]    =  0;
    REG_SIZE[REG_GoMark]    =  0;
    REG_SIZE[REG_ResetPos]  =  0;
    REG_SIZE[REG_ResetDevice]= 0;
    REG_SIZE[REG_StopSoft]  =  0;
    REG_SIZE[REG_StopHard]  =  0;
    REG_SIZE[REG_HiZSoft]   =  0;
    REG_SIZE[REG_HiZHard]   =  0;
    REG_SIZE[REG_GetStatus] =  16;


#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:reg_size_init end\n");
#endif

}

void L6470_setting_init(void)
{

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:setting_init start\n");
#endif


    L6470_setting = (union L6470_packet*)malloc((0x19 + 1) * sizeof(union L6470_packet));

    for (int reg = 0; reg < (0x19 +1); reg++){
        switch (reg) {
            case REG_NOP:
            case REG_SPEED:
            case REG_ADC_OUT:
            case REG_STATUS:
                //do nothing
                break;

            default:
                //copy user_setting to setting
                //set L6470

                //when use L6470_rw, L6470_setting is written by SDO 
                L6470_setting[reg] = L6470_user_setting[reg];

                int len, SPI_res = 0;
                len = REG_SIZE[reg];
#ifdef L6470_PRINT_MESSAGE
                printf("[L6470 DEBUG]:setting_init before reg:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
				L6470_setting[reg].data.reg_addr,
				L6470_setting[reg].value8b[0],
				L6470_setting[reg].value8b[1],
				L6470_setting[reg].value8b[2],
				L6470_setting[reg].value8b[3],
				(int)(1 + (len +8 -1)/8));
#endif
                SPI_res = L6470_rw(L6470_setting[reg].value8b, (int)(1 + (len + 8 -1)/8));

#ifdef L6470_PRINT_MESSAGE
                printf("[L6470 DEBUG]:setting_init after reg:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
				L6470_setting[reg].data.reg_addr,
				L6470_setting[reg].value8b[0],
				L6470_setting[reg].value8b[1],
				L6470_setting[reg].value8b[2],
				L6470_setting[reg].value8b[3],
				(int)(1 + (len +8 -1)/8));
#endif
            break;
            }
        }

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:setting_init end\n");
#endif

}


void L6470_SPI_init(void)
{
    int SPI_res;
    SPI_res = wiringPiSPISetupMode(SPI_CH,SPI_SPEED,SPI_MODE);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:SPI_init ch:%d\n",SPI_res);
#endif
}

/*
void L6470_setting_init(void)
{
    
    int itr_row,itr_col;
    
    itr_row =  sizeof(L6470_setting) / sizeof(L6470_setting[0]);


    for (int itr = 0; itr < itr_row; itr++){
        int SPI_res;
	union L6470_packet temp;
       	temp = L6470_setting[itr];
#ifdef L6470_PRINT_MESSAGE
            printf("[L6470 DEBUG]:setting_init before\tres:%d,\treg:0x%x,\tvalue:0x%x,\tlen:%d\n",
                    0,
                    temp.data.reg_addr,
                    temp.data.value32b,
		    (REG_SIZE[temp.data.reg_addr] + 8 - 1)/8);
#endif
     	    SPI_res = L6470_rw( temp.value8b,
                            (1 + (REG_SIZE[temp.data.reg_addr] + 8 - 1)/8));
            //切り上げ処理 (roundup(x%8) = (x+8-1)/8
            
#ifdef L6470_PRINT_MESSAGE
            printf("[L6470 DEBUG]:setting_init after\tres:%d,\treg:0x%x,\tvalue:0x%x\n",
                    SPI_res,
                    temp.data.reg_addr,
                    temp.data.value32b);
#endif
      }
}
*/

void L6470_init(void)
{
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:init Start\n");
#endif

    L6470_SPI_init();
    L6470_reg_size_init();
    L6470_setting_init();

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:init Done\n");
#endif
}

int L6470_rw(uint8_t *data,int len)
{
	int i = 0,j = 0;
	for (i = 0; i<len; i++){
		j += wiringPiSPIDataRW(SPI_CH, data,1);
		data += 1;
	}

   return j; 
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


    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:SetParam res:%d\n",SPI_res);
#endif
}

union L6470_packet L6470_GetParam(uint8_t param_addr)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[param_addr];

    pkt.data.reg_addr = (param_addr | REG_GETPARAM);
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetParam before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif


    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetParam after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif


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

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveCont before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif


    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveCont after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif

}

void L6470_MoveStepClock(uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveStepClock];

    pkt.data.reg_addr = (REG_MoveStepClock | dir);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStepClock before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStepClock after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
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

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStep before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif


    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveStep after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_MoveGoTo(int32_t abs_pos)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveGoTo];
    
    printf("%x\n",abs_pos);

    pkt.data.reg_addr = (REG_MoveGoTo);
    pkt.data.value8b[0] = ((abs_pos & 0x3F0000) >> 16);
    pkt.data.value8b[1] = ((abs_pos & 0x00FF00) >> 8);
    pkt.data.value8b[2] = ((abs_pos & 0x0000FF));
#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoTo before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif

   SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoTo after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
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

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToDir before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToDir after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
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

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToUntil before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoToUntil after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_MoveRelease(uint8_t act, uint8_t dir)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_MoveRelease];

    pkt.data.reg_addr = (REG_MoveRelease | dir | act);
    
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveRelease res:%d,\taddr:0x%2x,\tvalue:0x%6x\n",SPI_res,pkt.data.reg_addr, pkt.value32b);
#endif
}

void L6470_GoHome(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_GoHome];

    pkt.data.reg_addr = (REG_GoHome);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoHome before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoHome after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_GoMark(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_GoMark];

    pkt.data.reg_addr = (REG_GoMark);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoMark before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:MoveGoMark after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_ResetPos(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_ResetPos];

    pkt.data.reg_addr = (REG_ResetPos);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetPos before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif

    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetPos after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_ResetDevice(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_ResetDevice];

    pkt.data.reg_addr = (REG_ResetDevice);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetDevice before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:ResetDevice after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_StopSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_StopSoft];

    pkt.data.reg_addr = (REG_StopSoft);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopSoft before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopSoft after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_StopHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_StopHard];

    pkt.data.reg_addr = (REG_StopHard);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopHard before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:StopHard after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_HiZSoft(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_HiZSoft];

    pkt.data.reg_addr = (REG_HiZSoft);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZSoft before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZSoft after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

void L6470_HiZHard(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_HiZHard];

    pkt.data.reg_addr = (REG_HiZHard);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZHart before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:HiZHard after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
}

uint16_t L6470_GetStatus(void)
{
    union L6470_packet pkt={0};
    int SPI_res = 0;
    int size = REG_SIZE[REG_GetStatus];

    pkt.data.reg_addr = (REG_GetStatus);

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetStatus before\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif
    SPI_res = L6470_rw((pkt.value8b),(1 + (size+8-1)/8));

#ifdef L6470_PRINT_MESSAGE
    printf("[L6470 DEBUG]:GetStatus after\tres:%d,\taddr:0x%x\tvalue:0x%x\t%x\t%x\t%x\tlen:%d\n",
		    	SPI_res,
			pkt.data.reg_addr,
			pkt.value8b[0],
			pkt.value8b[1],
			pkt.value8b[2],
			pkt.value8b[3],
			size);
#endif

    return (pkt.value8b[2] << 8) & (pkt.value8b[3]);

}
