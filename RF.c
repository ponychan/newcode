/*本文件是对PinDefine.h中API命令的第一次封装，通过把API封装成函数，供RFAPI.c中的函数调用*/

#include"PinDefine.h"
#include"SPIInterfaceDriver.c"

//以下为射频物理层频道参数
//下面的宏定义给出了频点分布范围
#define RF_FRE_A_AMOUNT   5   //射频物理层定义A区频点数量
#define RF_FRE_B_AMOUNT   0   //射频物理层定义B区频点数量
#define RF_FRE_AMOUNT    (RF_FRE_A_AMOUNT+RF_FRE_B_AMOUNT)  //系统总共可用频点数量

//设定RSSI的下限对应值
#define RF_RSSI_BEST    -80  //0xF6     //设定监测到的"优"信号强度下限值  ，取-80dbm   
#define RF_RSSI_BETTER  -85  //0xEC     //设定"好"信号强度下限值   取-85dbm
#define RF_RSSI_GOOD    -90  //0xE2     //设定监测到的"较好"信号强度下限值  取-90dbm
#define RF_RSSI_NORMAL  -95  //0xD8     //设定一般信号强度下限值    取－95dBm

#define RF_TRANSMIT_RSSI  -85//-90//0xE2 //无线通信传输范围载波信号下限功率值-90dBm
#define RF_LISTEN_RSSI    -75//-95//-100//0xCE //无线通信侦听范围载波信号下限功率值-100dBm
#define RF_RSSI_LOGON    RF_TRANSMIT_RSSI //设定注册信号强度下限值，和设备传输范围信号功率值相同－90dBm

/*API列表：
API_POWER_UP
API_PART_INFO

*/

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

/*以下是中断部分的方法定义*/
/***************************************************************
读取中断标志，并清除中断标志的值
读取的是PH.MODEM.CHIP三个中断的标志
形参：IntStatusLength：命令的回复流的长度
      *IntStatus：存储回复数据的数组指针
返回值：0x00:读取返回值数据成功
        0x01:读取返回值数据失败
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
清除数据包处理的状态标志位
形参：无
返回值：无
***************************************************************/
void API_ClearPHInt()
{
    unsigned char API_WRITER[2];
    API_WRITER[0]=CMD_GET_INT_STATUS;
    API_WRITER[1]=0x00;
    API_SendCommand(0x02,API_WRITER);
    //延时3毫秒，等待NIRQ标志位的清除
    /**注意***/
    //该延时函数不可删除，删除可能会导致无线数据读取的错误
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();
}

/****************************************************************
获取数据包处理的中断状态,可能会清除状态标志位
形参：PHIntStatusLength：返回状态数据的长度
      *PHIntStatus：存储返回数据数组的头指针
返回值：0x00:读取返回值数据成功
        0x01:读取返回值数据失败
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
获取调制状态的中断状态，可能会清除状态标志位
形参：ModemIntStatusLength：返回状态数据的长度
      *ModemIntStatus：存储返回数据数组的头指针
返回值：0x00:读取返回值数据成功
        0x01:读取返回值数据失败
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
获取芯片状态的中断状态，可能会清除状态标志位
形参:ChipIntStatusLength：返回状态数据的长度
      *ChipIntStatus：存储返回数据数组的头指针
返回值：0x00:读取返回值数据成功
        0x01:读取返回值数据失败
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
获取芯片的基本信息
形参：PARTInfoLength:返回芯片基本数据的长度
      *PARTInfo：存储返回数据数组的头指针
返回值：0x00:读取设备信息正常
        0x01:读取设备信息失败
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
向TXFIFO中写入数据，一次性最多可以写入64字节
形参：TxFifoLenght：写入数据的长度
      *TxFifoData：存储FIFO数据数组的头指针
返回值：0
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
从RXFIFO中读取数据
形参：RxFifoLength：读取数据的长度
      *RxFifoData：存储RXFIFO中数据数组的头指针
返回值：0
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
清空TXFIFO
形参：无
返回值：TXFIFO剩余的空间
        0xff:清空TXFIFO失败
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

uchar RFResetTxFIFO()   //对于链路层函数
{
    unsigned char Ret=API_ClearTxFIFO();
    return Ret;
}
/*************************************************************
清空RXFIFO
形参：无
返回值：RXFIFO的使用空间
        0xff:RXFIFO清空失败
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

uchar RFResetRxFIFO()   //对于链路层函数
{
    unsigned char Ret=API_ClearRxFIFO();
    return Ret;
}

/*********************************************************
读取快速反应寄存器里的存储值
形参：bStartReg：寄存器的开始地址
      bNumberOfReg：读取寄存器的个数
      RegValues： 存储寄存器的二维数组头指针
返回值：0x01:数据读取错误（读取寄存器个数或者地址错误）
        0x00:读取数据成功
**********************************************************/
uchar API_GetFastResponseRegister(uchar bStartReg,uchar bNumberOfReg,uchar *RegValues)
{
    if (bNumberOfReg<=0||bNumberOfReg>4)   //判读是否读取的个数错误
    {
        return 0x01;
    }
    if (bStartReg==0x50||bStartReg==0x51||bStartReg==0x53||bStartReg==0x57) //判断输入的命令是否是读取几个寄存器的命令
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
读出FIFO的剩余空间，不重置FIFO
形参：存储剩余空间的二维数组头指针
返回值：无*/
void API_FIFO_INFO(uchar *FIFO_INFO)
{
    unsigned char API_WRITER[2];
    API_WRITER[0]=CMD_FIFO_INFO;
    API_WRITER[1]=0x00;
    API_SendCommand(2,API_WRITER);
    API_GetResponse(2,FIFO_INFO);
}
 
 /***************************************************************
 RF通用IO管脚配置
形参：GPIO0：GPIO0配置方式
      GPIO1：GPIO1配置方式
      GPIO2：GPIO2配置方式
      GPIO3: GPIO3配置方式
 返回值：无
参考：GPIO0：0X20，GPIO1：0X21
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
上电芯片初始化,打开RF芯片后，初始化RF
形参：无    返回值：无   
发送启动命令，包含将芯片上电至EZRadio PRO功能和晶振频率30MHz两个参数
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
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();//延时6毫秒
    PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();PHYMCLKSoftDelay1ms();
}

/*设置和读取寄存器*/
/**********************************************************************
寄存器的设置，对同一个组的多个寄存器连续进行设置
形参：group：寄存器所属的组
      num_pro：需要连续设置寄存器的个数
     start_pro：设置寄存器组的初始地址
     *Data：寄存器设置的数据
返回值：1：一次性配置的寄存器过多，配置失败
        0：一次性配置寄存器成功
************************************************************************/
uchar API_SET_PROPERTY_X(unsigned char group,unsigned char num_pro,unsigned char start_pro,unsigned char *Data)  //unsigned char *Data
{
    uchar API_WRITER[20];       
    uchar m=4;         //开始寄存器数据的数组下标
    uchar num=num_pro; //需要配置的寄存器的个数
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
        if(API_WaitforCTS())     //CTS返回值错误
            return 0x01;
        return 0x00;
     }
}

/**********************************************************************
对一个寄存器进行设置
形参：group:该寄存器所属的组\address：该寄存器的地\Data：对该寄存器配置的数据
返回值：0：对寄存器的设置成功 1：对寄存器的设置失败*/
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

/**读取寄存器的设置的值**/
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


//RF状态定义
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
unsigned char g_uchrRFMode;  //RF状态标志
/******************************************************************
改变芯片所处的状态
形参：RFStatus：RF将要进入的状态
返回值：0x01:状态改变不成功
        0x00:状态改变成功
******************************************************************/
uchar API_CHANGE_STATE(uchar RFStatus)       //使用该代码完成时射频模块进入到相应的状态
{
    uchar API_WRITER[2];
    API_WRITER[0]=CMD_CHANGE_STATE;
    API_WRITER[1]=RFStatus;
    API_SendCommand(0x02,API_WRITER);
    if(API_WaitforCTS())
        return 0x01;
    return 0x00;
} 
