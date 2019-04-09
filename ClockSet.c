
/*时钟分为MCLK 主系统时钟，CPU使用。SMCLK次主时钟，外设使用。ACLK辅助时钟*/
#define PHY_FLLN      127         //DCO内部数控振荡器倍频 4.2MHz
#define PHY_MCLK      4194304     //MCLK=((PHY_FLLN+1)*32768)=4194304
#define PHY_MCLK_1MS  4096        //((PHY_FLLN+1)*32768)/4096 = 1024

//SMCLK驱动
#define PHY_SMCLK_DCO   1
#define PHY_SMCLK_XT2   2
//SMCLK频率
#define PHY_SMCLK_4MHZ   1
#define PHY_SMCLK_4200KHZ   2
#define PHY_SMCLK_8MHZ   3

//ACLK频率
#define PHY_ACLK      32768     //辅助时钟
#define PHY_ACLK_1MS  32        // 32768/32 = 1024

#define EN_XT2CLK 1 //开启XT2时钟 
#define DIS_XT2CLK 0//关闭XT2时钟

//XT2时钟开启标志
unsigned char g_uchPHYXt2Flag = DIS_XT2CLK;

//SMCLK时钟选择
unsigned char g_uchPHYSMclkSel = PHY_SMCLK_DCO;     //SMCLK可以选择XT2（2），DCO（1）

//SMCLK时钟频率设定
unsigned char g_uchPHYSMclkSet = PHY_SMCLK_4MHZ;

/****************************************************************************/
/*低功耗模式下，没有用到的管脚的初始化,对整个系统中没有用到的管脚全部设置为高阻状态*/
/* 注意在程序在开始执行情况下，要对所有的管脚进行初始化状态,降低系统的功耗 */
/****************************************************************************/
void LowPowerPinInit(void)
{
     P1REN=0xFF; P2REN=0xFF;P3REN=0xFF; P4REN=0xFF;
     P5REN=0xFF;P6REN=0xFF; P7REN=0xFF; P8REN=0xFF;
     P9REN=0xFF;P10REN=0xFF;P11REN=0xFF;PJREN=0xFF;
     
     P1DIR = 0x00;P2DIR = 0x00;P3DIR = 0x00; P4DIR = 0x00;
     P5DIR = 0x00;P6DIR = 0x00;P7DIR = 0x00;P8DIR = 0x00;
     P9DIR = 0x00;P10DIR = 0x00;P11DIR = 0x00;PJDIR = 0x00;
  
     P1OUT = 0xFF;P2OUT = 0xFF;P3OUT = 0xFF;P4OUT = 0xFF;
     P5OUT = 0xFF;P6OUT = 0xFF;P7OUT = 0xFF;P8OUT = 0xFF;
     P9OUT = 0xFF;P10OUT = 0xFF;P11OUT = 0xFF;PJOUT = 0xFF;
}


/**********************************************************************/										 
/*初始化系统时钟DCO= MCLK = SMCLK ,XT1CLK=ACLK ,	关闭 XT2		  */
/**********************************************************************/
void SetDCOClk(void)
{  
	P5SEL &= ~0x0C; 			// Port Dis-select XT2
	P7SEL |= 0x03;				// Port select XT1
	
	UCSCTL6 &= ~XT1OFF; 	    // XT1 ON  
	UCSCTL6 |= XT2OFF;		    // Set XT2 Off
	
	UCSCTL6 |= (XT1DRIVE_3);   //XT1 drive strength
	UCSCTL6 &= ~(XT2DRIVE_3);  //XT2 drive strength  
	
	UCSCTL3 = SELREF_0; 	  // Set DCO FLL reference =xt1
	
	UCSCTL0 = 0x00; 			 // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_4;		 // Select DCO range
	UCSCTL2 = PHY_FLLN; 		 // Set DCO Multiplier for 4MHz
	// (N + 1) * FLLRef = Fdco
	// (122 + 1) * 32768 = 4030464 Hz
	
	//Set SMCLK =DCOCLK	//Set MCLK = DCOCLK	//Set ACLK = xt1
	UCSCTL4 = SELS_3 + SELM_3 + SELA_0; 
	do
	{
		UCSCTL7 &= ~(XT1LFOFFG +XT2OFFG +DCOFFG);
		// Clear XT2,XT1 default flags
		SFRIFG1 &= ~OFIFG;						// Clear fault flags
		for(unsigned int i=0;i<0xFFFF;i++); 	// Delay for Osc to stabilize
	}while (SFRIFG1&OFIFG); 				  // Test oscillator fault flag
	
	UCSCTL6 &= ~(XT1DRIVE_3);	        // Xtal is now stable, reduce drive strength
	g_uchPHYXt2Flag = DIS_XT2CLK;      //记录ST2时钟已关闭
}
/**********************************************************************/										 
/*		  设置系统时钟DCO =MCLK=4MHz,XT2 =SMCLK,xt2=ACLK			 */
/**********************************************************************/
void SetXT2ClkOn(void)
{  
	//如果XT2已经开启，则退出
	if(g_uchPHYXt2Flag == EN_XT2CLK )
		return;
	
	P5SEL |= 0x0C;				// Port select XT2
	P7SEL |= 0x03;				// Port select XT1
	
	UCSCTL6 &= ~XT1OFF; 	  // XT1 ON  
	UCSCTL6 &= ~XT2OFF; 	  // XT2 On  XT2 enabled in active mode (AM) through LPM4.
	
	UCSCTL6 |= (XT1DRIVE_3); //XT1 drive strength
	UCSCTL6 &= ~(XT2DRIVE_3);//XT2 drive strength  
	
	UCSCTL3 = SELREF_0; 	  // Set DCO FLL reference =xt1
	
	UCSCTL0 = 0x00; 			 // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_4;		 // Select DCO range
	UCSCTL2 = PHY_FLLN; 		 // Set DCO Multiplier for 4.2MHz
	// (N + 1) * FLLRef = Fdco
	// (122 + 1) * 32768 = 4030464 Hz
        //(127+1)*32768=4194304HZ   //ZK 在这里N设置成为了127
	
	//Set SMCLK =XT2CLK when available, otherwise DCOCLKDIV
	//Set MCLK = DCOCLK
	//Set ACLK = XT1
	UCSCTL4 = SELS_5 + SELM_3 + SELA_0;
	
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG+ DCOFFG );
		// Clear XT2,XT1 default flags
		SFRIFG1 &= ~OFIFG;						// Clear fault flags
		for(unsigned int i=0;i<0xFFFF;i++); 	// Delay for Osc to stabilize
	}while (SFRIFG1&OFIFG); 				  // Test oscillator fault flag
	
	g_uchPHYXt2Flag = EN_XT2CLK;//记录XT2已开启
}


/**********************************************************************/										 
/*		 根据宏定义选择不同的时钟系统								 */
/* PHY_SMCLK_DCO:DCO= MCLK = SMCLK ,XT1CLK=ACLK ,	 关闭 XT2		 */
/* PHY_SMCLK_XT2:DCO =MCLK=4MHz,XT2 =SMCLK,xt2=ACLK 				 */
/* 默认定义PHY_SMCLK_DCO											 */
/**********************************************************************/
//对系统整个时钟的设定，SMCLK通过选择，判断SMCLK时钟源
void InitClk(void)
{ 
	WDTCTL = WDTPW+WDTHOLD; 				  // Stop WDT 
	if(g_uchPHYSMclkSel == PHY_SMCLK_DCO)//如果选择内部振荡器
		SetDCOClk();                                      //系统时钟初始化
	else if(g_uchPHYSMclkSel==PHY_SMCLK_XT2)//选择外部高频晶振
		SetXT2ClkOn();                                   //设置系统时钟
	else//默认内部振荡器
		SetDCOClk();
    SFRIE1 = OFIE;    // Enable osc fault interrupt
}



/*以下三个分别为延时1毫秒、0.5毫秒、0.25毫秒的函数*/

/**********************************************************************/										 
/*		利用系统主时钟系统软件延时1/1024秒,约为1ms	      */
/**********************************************************************/
void PHYMCLKSoftDelay1ms(void)
{
	//1个时钟周期(1/PHY_MCLK)秒
	unsigned int i = (PHY_MCLK_1MS>>2);  /*PHY_MCLK_1MS>>2：时钟延时的1/4*/    
	while(--i);//4*i 个时钟周期 = 1/1024秒       /*一次while循环相当于执行4条指令*/
}


/**********************************************************************/										 
/*		利用系统主时钟系统软件延时1/2048秒,约为0.5ms	      */
/**********************************************************************/
void PHYMCLKSoftDelayHalfms(void)
{
	//1个时钟周期(1/PHY_MCLK)秒
	unsigned int i = (PHY_MCLK_1MS>>3);
	while(--i);//4*i 个时钟周期 = 1/2048秒
}

/**********************************************************************/										 
/*		利用系统主时钟系统软件延时1/4096秒,约为244us	      */
/**********************************************************************/
void PHYMCLKSoftDelay250us(void)
{
	//1个时钟周期(1/PHY_MCLK)秒
	unsigned int i = (PHY_MCLK_1MS>>4);
	while(--i);//4*i 个时钟周期 = 1/4096秒
}