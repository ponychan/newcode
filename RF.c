/*���ļ��Ƕ�PinDefine.h��API����ĵ�һ�η�װ��ͨ����API��װ�ɺ�������RFAPI.c�еĺ�������*/

#include"PinDefine.h"
#include"SPIInterfaceDriver.c"

//����Ϊ��Ƶ�����Ƶ������
//����ĺ궨�������Ƶ��ֲ���Χ
#define RF_FRE_A_AMOUNT   5   //��Ƶ����㶨��A��Ƶ������
#define RF_FRE_B_AMOUNT   0   //��Ƶ����㶨��B��Ƶ������
#define RF_FRE_AMOUNT    (RF_FRE_A_AMOUNT+RF_FRE_B_AMOUNT)  //ϵͳ�ܹ�����Ƶ������

//�趨RSSI�����޶�Ӧֵ
#define RF_RSSI_BEST    -80  //0xF6     //�趨��⵽��"��"�ź�ǿ������ֵ  ��ȡ-80dbm   
#define RF_RSSI_BETTER  -85  //0xEC     //�趨"��"�ź�ǿ������ֵ   ȡ-85dbm
#define RF_RSSI_GOOD    -90  //0xE2     //�趨��⵽��"�Ϻ�"�ź�ǿ������ֵ  ȡ-90dbm
#define RF_RSSI_NORMAL  -95  //0xD8     //�趨һ���ź�ǿ������ֵ    ȡ��95dBm

#define RF_TRANSMIT_RSSI  -85//-90//0xE2 //����ͨ�Ŵ��䷶Χ�ز��ź����޹���ֵ-90dBm
#define RF_LISTEN_RSSI    -75//-95//-100//0xCE //����ͨ��������Χ�ز��ź����޹���ֵ-100dBm
#define RF_RSSI_LOGON    RF_TRANSMIT_RSSI //�趨ע���ź�ǿ������ֵ�����豸���䷶Χ�źŹ���ֵ��ͬ��90dBm

/*API�б�
API_POWER_UP
API_PART_INFO

*/

/******************************
RF���ƹܽ�״̬��ʼ��
******************************/
void RFCtlLineInit()
{
    //GPIO2���뷽��
    SET_GPIO2_IN;//GPIO2���뷽��
    EN_GPIO2_RES;//GPIO2��/��������ʹ��
    GPIO2_OUT_L; //GPIO2��������

    //SDN
    DIS_SDN_RES;//SDN��Ҫ����/��������
    SET_SDN_OUT;//����SDNΪ���  
    SDN_OUT_H;//SDN����ߵ�ƽ RF����power down

    //SCLK
    DIS_SCLK_RES;//SCLK��Ҫ����/��������
    SET_SCLK_OUT;//����SCLKΪ��� 
    SCLK_OUT_L;

    //SDI
    DIS_SDI_RES;//SDI��Ҫ����/��������
    SET_SDI_OUT;//����SDIΪ���
    SDI_OUT_L;
    //SDO
    SDO_OUT_L;//SDO����͵�ƽ
    EN_SDO_RES;//SDOҪ��������  
    SET_SDO_IN;//����SDOΪ����

    //NSEL
    DIS_NSEL_RES;//NSEL��Ҫ����/��������
    SET_NSEL_OUT;//����NSELΪ��� 
    NSEL_OUT_H;

    //NIRQ  �����������룬�ر��ж�
    NIRQ_OUT_H;//NIRQ����ߵ�ƽ 
    EN_NIRQ_RES;//NIRQ����������  
    //DIS_NIRQ_RES;//NIRQ������/��������  
    SET_NIRQ_IN;//�ٶ���NIRQΪ����
    SET_NIRQ_IES;//�����ɸߵ����ж�
    CLR_NIRQ_IFG;//����жϱ��
    DINT_NIRQ;  //�жϹر�
}

/*�������жϲ��ֵķ�������*/
/***************************************************************
��ȡ�жϱ�־��������жϱ�־��ֵ
��ȡ����PH.MODEM.CHIP�����жϵı�־
�βΣ�IntStatusLength������Ļظ����ĳ���
      *IntStatus���洢�ظ����ݵ�����ָ��
����ֵ��0x00:��ȡ����ֵ���ݳɹ�
        0x01:��ȡ����ֵ����ʧ��
****************************************************************/
uchar API_Get_All_IntStatus(uchar IntStatusLength,uchar *IntStatus)
{
    unsigned char API_WRITER[4];
    API_WRITER[0]=CMD_GET_INT_STATUS;
    API_WRITER[1]=0x00;
    API_WRITER[2]=0x00;
    API_WRITER[3]=0x00;
    API_SendCommand(0x04,API_WRITER);
    if(API_GetResponse(IntStatusLength,IntStatus)==0)
        return 0x00;
    return 0x01; 
}

/***************************************************************
������ݰ������״̬��־λ
�βΣ���
����ֵ����
***************************************************************/
void API_ClearPHInt()
{
    unsigned char API_WRITER[2];
    API_WRITER[0]=CMD_GET_INT_STATUS;
    API_WRITER[1]=0x00;
    API_SendCommand(0x02,API_WRITER);
    //��ʱ3���룬�ȴ�NIRQ��־λ�����
    /**ע��***/
    //����ʱ��������ɾ����ɾ�����ܻᵼ���������ݶ�ȡ�Ĵ���
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();
}

/****************************************************************
��ȡ���ݰ�������ж�״̬,���ܻ����״̬��־λ
�βΣ�PHIntStatusLength������״̬���ݵĳ���
      *PHIntStatus���洢�������������ͷָ��
����ֵ��0x00:��ȡ����ֵ���ݳɹ�
        0x01:��ȡ����ֵ����ʧ��
****************************************************************/
uchar API_Get_PH_IntStatus(uchar PHIntStatusLength,uchar *PHIntStatus)
{
    unsigned char API_Writer=CMD_GET_PH_STATUS;
    API_SendCommand(0x01,&API_Writer);
    if(API_GetResponse(PHIntStatusLength,PHIntStatus)==0)
        return 0x00;
    return 0x01;
}

/****************************************************************
��ȡ����״̬���ж�״̬�����ܻ����״̬��־λ
�βΣ�ModemIntStatusLength������״̬���ݵĳ���
      *ModemIntStatus���洢�������������ͷָ��
����ֵ��0x00:��ȡ����ֵ���ݳɹ�
        0x01:��ȡ����ֵ����ʧ��
****************************************************************/
uchar API_Get_Modem_IntStatus(uchar ModemIntStatusLength,uchar *ModemIntStatus)
{
    unsigned char API_Writer=CMD_GET_MODEM_STATUS;
    API_SendCommand(0x01,&API_Writer);
    if(API_GetResponse(ModemIntStatusLength,ModemIntStatus)==0)
        return 0x00;
    return 0x01;
}

/****************************************************************
��ȡоƬ״̬���ж�״̬�����ܻ����״̬��־λ
�β�:ChipIntStatusLength������״̬���ݵĳ���
      *ChipIntStatus���洢�������������ͷָ��
����ֵ��0x00:��ȡ����ֵ���ݳɹ�
        0x01:��ȡ����ֵ����ʧ��
****************************************************************/
uchar  API_Get_Chip_IntStatus(uchar ChipIntStatusLength,uchar *ChipIntStatus)
{
    unsigned char API_Writer=CMD_GET_CHIP_STATUS;
    API_SendCommand(0x01,&API_Writer);
    if(API_GetResponse(ChipIntStatusLength,ChipIntStatus)==0)
        return 0x00;
    return 0x01;
}

/*************************************************************
��ȡоƬ�Ļ�����Ϣ
�βΣ�PARTInfoLength:����оƬ�������ݵĳ���
      *PARTInfo���洢�������������ͷָ��
����ֵ��0x00:��ȡ�豸��Ϣ����
        0x01:��ȡ�豸��Ϣʧ��
*************************************************************/
uchar API_PART_INFO(uchar PARTInfoLength,uchar *PARTInfo)
{
    unsigned char API_WRITER=CMD_PART_INFO; 
    API_SendCommand(0x01,&API_WRITER);
    if(API_GetResponse(PARTInfoLength,PARTInfo)==0)
        return 0x00;
    return 0x01;
}

/*************************************************************
��TXFIFO��д�����ݣ�һ����������д��64�ֽ�
�βΣ�TxFifoLenght��д�����ݵĳ���
      *TxFifoData���洢FIFO���������ͷָ��
����ֵ��0
**************************************************************/
uchar API_WriteTxDataBuffer(uchar TxFifoLenght,uchar *TxFifoData)
{
    NSEL_OUT_L;
    API_SendDataByte(0x66);
    API_SendDataNoResponse(TxFifoLenght,TxFifoData);
    NSEL_OUT_H;
    return 0;
}

/***************************************************************
��RXFIFO�ж�ȡ����
�βΣ�RxFifoLength����ȡ���ݵĳ���
      *RxFifoData���洢RXFIFO�����������ͷָ��
����ֵ��0
***************************************************************/
uchar API_ReadRxDataBuffer(uchar RxFifoLength,uchar *RxFifoData)
{
    NSEL_OUT_L;
    API_SendDataByte(0x77);
    API_GetResponseofSendData(RxFifoLength,RxFifoData);
    NSEL_OUT_H;
    return 0x00;
}

/**************************************************************
���TXFIFO
�βΣ���
����ֵ��TXFIFOʣ��Ŀռ�
        0xff:���TXFIFOʧ��
***************************************************************/
uchar API_ClearTxFIFO(void)
{
    unsigned char API_WRITER[2];
    unsigned char res[2];
    API_WRITER[0]=CMD_FIFO_INFO;
    API_WRITER[1]=0x01;
    API_SendCommand(2,API_WRITER);
    if(API_GetResponse(0x02,res)==0)
        return res[1];
    else
        return 0xff;
}

uchar RFResetTxFIFO()   //������·�㺯��
{
    unsigned char Ret=API_ClearTxFIFO();
    return Ret;
}
/*************************************************************
���RXFIFO
�βΣ���
����ֵ��RXFIFO��ʹ�ÿռ�
        0xff:RXFIFO���ʧ��
**************************************************************/
uchar API_ClearRxFIFO(void)
{
    unsigned char API_WRITER[2];
    unsigned char ReturnValue[2];
    API_WRITER[0]=CMD_FIFO_INFO;
    API_WRITER[1]=0x02;
    API_SendCommand(2,API_WRITER);
    if(API_GetResponse(0x02,ReturnValue)==0)
    return ReturnValue[0];
    else
    {
        return 0xff;
    }
}

uchar RFResetRxFIFO()   //������·�㺯��
{
    unsigned char Ret=API_ClearRxFIFO();
    return Ret;
}

/*********************************************************
��ȡ���ٷ�Ӧ�Ĵ�����Ĵ洢ֵ
�βΣ�bStartReg���Ĵ����Ŀ�ʼ��ַ
      bNumberOfReg����ȡ�Ĵ����ĸ���
      RegValues�� �洢�Ĵ����Ķ�ά����ͷָ��
����ֵ��0x01:���ݶ�ȡ���󣨶�ȡ�Ĵ����������ߵ�ַ����
        0x00:��ȡ���ݳɹ�
**********************************************************/
uchar API_GetFastResponseRegister(uchar bStartReg,uchar bNumberOfReg,uchar *RegValues)
{
    if (bNumberOfReg<=0||bNumberOfReg>4)   //�ж��Ƿ��ȡ�ĸ�������
    {
        return 0x01;
    }
    if (bStartReg==0x50||bStartReg==0x51||bStartReg==0x53||bStartReg==0x57) //�ж�����������Ƿ��Ƕ�ȡ�����Ĵ���������
    {
        NSEL_OUT_L;
        API_SendDataByte(bStartReg);
        API_GetResponseofSendData(bNumberOfReg,RegValues);
        NSEL_OUT_H;
        return 0;
    }
    return 0x01;
}

/*****************************************************************
����FIFO��ʣ��ռ䣬������FIFO
�βΣ��洢ʣ��ռ�Ķ�ά����ͷָ��
����ֵ����*/
void API_FIFO_INFO(uchar *FIFO_INFO)
{
    unsigned char API_WRITER[2];
    API_WRITER[0]=CMD_FIFO_INFO;
    API_WRITER[1]=0x00;
    API_SendCommand(2,API_WRITER);
    API_GetResponse(2,FIFO_INFO);
}
 
 /***************************************************************
 RFͨ��IO�ܽ�����
�βΣ�GPIO0��GPIO0���÷�ʽ
      GPIO1��GPIO1���÷�ʽ
      GPIO2��GPIO2���÷�ʽ
      GPIO3: GPIO3���÷�ʽ
 ����ֵ����
�ο���GPIO0��0X20��GPIO1��0X21
 ***************************************************************/
void API_GPIO_CFG(uchar GPIO0,uchar GPIO1,uchar GPIO2,uchar GPIO3)
{
    unsigned char API_WRITER[8];
    API_WRITER[0]=CMD_GPIO_PIN_CFG; API_WRITER[1]=GPIO0;
    API_WRITER[2]=GPIO1;            API_WRITER[3]=GPIO2;
    API_WRITER[4]=GPIO3;             API_WRITER[5]=0x00;
    API_WRITER[6]=0x00;             API_WRITER[7]=0x00; 
    API_SendCommand(0x08,API_WRITER);
    //API_WaitforCTS();
 }
 
/**********************************************************
�ϵ�оƬ��ʼ��,��RFоƬ�󣬳�ʼ��RF
�βΣ���    ����ֵ����   
�����������������оƬ�ϵ���EZRadio PRO���ܺ;���Ƶ��30MHz��������
**********************************************************/
void API_POWER_UP()
{
    unsigned char API_WRITER[7];
    API_WRITER[0]=CMD_POWER_UP; API_WRITER[1]=0x01;
    API_WRITER[2]=0x00;         API_WRITER[3]=0x01;
    API_WRITER[4]=0xc9;         API_WRITER[5]=0xc3;
    API_WRITER[6]=0x80;         
    API_SendCommand(0x07,API_WRITER);
    API_WaitforCTS();
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();//��ʱ6����
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();
}

/*���úͶ�ȡ�Ĵ���*/
/**********************************************************************
�Ĵ��������ã���ͬһ����Ķ���Ĵ���������������
�βΣ�group���Ĵ�����������
      num_pro����Ҫ�������üĴ����ĸ���
     start_pro�����üĴ�����ĳ�ʼ��ַ
     *Data���Ĵ������õ�����
����ֵ��1��һ�������õļĴ������࣬����ʧ��
        0��һ�������üĴ����ɹ�
************************************************************************/
uchar API_SET_PROPERTY_X(unsigned char group,unsigned char num_pro,unsigned char start_pro,unsigned char *Data)  //unsigned char *Data
{
    uchar API_WRITER[20];       
    uchar m=4;         //��ʼ�Ĵ������ݵ������±�
    uchar num=num_pro; //��Ҫ���õļĴ����ĸ���
    if(num_pro>12)
    {
        return 0x01;
    }
    else
    {
        API_WRITER[0]=CMD_SET_PROPERTY; 
        API_WRITER[1]=group;
        API_WRITER[2]=num_pro;
        API_WRITER[3]=start_pro;
        while(num>0)
        {
            API_WRITER[m]=*Data;
            Data++;
            m++;
            num--; 
        }
        API_SendCommand(num_pro+4,API_WRITER);
        if(API_WaitforCTS())     //CTS����ֵ����
            return 0x01;
        return 0x00;
     }
}

/**********************************************************************
��һ���Ĵ�����������
�βΣ�group:�üĴ�����������\address���üĴ����ĵ�\Data���ԸüĴ������õ�����
����ֵ��0���ԼĴ��������óɹ� 1���ԼĴ���������ʧ��*/
uchar API_SET_PROPERTY_1(unsigned char group,unsigned char address,unsigned char Data)
{
    uchar API_WRITER[5];
    API_WRITER[0]=CMD_SET_PROPERTY; 
    API_WRITER[1]=group;
    API_WRITER[2]=0X01;
    API_WRITER[3]=address;
    API_WRITER[4]=Data;
    API_SendCommand(0x05,API_WRITER);
    if(API_WaitforCTS())
        return 0x01;
    return 0x00;
}

/**��ȡ�Ĵ��������õ�ֵ**/
uchar API_GET_PROPERTY_1(unsigned char group,unsigned char start_pro)
{
    uchar API_PROPERTY;
    uchar API_WRITER[4];
    API_WRITER[0]=CMD_GET_PROPERTY; 
    API_WRITER[1]=group;
    API_WRITER[2]=0x01;
    API_WRITER[3]=start_pro;
    API_SendCommand(0x04,API_WRITER);
    API_GetResponse(0x01,&API_PROPERTY);
    return API_PROPERTY;
}


//RF״̬����
#define RF_Shutdown 0
#define RF_Standby  1
#define RF_Sleep    2
#define RF_SPIactive 3
#define RF_Ready    4
#define RF_TxTune   5
#define RF_RxTune   6
#define RF_Tx       7
#define RF_Rx       8

#define RF_SHUTDOWN  RF_Shutdown
#define RF_STANDBY   RF_Standby
#define RF_SLEEP     RF_Sleep
#define RF_READY     RF_Ready
#define RF_RX        RF_Rx
#define RF_TX        RF_Tx
unsigned char g_uchrRFMode;  //RF״̬��־
/******************************************************************
�ı�оƬ������״̬
�βΣ�RFStatus��RF��Ҫ�����״̬
����ֵ��0x01:״̬�ı䲻�ɹ�
        0x00:״̬�ı�ɹ�
******************************************************************/
uchar API_CHANGE_STATE(uchar RFStatus)       //ʹ�øô������ʱ��Ƶģ����뵽��Ӧ��״̬
{
    uchar API_WRITER[2];
    API_WRITER[0]=CMD_CHANGE_STATE;
    API_WRITER[1]=RFStatus;
    API_SendCommand(0x02,API_WRITER);
    if(API_WaitforCTS())
        return 0x01;
    return 0x00;
} 
