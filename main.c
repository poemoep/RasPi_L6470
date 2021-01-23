#include <stdio.h>
#include "L6470.h"

int main(int argc, char** argv)
{

    L6470_init();


    int pos_aim,pos;

    pos = L6470_GetAbsPos();
    L6470_MoveRun(DIR_FWD, 500000);
    sleep(5);
    pos = L6470_GetAbsPos();
    L6470_MoveRun(DIR_FWD, 5120000);
    sleep(5);
    pos = L6470_GetAbsPos();
    
    
    
    L6470_StopSoft();
    sleep(2);
    pos = L6470_GetAbsPos();

    L6470_MoveRun(DIR_RVS, 1600000);
    sleep(5);
    pos = L6470_GetAbsPos();
    L6470_StopSoft();
    sleep(2);
    pos = L6470_GetAbsPos();
    
    
    L6470_MoveStepClock(DIR_FWD);
    sleep(3);
    pos = L6470_GetAbsPos();
    L6470_MoveStepClock(DIR_RVS);
    sleep(3);
    pos = L6470_GetAbsPos();

    for(int i = 0; i<1; i++){
        L6470_MoveStep(DIR_FWD,200);
        sleep(1);
    	pos = L6470_GetAbsPos();
        L6470_MoveStep(DIR_RVS,200);
        sleep(1);
    	pos = L6470_GetAbsPos();
    }
    sleep(3);

    pos_aim=10000;
    pos = pos_aim + 1;
    
    L6470_MoveGoTo(pos_aim);
    while(pos != pos_aim){
   // for(int l = 0 ; l < 20; l++){
	pos = L6470_GetAbsPos();
        sleep(1);
    }

    
   // L6470_MoveStep(DIR_RVS,200);
    sleep(1);
    
    pos_aim=-1;
    pos = pos_aim + 1;
    
    L6470_MoveGoToDir(DIR_RVS, pos_aim);
    while(pos != pos_aim){
    //for(int l = 0 ; l < 20; l++){
	pos = L6470_GetAbsPos();
        sleep(1);
    }
    
    L6470_MoveGoToUntil(ACT_POS_TO_MARK,DIR_FWD,10000);
    for(int i= 0; i<12; i++){
	pos = L6470_GetAbsPos();
        sleep(1);
    }

    L6470_GoHome();
    for(int i= 0; i<12; i++){
	pos = L6470_GetAbsPos();
        sleep(1);
    }

    L6470_GoMark();
    for(int i= 0; i<12; i++){
	pos = L6470_GetAbsPos();
        sleep(1);
    }

    L6470_HiZSoft();
    
    return 0;
}
