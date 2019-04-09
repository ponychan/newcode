#include<msp430.h>
#include"ClockSet.c"
#include"PinDefine.h"
#include"RF.c"

void InitSystem(void){
    LowPowerPinInit();
    //SMCLK时钟选择
     g_uchPHYSMclkSel = PHY_SMCLK_DCO;      //子系统时钟SMCLK选择DCO;
    //SMCLK时钟频率设定
     g_uchPHYSMclkSet = PHY_SMCLK_4200KHZ;  //SMCLK时钟频率设定为4.2MHZ;
     InitClk();
     HWResetRF();	            //射频硬件复位
}

void main(void){
    InitSystem();
}

