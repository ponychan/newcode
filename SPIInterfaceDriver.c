//SPI Interface Driver
#define  uchar unsigned char


/**************************************
发送一个字节的数据
形参：Data需要发送的数据
返回值：无
****************************************/
void  API_SendDataByte(uchar Data)   //子函数
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
发送多个字节的数据，不获取返回值
形参：DataLength发送数据长度
      *Data：数组头指针
返回值：无
***************************************/
void API_SendDataNoResponse(uchar DataLength,uchar *Data)   //子函数
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
得到发送数据的返回值，仅仅是获取输出字节的函数
形参：DataLength返回值的长度
      *Data存储返回值数组的头指针
返回值：无
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
      if(GET_SDO_BIT)     //如果返回的是高电平
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
发送命令函数
形参：CmdLength命令的长度
      *CmdData命令数组的头指针
返回值：0
**************************************************/
uchar API_SendCommand(uchar CmdLength,uchar *CmdData)
{  
    NSEL_OUT_L;        //NSEL低电平初始化通讯接口
    API_SendDataNoResponse(CmdLength,CmdData);
    NSEL_OUT_H;
    return 0x00;
}

/***************************************************
当完成发送命令后，得到发送命令后得到的返回值
形参：DataLength返回数据的长度
     *Data存储返回数据的数组头指针
返回值：0：获取返回数据成功
        1：获取返回数据失败
 ****************************************************/
uchar API_GetResponse(uchar DataLength,uchar *Data)
{
     unsigned char CTS_value=0;     //返回的CTS
     unsigned int  CTS_err=0;       //读取CTS错误的次数
     while(CTS_value!=0xff)    //判断是否完成命令，判断CTS
    {
      NSEL_OUT_L;
      API_SendDataByte(CMD_READ_CMD_BUFF);   //发送READ_CMD_BUFFER命令
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
     API_SendDataGetResponse(DataLength,Data); //CTS完成后可以读取BUFFER的值
     NSEL_OUT_H;
     return 0;
}

/***********************************************************
等待命令处理的完成，得到正确的CTS
返回值：0:处理命令成功
        1:处理命令失败
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