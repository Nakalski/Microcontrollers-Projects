/* Servo Control */

#include <msp430.h> 

int sel=0, dir=0;
unsigned char P1BT=0, P1ENC=0;

void ini_p1p2(void)
{
        P1DIR = BIT3+BIT2+BIT4+BIT5+BIT6+BIT7; //SETA OS BITS 2,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 1
        P1REN = BIT0+BIT1;
        P1OUT = BIT0+BIT1;
        P1IE  = BIT0; //HABILITA AS INTERRUPÇÕES DA PORTA P1.3
        P1IES = BIT0; //SETA AS INTERRUPÇOES PARA BORDA DE DESCIDA
        P1IFG = 0; //=LIMPA AS INTERRUPÇOES DA PORTA 1;

        P2DIR = 0xFF; // SETA OS BITS 0,1,2,3,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 2
        P2OUT = 0; // SETA TODOS OS BITS DA PORTA 2 COMO SAIDA EM NIVEL BAIXO
        P2DIR = 0xFF;
        P2OUT = 0;
        P2SEL |= BIT1+BIT2;
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

void ini_TA0(void)
{
    TA0CTL = TASSEL0 + MC1;
    TA0CCR0 = 1;
}

void ini_TA1(void){
    TA1CTL = TASSEL0 + MC0 + MC1;
    TA1CCTL1 = OUTMOD1 + OUT;
    TA1CCR0 = 327;
    TA1CCR1 = 17;  // 10%
}

void main(void)
{
    ini_p1p2();
    config_ini();
    ini_TA0();
    ini_TA1();
    do{

    }while(1);
}


#pragma  vector=TIMER0_A0_VECTOR
__interrupt void TimerA0_CC0_RTI(void)
{
    TA0CCR0 += 1;
    if(P1ENC==BIT0)
    {
        if((BIT1==(P1IN&BIT1))&&((0)==(BIT0&P1IN)))
        {
                if((TA1CCR1+2)<33)
                {
                    TA1CCR1+=2;
                }
                else
                    TA1CCR1=33;
        }
        else if(((0)==(BIT0&P1IN))&&((0)==(BIT1&P1IN)))
        {
            if((TA1CCR1-2)>15)
            {
                TA1CCR1-=2;
            }
            else
                TA1CCR1=15;
        }
    }
    P1ENC=0;
    P1IE |= (BIT0);
    TA0CCTL0 &= ~(CCIE);

}

#pragma  vector=PORT1_VECTOR
__interrupt void P1_RTI(void)
{
    P1ENC=(P1IFG&BIT0);
    P1IFG=0;
    P1IE &= ~(BIT0);
    TA0CCTL0 |= CCIE;
}
