#include <stdio.h>
#include <unistd.h>

#include "L6470.h"
//#include "L6470_user.h"

int main(int argc, char** argv)
{
/*
    for (int i=0; i< 22;i++){
	 printf("REG:%x\t value:%x\t%x\t%x\n",
			 L6470_setting[i]->value8b[0],
			 L6470_setting[i]->value8b[1],
			 L6470_setting[i]->value8b[2],
			 L6470_setting[i]->value8b[3]);
 	} */

    L6470_init();

    L6470_MoveCont(DIR_FWD, 10000);
    sleep(3);

    L6470_StopSoft();

    for (int i =0; i <10; i++){
        L6470_MoveStepClock(DIR_RVS);
        sleep(0.5);
    }
    sleep(3);

    for(int i = 0; i<10; i++){
        L6470_MoveStep(DIR_FWD,2000);
        sleep(1);
    }
    sleep(3);

    L6470_MoveGoTo(0);
    sleep(5);

    L6470_MoveGoToUntil(ACT_POS_TO_MARK,DIR_FWD,1000);
    sleep(10);

    L6470_HiZSoft();
    
    return 0;
}
