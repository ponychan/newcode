/*本文件分为两部分、前面是射频芯片和430连接部分的管脚定义。后面部分是4463射频芯片内置的API命令的定义
这部分的内容将在RF.c中被引用*/

/*RF引脚定义部分*/
#define uchar unsigned char 
/*RF管脚定义：
   SDN:P8.2     关断控制
   NSEL:P8.1    SPI通讯允许选择...NSEL管脚拉低初始化通讯接口
   SCLK:P8.0    SPI时钟信号管脚，运行最大10MHz
   SDI:P7.3     数据输入管脚
   SDO:P7.2     数据输出管脚
   NIRQ:P1.6    中断管脚
   GPIO2:P8.4   功能待定???????
*/
//<注意>：在一些管脚中，当PXSEL的管脚选择第一功能的时候，就具有外部中断功能
//GPIO2管脚P8.4没有外部中断功能，所以也不存在P8IE
#define RF_SI_GPIO2_PxOUT        P8OUT       //输出电平控制
#define RF_SI_GPIO2_PxIN         P8IN        //输入电平判断
#define RF_SI_GPIO2_PxDIR        P8DIR        //方向控制
#define RF_SI_GPIO2_PxREN        P8REN        //上/下拉电阻使能控制
#define RF_SI_GPIO2_PxIES        P8IES        //中断产生条件控制
#define RF_SI_GPIO2_PxIFG        P8IFG        //状态标志位
#define RF_SI_GPIO2_PIN          BIT4         //管脚编号

#define RF_SI_NIRQ_PxOUT        P1OUT
#define RF_SI_NIRQ_PxIN         P1IN
#define RF_SI_NIRQ_PxDIR        P1DIR
#define RF_SI_NIRQ_PxREN        P1REN
#define RF_SI_NIRQ_PxIE         P1IE
#define RF_SI_NIRQ_PxIES        P1IES
#define RF_SI_NIRQ_PxIFG        P1IFG
#define RF_SI_NIRQ_PIN          BIT6

#define RF_SI_SDO_PxOUT        P7OUT
#define RF_SI_SDO_PxIN         P7IN
#define RF_SI_SDO_PxDIR        P7DIR
#define RF_SI_SDO_PxREN        P7REN
#define RF_SI_SDO_PIN          BIT2

#define RF_SI_SDI_PxOUT        P7OUT
#define RF_SI_SDI_PxIN         P7IN
#define RF_SI_SDI_PxDIR        P7DIR
#define RF_SI_SDI_PxREN        P7REN
#define RF_SI_SDI_PIN          BIT3

#define RF_SI_SCLK_PxOUT        P8OUT
#define RF_SI_SCLK_PxIN         P8IN
#define RF_SI_SCLK_PxDIR        P8DIR
#define RF_SI_SCLK_PxREN        P8REN
#define RF_SI_SCLK_PIN          BIT0

#define RF_SI_NSEL_PxOUT        P8OUT
#define RF_SI_NSEL_PxIN         P8IN
#define RF_SI_NSEL_PxDIR        P8DIR
#define RF_SI_NSEL_PxREN        P8REN
#define RF_SI_NSEL_PIN          BIT1

#define RF_SI_SDN_PxOUT        P8OUT
#define RF_SI_SDN_PxIN         P8IN
#define RF_SI_SDN_PxDIR        P8DIR
#define RF_SI_SDN_PxREN        P8REN
#define RF_SI_SDN_PIN          BIT2

//GPIO2相关配置    
#define SET_GPIO2_OUT (RF_SI_GPIO2_PxDIR |= RF_SI_GPIO2_PIN)//GPIO2输出
#define GPIO2_OUT_H   (RF_SI_GPIO2_PxOUT |= RF_SI_GPIO2_PIN)//GPIO2输出高电平
#define GPIO2_OUT_L   (RF_SI_GPIO2_PxOUT &= ~RF_SI_GPIO2_PIN)//GPIO2输出低电平
#define EN_GPIO2_RES  (RF_SI_GPIO2_PxREN |= RF_SI_GPIO2_PIN)//GPIO2带上拉电阻
#define SET_GPIO2_IN  (RF_SI_GPIO2_PxDIR &= ~RF_SI_GPIO2_PIN)//GPIO2为输入
#define GET_GPIO2_BIT  (RF_SI_GPIO2_PxIN & RF_SI_GPIO2_PIN)//获取当前GPIO2的位 
 
//NIRQ中断输入型 
#define SET_NIRQ_OUT  (RF_SI_NIRQ_PxDIR |= RF_SI_NIRQ_PIN)//NIRQ输出 
#define NIRQ_OUT_H    (RF_SI_NIRQ_PxOUT |= RF_SI_NIRQ_PIN)//NIRQ输出高电平 
#define EN_NIRQ_RES   (RF_SI_NIRQ_PxREN |= RF_SI_NIRQ_PIN)//NIRQ带上拉电阻
#define DIS_NIRQ_RES  (RF_SI_NIRQ_PxREN &= ~RF_SI_NIRQ_PIN)//NIRQ不带上拉/下拉电阻
#define SET_NIRQ_IN   (RF_SI_NIRQ_PxDIR &= ~RF_SI_NIRQ_PIN)//NIRQ为输入
#define SET_NIRQ_IES  (RF_SI_NIRQ_PxIES |= RF_SI_NIRQ_PIN)//NIRQ高到底中断
#define CLR_NIRQ_IFG  (RF_SI_NIRQ_PxIFG &= ~RF_SI_NIRQ_PIN)//清除中断标记
#define EINT_NIRQ     (RF_SI_NIRQ_PxIE |= RF_SI_NIRQ_PIN)//允许NIRQ中断
#define DINT_NIRQ     (RF_SI_NIRQ_PxIE &= ~RF_SI_NIRQ_PIN)//禁止NIRQ中断
#define GET_NIRQ_BIT  (RF_SI_NIRQ_PxIN & RF_SI_NIRQ_PIN)//获取当前NIRQ的位

//SDO输入  ==射频的输出对应MCU的输入
#define DIS_SDO_RES   (RF_SI_SDO_PxREN &= ~RF_SI_SDO_PIN)//SDO不要上拉/下拉电阻
#define EN_SDO_RES    (RF_SI_SDO_PxREN |= RF_SI_SDO_PIN)//SDO要下拉电阻
#define SDO_OUT_H     (RF_SI_SDO_PxOUT |= RF_SI_SDO_PIN)//SDO输出高电平
#define SDO_OUT_L     (RF_SI_SDO_PxOUT &= ~RF_SI_SDO_PIN)//SDO输出低电平
#define SET_SDO_IN    (RF_SI_SDO_PxDIR &= ~RF_SI_SDO_PIN)//定义SDO为输入
#define GET_SDO_BIT   (RF_SI_SDO_PxIN & RF_SI_SDO_PIN)//获取当前SDO的位

//SDI输出
#define DIS_SDI_RES   (RF_SI_SDI_PxREN &= ~RF_SI_SDI_PIN)//SDI不要上拉/下拉电阻
#define SET_SDI_OUT   (RF_SI_SDI_PxDIR |= RF_SI_SDI_PIN)//定义SDI为输出
#define SDI_OUT_H     (RF_SI_SDI_PxOUT |= RF_SI_SDI_PIN)//SDI输出高电平
#define SDI_OUT_L     (RF_SI_SDI_PxOUT &= ~RF_SI_SDI_PIN)//SDI输出低电平

//SCLK输出
#define DIS_SCLK_RES  (RF_SI_SCLK_PxREN &= ~RF_SI_SCLK_PIN)//SCLK不要上拉/下拉电阻
#define SET_SCLK_OUT  (RF_SI_SCLK_PxDIR |= RF_SI_SCLK_PIN)//定义SCLK为输出 
#define SCLK_OUT_H    (RF_SI_SCLK_PxOUT |= RF_SI_SCLK_PIN)//SCLK输出高电平
#define SCLK_OUT_L    (RF_SI_SCLK_PxOUT &= ~RF_SI_SCLK_PIN)//SCLK输出低电平

//NSEL输出
#define DIS_NSEL_RES  (RF_SI_NSEL_PxREN &= ~RF_SI_NSEL_PIN)//NSEL不要上拉/下拉电阻
#define SET_NSEL_OUT  (RF_SI_NSEL_PxDIR |= RF_SI_NSEL_PIN)//定义NSEL为输出 
#define NSEL_OUT_H    (RF_SI_NSEL_PxOUT |= RF_SI_NSEL_PIN)//NSEL输出高电平
#define NSEL_OUT_L    (RF_SI_NSEL_PxOUT &= ~RF_SI_NSEL_PIN)//NSEL输出低电平


//SDN输出
#define DIS_SDN_RES   (RF_SI_SDN_PxREN &= ~RF_SI_SDN_PIN)//SDN不要上拉/下拉电阻
#define SET_SDN_OUT   (RF_SI_SDN_PxDIR |= RF_SI_SDN_PIN)//定义SDN为输出
#define SDN_OUT_H     (RF_SI_SDN_PxOUT |= RF_SI_SDN_PIN)//SDN输出高电平
#define SDN_OUT_L     (RF_SI_SDN_PxOUT &= ~RF_SI_SDN_PIN)//SDN输出低电平


/*RF芯片内置API部分，分为Commands命令和Properties参数
API接口可以做的事情：向射频芯片发送命令\读取状态信息
                    设置并获取射频参数\处理发送和接收队列*/
/*Commands命令*/
/*Boot Commands为设备上电并选择操作模式和功能*/
#define CMD_POWER_UP  0x02
/*Common Commands*/
#define CMD_NOP             0x00//空命令
#define CMD_PART_INFO       0x01//报告关于设备的基本信息
#define CMD_FUNC_INFO       0x10//返回设备的功能修订信息
#define CMD_SET_PROPERTY    0x11//设置设备的一个或多个属性的值
#define CMD_GET_PROPERTY    0x12//检索一个或多个属性的值
#define CMD_GPIO_PIN_CFG    0x13//配置GPIO引脚
#define CMD_FIFO_INFO       0x15//访问TX和RX FIFO中的当前字节计数，并提供重置FIFO的功能。
#define CMD_GET_INT_STATUS  0x20//返回所有可能的中断事件（STATUS和PENDING）的中断状态。可选地，它可以用于清除锁存（PENDING）中断事件。
#define CMD_REQUEST_DEVICE_STATE 0x33//返回当前的河北状态和频段
#define CMD_CHANGE_STATE    0x34//手动将芯片切换到所需的操作状态。
#define CMD_READ_CMD_BUFF   0x44//用于读取CTS和命令响应。
#define CMD_FRR_A_READ      0x50//从FRR_A开始读取快速响应寄存器（FRR）。
#define CMD_FRR_B_READ      0x51//从FRR_B开始读取快速响应寄存器（FRR）。
#define CMD_FRR_C_READ      0x53//从FRR_C开始读取快速响应寄存器（FRR）。
#define CMD_FRR_D_READ      0x57//从FRR_D开始读取快速响应寄存器（FRR）。

/*IR_CAL_COMMANDS*/
#define CMD_IRCAL           0x17//图像抑制校准。
#define CMD_IRCAL_MANUAL    0x1a
/*TX_COMMANDS*/
#define CMD_START_TX        0x31//切换到手动状态并开始传送数据包
#define CMD_WRITE_TX_FIFO   0x66//将数据字节写入发送队列
/*RX_COMMANDS*/
#define CMD_PACKET_INFO     0x16//返回有关接收的最后一个数据包中变量字段长度的信息，并（可选）覆盖字段长度。
#define CMD_GET_MODEM_STATUS 0x22//返回调制解调器中断组的中断状态（STATUS和PENDING）。可选地，它可以用于清除锁存（PENDING）中断事件。
#define CMD_START_RX        0x32//切换到RX状态并开始接收数据包。
#define CMD_RX_HOP          0x36//在RX模式下手动跳到新频率。
#define CMD_READ_RX_FIFO    0x77//从RX FIFO读取数据字节。
/*ADVANCED_COMMANDS*/
#define CMD_GET_ADC_READING 0x14//使用辅助ADC执行转换并返回这些转换的结果。
//#define CMD_PROTOCOL_CFG    0x18//B1和C2版本的API都没有本条
#define CMD_GET_PH_STATUS   0x21//返回数据包处理程序中断组的中断状态（STATUS和PENDING）。可选地，它可以用于清除锁存（PENDING）中断事件。
#define CMD_GET_CHIP_STATUS 0x23//返回芯片中断组的中断状态（STATUS和PENDING）。可选地，它可以用于清除锁存（PENDING）中断事件。


/*Property参数*/
/**********************************
GLOBAL group:0x00
定义格式：第一行是组名称宏定义，后面是组内地址宏定义
***********************************/
#define Group_GLOBAL                  0x00          //组名称定义
#define ad_GLOBAL_XO_TUNE             0x00          
#define ad_GLOBAL_CLK_CFG             0x01
#define ad_GLOBAL_LOW_BATT_THRESH     0x02
#define ad_GLOBAL_CONFIG              0x03
#define ad_GLOBAL_WUT_CONFIG          0x04
#define ad_GLOBAL_WUT_M_15_8          0x05
#define ad_GLOBAL_WUT_M_7_0           0x06
#define ad_GLOBAL_WUT_R               0x07
#define ad_GLOBAL_WUT_LDC             0x08
#define ad_GLOBAL_WUT_CAL             0x09
//算法
#define GLOBAL_XO_TUNE( x )                 API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_XO_TUNE,x)
#define GLOBAL_CLK_CFG( x )                 API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_CLK_CFG,x)
#define GLOBAL_LOW_BATT_THRESH( x )         API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_LOW_BATT_THRESH,x)
#define GLOBAL_CONFIG( x )                  API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_CONFIG,x)
#define GLOBAL_WUT_CONFIG( x )              API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_CONFIG,x)
#define GLOBAL_WUT_M_15_8( x )              API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_M_15_8,x)
#define GLOBAL_WUT_M_7_0( x )               API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_M_7_0,x)
#define GLOBAL_WUT_R( x )                   API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_R,x)
#define GLOBAL_WUT_LDC( x )                 API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_LDC,x)
#define GLOBAL_WUT_CAL( x )                 API_SET_PROPERTY_1(Group_GLOBAL,ad_GLOBAL_WUT_CAL,x)
/******************************************
INT  group:0x01  中断寄存器
定义格式：
组名称宏定义
组内地址宏定义
*******************************************/
#define Grout_INT                     0x01
#define ad_INT_CTL_ENABLE             0x00
#define ad_INT_CTL_PH_ENABLE          0x01
#define ad_INT_CTL_MODEM_ENABLE       0x02
#define ad_INT_CTL_CHIP_ENABLE        0x03
//对单个寄存器进行设置
#define INT_CTL_ENABLE( x )                 API_SET_PROPERTY_1(Grout_INT,ad_INT_CTL_ENABLE,x)
#define INT_CTL_PH_ENABLE( x )              API_SET_PROPERTY_1(Grout_INT,ad_INT_CTL_PH_ENABLE,x)
#define INT_CTL_MODEM_ENABLE( x )           API_SET_PROPERTY_1(Grout_INT,ad_INT_CTL_MODEM_ENABLE,x)
#define INT_CTL_CHIP_ENABLE( x )            API_SET_PROPERTY_1(Grout_INT,ad_INT_CTL_CHIP_ENABLE,x)
//读取寄存器值
#define GET_INT_CTL_ENABLE(void)                 API_GET_PROPERTY_1(Grout_INT,ad_INT_CTL_ENABLE)
#define GET_INT_CTL_PH_ENABLE(void)              API_GET_PROPERTY_1(Grout_INT,ad_INT_CTL_PH_ENABLE)
#define GET_INT_CTL_MODEM_ENABLE(void)           API_GET_PROPERTY_1(Grout_INT,ad_INT_CTL_MODEM_ENABLE)
#define GET_INT_CTL_CHIP_ENABLE(void)            API_GET_PROPERTY_1(Grout_INT,ad_INT_CTL_CHIP_ENABLE)
/*****************************************
FRR  group:0x02   快速反应寄存器 
定义格式：
组名称宏定义
组内地址宏定义
******************************************/
#define Grout_FRR                     0x02
#define ad_FRR_CTL_A_MODE             0x00
#define ad_FRR_CTL_B_MODE             0x01
#define ad_FRR_CTL_C_MODE             0x02
#define ad_FRR_CTL_D_MODE             0x03
//寄存器配置
#define FRR_CTL_A_MODE( x )                 API_SET_PROPERTY_1(Grout_FRR,ad_FRR_CTL_A_MODE,x)
#define FRR_CTL_B_MODE( x )                 API_SET_PROPERTY_1(Grout_FRR,ad_FRR_CTL_B_MODE,x)
#define FRR_CTL_C_MODE( x )                 API_SET_PROPERTY_1(Grout_FRR,ad_FRR_CTL_C_MODE,x)
#define FRR_CTL_D_MODE( x )                 API_SET_PROPERTY_1(Grout_FRR,ad_FRR_CTL_D_MODE,x)
/******************************************
PREAMBLE  group:0x10   前导码寄存器 
定义格式：
组名称宏定义
组内地址宏定义
*******************************************/
#define Group_PREAMBLE                0x10
#define ad_PREAMBLE_TX_LENGTH         0x00
#define ad_PREAMBLE_CONFIG_STD_1      0x01
#define ad_PREAMBLE_CONFIG_NSTD       0x02
#define ad_PREAMBLE_CONFIG_STD_2      0x03
#define ad_PREAMBLE_CONFIG            0x04
#define ad_PREAMBLE_PATTERN_31_24     0x05
#define ad_PREAMBLE_PATTERN_23_16     0x06
#define ad_PREAMBLE_PATTERN_15_8      0x07
#define ad_PREAMBLE_PATTERN_7_0       0x08
/*chenkebao add*/
#define ad_PREAMBLE_POSTAMBLE_CONFIG  0x09
#define ad_PREAMBLE_POSTAMBLE_PATTERN31_24 0x0a
#define ad_PREAMBLE_POSTAMBLE_PATTERN23_16 0x0b
#define ad_PREAMBLE_POSTAMBLE_PATTERN15_8 0x0c
#define ad_PREAMBLE_POSTAMBLE_PATTERN0_7 0x0d
/*chenkebao add end*/

//寄存器配置
#define PREAMBLE_TX_LENGTH(x)             API_SET_PROPERTY_1(Group_PREAMBLE,ad_PREAMBLE_TX_LENGTH,x)      //0X0A
#define PREAMBLE_CONFIG(x)                API_SET_PROPERTY_1(Group_PREAMBLE,ad_PREAMBLE_CONFIG,x)         //0X31
#define PREAMBLE_CONFIG_STD1( x )           API_SET_PROPERTY_1(Group_PREAMBLE,ad_PREAMBLE_CONFIG_STD_1,x)   //
#define PREAMBLE_CONFIG_STD2( x )           API_SET_PROPERTY_1(Group_PREAMBLE,ad_PREAMBLE_CONFIG_STD_2,x)   //
/*******************************************
SYNC  group:0x11    同步字配置寄存器
定义格式：
组名称宏定义
组内地址宏定义
********************************************/
#define Group_SYNC                    0x11
#define ad_SYNC_CONFIG                0x00
#define ad_SYNC_BITS_31_24            0x01
#define ad_SYNC_BITS_23_16            0x02
#define ad_SYNC_BITS_15_8             0x03
#define ad_SYNC_BITS_7_0              0x04
//寄存器配置
#define SYNC_CONFIG( x )                   API_SET_PROPERTY_1(Group_SYNC,ad_SYNC_CONFIG,x) //0X01
#define SYNC_BITS_31_24( x )               API_SET_PROPERTY_1(Group_SYNC,ad_SYNC_BITS_31_24,x) //0XB4
#define SYNC_BITS_23_16( x )               API_SET_PROPERTY_1(Group_SYNC,ad_SYNC_BITS_23_16,x) //0X2B
#define SYNC_BITS_15_8( x )                API_SET_PROPERTY_1(Group_SYNC,ad_SYNC_BITS_15_8,x) //
#define SYNC_BITS_7_0( x )                 API_SET_PROPERTY_1(Group_SYNC,ad_SYNC_BITS_7_0,x) //
/********************************************
PKT grout:0x12    数据包配置
定义格式：
组名称宏定义
组内地址宏定义
********************************************/
#define Group_PKT                     0x12
#define ad_PKT_CRC_CONFIG             0x00
#define ad_PKT_WHT_POLY_15_8          0x01
#define ad_PKT_WHT_POLY_7_0           0x02
#define ad_PKT_WHT_SEED_15_8          0x03
#define ad_PKT_WHT_SEED_7_0           0x04
#define ad_PKT_WHT_BIT_NUM            0x05
#define ad_PKT_CONFIG1                0x06
#define ad_PKT_LEN                    0x08
#define ad_PKT_LEN_FIELD_SOURCE       0x09
#define ad_PKT_LEN_ADJUST             0x0a
#define ad_PKT_TX_THRESHOLD           0x0b
#define ad_PKT_RX_THRESHOLD           0x0c
#define ad_PKT_FIELD_1_LENGTH_15_8    0x0d
#define ad_PKT_FIELD_1_LENGTH_7_0     0x0e
#define ad_PKT_FIELD_1_CONFIG         0x0f
#define ad_PKT_FIELD_1_CRC_CONFIG     0x10
#define ad_PKT_FIELD_2_LENGTH_15_8    0x11
#define ad_PKT_FIELD_2_LENGTH_7_0     0x12
#define ad_PKT_FIELD_2_CONFIG         0x13
#define ad_PKT_FIELD_2_CRC_CONFIG     0x14
#define ad_PKT_FIELD_3_LENGTH_15_8    0x15
#define ad_PKT_FIELD_3_LENGTH_7_0     0x16
#define ad_PKT_FIELD_3_CONFIG         0x17
#define ad_PKT_FIELD_3_CRC_CONFIG     0x18
#define ad_PKT_FIELD_4_LENGTH_15_8    0x19
#define ad_PKT_FIELD_4_LENGTH_7_0     0x1a
#define ad_PKT_FIELD_4_CONFIG         0x1b
#define ad_PKT_FIELD_4_CRC_CONFIG     0x1c 
#define ad_PKT_FIELD_5_LENGTH_15_8    0x1d
#define ad_PKT_FIELD_5_LENGTH_7_0     0x1e
#define ad_PKT_FIELD_5_CONFIG         0x1f
#define ad_PKT_FIELD_5_CRC_CONFIG     0x20
#define ad_PKT_RX_FIELD_1_LENGTH_15_8 0x21
#define ad_PKT_RX_FIELD_1_LENGTH_7_0  0x22
#define ad_PKT_RX_FIELD_1_CONFIG      0x23
#define ad_PKT_RX_FIELD_1_CRC_CONFIG  0x24
#define ad_PKT_RX_FIELD_2_LENGTH_15_8 0x25
#define ad_PKT_RX_FIELD_2_LENGTH_7_0  0x26
#define ad_PKT_RX_FIELD_2_CONFIG      0x27
#define ad_PKT_RX_FIELD_2_CRC_CONFIG  0x28
#define ad_PKT_RX_FIELD_3_LENGTH_15_8 0x29
#define ad_PKT_RX_FIELD_3_LENGTH_7_0  0x2a
#define ad_PKT_RX_FIELD_3_CONFIG      0x2b
#define ad_PKT_RX_FIELD_3_CRC_CONFIG  0x2c
#define ad_PKT_RX_FIELD_4_LENGTH_15_8 0x2d
#define ad_PKT_RX_FIELD_4_LENGTH_7_0  0x2e
#define ad_PKT_RX_FIELD_4_CONFIG      0x2f
#define ad_PKT_RX_FIELD_4_CRC_CONFIG  0x30
#define ad_PKT_RX_FIELD_5_LENGTH_15_8 0x31
#define ad_PKT_RX_FIELD_5_LENGTH_7_0  0x32
#define ad_PKT_RX_FIELD_5_CONFIG      0x33
#define ad_PKT_RX_FIELD_5_CRC_CONFIG  0x34

//寄存器配置
#define PKT_CONFIG1( x )                   API_SET_PROPERTY_1(Group_PKT,ad_PKT_CONFIG1,x) //0X02
#define PKT_LEN(x)                         API_SET_PROPERTY_1(Group_PKT,ad_PKT_LEN,x) //0X02                   
#define PKT_LEN_FIELD_SOURCE(x)            API_SET_PROPERTY_1(Group_PKT,ad_PKT_LEN_FIELD_SOURCE,x)       
#define PKT_LEN_ADJUST(x)                  API_SET_PROPERTY_1(Group_PKT,ad_PKT_LEN_ADJUST,x)              



#define PKT_FIELD_1_CONFIG( x )            API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_1_CONFIG,x) //0X04
#define PKT_FIELD_1_LENGTH_7_0( x )        API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_1_LENGTH_7_0,x) //0X07
#define PKT_FIELD_1_LENGTH_12_8( x )       API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_1_LENGTH_15_8,x) //0X00
#define PKT_FIELD_1_CRC_CONFIG( x )        API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_1_CRC_CONFIG,x) //0X07

#define PKT_FIELD_2_LENGTH_7_0(x)          API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_2_LENGTH_7_0,x) //0X07
#define PKT_FIELD_2_LENGTH_15_8(x)         API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_2_LENGTH_15_8,x) //0X07
#define PKT_FIELD_2_CONFIG(x)             API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_2_CONFIG,x) //0X07
#define PKT_FIELD_2_CRC_CONFIG(x)          API_SET_PROPERTY_1(Group_PKT,ad_PKT_FIELD_2_CRC_CONFIG,x) //0X07

#define PKT_CRC_CONFIG( x )                API_SET_PROPERTY_1(Group_PKT,ad_PKT_CRC_CONFIG,x) //0X00
#define PKT_TX_THRESHOLD(x)                API_SET_PROPERTY_1(Group_PKT,ad_PKT_TX_THRESHOLD,x)
#define PKT_RX_THRESHOLD(x)                API_SET_PROPERTY_1(Group_PKT,ad_PKT_RX_THRESHOLD,x)
/***********************************************
MODEM  group:0x20  调制模式配置寄存器
定义格式：
组名称宏定义
组内地址宏定义
************************************************/
#define Group_MODEM                   0x20
#define ad_MODEM_MOD_TYPE             0x00
#define ad_MODEM_MAP_CONTROL          0x01
#define ad_MODEM_DSM_CTRL             0x02
#define ad_MODEM_DATA_RATE_2          0x03
#define ad_MODEM_DATA_RATE_1          0x04
#define ad_MODEM_DATA_RATE_0          0x05
#define ad_MODEM_TX_NCO_MODEM_3       0x06
#define ad_MODEM_TX_NCO_MODEM_2       0x07
#define ad_MODEM_TX_NCO_MODEM_1       0x08
#define ad_MODEM_TX_NCO_MODEM_0       0x09
#define ad_MODEM_FREQ_DEV_2           0x0a
#define ad_MODEM_FREQ_DEV_1           0x0b
#define ad_MODEM_FREQ_DEV_0           0x0c
#define ad_MODEM_FREQ_OFFSET_1        0x0d
#define ad_MODEM_FREQ_OFFSET_0        0x0e
#define ad_MODEM_TX_FILTER_COEFF_8    0x0f
#define ad_MODEM_TX_FILTER_COEFF_7    0x10
#define ad_MODEM_TX_FILTER_COEFF_6    0x11
#define ad_MODEM_TX_FILTER_COEFF_5    0x12
#define ad_MODEM_TX_FILTER_COEFF_4    0x13
#define ad_MODEM_TX_FILTER_COEFF_3    0x14
#define ad_MODEM_TX_FILTER_COEFF_2    0x15
#define ad_MODEM_TX_FILTER_COEFF_1    0x16
#define ad_MODEM_TX_FILTER_COEFF_0    0x17
#define ad_MODEM_TX_RAMP_DELAY        0x18
#define ad_MODEM_MDM_CTRL             0x19
#define ad_MODEM_IF_CONTROL           0x1a
#define ad_MODEM_IF_FREQ_2            0x1b
#define ad_MODEM_IF_FREQ_1            0x1c
#define ad_MODEM_IF_FREQ_0            0x1d
#define ad_MODEM_DECIMATION_CFG1      0x1e
#define ad_MODEM_DECIMATION_CFG0      0x1f
#define ad_MODEM_BCR_OSR_1            0x22
#define ad_MODEM_BCR_OSR_0            0x23
#define ad_MODEM_BCR_NCO_OFFSET_2     0x24
#define ad_MODEM_BCR_NCO_OFFSET_1     0x25
#define ad_MODEM_BCR_NCO_OFFSET_0     0x26
#define ad_MODEM_BCR_GAIN_1           0x27
#define ad_MODEM_BCR_GAIN_0           0x28
#define ad_MODEM_BCR_GEAR             0x29
#define ad_MODEM_BCR_MISC1            0x2a
#define ad_MODEM_BCR_MISC0            0x2b
#define ad_MODEM_AFC_GEAR             0x2c
#define ad_MODEM_AFC_WAIT             0x2d
#define ad_MODEM_AFC_GAIN_1           0x2e
#define ad_MODEM_AFC_GAIN_0           0x2f
#define ad_MODEM_AFC_LIMITER_1        0x30
#define ad_MODEM_AFC_LIMITER_0        0x31
#define ad_MODEM_AFC_MISC             0x32
#define ad_MODEM_AFC_ZIFOFF           0x33
#define ad_MODEM_ADC_CTRL             0x34
#define ad_MODEM_AGC_CONTROL          0x35
#define ad_MODEM_AGC_WINDOW_SIZE      0x38
#define ad_MODEM_AGC_RFPD_DECAY       0x39
#define ad_MODEM_AGC_IFPD_DECAY       0x3a
#define ad_MODEM_FSK4_GAIN1           0x3b
#define ad_MODEM_FSK4_GAIN0           0x3c
#define ad_MODEM_FSK4_TH_1            0x3d
#define ad_MODEM_FSK4_TH_0            0x3e
#define ad_MODEM_FSK4_MAP             0x3f
#define ad_MODEM_OOK_PDTC             0x40
#define ad_MODEM_OOK_BLOPK            0x41
#define ad_MODEM_OOK_CNT1             0x42
#define ad_MODEM_OOK_MISC             0x43
#define ad_MODEM_RAW_SEARCH           0x44
#define ad_MODEM_RAW_CONTROL          0x45
#define ad_MODEM_RAW_EYE_1            0x46
#define ad_MODEM_RAW_EYE_0            0x47
#define ad_MODEM_ANT_DIV_MODE         0x48
#define ad_MODEM_ANT_DIV_CONTROL      0x49
#define ad_MODEM_RSSI_THRESH          0x4a
#define ad_MODEM_RSSI_JUMP_THRESH     0x4b
#define ad_MODEM_RSSI_CONTROL         0x4c
#define ad_MODEM_RSSI_CONTROL2        0x4d
#define ad_MODEM_RSSI_COMP            0x4e
#define ad_MODEM_CLKGEN_BAND          0x51
//寄存器配置
#define MODEM_MOD_TYPE( x )                   API_SET_PROPERTY_1(0X20,0X00,x) 
#define MODEM_MAP_CONTROL( x )                API_SET_PROPERTY_1(0X20,0X01,x) 
#define MODEM_DSM_CONTROL( x )                API_SET_PROPERTY_1(0X20,0X02,x) 
#define MODEM_DATA_RATE_2( x )                API_SET_PROPERTY_1(0X20,0X03,x) 
#define MODEM_DATA_RATE_1( x )                API_SET_PROPERTY_1(0X20,0X04,x) 
#define MODEM_DATA_RATE_0( x )                API_SET_PROPERTY_1(0X20,0X05,x) 
#define MODEM_TX_NCO_MODE_3(x)                API_SET_PROPERTY_1(0X20,0X06,x)
#define MODEM_TX_NCO_MODE_2(x)                API_SET_PROPERTY_1(0X20,0X07,x)
#define MODEM_TX_NCO_MODE_1(x)                API_SET_PROPERTY_1(0X20,0X08,x)
#define MODEM_TX_NCO_MODE_0(x)                API_SET_PROPERTY_1(0X20,0X09,x)
#define MODEM_FREQ_DEV_2(x)                   API_SET_PROPERTY_1(0X20,0X0A,x)
#define MODEM_FREQ_DEV_1(x)                   API_SET_PROPERTY_1(0X20,0X0B,x)
#define MODEM_FREQ_DEV_0(x)                   API_SET_PROPERTY_1(0X20,0X0C,x)
#define MODEM_TX_RAMP_DELAY(x)                API_SET_PROPERTY_1(0X20,0X18,x)
#define MODEM_IF_CONTROL(x)                   API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_IF_CONTROL,x)
#define MODEM_IF_FREQ_2(x)                    API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_IF_FREQ_2,x)
#define MODEM_IF_FREQ_1(x)                    API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_IF_FREQ_1,x)
#define MODEM_IF_FREQ_0(x)                    API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_IF_FREQ_0,x)
#define MODEM_DECIMATION_CFG1(x)              API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_DECIMATION_CFG1,x)
#define MODEM_DECIMATION_CFG0(x)              API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_DECIMATION_CFG0,x)
#define MODEM_CLKGEN_BAND(x)                  API_SET_PROPERTY_1(Group_MODEM,0X51,x)
#define MODEM_RSSI_THRESH(x)                  API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_RSSI_THRESH,x)
#define MODEM_RSSI_JUMP_THRESH(x)             API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_RSSI_JUMP_THRESH,x)
#define MODEM_RSSI_CONTROL(x)                 API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_RSSI_CONTROL,x)
#define MODEM_RSSI_CONTROL2(x)                API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_RSSI_CONTROL2,x)
#define MODEM_RSSI_COMP(x)                    API_SET_PROPERTY_1(Group_MODEM,ad_MODEM_RSSI_COMP,x)
/**********************************************
MODEM_CHFLT group:0x21
定义格式：
组名称宏定义
组内地址宏定义
**********************************************/
#define Group_MODEM_CHFLT                     0x21
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_13       0x00
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_12       0x01
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_11       0x02
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_10       0x03
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_9        0x04
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_8        0x05
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_7        0x06
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_6        0x07
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_5        0x08
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_4        0x09
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_3        0x0a
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_2        0x0b
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_1        0x0c
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_0        0x0d
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_10_13    0x0e
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_6_9      0x0f
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_2_5      0x10
#define ad_MODEM_CHFLT_RX1_CHFLT_COE_0_1      0x11
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_13       0x12
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_12       0x13
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_11       0x14
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_10       0x15
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_9        0x16
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_8        0x17
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_7        0x18
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_6        0x19
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_5        0x1a
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_4        0x1b
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_3        0x1c
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_2        0x1d
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_1        0x1e 
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_0        0x1f
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_10_13    0x20
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_6_9      0x21
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_2_5      0x22
#define ad_MODEM_CHFLT_RX2_CHFLT_COE_0_1      0x23
//寄存器配置

/******************************************************
PA group:0x22 功率放大器配置寄存器
定义格式：
组名称宏定义
组内地址宏定义
*******************************************************/
#define Group_PA                               0x22
#define ad_PA_MODE                             0x00
#define ad_PA_PWR_LVL                          0x01
#define ad_PA_BIAS_CLKDUTY                     0x02
#define ad_PA_TC                               0x03
#define ad_PA_RAMP_EX                          0x04
#define ad_PA_RAMP_DOWN_DELAY                  0x05
//寄存器配置
#define PA_MODE( x )                       API_SET_PROPERTY_1(0X22,0X00,x) //0X08
#define PA_PWR_LVL( x )                    API_SET_PROPERTY_1(0X22,0X01,x) //0X7F
#define PA_BIAS_CLKDUTY( x )               API_SET_PROPERTY_1(0X22,0X02,x) //0X00
#define PA_TC( x )                         API_SET_PROPERTY_1(0X22,0X03,x) //0X3D
/******************************************************
SYNTH group:0x23
定义格式：
组名称宏定义
组内地址宏定义
*******************************************************/
#define Group_SYNTH                           0x23
#define ad_SYNTH_PFDCP_CPFF                   0x00
#define ad_SYNTH_PFDCP_CPINT                  0x01
#define ad_SYNTH_VCO_KV                       0x02
#define ad_SYNTH_LPFILT3                      0x03
#define ad_SYNTH_LPFILT2                      0x04
#define ad_SYNTH_LPFILT1                      0x05
#define ad_SYNTH_LPFILT0                      0x06
#define ad_SYNTH_VCO_KVCAL                    0x07
//寄存器配置
#define SYNTH_PFDCP_CPFF(x)             API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_PFDCP_CPFF,x) 
#define SYNTH_PFDCP_CPINT(x)            API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_PFDCP_CPINT,x)
#define VCO_KV(x)                       API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_VCO_KV,x)
#define SYNTH_LPFILT3(x)                API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_LPFILT3,x) 
#define SYNTH_LPFILT2(x)                API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_LPFILT2,x)
#define SYNTH_LPFILT1(x)                API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_LPFILT1,x)
#define SYNTH_LPFILT0(x)                API_SET_PROPERTY_1(Group_SYNTH,ad_SYNTH_LPFILT0,x)
/*******************************************************
MATCH group:0x30
定义格式：
组名称宏定义
组内地址宏定义
********************************************************/
#define Group_MATCH                           0x30
#define ad_MATCH_VALUE_1                      0x00
#define ad_MATCH_MASK_1                       0x01
#define ad_MATCH_CTRL_1                       0x02
#define ad_MATCH_VALUE_2                      0x03
#define ad_MATCH_MASK_2                       0x04
#define ad_MATCH_CTRL_2                       0x05
#define ad_MATCH_VALUE_3                      0x06
#define ad_MATCH_ MASK_3                      0x07
#define ad_MATCH_CTRL_3                       0x08
#define ad_MATCH_VALUE_4                      0x09
#define ad_MATCH_MASK_4                       0x0a
#define ad_MATCH_CTRL_4                       0x0b
/******************************************************
FREQ_CONTROL group:0x40
定义格式：
组名称宏定义
组内地址宏定义
*******************************************************/
#define Group_FREQ_CONTROL                    0x40
#define ad_FREQ_CONTROL_INTE                  0x00
#define ad_FREQ_CONTROL_FRAC_2                0x01
#define ad_FREQ_CONTROL_FRAC_1                0x02
#define ad_FREQ_CONTROL_FRAC_0                0x03
#define ad_FREQ_CONTROL_CHANNEL_STEP_SIZE_1   0x04
#define ad_FREQ_CONTROL_CHANNEL_STEP_SIZE_0   0x05
#define ad_FREQ_CONTROL_W_SIZE                0x06
#define ad_FREQ_CONTROL_VCOCNT_RX_ADJ         0x07
//寄存器配置
#define FREQ_CONTROL_INTE(x)                             API_SET_PROPERTY_1(0X40,0X00,x)
#define FREQ_CONTROL_FRAC_2(x)                           API_SET_PROPERTY_1(0X40,0X01,x)
#define FREQ_CONTROL_FRAC_1(x)                           API_SET_PROPERTY_1(0X40,0X02,x)  
#define FREQ_CONTROL_FRAC_0(x)                           API_SET_PROPERTY_1(0X40,0X03,x)
#define FREQ_CONTROL_CHANNEL_STEP_SIZE_1(x)              API_SET_PROPERTY_1(0X40,0X04,x)
#define FREQ_CONTROL_CHANNEL_STEP_SIZE_0(x)              API_SET_PROPERTY_1(0X40,0X05,x)
#define FREQ_CONTROL_W_SIZE(x)                           API_SET_PROPERTY_1(0X40,0X06,x)
#define FREQ_CONTROL_VCOCNT_RX_ADJ(x)                    API_SET_PROPERTY_1(0X40,0X07,x)
/*****************************************************
RX_HOP  group:0x50
定义格式：
组名称宏定义
组内地址宏定义
******************************************************/
#define Group_RX_HOP                          0x50
#define ad_RX_HOP_CONTROL                     0x00
#define ad_RX_HOP_TABLE_SIZE                  0x01
#define ad_RX_HOP_TABLE_ENTRY_0               0x02
/*后面包括ad_RX_HOP_TABLE_ENTRY[0-63]宏定义，不一一列举，
使用的时候自行添加*/