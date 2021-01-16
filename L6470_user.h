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
    {L6470_param[enum_L6470_ABS_POS].addr,       0x00,   0x00,   0x00}, //0x000000
    {L6470_param[enum_L6470_EL_POS].addr,        0x00,   0x00,   0x00}, //0x000
    {L6470_param[enum_L6470_MARK].addr,          0x00,   0x00,   0x00}, //0x000000
    {L6470_param[enum_L6470_ACC].addr,           0x00,   0x8A,   0x00}, //0x08A
    {L6470_param[enum_L6470_DEC].addr,           0x00,   0x8A,   0x00}, //0x08A
    {L6470_param[enum_L6470_MAX_SPEED].addr,     0x00,   0x41,   0x00}, //0x041
    {L6470_param[enum_L6470_MIN_SPEED].addr,     0x00,   0x00,   0x00}, //0x000
    {L6470_param[enum_L6470_KVAL_HOLD].addr,     0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_KVAL_RUN].addr,      0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_KVAL_ACC].addr,      0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_KVAL_DEC].addr,      0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_INT_SPEED].addr,     0x04,   0x08,   0x00}, //0x0408
    {L6470_param[enum_L6470_ST_SLP].addr,        0x19,   0x00,   0x00}, //0x19 
    {L6470_param[enum_L6470_FN_SLP_ACC].addr,    0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_FN_SLP_DEC].addr,    0x29,   0x00,   0x00}, //0x29
    {L6470_param[enum_L6470_K_THERM].addr,       0x00,   0x00,   0x00}, //0x0
    {L6470_param[enum_L6470_OCD_TH].addr,        0x08,   0x00,   0x00}, //0x8
    {L6470_param[enum_L6470_STALL_TH].addr,      0x40,   0x00,   0x00}, //0x40
    {L6470_param[enum_L6470_FS_SPD].addr,        0x00,   0x27,   0x00}, //0x027
    {L6470_param[enum_L6470_STEP_MODE].addr,     0x00,   0x07,   0x00}, //0x07
    {L6470_param[enum_L6470_ALARM_EN].addr,      0xFF,   0x00,   0x00}, //0xFF
    {L6470_param[enum_L6470_CONFIG].addr,        0x2E,   0x88,   0x00}, //0x2E88
    //Dummy READONLY param &  RESERVED param
    {L6470_param[enum_L6470_SPEED].addr,         0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_ADC_OUT].addr,       0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_STATUS].addr,        0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_RESERVED_h1A].addr,  0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_RESERVED_h1B].addr,  0x00,   0x00,   0x00}, //dummy

};

#endif
