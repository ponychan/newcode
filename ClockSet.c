
/*ʱ�ӷ�ΪMCLK ��ϵͳʱ�ӣ�CPUʹ�á�SMCLK����ʱ�ӣ�����ʹ�á�ACLK����ʱ��*/
#define PHY_FLLN      127         //DCO�ڲ�����������Ƶ 4.2MHz
#define PHY_MCLK      4194304     //MCLK=((PHY_FLLN+1)*32768)=4194304
#define PHY_MCLK_1MS  4096        //((PHY_FLLN+1)*32768)/4096 = 1024

//SMCLK����
#define PHY_SMCLK_DCO   1
#define PHY_SMCLK_XT2   2
//SMCLKƵ��
#define PHY_SMCLK_4MHZ   1
#define PHY_SMCLK_4200KHZ   2
#define PHY_SMCLK_8MHZ   3

//ACLKƵ��
#define PHY_ACLK      32768     //����ʱ��
#define PHY_ACLK_1MS  32        // 32768/32 = 1024

#define EN_XT2CLK 1 //����XT2ʱ�� 
#define DIS_XT2CLK 0//�ر�XT2ʱ��

//XT2ʱ�ӿ�����־
unsigned char g_uchPHYXt2Flag = DIS_XT2CLK;

//SMCLKʱ��ѡ��
unsigned char g_uchPHYSMclkSel = PHY_SMCLK_DCO;     //SMCLK����ѡ��XT2��2����DCO��1��

//SMCLKʱ��Ƶ���趨
unsigned char g_uchPHYSMclkSet = PHY_SMCLK_4MHZ;

/****************************************************************************/
/*�͹���ģʽ�£�û���õ��Ĺܽŵĳ�ʼ��,������ϵͳ��û���õ��Ĺܽ�ȫ������Ϊ����״̬*/
/* ע���ڳ����ڿ�ʼִ������£�Ҫ�����еĹܽŽ��г�ʼ��״̬,����ϵͳ�Ĺ��� */
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
/*��ʼ��ϵͳʱ��DCO= MCLK = SMCLK ,XT1CLK=ACLK ,	�ر� XT2		  */
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
	g_uchPHYXt2Flag = DIS_XT2CLK;      //��¼ST2ʱ���ѹر�
}
/**********************************************************************/										 
/*		  ����ϵͳʱ��DCO =MCLK=4MHz,XT2 =SMCLK,xt2=ACLK			 */
/**********************************************************************/
void SetXT2ClkOn(void)
{  
	//���XT2�Ѿ����������˳�
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
        //(127+1)*32768=4194304HZ   //ZK ������N���ó�Ϊ��127
	
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
	
	g_uchPHYXt2Flag = EN_XT2CLK;//��¼XT2�ѿ���
}


/**********************************************************************/										 
/*		 ���ݺ궨��ѡ��ͬ��ʱ��ϵͳ								 */
/* PHY_SMCLK_DCO:DCO= MCLK = SMCLK ,XT1CLK=ACLK ,	 �ر� XT2		 */
/* PHY_SMCLK_XT2:DCO =MCLK=4MHz,XT2 =SMCLK,xt2=ACLK 				 */
/* Ĭ�϶���PHY_SMCLK_DCO											 */
/**********************************************************************/
//��ϵͳ����ʱ�ӵ��趨��SMCLKͨ��ѡ���ж�SMCLKʱ��Դ
void InitClk(void)
{ 
	WDTCTL = WDTPW+WDTHOLD; 				  // Stop WDT 
	if(g_uchPHYSMclkSel == PHY_SMCLK_DCO)//���ѡ���ڲ�����
		SetDCOClk();                                      //ϵͳʱ�ӳ�ʼ��
	else if(g_uchPHYSMclkSel==PHY_SMCLK_XT2)//ѡ���ⲿ��Ƶ����
		SetXT2ClkOn();                                   //����ϵͳʱ��
	else//Ĭ���ڲ�����
		SetDCOClk();
    SFRIE1 = OFIE;    // Enable osc fault interrupt
}



/*���������ֱ�Ϊ��ʱ1���롢0.5���롢0.25����ĺ���*/

/**********************************************************************/										 
/*		����ϵͳ��ʱ��ϵͳ�����ʱ1/1024��,ԼΪ1ms	      */
/**********************************************************************/
void PHYMCLKSoftDelay1ms(void)
{
	//1��ʱ������(1/PHY_MCLK)��
	unsigned int i = (PHY_MCLK_1MS>>2);  /*PHY_MCLK_1MS>>2��ʱ����ʱ��1/4*/    
	while(--i);//4*i ��ʱ������ = 1/1024��       /*һ��whileѭ���൱��ִ��4��ָ��*/
}


/**********************************************************************/										 
/*		����ϵͳ��ʱ��ϵͳ�����ʱ1/2048��,ԼΪ0.5ms	      */
/**********************************************************************/
void PHYMCLKSoftDelayHalfms(void)
{
	//1��ʱ������(1/PHY_MCLK)��
	unsigned int i = (PHY_MCLK_1MS>>3);
	while(--i);//4*i ��ʱ������ = 1/2048��
}

/**********************************************************************/										 
/*		����ϵͳ��ʱ��ϵͳ�����ʱ1/4096��,ԼΪ244us	      */
/**********************************************************************/
void PHYMCLKSoftDelay250us(void)
{
	//1��ʱ������(1/PHY_MCLK)��
	unsigned int i = (PHY_MCLK_1MS>>4);
	while(--i);//4*i ��ʱ������ = 1/4096��
}