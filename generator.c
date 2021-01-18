#include <stdio.h>
#include "L6470.h"


int output_header(void);
int output_footer(void);

int main (int argc, char* argv)
{
    output_header();

print_pkt(gen_ABS_POS(int32_t abs_pos));
print_pkt(gen_EL_POS(uint8_t step, uint8_t el_step));
print_pkt(gen_MARK(int32_t mark));
print_pkt(gen_ACC(float step_per_ss));
print_pkt(gen_DEC(float step_per_ss));
print_pkt(gen_MAX_SPEED(float step_per_s));
print_pkt(gen_MIN_SPEED(float step_per_s, int16_t enable_LSPD));
print_pkt(gen_KVAL_HOLD(uint8_t kval));
print_pkt(gen_KVAL_RUN(uint8_t kval));
print_pkt(gen_KVAL_ACC(uint8_t kval));
print_pkt(gen_KVAL_DEC(uint8_t kval));
print_pkt(gen_INT_SPEED(float step_per_s));
print_pkt(gen_ST_SLP(float slp));
print_pkt(gen_FN_SLP_ACC(float slp_acc));
print_pkt(gen_FN_SLP_DEC(float slp_dec));
print_pkt(gen_K_THERM(float k_therm));
print_pkt(gen_OCD_TH(uint16_t ocd_th));
print_pkt(gen_STALL_TH(float stall_th));
print_pkt(gen_FS_SPD(float fs_spd));
print_pkt(gen_STEP_MODE(uint8_t sync_en, uint8_t sync_sel, uint8_t step_sel));
print_pkt(gen_ALARM_EN(uint8_t alm));
print_pkt(gen_CONFIG(uint8_t f_pwm_int, uint8_t f_pwm_dec, uint8_t pow_sr, uint8_t oc_sd, uint8_t en_vscomp, uint8_t sw_mode, uint8_t ext_clk, uint8_t osc_sel));




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