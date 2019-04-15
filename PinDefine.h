
/*
RF管脚定义：
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
#define RF_SI_GPIO2_PIN          BIT4          //管脚编号

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