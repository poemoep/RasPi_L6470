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

    {{	0x01,	{0x0f,	0xb9,	0x8f}}},
    {{	0x02,	{0x00,	0xbf,	0x00}}},
    {{	0x03,	{0xfc,	0x6b,	0xb9}}},
    {{0x04,         {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution ACC is rounded to 803160 [x0.01 step/s^2]
    {{	0x05,	{0x02,	0x28,	0x00}}},
// [L6470 DEBUG]:  Caution DEC is rounded to 200790 [x0.01 step/s^2]
    {{	0x06,	{0x00,	0x8a,	0x00}}},
// [L6470 DEBUG]:  Caution MAX_SPEED is rounded to 1561600 [x0.01 step/s]
    {{	0x07,	{0x04,	0x00,	0x00}}},
    {{	0x08,	{0x00,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 1607[0.01%]
    {{	0x09,	{0x29,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 3019[0.01%]
    {{	0x0a,	{0x4d,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0b,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0c,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution INT_SPEED is rounded to 1000088 [x0.0001 step/s] 
    {{	0x0d,	{0x06,	0x8e,	0x00}}},
    {{	0x0e,	{0x19,	0x00,	0x00}}},
    {{	0x0f,	{0x29,	0x00,	0x00}}},
    {{	0x10,	{0x29,	0x00,	0x00}}},
    {{	0x11,	{0x00,	0x00,	0x00}}},
    {{0x12,       {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution OCD_TH is rounded to 3375 [mA]
    {{	0x13,	{0x08,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution STALL_TH is rounded to 203125 [x0.01 mA]
    {{	0x14,	{0x40,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution FS_SPD is rounded to 1562362 [x0.01 step/s]
    {{	0x15,	{0x04,	0x00,	0x00}}},
    {{	0x16,	{0x02,	0x00,	0x00}}},
    {{	0x17,	{0xff,	0x00,	0x00}}},
    {{	0x18,	{0x2f,	0x88,	0x00}}},
    {{0x19,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1A].addr,  {0x00,   0x00,   0x00}}}, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1B].addr,  {0x00,   0x00,   0x00}}}, //dummy

};
#endif
#if 0
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

    {{	0x01,	{0x0f,	0xb9,	0x8f}}},
    {{	0x02,	{0x00,	0xbf,	0x00}}},
    {{	0x03,	{0xfc,	0x6b,	0xb9}}},
    {{0x04,         {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution ACC is rounded to 803160 [x0.01 step/s^2]
    {{	0x05,	{0x02,	0x28,	0x00}}},
// [L6470 DEBUG]:  Caution DEC is rounded to 200790 [x0.01 step/s^2]
    {{	0x06,	{0x00,	0x8a,	0x00}}},
// [L6470 DEBUG]:  Caution MAX_SPEED is rounded to 1561600 [x0.01 step/s]
    {{	0x07,	{0x04,	0x00,	0x00}}},
    {{	0x08,	{0x00,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 1607[0.01%]
    {{	0x09,	{0x29,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 3019[0.01%]
    {{	0x0a,	{0x4d,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0b,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0c,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution INT_SPEED is rounded to 1000088 [x0.0001 step/s] 
    {{	0x0d,	{0x06,	0x8e,	0x00}}},
    {{	0x0e,	{0x19,	0x00,	0x00}}},
    {{	0x0f,	{0x29,	0x00,	0x00}}},
    {{	0x10,	{0x29,	0x00,	0x00}}},
    {{	0x11,	{0x00,	0x00,	0x00}}},
    {{0x12,       {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution OCD_TH is rounded to 3375 [mA]
    {{	0x13,	{0x08,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution STALL_TH is rounded to 203125 [x0.01 mA]
    {{	0x14,	{0x40,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution FS_SPD is rounded to 1562362 [x0.01 step/s]
    {{	0x15,	{0x04,	0x00,	0x00}}},
    {{	0x16,	{0x02,	0x00,	0x00}}},
    {{	0x17,	{0xff,	0x00,	0x00}}},
    {{	0x18,	{0x2f,	0x88,	0x00}}},
    {{0x19,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1A].addr,  {0x00,   0x00,   0x00}}}, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1B].addr,  {0x00,   0x00,   0x00}}}, //dummy

};
#endif
#if 0
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

    {{	0x01,	{0x0f,	0xb9,	0x8f}}},
    {{	0x02,	{0x00,	0xbf,	0x00}}},
    {{	0x03,	{0xfc,	0x6b,	0xb9}}},
    {{0x04,         {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution ACC is rounded to 803160 [x0.01 step/s^2]
    {{	0x05,	{0x02,	0x28,	0x00}}},
// [L6470 DEBUG]:  Caution DEC is rounded to 200790 [x0.01 step/s^2]
    {{	0x06,	{0x00,	0x8a,	0x00}}},
// [L6470 DEBUG]:  Caution MAX_SPEED is rounded to 1561600 [x0.01 step/s]
    {{	0x07,	{0x04,	0x00,	0x00}}},
    {{	0x08,	{0x00,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 1607[0.01%]
    {{	0x09,	{0x29,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 3019[0.01%]
    {{	0x0a,	{0x4d,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0b,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0c,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution INT_SPEED is rounded to 1000088 [x0.0001 step/s] 
    {{	0x0d,	{0x06,	0x8e,	0x00}}},
    {{	0x0e,	{0x19,	0x00,	0x00}}},
    {{	0x0f,	{0x29,	0x00,	0x00}}},
    {{	0x10,	{0x29,	0x00,	0x00}}},
    {{	0x11,	{0x00,	0x00,	0x00}}},
    {{0x12,       {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution OCD_TH is rounded to 3375 [mA]
    {{	0x13,	{0x08,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution STALL_TH is rounded to 203125 [x0.01 mA]
    {{	0x14,	{0x40,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution FS_SPD is rounded to 1562362 [x0.01 step/s]
    {{	0x15,	{0x04,	0x00,	0x00}}},
    {{	0x16,	{0x02,	0x00,	0x00}}},
    {{	0x17,	{0xff,	0x00,	0x00}}},
    {{	0x18,	{0x2f,	0x88,	0x00}}},
    {{0x19,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1A].addr,  {0x00,   0x00,   0x00}}}, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1B].addr,  {0x00,   0x00,   0x00}}}, //dummy

};
#endif
#if 0
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

    {{	0x01,	{0x0f,	0xb9,	0x8f}}},
    {{	0x02,	{0x00,	0xbf,	0x00}}},
    {{	0x03,	{0xfc,	0x6b,	0xb9}}},
    {{0x04,         {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution ACC is rounded to 803160 [x0.01 step/s^2]
    {{	0x05,	{0x02,	0x28,	0x00}}},
// [L6470 DEBUG]:  Caution DEC is rounded to 200790 [x0.01 step/s^2]
    {{	0x06,	{0x00,	0x8a,	0x00}}},
// [L6470 DEBUG]:  Caution MAX_SPEED is rounded to 1561600 [x0.01 step/s]
    {{	0x07,	{0x04,	0x00,	0x00}}},
    {{	0x08,	{0x00,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 1607[0.01%]
    {{	0x09,	{0x29,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 3019[0.01%]
    {{	0x0a,	{0x4d,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0b,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0c,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution INT_SPEED is rounded to 1000088 [x0.0001 step/s] 
    {{	0x0d,	{0x06,	0x8e,	0x00}}},
    {{	0x0e,	{0x19,	0x00,	0x00}}},
    {{	0x0f,	{0x29,	0x00,	0x00}}},
    {{	0x10,	{0x29,	0x00,	0x00}}},
    {{	0x11,	{0x00,	0x00,	0x00}}},
    {{0x12,       {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution OCD_TH is rounded to 3375 [mA]
    {{	0x13,	{0x08,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution STALL_TH is rounded to 203125 [x0.01 mA]
    {{	0x14,	{0x40,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution FS_SPD is rounded to 1562362 [x0.01 step/s]
    {{	0x15,	{0x04,	0x00,	0x00}}},
    {{	0x16,	{0x02,	0x00,	0x00}}},
    {{	0x17,	{0xff,	0x00,	0x00}}},
    {{	0x18,	{0x2f,	0x88,	0x00}}},
    {{0x19,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1A].addr,  {0x00,   0x00,   0x00}}}, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1B].addr,  {0x00,   0x00,   0x00}}}, //dummy

};
#endif
#if 0
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

    {{	0x01,	{0x0f,	0xb9,	0x8f}}},
    {{	0x02,	{0x00,	0xbf,	0x00}}},
    {{	0x03,	{0xfc,	0x6b,	0xb9}}},
    {{0x04,         {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution ACC is rounded to 803160 [x0.01 step/s^2]
    {{	0x05,	{0x02,	0x28,	0x00}}},
// [L6470 DEBUG]:  Caution DEC is rounded to 200790 [x0.01 step/s^2]
    {{	0x06,	{0x00,	0x8a,	0x00}}},
// [L6470 DEBUG]:  Caution MAX_SPEED is rounded to 1561600 [x0.01 step/s]
    {{	0x07,	{0x04,	0x00,	0x00}}},
    {{	0x08,	{0x00,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 1607[0.01%]
    {{	0x09,	{0x29,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 3019[0.01%]
    {{	0x0a,	{0x4d,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0b,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution percentage is round to 39[0.01%]
    {{	0x0c,	{0x01,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution INT_SPEED is rounded to 1000088 [x0.0001 step/s] 
    {{	0x0d,	{0x06,	0x8e,	0x00}}},
    {{	0x0e,	{0x19,	0x00,	0x00}}},
    {{	0x0f,	{0x29,	0x00,	0x00}}},
    {{	0x10,	{0x29,	0x00,	0x00}}},
    {{	0x11,	{0x00,	0x00,	0x00}}},
    {{0x12,       {0x00,   0x00,   0x00}}}, //dummy
// [L6470 DEBUG]:  Caution OCD_TH is rounded to 3375 [mA]
    {{	0x13,	{0x08,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution STALL_TH is rounded to 203125 [x0.01 mA]
    {{	0x14,	{0x40,	0x00,	0x00}}},
// [L6470 DEBUG]:  Caution FS_SPD is rounded to 1562362 [x0.01 step/s]
    {{	0x15,	{0x04,	0x00,	0x00}}},
    {{	0x16,	{0x07,	0x00,	0x00}}},
    {{	0x17,	{0xff,	0x00,	0x00}}},
    {{	0x18,	{0x2f,	0x88,	0x00}}},
    {{0x19,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1A].addr,  {0x00,   0x00,   0x00}}}, //dummy
//    {{L6470_param[enum_L6470_RESERVED_h1B].addr,  {0x00,   0x00,   0x00}}}, //dummy

};
#endif
#if 0

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
    {{REG_ABS_POS,       {0x00,   0x00,   0x00}}}, //0x000000
    {{REG_EL_POS,        {0x00,   0x00,   0x00}}}, //0x000
    {{REG_MARK,          {0x00,   0x00,   0x00}}}, //0x000000
    {{REG_SPEED,         {0x00,   0x00,   0x00}}}, //dummy
    {{REG_ACC,           {0x00,   0x8A,   0x00}}}, //0x08A
    {{REG_DEC,           {0x00,   0x8A,   0x00}}}, //0x08A
    {{REG_MAX_SPEED,     {0x00,   0x41,   0x00}}}, //0x041
    {{REG_MIN_SPEED,     {0x00,   0x00,   0x00}}}, //0x000
    {{REG_KVAL_HOLD,     {0x29,   0x00,   0x00}}}, //0x29
    {{REG_KVAL_RUN,      {0x29,   0x00,   0x00}}}, //0x29
    {{REG_KVAL_ACC,      {0x29,   0x00,   0x00}}}, //0x29
    {{REG_KVAL_DEC,      {0x29,   0x00,   0x00}}}, //0x29
    {{REG_INT_SPEED,     {0x04,   0x08,   0x00}}}, //0x0408
    {{REG_ST_SLP,        {0x19,   0x00,   0x00}}}, //0x19 
    {{REG_FN_SLP_ACC,    {0x29,   0x00,   0x00}}}, //0x29
    {{REG_FN_SLP_DEC,    {0x29,   0x00,   0x00}}}, //0x29
    {{REG_K_THERM,       {0x00,   0x00,   0x00}}}, //0x0
    {{REG_ADC_OUT,       {0x00,   0x00,   0x00}}}, //dummy
    {{REG_OCD_TH,        {0x08,   0x00,   0x00}}}, //0x8
    {{REG_STALL_TH,      {0x40,   0x00,   0x00}}}, //0x40
    {{REG_FS_SPD,        {0x00,   0x27,   0x00}}}, //0x027
    {{REG_STEP_MODE,     {0x07,   0x00,   0x00}}}, //0x07
    {{REG_ALARM_EN,      {0xFF,   0x00,   0x00}}}, //0xFF
    {{REG_CONFIG,        {0x2E,   0x88,   0x00}}}, //0x2E88
    {{REG_STATUS,        {0x00,   0x00,   0x00}}}//, //dummy
//    {{REG_RESERVED_h1A,  {0x00,   0x00,   0x00}}}, //dummy
//    {{REG_RESERVED_h1B,  {0x00,   0x00,   0x00}}}, //dummy

};

#endif

#endif
#endif
#endif
#endif
#endif
