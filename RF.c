#include"DevCtrl.c"
#include"RFAPI.c"


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


/***************************************************************
Ӳ������RF Reset RF
****************************************************************/
 void HWResetRF()
{
  uchar IntStatus[8];
  uchar DeviceInfo[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  RFCtlLineInit(); //RF�����߳�ʼ��
  
 
  //SetRFOff();  //�ر�RF  �ر�֮�����ٵȴ�10ns
  //PHYMCLKSoftDelay1ms();   //��ʱ1ms
  //SetRFOn(); //RF����
  //API_PART_INFO(0x08,DeviceInfo);  //��ȡ�豸��Ϣ
  //if(DeviceInfo[1]!=0x44||DeviceInfo[2]!=0x63)  //�ж��豸�Ķ�ȡ��Ϣ�Ƿ���ȷ
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
  //API_Get_All_IntStatus(0x08,IntStatus);//��ȡ�жϱ�־������жϱ�־λ
}


/**********************************************************************
��һ���Ĵ�����������
�βΣ�group:�üĴ�����������
      address���üĴ����ĵ�ַ
      Data���ԸüĴ������õ�����
����ֵ��0���ԼĴ��������óɹ�
        1���ԼĴ���������ʧ��
**********************************************************************/
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