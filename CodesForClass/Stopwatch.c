/* Stopwatch, for minutes, seconds, decimal of a second, and centesimal of a second, and you can pause by pressing
the P1.3 of the lauchpad.*/

#include <msp430.h> 

unsigned int min=0, seg=0, dec_seg=0, cent_seg=0, pause=0;
unsigned char P1BT=0;

void ini_p1p2(void)
{
        P1DIR = BIT0+BIT1+BIT2+BIT4+BIT5+BIT6+BIT7; //SETA OS BITS 0,1,2,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 1
        P1REN = BIT3; //ATIVA O RESISTOR DA ENTRADA DO BIT 3 DA PORTA 1
        P1OUT = BIT3; //SETA OS O RESISTOR DE PULL-UP E OS VALORES DA PORTA 1.0 E 1.1
        P1IE = BIT3; //HABILITA AS INTERRUPÇÕES DA PORTA P1.3
        P1IES = BIT3; //SETA AS INTERRUPÇOES PARA BORDA DE DESCIDA
        P1IFG = 0; //LIMPA AS INTERRUPÇOES DA PORTA 1;

        P2DIR = 0xFF; // SETA OS BITS 0,1,2,3,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 2
        P2OUT = 0; // SETA TODOS OS BITS DA PORTA 2 COMO SAIDA EM NIVEL BAIXO
        __enable_interrupt();
}

void config_ini(void)
{
        WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
        DCOCTL = CALDCO_16MHZ; // Freq. Calibrada de 16 MHz
        BCSCTL1 = CALBC1_16MHZ;
        BCSCTL2 = DIVS0 + DIVS1; // Fator divisao = 8 para SMCLK
        BCSCTL3 = XCAP0 + XCAP1; // Capacitor do cristal ~ 12.5pF
        while(BCSCTL3 & LFXT1OF); // Sai deste loop quando clock de LFXT1 estiver estavel

}

void ini_TA0(void){

    // taclk = ACLK = 32768 Hz, Modo Continuo
    // CCR0 com Interrup. a cada 0,01s
    TA0CTL = TASSEL0 + MC1;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 327;
}

void main(void)
{
    ini_p1p2();
    config_ini();
    ini_TA0();
    do{

    }while(1);
}

#pragma  vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_CC0_RTI(void)
{
    TA0CCR0 += 327;
    if((pause==1) && (P1BT==BIT3))
    {
        P1BT=0;
        pause=0;
        P1IE |= BIT3;
    }
    if((pause==0) && (P1BT==BIT3))
    {
        P1BT=0;
        pause=1;
        P1IE |= BIT3;
    }
    if(pause==0)
    {
        cent_seg++;
        if(cent_seg==10)
        {
            cent_seg=0;
            dec_seg++;
            if(dec_seg==10)
            {
                dec_seg=0;
                seg++;
                if(seg==60)
                {
                     seg=0;
                     min++;
                     if(min==60)
                     {
                         seg=0;
                         min=0;
                         dec_seg=0;
                         cent_seg=0;
                     }
                }
            }
        }
    }
}

// RT1 da PORTA 1
#pragma  vector=PORT1_VECTOR
__interrupt void P1_RTI(void)
{
    P1BT=P1IFG;
    P1IFG=0;
    P1IE &= ~BIT3;
}
