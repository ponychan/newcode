
/*
RF�ܽŶ��壺
   SDN:P8.2     �ضϿ���
   NSEL:P8.1    SPIͨѶ����ѡ��...NSEL�ܽ����ͳ�ʼ��ͨѶ�ӿ�
   SCLK:P8.0    SPIʱ���źŹܽţ��������10MHz
   SDI:P7.3     ��������ܽ�
   SDO:P7.2     ��������ܽ�
   NIRQ:P1.6    �жϹܽ�
   GPIO2:P8.4   ���ܴ���???????
*/
//<ע��>����һЩ�ܽ��У���PXSEL�Ĺܽ�ѡ���һ���ܵ�ʱ�򣬾;����ⲿ�жϹ���
//GPIO2�ܽ�P8.4û���ⲿ�жϹ��ܣ�����Ҳ������P8IE
#define RF_SI_GPIO2_PxOUT        P8OUT       //�����ƽ����
#define RF_SI_GPIO2_PxIN         P8IN        //�����ƽ�ж�
#define RF_SI_GPIO2_PxDIR        P8DIR        //�������
#define RF_SI_GPIO2_PxREN        P8REN        //��/��������ʹ�ܿ���
#define RF_SI_GPIO2_PxIES        P8IES        //�жϲ�����������
#define RF_SI_GPIO2_PxIFG        P8IFG        //״̬��־λ
#define RF_SI_GPIO2_PIN          BIT4          //�ܽű��

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

//GPIO2�������    
#define SET_GPIO2_OUT (RF_SI_GPIO2_PxDIR |= RF_SI_GPIO2_PIN)//GPIO2���
#define GPIO2_OUT_H   (RF_SI_GPIO2_PxOUT |= RF_SI_GPIO2_PIN)//GPIO2����ߵ�ƽ
#define GPIO2_OUT_L   (RF_SI_GPIO2_PxOUT &= ~RF_SI_GPIO2_PIN)//GPIO2����͵�ƽ
#define EN_GPIO2_RES  (RF_SI_GPIO2_PxREN |= RF_SI_GPIO2_PIN)//GPIO2����������
#define SET_GPIO2_IN  (RF_SI_GPIO2_PxDIR &= ~RF_SI_GPIO2_PIN)//GPIO2Ϊ����
#define GET_GPIO2_BIT  (RF_SI_GPIO2_PxIN & RF_SI_GPIO2_PIN)//��ȡ��ǰGPIO2��λ 
 
//NIRQ�ж������� 
#define SET_NIRQ_OUT  (RF_SI_NIRQ_PxDIR |= RF_SI_NIRQ_PIN)//NIRQ��� 
#define NIRQ_OUT_H    (RF_SI_NIRQ_PxOUT |= RF_SI_NIRQ_PIN)//NIRQ����ߵ�ƽ 
#define EN_NIRQ_RES   (RF_SI_NIRQ_PxREN |= RF_SI_NIRQ_PIN)//NIRQ����������
#define DIS_NIRQ_RES  (RF_SI_NIRQ_PxREN &= ~RF_SI_NIRQ_PIN)//NIRQ��������/��������
#define SET_NIRQ_IN   (RF_SI_NIRQ_PxDIR &= ~RF_SI_NIRQ_PIN)//NIRQΪ����
#define SET_NIRQ_IES  (RF_SI_NIRQ_PxIES |= RF_SI_NIRQ_PIN)//NIRQ�ߵ����ж�
#define CLR_NIRQ_IFG  (RF_SI_NIRQ_PxIFG &= ~RF_SI_NIRQ_PIN)//����жϱ��
#define EINT_NIRQ     (RF_SI_NIRQ_PxIE |= RF_SI_NIRQ_PIN)//����NIRQ�ж�
#define DINT_NIRQ     (RF_SI_NIRQ_PxIE &= ~RF_SI_NIRQ_PIN)//��ֹNIRQ�ж�
#define GET_NIRQ_BIT  (RF_SI_NIRQ_PxIN & RF_SI_NIRQ_PIN)//��ȡ��ǰNIRQ��λ

//SDO����  ==��Ƶ�������ӦMCU������
#define DIS_SDO_RES   (RF_SI_SDO_PxREN &= ~RF_SI_SDO_PIN)//SDO��Ҫ����/��������
#define EN_SDO_RES    (RF_SI_SDO_PxREN |= RF_SI_SDO_PIN)//SDOҪ��������
#define SDO_OUT_H     (RF_SI_SDO_PxOUT |= RF_SI_SDO_PIN)//SDO����ߵ�ƽ
#define SDO_OUT_L     (RF_SI_SDO_PxOUT &= ~RF_SI_SDO_PIN)//SDO����͵�ƽ
#define SET_SDO_IN    (RF_SI_SDO_PxDIR &= ~RF_SI_SDO_PIN)//����SDOΪ����
#define GET_SDO_BIT   (RF_SI_SDO_PxIN & RF_SI_SDO_PIN)//��ȡ��ǰSDO��λ

//SDI���
#define DIS_SDI_RES   (RF_SI_SDI_PxREN &= ~RF_SI_SDI_PIN)//SDI��Ҫ����/��������
#define SET_SDI_OUT   (RF_SI_SDI_PxDIR |= RF_SI_SDI_PIN)//����SDIΪ���
#define SDI_OUT_H     (RF_SI_SDI_PxOUT |= RF_SI_SDI_PIN)//SDI����ߵ�ƽ
#define SDI_OUT_L     (RF_SI_SDI_PxOUT &= ~RF_SI_SDI_PIN)//SDI����͵�ƽ

//SCLK���
#define DIS_SCLK_RES  (RF_SI_SCLK_PxREN &= ~RF_SI_SCLK_PIN)//SCLK��Ҫ����/��������
#define SET_SCLK_OUT  (RF_SI_SCLK_PxDIR |= RF_SI_SCLK_PIN)//����SCLKΪ��� 
#define SCLK_OUT_H    (RF_SI_SCLK_PxOUT |= RF_SI_SCLK_PIN)//SCLK����ߵ�ƽ
#define SCLK_OUT_L    (RF_SI_SCLK_PxOUT &= ~RF_SI_SCLK_PIN)//SCLK����͵�ƽ

//NSEL���
#define DIS_NSEL_RES  (RF_SI_NSEL_PxREN &= ~RF_SI_NSEL_PIN)//NSEL��Ҫ����/��������
#define SET_NSEL_OUT  (RF_SI_NSEL_PxDIR |= RF_SI_NSEL_PIN)//����NSELΪ��� 
#define NSEL_OUT_H    (RF_SI_NSEL_PxOUT |= RF_SI_NSEL_PIN)//NSEL����ߵ�ƽ
#define NSEL_OUT_L    (RF_SI_NSEL_PxOUT &= ~RF_SI_NSEL_PIN)//NSEL����͵�ƽ


//SDN���
#define DIS_SDN_RES   (RF_SI_SDN_PxREN &= ~RF_SI_SDN_PIN)//SDN��Ҫ����/��������
#define SET_SDN_OUT   (RF_SI_SDN_PxDIR |= RF_SI_SDN_PIN)//����SDNΪ���
#define SDN_OUT_H     (RF_SI_SDN_PxOUT |= RF_SI_SDN_PIN)//SDN����ߵ�ƽ
#define SDN_OUT_L     (RF_SI_SDN_PxOUT &= ~RF_SI_SDN_PIN)//SDN����͵�ƽ