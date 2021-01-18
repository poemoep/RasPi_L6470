#include <stdio.h>
#include "L6470.h"

int main (int argc, char* argv)
{
    output_header();
    output_footer();

    return 0

}

int output_header()
{
    char* header = \
"#include \"L6470.h\" \

#ifndef __L6470_USER_HEADER__ \
#define __L6470_USER_HEADER__ \

//#define L6470_DAISY_CHAIN  \
#define L6470_SPI_CH 0  // 0 or 1 \
#define SPI_SPEED 1000000 // [Hz] \

#if defined (L6470_DAISY_CHAIN) \
#define L6470_DEV_NUM 2 \ 
#endif \
\
const union L6470_packet L6470_user_setting[PARAM_NUM] = \
{// L6470_PARAM_addr,     setting[2],setting[1],setting[0]} //reset_val \
//Left justified, MSB first" \
"";

printf("%s\n",header);

return 0;
}

int output_footer()
{
    char* footer = \
'    //Dummy READONLY param &  RESERVED param
    {L6470_param[enum_L6470_SPEED].addr,         0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_ADC_OUT].addr,       0x00,   0x00,   0x00}, //dummy
    {L6470_param[enum_L6470_STATUS].addr,        0x00,   0x00,   0x00}//, //dummy
//    {L6470_param[enum_L6470_RESERVED_h1A].addr,  0x00,   0x00,   0x00}, //dummy
//    {L6470_param[enum_L6470_RESERVED_h1B].addr,  0x00,   0x00,   0x00}, //dummy

};

#endif
';

printf("%s\n", footer);

return 0
}

int output_param(union L6470_packet pkt)
{



}