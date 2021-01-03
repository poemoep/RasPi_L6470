#include <stdio.h>
#include <unistd.h>

#include "L6470.h"
//#include "L6470_user.h"

int main(int argc, char** argv)
{

    L6470_init();

    L6470_MoveCont(DIR_FWD, 256000);
    sleep(5);
    L6470_MoveCont(DIR_FWD, 512000);
    sleep(5);
    
    
    
    L6470_StopSoft();
    sleep(2);

    L6470_MoveCont(DIR_RVS, 16000);
    sleep(5);
    L6470_StopSoft();
    sleep(2);
    
    
    L6470_MoveStepClock(DIR_FWD);
    sleep(3);
    L6470_MoveStepClock(DIR_RVS);
    sleep(3);
    sleep(3);

    for(int i = 0; i<1; i++){
        L6470_MoveStep(DIR_FWD,200);
        sleep(1);
        L6470_MoveStep(DIR_RVS,200);
        sleep(1);
    }
    sleep(3);

    int pos_aim=-1;
    int pos = pos_aim + 1;
    
    L6470_MoveGoTo(pos_aim);
// while(pos != pos_aim){
    for(int l = 0 ; l < 20; l++){
	union L6470_packet pkt;
	pkt = L6470_GetParam(REG_ABS_POS);
	
	pos = ((pkt.value8b[1] & 0x3F) << 16);
	pos += ((pkt.value8b[2] & 0xFF) << 8);
	pos += ((pkt.value8b[3] & 0xFF));
	
	if(((pos & 0x200000) >> 21) == 1){
	       printf("inv\n");
	       pos = (-1) * ((~pos + 1) & 0x3FFFFF);	
	}

	printf("pos: %d\tand: %d\n", pos, ((pos & 0x200000) >> 21));

        sleep(1);
    }

    
   // L6470_MoveStep(DIR_RVS,200);
    sleep(1);
    
    pos_aim=1;
    pos = pos_aim + 1;
    
    L6470_MoveGoToDir(DIR_RVS, pos_aim);
    //while(pos != pos_aim){
    for(int l = 0 ; l < 20; l++){
	union L6470_packet pkt;
	pkt = L6470_GetParam(REG_ABS_POS);
	
	pos = ((pkt.value8b[1] & 0x3F) << 16);
	pos += ((pkt.value8b[2] & 0xFF) << 8);
	pos += ((pkt.value8b[3] & 0xFF));
	
	if(((pos & 0x200000) >> 21) == 1){
	       	pos = (-1) * ((~pos + 1) & 0x3FFFFF);	
		printf("inv\n");
	}
	printf("pos: %d\tand: %d\n", pos, ((pos & 0x200000) >> 21));

        sleep(1);
    }
    
    L6470_MoveGoToUntil(ACT_POS_TO_MARK,DIR_FWD,1000);
    for(int i= 0; i<12; i++){
	union L6470_packet pkt;
	pkt = L6470_GetParam(REG_ABS_POS);
	
	printf("pkt: %x\n", pkt);
	
	pos = ((pkt.value8b[1] & 0x3F) << 16);
	pos += ((pkt.value8b[2] & 0xFF) << 8);
	pos += ((pkt.value8b[3] & 0xFF));

	printf("pos: %d\n", pos);

        sleep(1);
    }

    L6470_GoHome();
    for(int i= 0; i<12; i++){
	union L6470_packet pkt;
	pkt = L6470_GetParam(REG_ABS_POS);
	
	printf("pkt: %x\n", pkt);
	
	pos = ((pkt.value8b[1] & 0x3F) << 16);
	pos += ((pkt.value8b[2] & 0xFF) << 8);
	pos += ((pkt.value8b[3] & 0xFF));

	printf("pos: %d\n", pos);

        sleep(1);
    }

    L6470_GoMark();
    for(int i= 0; i<12; i++){
	union L6470_packet pkt;
	pkt = L6470_GetParam(REG_ABS_POS);
	
	printf("pkt: %x\n", pkt);
	
	pos = ((pkt.value8b[1] & 0x3F) << 16);
	pos += ((pkt.value8b[2] & 0xFF) << 8);
	pos += ((pkt.value8b[3] & 0xFF));


	printf("pos: %d\n", pos);

        sleep(1);
    }

    L6470_HiZSoft();
    
    return 0;
}
