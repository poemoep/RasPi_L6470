#include "L6470.h"
#ifndef __L6470_USER_HEADER__
#define __L6470_USER_HEADER__
//#define L6470_DAISY_CHAIN
#define L6470_SPI_CH 0  // 0 or 1
#define SPI_SPEED 1000000 // [Hz]
#if defined (L6470_DAISY_CHAIN)
#define L6470_DEV_NUM 2
#endif
const union L6470_packet L6470_user_setting[PARAM_NUM] =
{// L6470_PARAM_addr,     setting[2],setting[1],setting[0]} //reset_val
//Left justified, MSB first

[L6470 DEBUG]:  Caution abs_pos is over/under flow
    {	0x01,	0x05,	0x03,	0x4f},
[L6470 DEBUG]:  Caution step is selected STEP_ePOS_90deg.
[L6470 DEBUG]:  Caution el_step is selected 67
    {	0x02,	0x00,	0xc3,	0x00},
    {	0x03,	0x1f,	0xff,	0xff},
[L6470 DEBUG]:  Caution ACC step_per_ss is more than equal 1455 [x0.01 step/s^2]
[L6470 DEBUG]:  Caution set minumum value.
    {	0x05,	0x00,	0x01,	0x00},
[L6470 DEBUG]:  Caution DEC step_per_ss is more than equal 1455 [x0.01 step/s^2]
[L6470 DEBUG]:  Caution set minumum value.
    {	0x06,	0x00,	0x01,	0x00},
[L6470 DEBUG]:  Caution MAX_SPEED is rounded to 398670 [x0.01 step/s]
    {	0x07,	0x01,	0x12,	0x00},
    {	0x00,	0x00,	0x00,	0x00},
[L6470 DEBUG]:  Caution percentage is round to 76[%]
    {	0x09,	0x4c,	0x00,	0x00},
[L6470 DEBUG]:  Caution percentage is round to 127[%]
    {	0x0a,	0x7f,	0x00,	0x00},
    {	0x0b,	0xcc,	0x00,	0x00},
[L6470 DEBUG]:  Caution percentage is round to 229[%]
    {	0x0c,	0xe5,	0x00,	0x00},
[L6470 DEBUG]:  Caution INT_SPEED is rounded to 0 [x0.0001 step/s] 
    {	0x0d,	0x00,	0x00,	0x00},
[L6470 DEBUG]:  Caution ST_SLP is rounded to 90 [x0.000001] 
    {	0x0e,	0x06,	0x00,	0x00},
    {	0x0f,	0x02,	0x00,	0x00},
[L6470 DEBUG]:  Caution FN_SLP_DEC is rounded to 90 [x0.000001]
    {	0x10,	0x06,	0x00,	0x00},
[L6470 DEBUG]:  Caution K_THERM is rounded to 28126 [x0.00001]
    {	0x11,	0x09,	0x00,	0x00},
    {	0x13,	0x07,	0x00,	0x00},
    {	0x14,	0x00,	0x00,	0x00},
[L6470 DEBUG]:  Caution FS_SPD is rounded to 762 [x0.01 step/s]
    {	0x15,	0x00,	0x00,	0x00},
[L6470 DEBUG]:  Caution sync_sel is less than equal step_sel.
    {	0x16,	0x00,	0x00,	0xe7},
    {	0x17,	0xff,	0x00,	0x00},
    {	0x18,	0xd8,	0xbb,	0x00},
    //Dummy READONLY param &  RESERVED param
    {L6470_param[enum_L6470_SPEED].addr,         0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_ADC_OUT].addr,       0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_STATUS].addr,        0x00,   0x00,   0x00}//, //dummy
//    {L6470_param[enum_L6470_RESERVED_h1A].addr,  0x00,   0x00,   0x00}, //dummy
//    {L6470_param[enum_L6470_RESERVED_h1B].addr,  0x00,   0x00,   0x00}, //dummy

};
#endif
