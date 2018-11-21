/* Code that generates 3 square wave signals with different frequency 50Hz, 75Hz and 100Hz on the
ports P1.0, P1.4, P1.6 respectively */

#include <msp430.h> 

unsigned int min=0, seg=0, dec_seg=0, cent_seg=0, pause=0;
unsigned char P1BT=0;

void ini_p1p2(void)
{
        P1DIR = BIT0+BIT1+BIT2+BIT3+BIT4+BIT5+BIT6+BIT7; //SETA OS BITS 0,1,2,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 1
        P1OUT = 0;

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

void ini_TA0(void)
{
    // taclk = ACLK = 32768 Hz, Modo Continuo
    // CCR0 com Interrup. a cada 0,01s
    TA0CTL = TASSEL0 + MC1;
    TA0CCTL0 = CCIE;
    TA0CCTL1 = CCIE;
    TA0CCTL2 = CCIE;
    TA0CCR0 = 164;
    TA0CCR1 = 218;
    TA0CCR2 = 555;
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
    TA0CCR0 += 164;
    P1OUT ^=BIT0;
}


#pragma  vector=TIMER0_A0_VECTOR
__interrupt void Timer0A_CCR12C_RTI(void)
{
    switch(TA0IV){
            case 2:
                TA0CCR1 += 218;
                P1OUT ^= BIT4;
            break;
            case 4:
                TA0CCR2 += 555;
                P1OUT ^= BIT6;

            break;
        }
}
