#include"RF.c"
#include"DevCtrl.c"

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                SI4463����Ӧ�ú���
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*************************************************************
��ȡ�豸��Ϣ
*************************************************************/
extern uchar API_PART_INFO(uchar PARTInfoLength,uchar *PARTInfo);

/************************************************************
��ȡ�豸����������״̬
�βΣ��洢�������ݵ�����ָ��
����ֵ��0x00:��ȡ����ֵ�ɹ� 
        0x01:��ȡ����ֵʧ��
************************************************************/
extern uchar API_REQUEST_DEVICE_STATE(uchar *RFStatus);

/*************************************************************
����1����ȡ״̬��־λ�������״̬��־λ
����2����ȡPacket Handler���жϱ�־λ�����ǲ�һ������ж�
����3����ȡModem���жϱ�־λ�����ǲ�һ������ж�λ
����4����ȡChip���жϱ�־λ�����ǲ�һ������ж�λ��
*************************************************************/
//����1����ȡ״̬��־λ�������״̬��־λ
extern uchar  API_Get_All_IntStatus(uchar IntStatusLength,uchar *IntStatus);

//����2����ȡPacket Handler���жϱ�־λ�����ǲ�һ������ж�
extern uchar  API_Get_PH_IntStatus(uchar PHIntStatusLength,uchar *PHIntStatus);

//������ݰ�������жϱ�־λ
extern void API_ClearPHInt(void);

//����3����ȡModem���жϱ�־λ�����ǲ�һ������ж�λ
extern uchar  API_Get_Modem_IntStatus(uchar ModemIntStatusLength,uchar *ModemIntStatus);

//����4����ȡChip���жϱ�־λ�����ǲ�һ������ж�λ��
extern uchar  API_Get_Chip_IntStatus(uchar ChipIntStatusLength,uchar *ChipIntStatus);
/*****************************************************************
����1�����TxFIFO
����2�����RxFIFO
******************************************************************/
/*
���TxFIFO
����ֵ��0xff��մ���
        0x40:��ճɹ�
*/
extern uchar API_ClearTxFIFO(void);
extern uchar RFResetRxFIFO(void);    //������·�㺯��

/*
���RxFIFO
����ֵ��0xff:���ʧ��
        0x40:��ճɹ�
*/
extern uchar API_ClearRxFIFO(void);
extern uchar RFResetTxFIFO(void);    //������·�㺯��
/*
д��TXDataBuffer
�βΣ�д�����ݳ��ȣ�����ͷָ��
*/
extern uchar API_WriteTxDataBuffer(uchar TxFifoLenght,uchar *TxFifoData);
/*
����RxDataBuffer
�β�:���������ݳ��ȣ��������������ͷָ��
*/
extern uchar API_ReadRxDataBuffer(uchar RxFifoLength,uchar *RxFifoData);
/*
����FIFO�Ŀռ�ʹ�����
�βΣ��洢�������ݵ�����ͷָ��
*/
extern void API_FIFO_INFO(uchar *FIFO_INFO);

/*********************************************************
��ȡ���ٷ�Ӧ�Ĵ�����Ĵ洢ֵ
�βΣ�bStartReg���Ĵ����Ŀ�ʼ��ַ
      bNumberOfReg����ȡ�Ĵ����ĸ���
      RegValues�� �洢�Ĵ����Ķ�ά����ͷָ��
����ֵ��0x01:д���ַ����
        0x00:��ȡ���ݳɹ�
**********************************************************/
uchar API_GetFastResponseRegister(uchar bStartReg,uchar bNumberOfReg,uchar *RegValues);

/*********************************************************
RF��GPIO����
�βΣ�GPIO0��GPIO0���÷�ʽ
      GPIO1��GPIO1���÷�ʽ
      GPIO2��GPIO2���÷�ʽ
*********************************************************/
extern void API_GPIO_CFG(uchar GPIO0,uchar GPIO1,uchar GPIO2,uchar GPIO3);

/**********************************************************
�ı���Ƶģ���״̬
**********************************************************/
extern uchar API_CHANGE_STATE(uchar RFStatus);

/**********************************************************
�ϵ�оƬ��ʼ��
**********************************************************/
extern void API_POWER_UP(void);


/***********************************************************
�Ĵ������ú���
����һ������һ���Ĵ���
����������������һ�����ڵĶ���Ĵ���
************************************************************/
/*�Ĵ��������ã���ͬһ����Ķ���Ĵ���������������
�βΣ�group���Ĵ�����������
      num_pro����Ҫ�������üĴ����ĸ���
     start_pro�����üĴ�����ĳ�ʼ��ַ
     *Data���Ĵ������õ�����
����ֵ:0��һ�������üĴ����ɹ�
       1��һ�������õļĴ������࣬����ʧ��
        
*/
extern uchar API_SET_PROPERTY_X(unsigned char group,unsigned char num_pro,unsigned char start_pro,unsigned char *Data); 

/*
��һ���Ĵ�����������
�βΣ�group:�üĴ�����������
      address���üĴ����ĵ�ַ
      Data���ԸüĴ������õ�����
����ֵ��0���ԼĴ��������óɹ�
        1���ԼĴ���������ʧ��
*/
 extern uchar API_SET_PROPERTY_1(unsigned char group,unsigned char address,unsigned char Data);
 
 /*
 ��ȡһ���Ĵ�����ֵ
 �βΣ��üĴ����������飬�Ĵ����ĵ�ַ
 ����ֵ����ȡ�ļĴ�����ֵ
 */
 extern uchar API_GET_PROPERTY_1(unsigned char group,unsigned char start_pro);
 
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
ʹ�õĺ�������
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/**************************************************************/
/*�趨RF���뵽Power Downģʽ   �ĵ���1                        */
/**************************************************************/
extern void SetRFOff(void);

/***************************************************************/
/*�趨RF����                                                   */
/***************************************************************/
extern void SetRFOn(void);

/***************************************************************/
/*�趨RF����Standbyģʽ     �ĵ���2                             */
/****************************************************************/
extern void SetRFStandby(void);

/***************************************************************/
/*�趨RF����Sleepģʽ    �ĵ���3                               */
/****************************************************************/
extern void SetRFSleep(void);

/***************************************************************/
/*�趨RF����Readyģʽ    �ĵ���4                              */
/****************************************************************/
extern void SetRFReady(void);

/***************************************************************/
/*�趨RF����TXģʽ�µ�TUNEģʽ                                         */
/****************************************************************/
extern void SetRFTuneForTx(void);

/***************************************************************/
/*�趨RF����Rxģʽ�µ�TUNEģʽ                                         */
/****************************************************************/
extern void SetRFTuneForRx(void);

/***************************************************************/
/*�趨RF����TXģʽ (ע�����ݷ������֮���Զ��˳�)                     */
//ע������������������
/****************************************************************/
extern void SetRFTx(void);        //ʹ��START_TX����,���Ըı乤��Ƶ�����뷢�����ݳ���  
extern void SetRFStartTx(void);  //ʹ��CHANGE_STATE����  
 
/***************************************************************/
/*�趨RF����RXģʽ                                         */
//ע������������������
/****************************************************************/
extern void SetRFRx(void);      //ʹ��START_RX����

extern void SetRFStartRx(void);  //ʹ��CHANGE_STATE����

/***************************************************************
Ӳ������RF Reset RF
****************************************************************/
extern void HWResetRF(void);

/****************************************************************
��Ƶ������д����Ӧ�Ĳ�������Ƶ����Ӧ�ģ�Ƶ����
ע�⣺������Ƶֻ�Ǹı��˹���Ƶ���ŵ�ȫ�ֱ�������û��������ʵ��
��Ƶ��������ʵ����ƵҪ��SetRFStartTx(),SetRFStartRx()������ʵ�֣�
������ִ�з�������ͽ��������ʱ����ʵ����Ƶ
**********************************************************************/                                         
/*    ��Ƶ��ѡ���Ƶ��,����unsigned char RFFreѡ��������Ƶ��        */
// A��                                                           
// 0x00 -------------------------------------470.100MHz           
// 0x01 -------------------------------------470.300MHz             
// 0x02 -------------------------------------470.500MHz          
// 0x03 -------------------------------------470.700MHz           
// 0x04 -------------------------------------470.900MHz     
// B�� �� 
/****************************************************************/
extern void FrequencyHop(unsigned char RFFreNum);

/*****************************************************************
����RF�ڹ���Ƶ��
*****************************************************************/
extern void InitRFChipWorkBand(void);


/****************************************************************/
/*           ��ȡRSSIֵ����������                               */
/****************************************************************/
extern unsigned char GetRSSI(void);
extern unsigned char GetFastLatchRSSI(void);
extern int GetRSSIPower(void);
/****************************************************************
�趨RF���뵽TX�����ز�
*****************************************************************/
extern void SetTxCarrier(void);

/****************************************************************************/
/*  �������ݰ���                                                            */
/*  ��������:                                                               */
/*   char *txBuffer: �����͵����ݣ�                                         */
/*   int size�����txBuffer���ܹ���Ҫ���͵����ݳ���                         */
/*   �����͵����ݳ��Ȳ����� 255-5 ��250�ֽ�                                */
/*  ��������ֵ ��0: ���ͳɹ���-1������ʧ��;-2:���ݳ���̫��                 */
/*  ������Ϻ��Զ��������̬                                               */
/****************************************************************************/
extern int RFSendPacket(unsigned char *txBuffer, int size);

/****************************************************************************/
/*  �������ݰ������Ȳ���                                                    */
/*  ��������: unsigned char *rxBuffer ��Ž��յ�����                        */ 
/*                                          ,rxBuffer[0] �����Ч���ݰ���С */
/*  ��������ֵ ��0: ���ճɹ���
                -1�����̵�ַ��ƥ��;
                -2: û���յ��κ�����                         
                -3:�յ����ݵ���CRCУ�����                                  
                -4:�յ�ͬ���ֺͲ�������,�����ݽ��ճ�ʱʧ�ܣ�                */
/****************************************************************************/  
extern int RFReceivePacket(unsigned char *rxBuffer);


/*========================================
�����õ�ǰоƬ������״̬
�βΣ��洢RF״̬������ͷָ��
����ֵ��0x00:��ȡ����ֵ�ɹ� 
        0x01:��ȡ����ֵʧ��
0:no change /// 1:sleep state /// 2:spi active state
3:ready state /// 4:another enumeration for ready state
5:tune state for tx /// 6:tune state for rx
7:tx state /// 8:rx state
========================================*/
uchar API_REQUEST_DEVICE_STATE(uchar *RFStatus)
{
    uchar cmd=CMD_REQUEST_DEVICE_STATE;
    API_SendCommand(0x01,&cmd);
    if(API_GetResponse(0x02,RFStatus)==0)    //��ȡ����ֵ�ɹ�
        return 0x00;
    return 0x01;
}
/**************************************************************/
/*�趨RF���뵽Power Downģʽ                                  */
/***************************************************************/
void SetRFOff(void)
{
    SDN_OUT_H;  //SDN�ܽŸߵ�ƽ��RF���뵽ShutDownģʽ
    g_uchrRFMode=RF_Shutdown;    //��1��������0����
}

/***************************************************************/
/*�趨RF����                                                   */
/***************************************************************/
void SetRFOn(void)
{
    SDN_OUT_L;    //SDN�ܽŵ͵�ƽ��RF����
    //��shutdownģʽ�µ�TX/RXģʽ������15ms�����ٵȴ�15ms
    int i=40;   //��ʱԼ40ms
    while(i--)
        PHYMCLKSoftDelay1ms();
    g_uchrRFMode=RF_Standby;
}
/***************************************************************
Ӳ������RF Reset RF
****************************************************************/
void HWResetRF()
{
    uchar IntStatus[8];
    uchar DeviceInfo[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    RFCtlLineInit(); //RF�����߳�ʼ��
    SetRFOff();  //�ر�RF  �ر�֮�����ٵȴ�10ns
    PHYMCLKSoftDelay1ms();   //��ʱ1ms
    SetRFOn(); //RF����
    API_PART_INFO(0x08,DeviceInfo);  //��ȡ�豸��Ϣ
    if(DeviceInfo[1]!=0x44||DeviceInfo[2]!=0x63)  //�ж��豸�Ķ�ȡ��Ϣ�Ƿ���ȷ
    {
        int i=200;
        while(1)
        {
            LedRedOn();
            i=200;
            while(--i)
                PHYMCLKSoftDelay1ms();   //��ʱ1ms
            LedRedOff();
            i=200;
            while(--i)
                PHYMCLKSoftDelay1ms();   //��ʱ1ms        
        }
    }
    API_Get_All_IntStatus(0x08,IntStatus);//��ȡ�жϱ�־������жϱ�־λ
}

 /****************************************************************
��Ƶ������д����Ӧ�Ĳ�������Ƶ����Ӧ�ģ�Ƶ���ţ���Ƶ��ɺ���뵽
����״̬
����Ƶ�㣺��������������
****************************************************************/
void FrequencyHop(unsigned char RFFreNum)
{
    if(RFFreNum>(RF_FRE_AMOUNT-1))   //����Ƶ���Ŵ������Ƶ���ţ����������Ƶ����
        RFFreNum=RF_FRE_AMOUNT-1;
    //if(RFFreNum!=g_uchRFCurFreNum)
    {
        //g_uchRFCurFreNum = RFFreNum;       //��¼���������Ĺ���Ƶ��
        SetRFRx();                         //�����Ƶ�������뵽����ģʽ
    }
}

/***************************************************************/
/*�趨RF����Standbyģʽ                                        */
//Standby��Sleepģʽ�޷�ʹ��REQUEST_DEVICE_STATE����õ�
/***************************************************************/
void SetRFStandby(void)
{
    API_CHANGE_STATE(0x01);    //sleep state
    g_uchrRFMode = RF_Sleep;
}

/***************************************************************/
/*�趨RF����Sleepģʽ    �ĵ���3                               */
/****************************************************************/
void SetRFSleep()
{
    API_CHANGE_STATE(0x01);  //sleep state
    g_uchrRFMode = RF_Sleep;
}


/***************************************************************/
/*�趨RF����Readyģʽ                                         */
/****************************************************************/
void SetRFReady(void)
{
    uchar RFStatus[2]; //�洢�����豸״̬�ķ�������
    API_CHANGE_STATE(0x03);
    if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
    {
        if(RFStatus[0]==0x03)
        {
            g_uchrRFMode=RF_Ready;     //��¼�����豸����Readyģʽ
        }
    } 
}

/***************************************************************/
/*�趨RF����Txģʽ�µ�TUNEģʽ                                         */
/****************************************************************/
void SetRFTuneForTx(void)
{
    uchar RFStatus[2]; //�洢�����豸״̬�ķ�������
    API_CHANGE_STATE(0x05); 
    if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
    {
        if(RFStatus[0]==0x03)
        {
            g_uchrRFMode=RF_TxTune;     //��¼�����豸����TX_TUNEģʽ
        }
    } 
}
/***************************************************************/
/*�趨RF����Rxģʽ�µ�TUNEģʽ                                         */
/****************************************************************/
void SetRFTuneForRx(void)
{
    uchar RFStatus[2]; //�洢�����豸״̬�ķ�������
    API_CHANGE_STATE(0x06); 
    if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
    {
        if(RFStatus[0]==0x03)
        {
            g_uchrRFMode=RF_RxTune;     //��¼�����豸����RX_TUNEģʽ
        }
    } 
}

/***************************************************************/
/*�趨RF����TXģʽ (ע�����ݷ������֮���Զ��˳�)              */
//ע�����ߵ�����CHANGE_STATE����ķ��ͺ����޷�д��Ƶ���ţ����ͳ���
//START_TX��������д��Ƶ�����Լ����ݷ��ͳ���
/****************************************************************/
//ʹ��CHANGE_STATE����ķ��ͺ���
void SetRFStartTx(void)
{
    /*����ı�TX״̬��ʹ��CHANGE_STATE����   ��Ϊ�޷�д��Ƶ���ŵ�����  */
    uchar RFStatus[2]; //�洢�����豸״̬�ķ�������
    API_CHANGE_STATE(0x07);
    if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
    {
        if(RFStatus[0]==0x07)
        {
            g_uchrRFMode=RF_Tx;     //��¼�����豸����TXģʽ
        }
    } 
}
//ʹ��START_TX����ķ��ͺ���     ..Ƶ���ż��3��
/*�趨��Ƶ���뷢��ģʽ���������ʧ�ܣ���������ƵоƬ�����³�ʼ��*/
void SetRFTx()    //sizeʹ��uchar���ͣ���෢�͸��ֽ���ֻ����255
{
    /****************************************/
    /*�ɴ�������Ӵ���*/
    //��ӵ����ز�ģʽ�Ĵ���
    // MODEM_MOD_TYPE(0x00);   //�ز�ģʽ
    /*�ɴ�������Ӵ���*/
    /****************************************/
    unsigned char RFStatus[2]; //�洢�����豸״̬�ķ�������
    unsigned char Command_Tx[5];
    Command_Tx[0]=CMD_START_TX;
    Command_Tx[1]=g_uchRFSelfFreNum*3;   //ʹ����Ƶ����ı乤��Ƶ����
    Command_Tx[2]=0x30;     //������ɺ󣬽���3-readyģʽ�����˳�����ģʽ
    Command_Tx[3]=0x00;
    Command_Tx[4]=0x00;
    /*���ֶ�Ϊ�㣬��Ҫ����������ֽ�����PKT_FIELD_X_LENGTH���Ե�ֵָ��������������£���Ч�غɳ�������Ϊ5 x 8191 = 40955�ֽڣ���Ϊ��������ֶ��е�ÿһ������������Ϊ8191�ֽڵĳ��ȣ��������Ҫ�ض��ڳ��Ĵ������磬һ�����ϵ����ݰ׻���������һ�����ϵ����ݰ׻���һ�����ϵ�����˹�ر����������һ���ϵ����ݣ��ȵȣ�����÷����Ǳ�Ҫ��*/
    while(1)
    {
        unsigned char trytimes=0;
        while(++trytimes<3)
        {
            API_SendCommand(0x05,Command_Tx);     //API_WRITER 
            PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();
            if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
            {
                if(RFStatus[0]==0x07)
                {
                    g_uchrRFMode=RF_Tx; //��¼�����豸����TXģʽ
                    break;     
                }
            }       
        }
        if(g_uchrRFMode==RF_Tx)
            break;   
        /**********************************/
        /*�ɴ˴�������Ӵ���*/
        HWResetRF();    
        InitRFChipWorkBand();
        // FrequencyHop(g_uchRFSelfFreNum);    //������ڣ�2014-11-22
        /*�ɴ˴�������Ӵ���*/
        /**********************************/
    }
}
/***************************************************************/
/*    �趨RF����RXģʽ                                         */
/*    ����ı�RX״̬ʹ��CHANGE_STATE����                     */
/*      ��Ϊ�޷�д��Ƶ���ŵ�����                               */
/***************************************************************/
//ʹ��CHANGE_STATE������뵽RX״̬
void SetRFStartRx(void)
{
    uchar RFStatus[2]; //�洢�����豸״̬�ķ�������
    API_CHANGE_STATE(0x08); 
    if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
    {
        if(RFStatus[0]==0x08)
        {
            g_uchrRFMode=RF_Rx;     //��¼�����豸����RXģʽ
        }
    }  
}

//ʹ��START_RX������뵽RX״̬,�βδ�����Ҫ�޸��β�
void SetRFRx()  
{
    unsigned char RFStatus[2]; //�洢�����豸״̬�ķ�������
    //unsigned char RF_Mode=g_uchrRFMode; ��¼�ϴε�״̬���������ϴ�״̬ת����Ϊ����״̬����Ҫ��ʱ��
    unsigned char Command_Rx[7];
    Command_Rx[0]=CMD_START_RX;
    // Command_Rx[1]=g_uchRFCurFreNum*3;          //���ڵ�Ƶ��
    Command_Rx[2]=0x00;
    Command_Rx[3]=0x00;
    Command_Rx[4]=0x00;
    Command_Rx[5]=0x00;
    Command_Rx[6]=0x00;
    while(1)
    {
        unsigned char trytimes=0;
        while(++trytimes<3)
        {
            /*********************************************/
            /*�ɴ�������Ӵ���*/
            INT_CTL_ENABLE(0x01);     //�������ݰ��ж�
            INT_CTL_PH_ENABLE(0x19);   //RX_Fifo�����ͽ�������ж�
            // INT_CTL_PH_ENABLE(0x18);   //RX_Fifo�����ͽ�������ж�
            /*�ɴ�������Ӵ���*/
            /********************************************/
            API_ClearRxFIFO();                  //���RxFIFO
            API_SendCommand(0x07,Command_Rx);   //API_WRITER 
            API_WaitforCTS();
            if(API_REQUEST_DEVICE_STATE(RFStatus)==0)  //��ȡ�������ݳɹ�
            {
                if(RFStatus[0]==0x08)
                {
                    g_uchrRFMode=RF_Rx; //��¼�����豸����TXģʽ
                    break;     
                }
            }       
        }
        if(g_uchrRFMode==RF_Rx)
            break;  
        HWResetRF();
        InitRFChipWorkBand();
        // // FrequencyHop(g_uchRFSelfFreNum);    //������ڣ�2014-11-22
        //ע����SI4432������
        //���ﲻ�����Ƶ���룬��Ƶ�����ڷ��������Լ����������������
    }   
}

/****************************************************************/
/*           ��ȡRSSIֵ����������                               */
/****************************************************************/
unsigned char GetRSSI()
{ 
    unsigned int i=0;
    unsigned char RSSI[4];
    unsigned char count;
    unsigned char max=0;
    unsigned char min=0xff;
    //SetRFRx();     //���뵽����ģʽ
    for(count=0;count<6;count++)
    {
        //API_GetFastResponseRegister(0x51,0x01,&RSSI);    //���ٷ�Ӧ�Ĵ�����ȡ latch rssi
        API_Get_Modem_IntStatus(0x04,RSSI);
        i+=RSSI[2];
        if(RSSI[2]>max)
            max=RSSI[2];
        if(RSSI[2]<min)
            min=RSSI[2];
    }
    //SetRFReady();  //���뵽readyģʽ
    i=i-max-min;
    RSSI[2]=i/4;
    return RSSI[2];
}
 /****************************************************
 ͨ����ȡFast response��ȡlatch rssi
 *****************************************************/
unsigned char GetFastLatchRSSI()
{
    unsigned char RSSI=0x00;
    API_GetFastResponseRegister(0x51,0x01,&RSSI);    //���ٷ�Ӧ�Ĵ�����ȡ latch rssi
        return RSSI;
}
 /************************************************************
               ����ȡ��RSSI��ֵת��ΪdBm����ʽ
 *************************************************************/
int GetRSSIPower()
{
    int Ret=GetRSSI();
    return Ret;
}
/**************************************************************
 �趨RF���뵽TX�����ز�
***************************************************************/
void SetTxCarrier()
{
    MODEM_MOD_TYPE(0x00);
    SetRFStartTx();
}
//���Ƶ��470M
//����4kbps,Ƶ��ƫ��20KHz
/***********************************************************************/
/*            ������ʼ��RF��standby*/
/***********************************************************************/
void InitRFChipB470_Baud4000(void)    
{
    unsigned char API_WRITER[16];        //�����
    unsigned char IntSta[12];
    //power up
    API_POWER_UP();                          //��ͬ
    API_Get_All_IntStatus(0x08,IntSta);      //��ͬ
    //GPIO config
    // API_GPIO_CFG(0x20,0x21,0x20,0x21);
    API_GPIO_CFG(0x21,0x20,0x20,0x21);   //��Ҫ��������Ƶ���صķ��������趨
    
    //GLOBAL_XO_TUNE
    GLOBAL_XO_TUNE(0x50);                      //��ͬ
    //GLOBAL_CONFIG
    GLOBAL_CONFIG(0x60);                       //��ͬ
  
    //MODEM_CLK_BAND
    MODEM_CLKGEN_BAND(0x0A);        //��ͬ
  
    //MODEM
    //modem type
    MODEM_MOD_TYPE(0x03); //2GFSK,FIFO handler    //��ͬ
    MODEM_MAP_CONTROL(0x00);
    MODEM_DSM_CONTROL(0x07);
  
    //modem data rate         ������     //����ͬ�����Խ�������
    /*
    ODEM_DATA_RATE_2(0x0c);        //40kbps
    ODEM_DATA_RATE_1(0x35);                
    ODEM_DATA_RATE_0(0x00);
    ODEM_TX_NCO_MODE_3(0x09);                
    ODEM_TX_NCO_MODE_2(0xc9);                
    ODEM_TX_NCO_MODE_1(0xc3);                
    ODEM_TX_NCO_MODE_0(0x80);
    /
    ODEM_DATA_RATE_2(0x02);        //4kbps
    ODEM_DATA_RATE_1(0x71);                
    ODEM_DATA_RATE_0(0x00);
    ODEM_TX_NCO_MODE_3(0x05);                
    ODEM_TX_NCO_MODE_2(0xc9);                
    ODEM_TX_NCO_MODE_1(0xc3);                
    ODEM_TX_NCO_MODE_0(0x80);
    
    /modem deviation   Ƶƫ      20kHz
    ODEM_FREQ_DEV_2(0x00);    //��ͬ
    ODEM_FREQ_DEV_1(0x05);
    ODEM_FREQ_DEV_0(0x76);
    
    
    
    /RF_FREQ_CONTROL_INTE_8   //�������    Ƶ������
    REQ_CONTROL_INTE(0x3d);     //����Ƶ��470.1MHz  ������200khz
    REQ_CONTROL_FRAC_2(0x0d);
    REQ_CONTROL_FRAC_1(0x70);
    REQ_CONTROL_FRAC_0(0xa3);
    REQ_CONTROL_CHANNEL_STEP_SIZE_1(0x36);
    REQ_CONTROL_CHANNEL_STEP_SIZE_0(0x9d);
    REQ_CONTROL_W_SIZE(0x20);
    REQ_CONTROL_VCOCNT_RX_ADJ(0xfe);
    
    
    
    /INT_CTL_ENALBE
    INT_CTL_ENABLE(0x00);       //�ر����е��ж�
    
    
    /FRR_CTL_MODE
    
    RR_CTL_A_MODE(0x04);    //���ݰ���������ж�
    RR_CTL_B_MODE(0x0a);    //latch RSSI value as defined in MODEM_RSSI_CONTROL
    *���ٷ�Ӧ�Ĵ���C/D�ɸ���ʵ�������������*/
    //FRR_CTL_C_MODE(0X00);
    //FRR_CTL_D_MODE(0X00);
    
    //PREAMBLE  ǰ����
    REAMBLE_TX_LENGTH(0x0a);        //��ͬ
    REAMBLE_CONFIG(0x31);
    /*0x14��0x0fΪ�Ĵ���Ĭ��ֵ���������ﲻ��Ҫ���ã������Ҫ��
    �Ĵ������в��ָı���޸Ĵ˴�*/
    //PREAMBLE_CONFIG_STD1(0X14);  //RXǰ�����������
    //PREAMBLE_CONFIG_STD2(0X0F);  //RX����ǰ��������
    
    //SYNC   ͬ����                 //��ͬ
    YNC_CONFIG(0x01);   //�����ֽڵ�ͬ���֣���������˹�ر��룬����4FSK����
    YNC_BITS_31_24(0xB4);
    YNC_BITS_23_16(0x2B);
    
    //PKT_CRC_CONFIG  CRC����ѡ��
    
    PKT_CRC_CONFIG(0x85);
    PKT_CONFIG1(0x02);  //new
    PKT_TX_THRESHOLD(0x30);      //���Ϳ������ֵ  32�ֽ�
    PKT_RX_THRESHOLD(0x30);      //���ܿ�������ֵ  32��
   
#ifdef LengthFieldInTwoByte
    PKT_LEN(0x3a);               //�����ֽ����ó�Ϊ�����ֽ�
#else
    PKT_LEN(0x2a);               //�����ֽ����ó�Ϊһ���ֽ�
#endif   
    PKT_LEN_FIELD_SOURCE(0x01);            
    PKT_LEN_ADJUST(0x00);
    PKT_FIELD_1_LENGTH_7_0(0x01);
    PKT_FIELD_1_CONFIG(0x04);
    PKT_FIELD_2_LENGTH_7_0(0xff);
    PKT_FIELD_2_CONFIG(0x04);

   
    MODEM_RSSI_CONTROL(0x13);
    
/* �βΣ�group���Ĵ�����������
      num_pro����Ҫ�������üĴ����ĸ���
     start_pro�����üĴ�����ĳ�ʼ��ַ
     *Data���Ĵ������õ�����
  */
  //RF_MODEM_TX_RAMP_DELAY_8         //����ͬ
   
  API_WRITER[0]=0X01;        API_WRITER[1]=0x80; //API_WRITER[1]=0x00;
  API_WRITER[2]=0x08;         API_WRITER[3]=0x03;
  API_WRITER[4]=0x80;         API_WRITER[5]=0x00;
  API_WRITER[6]=0x20;       API_WRITER[7]=0x10;//  API_WRITER[7]=0x20;
  API_SET_PROPERTY_X(Group_MODEM,0X08,ad_MODEM_TX_RAMP_DELAY,API_WRITER);
  
 //RF_MODEM_BCR_OSR_1_9      //����ͬ
 /* API_WRITER[0]=0X00;          API_WRITER[1]=0x5E;
  API_WRITER[2]=0x05;          API_WRITER[3]=0x76;
  API_WRITER[4]=0x1A;          API_WRITER[5]=0x05;
  API_WRITER[6]=0x72;          API_WRITER[7]=0x02;
  API_WRITER[8]=0X00;*/   
  API_WRITER[0]=0X02;          API_WRITER[1]=0x71;
  API_WRITER[2]=0x00;          API_WRITER[3]=0xd1;
  API_WRITER[4]=0xb7;          API_WRITER[5]=0x00;
  API_WRITER[6]=0x69;          API_WRITER[7]=0x02;
  API_WRITER[8]=0Xc2;
  API_SET_PROPERTY_X(Group_MODEM,0X09,ad_MODEM_BCR_OSR_1,API_WRITER);
  
  
  //RF_MODEM_AFC_GEAR_7       //����ͬ
  /*
  API_WRITER[0]=0X00;          API_WRITER[1]=0x12;
  API_WRITER[2]=0x81;          API_WRITER[3]=0x5E;
  API_WRITER[4]=0x01;          API_WRITER[5]=0xCD;
  API_WRITER[6]=0xa0;  
  */
  API_WRITER[0]=0X04;          API_WRITER[1]=0x36;
  API_WRITER[2]=0xc0;          API_WRITER[3]=0x0c;
  API_WRITER[4]=0x24;          API_WRITER[5]=0x31;
  API_WRITER[6]=0xc0;  
  API_SET_PROPERTY_X(Group_MODEM,0X07,ad_MODEM_AFC_GEAR,API_WRITER);
  
  //RF_MODEM_AGC_CONTROL_1
  API_WRITER[0]=0xE2;           //��ͬ
  API_SET_PROPERTY_X(Group_MODEM,0x01,ad_MODEM_AGC_CONTROL,API_WRITER);
  
  //RF_MODEM_AGC_WINDOW_SIZE_9
  /*
   API_WRITER[0]=0X11;          API_WRITER[1]=0x15;   //����ͬ
  API_WRITER[2]=0x15;          API_WRITER[3]=0x00;
  API_WRITER[4]=0x1A;          API_WRITER[5]=0x40;
  API_WRITER[6]=0x00;          API_WRITER[7]=0x00;
  API_WRITER[8]=0X28;       
*/
  API_WRITER[0]=0X11;          API_WRITER[1]=0x89;   //����ͬ
  API_WRITER[2]=0x89;          API_WRITER[3]=0x00;
  API_WRITER[4]=0x1A;          API_WRITER[5]=0xff;
  API_WRITER[6]=0xff;          API_WRITER[7]=0x00;
  API_WRITER[8]=0X2b;
  API_SET_PROPERTY_X(Group_MODEM,0X09,ad_MODEM_AGC_WINDOW_SIZE,API_WRITER);
  
  //RF_MODEM_OOK_CNT1_11
 /* API_WRITER[0]=0xA4;          API_WRITER[1]=0x03;   //����ͬ
  API_WRITER[2]=0xD6;          API_WRITER[3]=0x03;
  API_WRITER[4]=0x00;          API_WRITER[5]=0xCC;
  API_WRITER[6]=0x01;          API_WRITER[7]=0x80;
  */
  API_WRITER[0]=0xA4;          API_WRITER[1]=0x02;   //����ͬ
  API_WRITER[2]=0xD6;          API_WRITER[3]=0x83;
  API_WRITER[4]=0x01;          API_WRITER[5]=0x33;
  API_WRITER[6]=0x01;          API_WRITER[7]=0x80;
 // API_WRITER[8]=0XFF;           API_WRITER[9]=0x0C;
  //API_WRITER[10]=0x00; 
  API_SET_PROPERTY_X(Group_MODEM,0X08,ad_MODEM_OOK_CNT1,API_WRITER);
  
  
 //RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12
  /*
  API_WRITER[0]=0xA2;          API_WRITER[1]=0x81;  //��ͬ
  API_WRITER[2]=0x26;          API_WRITER[3]=0xAF;
  API_WRITER[4]=0x3F;          API_WRITER[5]=0xEE;
  API_WRITER[6]=0xC8;          API_WRITER[7]=0xC7;
  API_WRITER[8]=0xDB;          API_WRITER[9]=0xF2;
  API_WRITER[10]=0x02;         API_WRITER[11]=0x08;
  */
  API_WRITER[0]=0xff;          API_WRITER[1]=0xba;  //��ͬ
  API_WRITER[2]=0x0f;          API_WRITER[3]=0x51;
  API_WRITER[4]=0xcf;          API_WRITER[5]=0xa9;
  API_WRITER[6]=0xC9;          API_WRITER[7]=0xfc;
  API_WRITER[8]=0x1b;          API_WRITER[9]=0x1e;
  API_WRITER[10]=0x0f;         API_WRITER[11]=0x01;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX1_CHFLT_COE_13,API_WRITER); 
  
  //RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12   //��ͬ
  /*
  API_WRITER[0]=0X07;          API_WRITER[1]=0x03;
  API_WRITER[2]=0x15;          API_WRITER[3]=0xFC;
  API_WRITER[4]=0x0F;          API_WRITER[5]=0x00;
  API_WRITER[6]=0xA2;          API_WRITER[7]=0x81;
  API_WRITER[8]=0x26;          API_WRITER[9]=0xAF;
  API_WRITER[10]=0x3F;         API_WRITER[11]=0xEE;
  */
  API_WRITER[0]=0Xfc;          API_WRITER[1]=0xfd;
  API_WRITER[2]=0x15;          API_WRITER[3]=0xff;
  API_WRITER[4]=0x00;          API_WRITER[5]=0x0f;
  API_WRITER[6]=0x5b;          API_WRITER[7]=0x47;
  API_WRITER[8]=0x0f;          API_WRITER[9]=0xc0;
  API_WRITER[10]=0x6d;         API_WRITER[11]=0x25;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX1_CHFLT_COE_1,API_WRITER); 
  
  //RF_MODEM_RX2_CHFLT_RX2_CHFLT_COE7_7_0_12
 /* API_WRITER[0]=0XC8;          API_WRITER[1]=0xC7;   //��ͬ
  API_WRITER[2]=0xDB;          API_WRITER[3]=0xF2;
  API_WRITER[4]=0x02;          API_WRITER[5]=0x08;
  API_WRITER[6]=0x07;          API_WRITER[7]=0x03;
  API_WRITER[8]=0x15;          API_WRITER[9]=0xFC;
  API_WRITER[10]=0x0F;         API_WRITER[11]=0x00;*/
  API_WRITER[0]=0Xf4;          API_WRITER[1]=0xdb;   //��ͬ
  API_WRITER[2]=0xD6;          API_WRITER[3]=0xdf;
  API_WRITER[4]=0xec;          API_WRITER[5]=0xf7;
  API_WRITER[6]=0xfe;          API_WRITER[7]=0x01;
  API_WRITER[8]=0x15;          API_WRITER[9]=0xF0;
  API_WRITER[10]=0xff;         API_WRITER[11]=0x03;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX2_CHFLT_COE_7,API_WRITER); 
  
  
  //RF_PA_MODE_4        ���ʷŴ���  //��ͬ
  PA_MODE(0x08);
  PA_PWR_LVL(0x7f);
  PA_BIAS_CLKDUTY(0x00);
  PA_TC(0x3d);
   
  
  //RF_SYNTH_PFDCP_CPFF_7     //��ͬ
  SYNTH_PFDCP_CPFF(0x2C);
  SYNTH_PFDCP_CPINT(0x0E);
  VCO_KV(0x0B);
  SYNTH_LPFILT3(0x04);
  SYNTH_LPFILT2(0x0C);
  SYNTH_LPFILT1(0x73);
  SYNTH_LPFILT0(0x03);
  
  
  //RF_MATCH_VALUE_1_12
  /****************************/
}
//���Ƶ��470.1M
//����40kbps,Ƶ��ƫ��20KHz
/***********************************************************************/
/*            ������ʼ��RF��standby*/
/***********************************************************************/
void InitRFChipB470_Baud40000(void)    
{
    unsigned char API_WRITER[16];  //�����
    unsigned char IntSta[12];

  //power up
  API_WRITER[0]=CMD_POWER_UP; API_WRITER[1]=0x01;
  API_WRITER[2]=0x00;         API_WRITER[3]=0x01;
  API_WRITER[4]=0xc9;         API_WRITER[5]=0xc3;
  API_WRITER[6]=0x80;         
  API_SendCommand(0x07,API_WRITER);
  API_WaitforCTS();

  
  //GPIO confi
  API_GPIO_CFG(0x21,0x20,0x20,0x21);
  
  
  //GLOBAL_XO_TUNE
  GLOBAL_XO_TUNE(0x52);
  
  //GLOBAL_CONFIG
  GLOBAL_CONFIG(0X60);
  
  //INT_CTL_ENALBE
  INT_CTL_ENABLE(0x00);  //Ĭ�Ϲر����е��ж�
//INT_CTL_PH_ENABLE(0x18);    //0x20
  
  
  //FRR_CTL_MODE            ����ʵ���������
  FRR_CTL_A_MODE(0x04);    //���ݰ���������ж�
  FRR_CTL_B_MODE(0x0a);    //latch RSSI value as defined in MODEM_RSSI_CONTROL
  /*���ٷ�Ӧ�Ĵ���C/D�ɸ���ʵ��ʹ����������趨*/
  //FRR_CTL_C_MODE(0X00);
  //FRR_CTL_D_MODE(0X00);
  
  //PREAMBLE
  PREAMBLE_TX_LENGTH(0X08);  //0x0a
  PREAMBLE_CONFIG(0X31);
  /*0x14��0x0fΪ�Ĵ���Ĭ��ֵ���������ﲻ��Ҫ���ã������Ҫ��
   �Ĵ������в��ָı���޸Ĵ˴�*/
 // PREAMBLE_CONFIG_STD1(0X14);  //RXǰ�����������
  //PREAMBLE_CONFIG_STD2(0X0F);  //RX����ǰ��������
  
  //SYNC
  SYNC_CONFIG(0X01);
  SYNC_BITS_31_24(0XB4);
  SYNC_BITS_23_16(0X2B);
  
  
  //PKT_CRC_CONFIG  CRC����ѡ��
  PKT_CONFIG1(0x02);
  PKT_CRC_CONFIG(0x85);
  PKT_TX_THRESHOLD(0x30);      //���Ϳ������ֵ  48�ֽ�
  PKT_RX_THRESHOLD(0x30);      //���ܿ�������ֵ  48�ֽ�
#ifdef LengthFieldInTwoByte
   PKT_LEN(0x3a);               //�����ֽ����ó�Ϊ�����ֽ�
#else
   PKT_LEN(0x2a);               //�����ֽ����ó�Ϊһ���ֽ�
#endif  
   PKT_LEN_FIELD_SOURCE(0x01);            
   PKT_LEN_ADJUST(0x00);
   PKT_FIELD_1_LENGTH_7_0(0x01);
   PKT_FIELD_1_CONFIG(0x04);
   PKT_FIELD_2_LENGTH_7_0(0xff);
   PKT_FIELD_2_CONFIG(0x04);
  
  //MODEM
  //modem type
  MODEM_MOD_TYPE(0x03); //2GFSK,FIFO handler
  MODEM_MAP_CONTROL(0x00);
  MODEM_DSM_CONTROL(0x07);
  
  //MODEM_CLK_BAND
  MODEM_CLKGEN_BAND(0X0A);
  
  //modem data rate         ������
  MODEM_DATA_RATE_2(0X0c);        //40kbps
  MODEM_DATA_RATE_1(0X35);                
  MODEM_DATA_RATE_0(0X00);
  MODEM_TX_NCO_MODE_3(0X09);                
  MODEM_TX_NCO_MODE_2(0Xc9);                
  MODEM_TX_NCO_MODE_1(0Xc3);                
  MODEM_TX_NCO_MODE_0(0X80);
  
  //modem deviation   Ƶƫ
  MODEM_FREQ_DEV_2(0x00);
  MODEM_FREQ_DEV_1(0x05);
  MODEM_FREQ_DEV_0(0x76);
  
  
  /*
  �βΣ�group���Ĵ�����������
      num_pro����Ҫ�������üĴ����ĸ���
     start_pro�����üĴ�����ĳ�ʼ��ַ
     *Data���Ĵ������õ�����
  */
  //RF_MODEM_TX_RAMP_DELAY_8
  API_WRITER[0]=0X01;         API_WRITER[1]=0x00;
  API_WRITER[2]=0x08;         API_WRITER[3]=0x03;
  API_WRITER[4]=0x80;         API_WRITER[5]=0x00;
  API_WRITER[6]=0x20;         API_WRITER[7]=0x20;
  API_SET_PROPERTY_X(Group_MODEM,0X08,ad_MODEM_TX_RAMP_DELAY,API_WRITER);
  
 //RF_MODEM_BCR_OSR_1_9 
  API_WRITER[0]=0X00;          API_WRITER[1]=0x5E;
  API_WRITER[2]=0x05;          API_WRITER[3]=0x76;
  API_WRITER[4]=0x1A;          API_WRITER[5]=0x05;
  API_WRITER[6]=0x72;          API_WRITER[7]=0x02;
  API_WRITER[8]=0X00;          
  API_SET_PROPERTY_X(Group_MODEM,0X09,ad_MODEM_BCR_OSR_1,API_WRITER);
  
  //RF_MODEM_AFC_GEAR_7
  API_WRITER[0]=0X00;          API_WRITER[1]=0x12;
  API_WRITER[2]=0xC1;          API_WRITER[3]=0x5E;
  API_WRITER[4]=0x01;          API_WRITER[5]=0xCD;
  API_WRITER[6]=0xE0;          
  API_SET_PROPERTY_X(Group_MODEM,0X07,ad_MODEM_AFC_GEAR,API_WRITER);
  
  //RF_MODEM_AGC_CONTROL_1
  API_WRITER[0]=0XE2;
  API_SET_PROPERTY_X(Group_MODEM,0X01,ad_MODEM_AGC_CONTROL,API_WRITER);
  
  //RF_MODEM_AGC_WINDOW_SIZE_9
   API_WRITER[0]=0X11;          API_WRITER[1]=0x15;
  API_WRITER[2]=0x15;          API_WRITER[3]=0x00;
  API_WRITER[4]=0x1A;          API_WRITER[5]=0x40;
  API_WRITER[6]=0x00;          API_WRITER[7]=0x00;
  API_WRITER[8]=0X28;          
  API_SET_PROPERTY_X(Group_MODEM,0X09,ad_MODEM_AGC_WINDOW_SIZE,API_WRITER);
  
  //RF_MODEM_OOK_CNT1_11
  API_WRITER[0]=0XA4;          API_WRITER[1]=0x03;
  API_WRITER[2]=0xD6;          API_WRITER[3]=0x03;
  API_WRITER[4]=0x00;          API_WRITER[5]=0xCC;
  API_WRITER[6]=0x01;          API_WRITER[7]=0x80;
  API_WRITER[8]=0XFF;           API_WRITER[9]=0x0C;
  API_WRITER[10]=0x00; 
  API_SET_PROPERTY_X(Group_MODEM,0X0B,ad_MODEM_OOK_CNT1,API_WRITER);
  
 //RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12
  API_WRITER[0]=0XA2;          API_WRITER[1]=0x81;
  API_WRITER[2]=0x26;          API_WRITER[3]=0xAF;
  API_WRITER[4]=0x3F;          API_WRITER[5]=0xEE;
  API_WRITER[6]=0xC8;          API_WRITER[7]=0xC7;
  API_WRITER[8]=0XDB;          API_WRITER[9]=0xF2;
  API_WRITER[10]=0x02;         API_WRITER[11]=0x08;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX1_CHFLT_COE_13,API_WRITER); 
  
  //RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12
  API_WRITER[0]=0X07;          API_WRITER[1]=0x03;
  API_WRITER[2]=0x15;          API_WRITER[3]=0xFC;
  API_WRITER[4]=0x0F;          API_WRITER[5]=0x00;
  API_WRITER[6]=0xA2;          API_WRITER[7]=0x81;
  API_WRITER[8]=0X26;          API_WRITER[9]=0xAF;
  API_WRITER[10]=0x3F;         API_WRITER[11]=0xEE;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX1_CHFLT_COE_1,API_WRITER); 
  
  //RF_MODEM_RX2_CHFLT_RX2_CHFLT_COE7_7_0_12
  API_WRITER[0]=0XC8;          API_WRITER[1]=0xC7;
  API_WRITER[2]=0xDB;          API_WRITER[3]=0xF2;
  API_WRITER[4]=0x02;          API_WRITER[5]=0x08;
  API_WRITER[6]=0x07;          API_WRITER[7]=0x03;
  API_WRITER[8]=0X15;          API_WRITER[9]=0xFC;
  API_WRITER[10]=0x0F;         API_WRITER[11]=0x00;
  API_SET_PROPERTY_X(Group_MODEM_CHFLT,0X0C,ad_MODEM_CHFLT_RX2_CHFLT_COE_7,API_WRITER); 
  
  //RF_PA_MODE_4  ���ʷŴ���
  PA_MODE(0x08);
  PA_PWR_LVL(0x7f);
  PA_BIAS_CLKDUTY(0x00);
  PA_TC(0x3d);
    
  //RF_SYNTH_PFDCP_CPFF_7
  SYNTH_PFDCP_CPFF(0X2C);
  SYNTH_PFDCP_CPINT(0X0E);
  VCO_KV(0X0B);
  SYNTH_LPFILT3(0X04);
  SYNTH_LPFILT2(0X0C);
  SYNTH_LPFILT1(0X73);
  SYNTH_LPFILT0(0X03);
  
  //RF_MATCH_VALUE_1_12
  /****************************/
  
  //RF_FREQ_CONTROL_INTE_8
  FREQ_CONTROL_INTE(0x3d);     //����Ƶ��470.1MHz  ������200khz
  FREQ_CONTROL_FRAC_2(0x0d);
  FREQ_CONTROL_FRAC_1(0x70);
  FREQ_CONTROL_FRAC_0(0xa3);
  FREQ_CONTROL_CHANNEL_STEP_SIZE_1(0x36);
  FREQ_CONTROL_CHANNEL_STEP_SIZE_0(0x9d);
  FREQ_CONTROL_W_SIZE(0x20);
  FREQ_CONTROL_VCOCNT_RX_ADJ(0xfe);
  API_Get_All_IntStatus(0x08,IntSta);
  
}

/**����RF��������Ӧ��Ƶ��*/
void InitRFChipWorkBand()
{
          // InitRFChipB470_Baud4000();
             InitRFChipB470_Baud40000();
}

/*********************************************************************/
/*  �������ݰ���                                                     */
/*  ��������:                                                        */
/*   char *txBuffer: �����͵����ݣ�                                  */
/*   int size�����txBuffer���ܹ���Ҫ���͵����ݳ���                  */
/*   �����͵����ݳ��Ȳ����� 255-5 ��250�ֽ�                          */
/*  ��������ֵ ��0: ���ͳɹ�;-1������ʧ��;-2:���ݳ���̫��;           */
/*  ������Ϻ��Զ��������̬                                         */
/*********************************************************************/
 int RFSendPacket(unsigned char *txBuffer, int size)
 {
#ifdef LengthFieldInTwoByte
   if(size>8187)
     return -2;
   unsigned int MaxSize=8187;   //������ܹ����͵������
   unsigned char TxBuffer[8191]; //�������ݻ���  
#else
   if(size>251)
     return -2;
   unsigned int MaxSize=251;    //������ܹ����͵������
   unsigned char TXBuffer[255]; //�������ݻ���
#endif
   unsigned char IntSta[8];     //�洢�жϱ�־
   unsigned int  DataSent=0;
   unsigned char length=size+4;
   unsigned char ret[2];

   //���������͵�����֡��ʽ��һ����Ҫ�󣬵�һ���ֽ�ҪΪ����֡���ܳ���
   //�����ݰ�����PKT_LEN(??)�ֶθı�ʱ����ʽҪ���Ÿı䣬����ο������ֲ�
#ifdef LengthFieldInTwoByte        //�����ֽڱ�ʾ����֡���ȣ��ܹ����ʹ���255�ֽڵ�����
     for(int i=2;i<size;i++)
   {
     TXBuffer[i+4]=txBuffer[i];
   }
   
    TXBuffer[0]=length/256;
    TXBuffer[1]=length%256;
   if(g_uchConfigFlag==0)
   {
      TXBuffer[2] = g_PHYDevInfo.IntegratorID.ucIntegratorID[0];   //������ID
      TXBuffer[3] = g_PHYDevInfo.IntegratorID.ucIntegratorID[1];
      TXBuffer[4] = g_PHYDevInfo.ProjectID.ucProjectID[0];          //�豸����ID
      TXBuffer[5] = g_PHYDevInfo.ProjectID.ucProjectID[1];
     
   }
   else
   {
     TXBuffer[5]=TXBuffer[2]=TXBuffer[3]=TXBuffer[4]=0x88;
   }
   PKT_FIELD_2_LENGTH_7_0(TXBuffer[1]-1);         //�ֶ�2�ĳ�������
   PKT_FIELD_2_LENGTH_12_8(TXBuffer[0]);          //�ֶ�2�ĳ�������
  
#else                           //һ���ֽڱ�ʾ����֡�ĳ���
   for(int i=1;i<size;i++)
   {
     TXBuffer[i+4]=txBuffer[i];
   }
   
    TXBuffer[0]=length;
  // if(g_uchConfigFlag==0)
   {
 //     TXBuffer[1] = g_PHYDevInfo.IntegratorID.ucIntegratorID[0];   //������ID
  //    TXBuffer[2] = g_PHYDevInfo.IntegratorID.ucIntegratorID[1];
   //   TXBuffer[3] = g_PHYDevInfo.ProjectID.ucProjectID[0];          //�豸����ID
   //   TXBuffer[4] = g_PHYDevInfo.ProjectID.ucProjectID[1];
     
   }
  // else
   {
     TXBuffer[1]=TXBuffer[2]=TXBuffer[3]=TXBuffer[4]=0x88;
   }
   PKT_FIELD_2_LENGTH_7_0(length-1);         //�ֶ�2�ĳ�������
#endif


 //���ﲻҪһ��������FIFO����������ᵼ��FIFO�����ʹ�����ݷ��Ͳ���ȷ
   if(size<=50)      //����FIFO�л�ʣ��10���ֽڵĿ�λ
   {
       API_ClearTxFIFO();
       INT_CTL_ENABLE(0x01);                  //�������ݰ��ж�
       INT_CTL_PH_ENABLE(0x20);               //�������ݷ�������ж�
       API_WriteTxDataBuffer(length,TXBuffer);      //ע������д�����length
       API_FIFO_INFO(ret);
       SetRFStartTx();               //��ʼ����
     while(GET_NIRQ_BIT);
       
     API_FIFO_INFO(ret);  
     API_Get_All_IntStatus(0x08,IntSta);    //����жϱ�־
        if(IntSta[3]&0x20)
        {
          return 0;   //���ͳɹ�
        } 
        else
        {
          return -1;     //����ʧ��
        }
       
   }
   else if(size<=MaxSize)
   {
     size-=50;
     DataSent=54;            //һ�����д��54�ֽڵ�FIFO��
     INT_CTL_ENABLE(0x01);       //�������ݰ��ж�
     INT_CTL_PH_ENABLE(0x02);    //����FIFO�������
     API_WriteTxDataBuffer(54,TXBuffer);
     API_FIFO_INFO(ret);
     API_Get_All_IntStatus(0x08,IntSta);    //����жϱ�־
     SetRFStartTx();    //��ʼ����
     while(size>48)
     {
         while(GET_NIRQ_BIT);  //�ȴ��жϵĲ��� 
        API_WriteTxDataBuffer(48,TXBuffer+DataSent);
        DataSent=DataSent+48;
        size=size-48;
        API_ClearPHInt();
     }
        while(GET_NIRQ_BIT);        //�ȴ��жϵĲ��� 
        API_WriteTxDataBuffer(size,TXBuffer+DataSent);
        INT_CTL_PH_ENABLE(0x20);    //���ݷ�������ж�
        while(GET_NIRQ_BIT);
        API_Get_All_IntStatus(0x08,IntSta);    //����жϱ�־
        if(IntSta[3]&0x20)
        {
          return 0;   //���ͳɹ�
        } 
        else
        {
          return -1;     //����ʧ��
        }
        
   } 
   return -1;
 }
/****************************************************************************/
/*  �������ݰ������Ȳ���                                                    */
/*  ��������: unsigned char *rxBuffer ��Ž��յ�����                        */ 
/*                                          ,rxBuffer[0] �����Ч���ݰ���С */
/*  ��������ֵ ��0: ���ճɹ���
                -1�����̵�ַ��ƥ��;
                -2: û���յ��κ�����                         
                -3:�յ����ݵ���CRCУ�����                                  
                -4:�յ�ͬ���ֺͲ�������,�����ݽ��ճ�ʱʧ�ܣ�                */
/****************************************************************************/  
 int RFReceivePacket(unsigned char *rxBuffer)
{
   unsigned char IntSta[8];        //�洢�жϱ�־
   unsigned int  offset=0;         //����ƫ��
   unsigned int  HaveReadLen=0;    //�ѽ��ܵ����ݰ�����
   unsigned int  DataLength=0;     //���ݰ��ĳ���
   unsigned char flag=0;           //��һ�����ݵı�־
   unsigned char ReadLen=0;        //ʵ��һ�ζ�ȡ����
   unsigned char OneTimeLen = 48;  //�趨һ�ζ�ȡ���ݳ��� 
   unsigned char IDcheck[4];       //У��ID
       
    //1��ʱ������(1/PHY_MCLK)��,
    unsigned long time = PHY_MCLK_1MS;    //���������ݴ������ʽ��͵�ʱ����Ҫ�޸Ĳ���ʱ��
    time=time*20;
    unsigned long  Timeout=time;
#ifdef  LengthFieldInTwoByte
    PKT_FIELD_2_LENGTH_7_0(0xff);    //���������ݵ����� 
    PKT_FIELD_2_LENGTH_12_8(0x1f);    //���������ݵ����� 
#else
    PKT_FIELD_2_LENGTH_7_0(255);    //���������ݵ����� 
#endif
     
    
   while(--Timeout)
   {
     if(GET_NIRQ_BIT==0)
     {
       API_GetFastResponseRegister(0x50,0x01,IntSta);   //��ȡ�жϱ�־λ
       API_ClearPHInt();                                //������ݰ��ж�
   
       
       if(IntSta[0]&0x80)   //CRCУ�����
       {
         API_ClearRxFIFO();
         return -3;
       }
       
       
       if(IntSta[0]&0x10)   //���ݰ��������
       {
         if(flag==0)  //��һ������
         {
            //�ȶ�ȡ����֡�����ֽڣ��ڶ�ȡ����ID
#ifdef    LengthFieldInTwoByte
             API_ReadRxDataBuffer(0x02,rxBuffer); //��ȡ�����ֽڵ�����֡����
             API_ReadRxDataBuffer(0x04,IDcheck);  //����ID,������ID
             DataLength=rxBuffer[0]*256+rxBuffer[1]-4; //���ݰ��ĳ���
             rxBuffer[0]=DataLength/256;               //����֡���ȵĸ��ֽ�
             rxBuffer[1]=DataLength%256;               //����֡���ȵĵ��ֽ�
#else
             API_ReadRxDataBuffer(0x01,rxBuffer); //��ȡ����֡����
             API_ReadRxDataBuffer(0x04,IDcheck);  //����ID,������ID
             DataLength=rxBuffer[0]-4;            //ȥ������ID������֡���ܳ���
             rxBuffer[0]=DataLength;              //����֡����
#endif
            
             
             if(DataLength<1)
             {
               API_ClearRxFIFO();  //���RxFIFO
               API_ClearPHInt();   //����жϱ�־
               return -4;
             }
             ReadLen=DataLength-1;
             if(ReadLen>0)
                API_ReadRxDataBuffer(ReadLen,rxBuffer+1);
             offset = ReadLen+1;//�ڶ�ȡ�������е�ƫ��
             HaveReadLen = ReadLen+1;                 
         }
         else if(DataLength>offset)
         {
           ReadLen = (DataLength-offset) ;
           API_ReadRxDataBuffer(ReadLen,rxBuffer+offset);
           offset+=ReadLen;
           HaveReadLen+=ReadLen;
         }
            API_ClearRxFIFO();
            return 0;  
       }
       
       
       if(IntSta[0]&0x01)     //RX_fifo����
       {
           if(flag==0)   //�ǵ�һ������
           {
             flag=1;
#ifdef  LengthFieldInTwoByte
             API_ReadRxDataBuffer(0x02,rxBuffer); //��ȡ�����ֽڵ�����֡����
             API_ReadRxDataBuffer(0x04,IDcheck);  //����ID,������ID
             DataLength=rxBuffer[0]*256+rxBuffer[1]-4;
             rxBuffer[0]=DataLength/256;
             rxBuffer[1]=DataLength%256;
#else
             API_ReadRxDataBuffer(0x01,rxBuffer); //��ȡһ���ֽڵ�����֡����
             API_ReadRxDataBuffer(0x04,IDcheck);  //����ID,������ID
             DataLength=rxBuffer[0]-4;
             rxBuffer[0]=DataLength;
#endif       
             if(DataLength<1)     //����֡���ȴ���
             {
                API_ClearRxFIFO();  //���RX_FIFO
                
                 return -4;
             }
               ReadLen=(DataLength-1)<OneTimeLen-5? (DataLength-1):OneTimeLen-5;
             if(ReadLen>0)
                API_ReadRxDataBuffer(ReadLen,rxBuffer+1);    //��ȡʣ��һ���Զ�ȡ���ֽ�
             offset=ReadLen+1;
             HaveReadLen=ReadLen+5; 
             
              //У��ID
          //   if(g_uchConfigFlag == 0)//��������̬ 
                {
                  /* if( (IDcheck[0] != g_PHYDevInfo.IntegratorID.ucIntegratorID[0]) ||
                       (IDcheck[1] != g_PHYDevInfo.IntegratorID.ucIntegratorID[1]) ||
                       (IDcheck[2] != g_PHYDevInfo.ProjectID.ucProjectID[0])       ||
                       (IDcheck[3] != g_PHYDevInfo.ProjectID.ucProjectID[1]) )*/
                                            
                        {
                            API_ClearRxFIFO();  //���RX_FIFO
                            
                            return -1; //��ַ��ƥ��
                            
                        } //end if  ������ID���߹���ID��ƥ��
                   
                  }//end if ��������̬ 
             //else//����̬ 
                  {
                     if( (IDcheck[0] != 0x88) ||
                         (IDcheck[1] != 0x88) ||
                         (IDcheck[2] != 0x88) ||
                         (IDcheck[3] != 0x88) )                                     
                        { 
                            API_ClearRxFIFO();  //���RX_FIFO
                                return -1; //��ַ��ƥ��                        
                        }        //end if  ����̬ID��ƥ��    
                     
                   }//end else ����̬      
             
             if(DataLength==offset)
             {
               API_ClearRxFIFO();  //���RxFIFO
               API_ClearPHInt();   //����жϱ�־
               return 0;
             }
           }   //end if RX_FIFO��������һ������
           else   //���ǵ�һ������
           {
              ReadLen=(DataLength-offset)<OneTimeLen ? (DataLength-offset):OneTimeLen;
              API_ReadRxDataBuffer(ReadLen,rxBuffer+offset); 
              offset=offset+ReadLen;           //λ��
              HaveReadLen=HaveReadLen+ReadLen;
              if(DataLength==offset)
              {
                  API_ClearRxFIFO();  //���RxFIFO
                  API_ClearPHInt();   //����жϱ�־
                  return 0;
              }
           }    //end else RX_FIFO���������ǵ�һ������
           Timeout = time;//ʱ������
           
       }   //end if RX_FIFO��Ҫ��
       
     }  //end if ���жϲ���
     
   }    //end if while
   return -4;
 }