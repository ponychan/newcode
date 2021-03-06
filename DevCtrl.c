/*======================================
红灯与绿灯只需要设置输出方向和高低电平
========================================*/
//LED 红P2.2  绿P2.1
#define PHY_LEDG_PxOUT        P2OUT      // ==输出电平的定义
#define PHY_LEDG_PxDIR        P2DIR      //==输出或输入方向的定义
#define PHY_LEDG_PxIN         BIT1       //==红灯管脚定义

#define PHY_LEDR_PxOUT        P2OUT
#define PHY_LEDR_PxDIR        P2DIR
#define PHY_LEDR_PxIN         BIT2


/****************************************************************************/
/*	Set Green light   control  控制 Green LED								*/
/*	用到的MCU管脚 :   P2.1												   */
/*	控制作用	  :   控制绿灯，Off关闭，On开启 							*/
/****************************************************************************/
void LedGreenOn(void)
{
	PHY_LEDG_PxDIR |= PHY_LEDG_PxIN;   
	PHY_LEDG_PxOUT |= PHY_LEDG_PxIN;	   
}

void LedGreenOff(void)
{
	PHY_LEDG_PxDIR |= PHY_LEDG_PxIN;   
	PHY_LEDG_PxOUT &= ~PHY_LEDG_PxIN;	 
	
}
/****************************************************************************/
/*	Set Red light  control	控制Red LED 									*/
/*	用到的MCU管脚 :   P2.2													*/
/*	控制作用	  :   控制红灯，Off关闭，On开启 							*/
/****************************************************************************/

void LedRedOn(void)
{
	PHY_LEDR_PxDIR |= PHY_LEDR_PxIN;   
	PHY_LEDR_PxOUT |= PHY_LEDR_PxIN;	  
}

void LedRedOff(void)
{
	PHY_LEDR_PxDIR |= PHY_LEDR_PxIN;   
	PHY_LEDR_PxOUT &= ~PHY_LEDR_PxIN;
}