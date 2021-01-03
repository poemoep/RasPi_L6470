#include <stdio.h>
#include <unistd.h>

#include "L6470.h"
//#include "L6470_user.h"

int main(int argc, char** argv)
{

	printf("sizeof(int): %d\n",sizeof(int));
    L6470_init();

    L6470_MoveCont(DIR_RVS, 2000);
    sleep(10);
    L6470_MoveCont(DIR_RVS, 4000);
    sleep(10);
    L6470_MoveCont(DIR_RVS, 6000);
    sleep(10);
    L6470_MoveCont(DIR_RVS, 8000);
    sleep(10);
    
    L6470_StopSoft();
    sleep(10);

    L6470_MoveCont(DIR_FWD, 2000);
    sleep(10);
    L6470_StopSoft();
    sleep(10);
    
    
    for (int i =0; i <10; i++){
        L6470_MoveStepClock(DIR_FWD);
        sleep(1);
        L6470_MoveStepClock(DIR_RVS);
        sleep(1);
    }
    sleep(3);

    for(int i = 0; i<10; i++){
        L6470_MoveStep(DIR_FWD,200);
        sleep(1);
        L6470_MoveStep(DIR_RVS,200);
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
