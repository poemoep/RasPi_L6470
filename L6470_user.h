#include "L6470.h"

#ifndef __L6470_USER_HEADER__
#define __L6470_USER_HEADER__


#define SPI_CH 0 
#define SPI_SPEED 1000000 // [Hz]
#define SPI_MODE 0 // default

const union L6470_packet L6470_setting[22] =
{// REG_ADDR,     setting[0],setting[1],setting[2])
    {REG_ABS_POS,       0x000000}, //0x000000
    {REG_EL_POS,        0x000}, //0x000
    {REG_MARK,          0x000000}, //0x000000
    {REG_ACC,           0x08A}, //0x08A
    {REG_DEC,           0x08A}, //0x08A
    {REG_MAX_SPEED,     0x041}, //0x041
    {REG_MIN_SPEED,     0x000}, //0x000
    {REG_KVAL_HOLD,     0x29}, //0x29
    {REG_KVAL_RUN,      0x29}, //0x29
    {REG_KVAL_ACC,      0x29}, //0x29
    {REG_KVAL_DEC,      0x29}, //0x29
    {REG_INT_SPEED,     0x0408}, //0x0408
    {REG_ST_SLP,        0x19}, //0x19 
    {REG_FN_SLP_ACC,    0x29}, //0x29
    {REG_FN_SLP_DEC,    0x29}, //0x29
    {REG_K_THERM,       0x0}, //0x0
    {REG_OCD_TH,        0x8}, //0x8
    {REG_STALL_TH,      0x40}, //0x40
    {REG_FS_SPD,        0x027}, //0x027
    {REG_STEP_MODE,     0x07}, //0x07
    {REG_ALARM_EN,      0xFF}, //0xFF
    {REG_CONFIG,        0x2E88}  //0x2E88
};
#define L6470_setting_bits 0 //whith col has bits info
#define L6470_setting_reg_addr 0

#endif
