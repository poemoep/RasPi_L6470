#include <stdio.h>
#include "L6470.h"
#include "generator.h"

int output_header(void);
int output_footer(void);
int print_pkt(union L6470_packet pkt);

int main (int argc, char** argv)
{
    output_header();


    print_pkt(gen_ABS_POS(USER_ABS_POS));
    print_pkt(gen_EL_POS(USER_EL_POS));
    print_pkt(gen_MARK(USER_MARK));
    print_pkt(gen_ACC(USER_ACC));
    print_pkt(gen_DEC(USER_DEC));
    print_pkt(gen_MAX_SPEED(USER_MAX_SPEED));
    print_pkt(gen_MIN_SPEED(USER_MIN_SPEED));
    print_pkt(gen_KVAL_HOLD(USER_KVAL_HOLD));
    print_pkt(gen_KVAL_RUN(USER_KVAL_RUN));
    print_pkt(gen_KVAL_ACC(USER_KVAL_ACC));
    print_pkt(gen_KVAL_DEC(USER_KVAL_DEC));
    print_pkt(gen_INT_SPEED(USER_INT_SPEED));
    print_pkt(gen_ST_SLP(USER_ST_SLP));
    print_pkt(gen_FN_SLP_ACC(USER_FN_SLP_ACC));
    print_pkt(gen_FN_SLP_DEC(USER_FN_SLP_DEC));
    print_pkt(gen_K_THERM(USER_K_THERM));
    print_pkt(gen_OCD_TH(USER_OCD_TH));
    print_pkt(gen_STALL_TH(USER_STALL_TH));
    print_pkt(gen_FS_SPD(USER_FS_SPD));
    print_pkt(gen_STEP_MODE(USER_STEP_MODE));
    print_pkt(gen_ALARM_EN(USER_ALARM_EN));
    print_pkt(gen_CONFIG(USER_CONFIG));

    output_footer();

    return 0;

}

int print_pkt(union L6470_packet pkt)
{
    printf("    {{\t0x%02x,\t{0x%02x,\t0x%02x,\t0x%02x}}},\n",pkt.value8b[0], pkt.value8b[1], pkt.value8b[2], pkt.value8b[3]);
    return 0;
}

int output_header()
{
printf("#include \"L6470.h\"\n");
printf("#ifndef __L6470_USER_HEADER__\n");
printf("#define __L6470_USER_HEADER__\n");
printf("\n");
printf("//#define L6470_DAISY_CHAIN\n");
printf("#define L6470_SPI_CH 0  // 0 or 1\n");
printf("#define SPI_SPEED 1000000 // [Hz]\n");
printf("\n");
printf("#if defined (L6470_DAISY_CHAIN)\n"); 
printf("#define L6470_DEV_NUM 2\n");
printf("#endif\n");
printf("\n");
printf("const union L6470_packet L6470_user_setting[PARAM_NUM] =\n");
printf("{// L6470_PARAM_addr,     setting[2],setting[1],setting[0]} //reset_val\n");
printf("//Left justified, MSB first\n");
printf("\n");


return 0;
}

int output_footer()
{
printf("    //Dummy READONLY param &  RESERVED param\n");
printf("    {0x04,         0x00,   0x00,   0x00}, //dummy\n");
printf("    {0x12,       0x00,   0x00,   0x00}, //dummy\n");
printf("    {0x19,        0x00,   0x00,   0x00}//, //dummy\n");
printf("//    {L6470_param[enum_L6470_RESERVED_h1A].addr,  0x00,   0x00,   0x00}, //dummy\n");
printf("//    {L6470_param[enum_L6470_RESERVED_h1B].addr,  0x00,   0x00,   0x00}, //dummy\n");
printf("\n");
printf("};\n");

printf("#endif\n");


return 0;
}
