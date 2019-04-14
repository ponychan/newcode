#include"DevCtrl.c"
#include"RFAPI.c"


/******************************
RF控制管脚状态初始化
******************************/
void RFCtlLineInit()
{
  //GPIO2输入方向
  SET_GPIO2_IN;//GPIO2输入方向
  EN_GPIO2_RES;//GPIO2上/下拉电阻使能
  GPIO2_OUT_L; //GPIO2下拉电阻
  
  //SDN
  DIS_SDN_RES;//SDN不要上拉/下拉电阻
  SET_SDN_OUT;//定义SDN为输出  
  SDN_OUT_H;//SDN输出高电平 RF进入power down
  
  //SCLK
  DIS_SCLK_RES;//SCLK不要上拉/下拉电阻
  SET_SCLK_OUT;//定义SCLK为输出 
  SCLK_OUT_L;
  
  //SDI
  DIS_SDI_RES;//SDI不要上拉/下拉电阻
  SET_SDI_OUT;//定义SDI为输出
  SDI_OUT_L;
  //SDO
  SDO_OUT_L;//SDO输出低电平
  EN_SDO_RES;//SDO要下拉电阻  
  SET_SDO_IN;//定义SDO为输入
  
  //NSEL
  DIS_NSEL_RES;//NSEL不要上拉/下拉电阻
  SET_NSEL_OUT;//定义NSEL为输出 
  NSEL_OUT_H;
  
  //NIRQ  上拉电阻输入，关闭中断
  NIRQ_OUT_H;//NIRQ输出高电平 
  EN_NIRQ_RES;//NIRQ带上拉电阻  
 //DIS_NIRQ_RES;//NIRQ不带上/下拉电阻  
  SET_NIRQ_IN;//再定义NIRQ为输入
  SET_NIRQ_IES;//设置由高到低中断
  CLR_NIRQ_IFG;//清除中断标记
  DINT_NIRQ;  //中断关闭
}


/***************************************************************
硬件重设RF Reset RF
****************************************************************/
 void HWResetRF()
{
  uchar IntStatus[8];
  uchar DeviceInfo[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  RFCtlLineInit(); //RF控制线初始化
  
 
  //SetRFOff();  //关闭RF  关闭之后至少等待10ns
  //PHYMCLKSoftDelay1ms();   //延时1ms
  //SetRFOn(); //RF开机
  //API_PART_INFO(0x08,DeviceInfo);  //读取设备信息
  //if(DeviceInfo[1]!=0x44||DeviceInfo[2]!=0x63)  //判断设备的读取信息是否正确
    {
      int i=200;
      while(1)
      {
        LedRedOn();
        i=200;
        while(--i)
          PHYMCLKSoftDelay1ms();   //延时1ms
         LedRedOff();
        i=200;
        while(--i)
          PHYMCLKSoftDelay1ms();   //延时1ms        
      }
    }
  //API_Get_All_IntStatus(0x08,IntStatus);//读取中断标志，清除中断标志位
}


/**********************************************************************
对一个寄存器进行设置
形参：group:该寄存器所属的组
      address：该寄存器的地址
      Data：对该寄存器配置的数据
返回值：0：对寄存器的设置成功
        1：对寄存器的设置失败
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