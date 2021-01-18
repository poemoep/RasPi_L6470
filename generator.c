#include <stdio.h>
#include "L6470.h"


int output_header(void);
int output_footer(void);

int main (int argc, char* argv)
{
    output_header();
    output_footer();

    return 0;

}

int output_header()
{
printf("#include \"L6470.h\"\n");
printf("#ifndef __L6470_USER_HEADER__\n");
printf("#define __L6470_USER_HEADER__\n");

printf("//#define L6470_DAISY_CHAIN\n");
printf("#define L6470_SPI_CH 0  // 0 or 1\n");
printf("#define SPI_SPEED 1000000 // [Hz]\n");

printf("#if defined (L6470_DAISY_CHAIN)\n"); 
printf("#define L6470_DEV_NUM 2\n");
printf("#endif\n");
\
printf("const union L6470_packet L6470_user_setting[PARAM_NUM] =\n");
printf("{// L6470_PARAM_addr,     setting[2],setting[1],setting[0]} //reset_val\n");
printf("//Left justified, MSB first\n");
printf("\n");


return 0;
}

int output_footer()
{
printf("    //Dummy READONLY param &  RESERVED param\n");
printf("    {L6470_param[enum_L6470_SPEED].addr,         0x00,   0x00,   0x00}, //dummy\n");
printf("    {L6470_param[enum_L6470_ADC_OUT].addr,       0x00,   0x00,   0x00}, //dummy\n");
printf("    {L6470_param[enum_L6470_STATUS].addr,        0x00,   0x00,   0x00}//, //dummy\n");
printf("//    {L6470_param[enum_L6470_RESERVED_h1A].addr,  0x00,   0x00,   0x00}, //dummy\n");
printf("//    {L6470_param[enum_L6470_RESERVED_h1B].addr,  0x00,   0x00,   0x00}, //dummy\n");
printf("\n");
printf("};\n");

printf("#endif\n");


return 0;
}

int output_param(union L6470_packet pkt)
{



}