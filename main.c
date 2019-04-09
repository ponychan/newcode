#include<msp430.h>
#include"ClockSet.c"
#include"PinDefine.h"
#include"RF.c"

void InitSystem(void){
    LowPowerPinInit();
    //SMCLKʱ��ѡ��
     g_uchPHYSMclkSel = PHY_SMCLK_DCO;      //��ϵͳʱ��SMCLKѡ��DCO;
    //SMCLKʱ��Ƶ���趨
     g_uchPHYSMclkSet = PHY_SMCLK_4200KHZ;  //SMCLKʱ��Ƶ���趨Ϊ4.2MHZ;
     InitClk();
     HWResetRF();	            //��ƵӲ����λ
}

void main(void){
    InitSystem();
}

