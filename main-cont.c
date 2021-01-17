#include <stdio.h>
#include <unistd.h>

#include "L6470.h"
//#include "L6470_user.h"

int main(int argc, char** argv)
{

    L6470_init();


    int pos_aim,pos;
   // L6470_MoveStepClock(DIR_RVS);
   L6470_MoveCont(DIR_RVS,40000);
    while(1)
    	{
 	    pos = L6470_GetAbsPos();
	    uint16_t hoge = L6470_GetStatus();
    	    sleep(1);
    }

    L6470_HiZSoft();
    
    return 0;
}
