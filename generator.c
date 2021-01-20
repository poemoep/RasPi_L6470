#include <stdio.h>
#include "L6470.h"


int output_header(void);
int output_footer(void);

int main (int argc, char* argv)
{
    output_header();

    print_pkt(gen_ABS_POS(0));
    print_pkt(gen_EL_POS(STEP_ePOS_0deg | 0));
    print_pkt(gen_MARK(0));
    print_pkt(gen_ACC(300));
    print_pkt(gen_DEC(400));
    print_pkt(gen_MAX_SPEED(400000));
    print_pkt(gen_MIN_SPEED(1 | ENABLE_LSPD));
    print_pkt(gen_KVAL_HOLD(30));
    print_pkt(gen_KVAL_RUN(50));
    print_pkt(gen_KVAL_ACC(80));
    print_pkt(gen_KVAL_DEC(90));
    print_pkt(gen_INT_SPEED(30));
    print_pkt(gen_ST_SLP(100));
    print_pkt(gen_FN_SLP_ACC(30));
    print_pkt(gen_FN_SLP_DEC(100));
    print_pkt(gen_K_THERM(30000));
    print_pkt(gen_OCD_TH(3000));
    print_pkt(gen_STALL_TH(3125));
    print_pkt(gen_FS_SPD(0));
    print_pkt(gen_STEP_MODE(SYNC_EN | SYNC_FFS_32TIMES | STEP_128DIV));
    print_pkt(gen_ALARM_EN(ALM_FULL));
    print_pkt(gen_CONFIG(F_PWM_INT(0b110) | F_PWM_DEC(0b110) | POW_SR_VFAST | ENABLE_OC_SD | ENABLE_VSCOMP 
                        |DISABLE_SW_STOPHARD_IRQ |USE_INTCLK_16M | USE_CLKOUT_16M));


    output_footer();

    return 0;

}

int print_pkt(union L6470_packet pkt)
{
    printf("    {\t0x%02x,\t0x%02x,\t0x%02x,\t0x%02x},\n",pkt.value8b[0], pkt.value8b[1], pkt.value8b[2], pkt.value8b[3]);
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