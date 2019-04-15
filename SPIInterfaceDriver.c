//SPI Interface Driver
#define  uchar unsigned char


/**************************************
����һ���ֽڵ�����
�βΣ�Data��Ҫ���͵�����
����ֵ����
****************************************/
void  API_SendDataByte(uchar Data)   //�Ӻ���
{
     unsigned char i; 

    for(i=0;i<8;i++)
    { 
        if(Data&0x80)
        {
          SDI_OUT_H;
        }
        else
        {
          SDI_OUT_L;
        }
        //_NOP();_NOP();_NOP();_NOP();
        SCLK_OUT_H;   
        //_NOP();_NOP();_NOP();_NOP(); 
        SCLK_OUT_L;   
       // _NOP();_NOP();_NOP();_NOP();  
        Data<<=1;
   }
}

/***************************************
���Ͷ���ֽڵ����ݣ�����ȡ����ֵ
�βΣ�DataLength�������ݳ���
      *Data������ͷָ��
����ֵ����
***************************************/
void API_SendDataNoResponse(uchar DataLength,uchar *Data)   //�Ӻ���
{
   unsigned char i;
   unsigned char data_in;
   while(DataLength>0)
   {      
         data_in=*Data;
         for(i=0;i<8;i++)
         {
             if(data_in&0x80)
            {
               SDI_OUT_H; 
            }
             else
            {
               SDI_OUT_L;
            }
          //  _NOP();_NOP();_NOP();_NOP();_NOP();
            SCLK_OUT_H;
            //_NOP();_NOP();_NOP();_NOP();_NOP();
            SCLK_OUT_L; 
            //_NOP();_NOP();_NOP();_NOP();_NOP(); 
            data_in<<=1;   
        }
        Data++;
        DataLength--;  
   }
}

/************************************************
�õ��������ݵķ���ֵ�������ǻ�ȡ����ֽڵĺ���
�βΣ�DataLength����ֵ�ĳ���
      *Data�洢����ֵ�����ͷָ��
����ֵ����
************************************************/
void API_SendDataGetResponse(uchar DataLength,uchar *Data)
{
  unsigned char i;
  unsigned char data_out=0x00;
  while(DataLength>0)
  { 
    for(i=0;i<8;i++)
    {
      data_out<<=1;
      //_NOP();_NOP();_NOP();_NOP();
      if(GET_SDO_BIT)     //������ص��Ǹߵ�ƽ
      {
        data_out=data_out|0x01;
      }
      SCLK_OUT_H;
      //_NOP();_NOP();_NOP();_NOP();_NOP(); 
      SCLK_OUT_L;  
     // _NOP();_NOP();_NOP();_NOP();_NOP(); 
    }
      *Data=data_out;
      data_out=0x00;
      Data++;
      DataLength-- ;
  }  
}

/*************************************************
���������
�βΣ�CmdLength����ĳ���
      *CmdData���������ͷָ��
����ֵ��0
**************************************************/
uchar API_SendCommand(uchar CmdLength,uchar *CmdData)
{  
    NSEL_OUT_L;        //NSEL�͵�ƽ��ʼ��ͨѶ�ӿ�
    API_SendDataNoResponse(CmdLength,CmdData);
    NSEL_OUT_H;
    return 0x00;
}

/***************************************************
����ɷ�������󣬵õ����������õ��ķ���ֵ
�βΣ�DataLength�������ݵĳ���
     *Data�洢�������ݵ�����ͷָ��
����ֵ��0����ȡ�������ݳɹ�
        1����ȡ��������ʧ��
 ****************************************************/
uchar API_GetResponse(uchar DataLength,uchar *Data)
{
     unsigned char CTS_value=0;     //���ص�CTS
     unsigned int  CTS_err=0;       //��ȡCTS����Ĵ���
     while(CTS_value!=0xff)    //�ж��Ƿ��������ж�CTS
    {
      NSEL_OUT_L;
      API_SendDataByte(CMD_READ_CMD_BUFF);   //����READ_CMD_BUFFER����
      API_SendDataGetResponse(1,&CTS_value);
      if(CTS_value!=0xff)
        {
          CTS_value=0;
          NSEL_OUT_H;
        }
      if(++CTS_err>=MAX_CTS_RETRY)
        {
         return 1;
        }
    }
     API_SendDataGetResponse(DataLength,Data); //CTS��ɺ���Զ�ȡBUFFER��ֵ
     NSEL_OUT_H;
     return 0;
}

/***********************************************************
�ȴ���������ɣ��õ���ȷ��CTS
����ֵ��0:��������ɹ�
        1:��������ʧ��
*************************************************************/
uchar API_WaitforCTS(void)
{
     unsigned char CTS_value=0;
     unsigned int  CTS_err=0;
     while(CTS_value!=0xff)
     {
        NSEL_OUT_L;
        API_SendDataByte(CMD_READ_CMD_BUFF);
        API_SendDataGetResponse(1,&CTS_value);
        NSEL_OUT_H;
        if(++CTS_err>=MAX_CTS_RETRY)
           { 
             CTS_value=0x00;
             return 1;
           }
     }
         return 0; 
}   