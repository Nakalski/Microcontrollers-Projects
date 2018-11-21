/* Code for generating two PWM signals with the same frequency but different duty cicles, that can increase/decrease by
twisting a rotary encoder, and select the PWM channel that's gonna be modified by pressing the P1.3 button on the lauchpad.*/

#include <msp430.h> 

int sel=0, dir=0;
unsigned char P1BT=0, P1ENC=0;

void ini_p1p2(void)
{
        P1DIR = BIT2+BIT4+BIT5+BIT6+BIT7; //SETA OS BITS 2,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 1
        P1REN = BIT0+BIT1+BIT3;
        P1OUT = BIT0+BIT1+BIT3;
        P1IE  = BIT3+BIT0; //HABILITA AS INTERRUPÇÕES DA PORTA P1.3
        P1IES = BIT3+BIT0; //SETA AS INTERRUPÇOES PARA BORDA DE DESCIDA
        P1IFG = 0; //=LIMPA AS INTERRUPÇOES DA PORTA 1;

        P2DIR = 0xFF; // SETA OS BITS 0,1,2,3,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 2
        P2OUT = 0; // SETA TODOS OS BITS DA PORTA 2 COMO SAIDA EM NIVEL BAIXO
        P2DIR = 0xFF;
        P2OUT = 0;
        P2SEL |= BIT1 + BIT2 + BIT4 + BIT5;
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
    TA1CTL = TASSEL1 + MC0 + MC1;
    TA1CCTL1 = OUTMOD1 + OUT;
    TA1CCTL2 = OUTMOD1 + OUT;
    TA1CCR0 = 976;
    TA1CCR1 = 49;  // 10%
    TA1CCR2 = 49;  // 10%
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
    if((P1BT==BIT3)&&((~P1IN&BIT3)==BIT3))
    {
        if(sel==1)
            sel=0;
        else if(sel==0)
            sel=1;
        P1BT = 0;
        P1OUT ^= BIT6;
    }
    if(P1ENC==BIT0)
    {
        if((BIT1==(P1IN&BIT1))&&((0)==(BIT0&P1IN)))
        {
            if(sel==0)
            {
                if((TA1CCR1+=49)<976)
                {
                    TA1CCR1+49;
                }
                else
                    TA1CCR1=975;
            }
            else if(sel==1)
            {
                if((TA1CCR2+=49)>976)
                {
                    TA1CCR2=975;
                }
                else
                    TA1CCR2+=49;
            }
        }
        else if(((0)==(BIT0&P1IN))&&((0)==(BIT1&P1IN)))
        {
            if(sel==0)
            {
                TA1CCR1-=49;
                if(TA1CCR1<=49)
                    TA1CCR1=49;
            }
            else if(sel==1)
            {
                TA1CCR2-=49;
                if(TA1CCR2<=49)
                  TA1CCR2=49;
            }
        }
        P1IE |= (BIT3+BIT0);
    }
    P1IE |= (BIT3+BIT0);
    TA0CCTL0 &= ~(CCIE);

}

#pragma  vector=PORT1_VECTOR
__interrupt void P1_RTI(void)
{
    P1BT=(P1IFG&BIT3);
    P1ENC=(P1IFG&BIT0);
    P1IFG=0;
    P1IE &= ~(BIT3+BIT0);
    TA0CCTL0 |= CCIE;
}
