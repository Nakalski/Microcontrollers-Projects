/* 7 segment counter from 00 to 99, increment the value by twisting a rotary encoder and
by pressing the button of the lauchpad you can change the gain of the increment. */

#include <msp430.h> 

#define     CONFIG_WT (WDTPW + WDTTMSEL + WDTCNTCL + WDTIS0)
#define     ZERO    (BIT6+BIT7)
#define     UM      (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7)
#define     DOIS    (BIT2+BIT5+BIT7)
#define     TRES    (BIT4 + BIT5 + BIT7)
#define     QUATRO  (BIT0 + BIT3 + BIT4 + BIT7)
#define     CINCO   (BIT1 + BIT4 + BIT7)
#define     SEIS    (BIT0 + BIT1 + BIT7)
#define     SETE    (BIT3 + BIT4 + BIT5 + BIT6 + BIT7)
#define     OITO    (0)
#define     NOVE    (BIT3 + BIT4 + BIT7)
#define     ERRO    (BIT1 + BIT2 + BIT7)

int unidade=0, dezena=0,flag=1, ganho=1;
unsigned char P1_FLAGB=0, P1_FLAGE=0, P1INC=0;

void ini_p1p2(void)
{
    P1DIR = BIT0+BIT1+BIT2+BIT4+BIT5; //PORTAS 1.3, 1.6, 1.7 SÃO ENTRADA DIGITAL;
    P1REN = BIT3+BIT6+BIT7; //ATIVANDO OS RESISTORES DA PORTA 1.3, 1.6, 1.7;
    P1OUT = BIT3+BIT6+BIT7+BIT1+BIT0;
    P1IE = BIT3 + BIT6;
    P1IES = BIT3 + BIT6;
    P1IFG=0;

    P2SEL &= ~(BIT6 + BIT7); // ALTERA AS FUNÇÕES NATIVAS DA PORTA 2.6 E 2.7 PARA SAIDA DIGITAL
    P2DIR = 0xFF; // SETA OS BITS 0,1,2,3,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 2
    P2OUT = 0; // SETA TODOS OS BITS DA PORTA 2 COMO SAIDA EM NIVEL BAIXO
    __enable_interrupt();
}

void config_ini(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
    DCOCTL = CALDCO_12MHZ; // Freq. Calibrada de 16 MHz
    BCSCTL1 = CALBC1_12MHZ;
    BCSCTL2 = DIVS0 + DIVS1; // Fator divisao = 8 para SMCLK
    //  BCSCTL3 = XCAP0 + XCAP1; // Capacitor do cristal ~ 12.5pF COMO UTILIZA A PORTA 2.6 DESABILITA-SE A UTILIZAÇÃO DO CRISTAL.
}

#pragma  vector=PORT1_VECTOR //VETOR DE INTERRUPÇÃO DA PORTA 1
__interrupt void P1_RTI(void) //RTI DA PORTA 1
{
    P1_FLAGB=P1IFG&(BIT3);
    P1_FLAGE=P1IFG&(BIT6);
    P1IFG&=~(BIT3+BIT6);
    P1IE&=~(BIT3+BIT6);
    WDTCTL = CONFIG_WT;
}


#pragma vector=WDT_VECTOR
__interrupt void WDT_RTI(void)
{
    flag=flag*-1;
    if(P1_FLAGB==BIT3)
    {
        if(ganho==1)
        {
             ganho=10;
        }
        else
        {
            ganho=1;
        }
        P1IE|=(BIT3+BIT6);
        P1_FLAGB=0;
    }
    if(P1_FLAGE==BIT6)
    {
         if((BIT7==(P1IN&BIT7))&&((0)==(BIT6&P1IN)))
         {
             unidade=unidade+ganho;
             if(unidade>=10)
             {
                 dezena++;
                 unidade=(unidade-10);
             }
             if(dezena>=10)
             {
                 dezena=9;
                 unidade=9;
             }

         }
         else if(((0)==(BIT6&P1IN))&&((0)==(BIT7&P1IN)))
         {
             unidade=unidade-ganho;
             if(unidade<0)
             {
                 dezena--;
                 unidade=(10+unidade);
             }
             if(dezena<0)
             {
                 unidade=0;
                 dezena=0;
             }
         }
         P1IE|=(BIT3+BIT6);
         P1_FLAGE=0;
    }
    WDTCTL = CONFIG_WT;
}

void imprime(char valor)
{
    switch(valor)
    {
        case 0:
            P2OUT = ZERO;
        break;
        case 1:
            P2OUT = UM;
        break;
        case 2:
            P2OUT = DOIS;
        break;
        case 3:
            P2OUT = TRES;
        break;
        case 4:
            P2OUT = QUATRO;
        break;
        case 5:
            P2OUT = CINCO;
        break;
        case 6:
            P2OUT = SEIS;
        break;
        case 7:
            P2OUT = SETE;
        break;
        case 8:
            P2OUT = OITO;
        break;
        case 9:
            P2OUT = NOVE;
        break;
        default:
            P2OUT = ERRO;
        break;
    }
}
void main(void)
{
    ini_p1p2();
    config_ini();
    WDTCTL = CONFIG_WT;
    IE1 |= WDTIE;
    do
    {
       if(flag==1)
             {
                 P1OUT=P1OUT&(BIT1+BIT3+BIT6+BIT7);
                 imprime(unidade);
                 P1OUT=P1OUT+BIT0;
             }
             if(flag==-1)
             {
                 P1OUT=P1OUT&(BIT0+BIT3+BIT6+BIT7);
                 imprime(dezena);
                 P1OUT=P1OUT+BIT1;
             }

    }while(1);
}
