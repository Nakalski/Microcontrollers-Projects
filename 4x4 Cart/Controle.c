#include <msp430.h> 
#include <stdio.h>

void ini_uCOn(void);
void ini_P1_P2(void);
void ini_ADC10(void);
void ini_Timer0(void);
void ini_USCI_A0_UART(void);

unsigned int ADC10_vetor[12],processa=0;
unsigned int MED1 = 0, MED2=0, MED3=0, i=0, is_canal,sum=0 ;
unsigned char TX_DATA[4];
int at=-1;
unsigned char tx_index = 0;

void main(void)
{
    ini_P1_P2();
    ini_uCOn();
    ini_ADC10();
    ini_Timer0();
    ini_USCI_A0_UART();

    do{
        if (at==1)
        {
            __bis_SR_register(LPM3_bits + GIE);

        }
        else
        {
            if(processa==1)
            {

                if(MED2<600 && MED2 >400 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='5';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>600 && MED2<700 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='6';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>700 && MED2<800 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='7';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>800 && MED2<900 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='8';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>900 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='9';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>600 && MED3<850 && MED2<600 && MED2 >400)
                {
                    TX_DATA[0]='5';
                    TX_DATA[1]='7';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>850 && MED2<600 && MED2 >400)
                {
                    TX_DATA[0]='5';
                    TX_DATA[1]='9';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<400 && MED3>250 && MED2<600 && MED2 >400)
                {
                    TX_DATA[0]='5';
                    TX_DATA[1]='3';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<250 && MED2<600 && MED2 >400)
                {
                    TX_DATA[0]='5';
                    TX_DATA[1]='1';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2<400 && MED2>250 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='3';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';

                }
                else if(MED2<100 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='1';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>100 && MED2<200 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='2';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>200 && MED2<300 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='3';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED2>300 && MED2<400 && MED3<600 && MED3>400)
                {
                    TX_DATA[0]='4';
                    TX_DATA[1]='5';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>600 && MED3<850 && MED2<850 && MED2 >600)
                {
                    TX_DATA[0]='7';
                    TX_DATA[1]='7';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>850 && MED2>850)
                {
                    TX_DATA[0]='9';
                    TX_DATA[1]='9';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>600 && MED3<850 && MED2<400 && MED2 >250)
                {
                    TX_DATA[0]='3';
                    TX_DATA[1]='7';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3>850 && MED2<250)
                {
                    TX_DATA[0]='1';
                    TX_DATA[1]='9';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<400 && MED3>250 && MED2<400 && MED2 >250)
                {
                    TX_DATA[0]='3';
                    TX_DATA[1]='3';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<250 && MED2<250)
                {
                    TX_DATA[0]='1';
                    TX_DATA[1]='1';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<400 && MED3>250 && MED2<600 && MED2 >850)
                {
                    TX_DATA[0]='7';
                    TX_DATA[1]='3';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }
                else if(MED3<250 && MED2>850)
                {
                    TX_DATA[0]='9';
                    TX_DATA[1]='1';
                    TX_DATA[2]='.';
                    TX_DATA[3]='\0';
                }

            processa=0;
            TA0CCTL0 = CCIE;
        }
        }



    }while(1);
}

// RTI de TX pela USCI - A0
#pragma vector=USCIAB0TX_VECTOR
__interrupt void RTI_USCI_TX(void){

    IFG2 &= ~UCA0TXIFG; // Limpa flag de TX

    if( TX_DATA[tx_index] == '\0'  ){
        tx_index = 0;
    }else{
        UCA0TXBUF = TX_DATA[tx_index];
        tx_index++;
    }

}



void ini_USCI_A0_UART(void){

    UCA0CTL1 = UCSSEL1 + UCSWRST;
    UCA0CTL0 = 0;
    UCA0BR0 = 0xA0;
    UCA0BR1 = 0x01;
    UCA0MCTL = UCBRS1;
    // Config. da Porta
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    UCA0CTL1 &= ~UCSWRST;
    IFG2 &= ~UCA0TXIFG;
    IE2 |= UCA0TXIE + UCA0RXIE;
}


// RTI do Mod. 0 do Timer 0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void RTI_M0_TIMER0(void)
{
    IFG2 |= UCA0TXIFG;
    ADC10CTL1 = INCH1 + INCH0 + CONSEQ1;
    ADC10AE0 = BIT3;
    ADC10DTC1 = 12;
    ADC10SA = &ADC10_vetor[0];
    is_canal=4;
    ADC10CTL0 |= (ENC + ADC10SC);
}


#pragma vector=ADC10_VECTOR
__interrupt void RTI_ADC10(void)
{
    ADC10CTL0 &= ~(ENC+ADC10SC);
    TA0CCTL0 &= ~(CCIE);
    switch (is_canal)
    {
        case 4:
        {
            for(i=0;i<12;i++)
            {
                sum=sum+ADC10_vetor[i];
            }
            MED1=sum/12;
            sum=0;
            is_canal=5;
            ADC10CTL1 = INCH2  + CONSEQ1;
            ADC10AE0 = BIT4;
            ADC10DTC1 = 12;
            ADC10SA = &ADC10_vetor[0];
            ADC10CTL0 |= (ENC + ADC10SC);
            break;
        }
        case 5:
        {
            for(i=0;i<12;i++)
            {
                sum=sum+ADC10_vetor[i];
            }
            MED2=sum/12;
            sum=0;
            is_canal=6;
            ADC10CTL1 = INCH2 + INCH0  + CONSEQ1;
            ADC10AE0 = BIT5;
            ADC10DTC1 = 12;
            ADC10SA = &ADC10_vetor[0];
            ADC10CTL0 |= (ENC + ADC10SC);
            break;
        }
        case 6:
        {
            for(i=0;i<12;i++)
            {
                sum=sum+ADC10_vetor[i];
            }
            MED3=sum/12;
            sum=0;
            processa=1;

            break;
        }
    }

}


void ini_Timer0(void)
{
    TA0CTL = TASSEL1 + MC0 + ID0 + ID1;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 49999;

}



void ini_ADC10(void)
{
    ADC10CTL0 = ADC10SHT0 + ADC10ON + ADC10IE + MSC;
    ADC10CTL1 = INCH1 + INCH0 + CONSEQ1;
    ADC10AE0 = BIT3;
}


void ini_uCOn(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Para o watchdog timer
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS1;
    __enable_interrupt();

}

// RT1 da PORTA 1
#pragma  vector=PORT1_VECTOR
__interrupt void P1_RTI(void){

    P1IFG &= ~BIT6;
    TX_DATA[0]='0';
    TX_DATA[1]='0';
    TX_DATA[2]='.';
    TX_DATA[3]='\0';
    P1OUT ^= BIT5;
    at=at*-1;
    _low_power_mode_off_on_exit();
}


void ini_P1_P2(void)
{
    P1DIR = BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT7;
    P1REN = BIT6;
    P1OUT = BIT6;
    P1IES = BIT6;
    P1IFG = 0;
    P1IE = BIT6;
    P2DIR = 0xFF;
    P2OUT = 0;
}
