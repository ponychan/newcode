/*======================================
������̵�ֻ��Ҫ�����������͸ߵ͵�ƽ
========================================*/
//LED ��P2.2  ��P2.1
#define PHY_LEDG_PxOUT        P2OUT      // ==�����ƽ�Ķ���
#define PHY_LEDG_PxDIR        P2DIR      //==��������뷽��Ķ���
#define PHY_LEDG_PxIN         BIT1       //==��ƹܽŶ���

#define PHY_LEDR_PxOUT        P2OUT
#define PHY_LEDR_PxDIR        P2DIR
#define PHY_LEDR_PxIN         BIT2


/****************************************************************************/
/*	Set Green light   control  ���� Green LED								*/
/*	�õ���MCU�ܽ� :   P2.1												   */
/*	��������	  :   �����̵ƣ�Off�رգ�On���� 							*/
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
/*	Set Red light  control	����Red LED 									*/
/*	�õ���MCU�ܽ� :   P2.2													*/
/*	��������	  :   ���ƺ�ƣ�Off�رգ�On���� 							*/
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