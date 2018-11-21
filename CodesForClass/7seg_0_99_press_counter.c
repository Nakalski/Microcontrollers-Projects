/* 7 segment counter from 00 to 99, increment the value by pressing the button on the lauchpad of the TI MSP430G2553 */

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

int flag=1;
unsigned char unidade=0, dezena=0;

void ini_p1p2(void)
{
    P1DIR = BIT0+BIT1+BIT2+BIT4+BIT5+BIT6+BIT7; //SETA OS BITS 0,1,2,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 1
    P1REN = BIT3; //ATIVA O RESISTOR DA ENTRADA DO BIT 3 DA PORTA 1
    P1OUT = BIT3+BIT0+BIT1; //SETA OS O RESISTOR DE PULL-UP E OS VALORES DA PORTA 1.0 E 1.1
    P1IE = BIT3; //HABILITA AS INTERRUPÇÕES DA PORTA P1.3
    P1IES = BIT3; //SETA AS INTERRUPÇOES PARA BORDA DE DESCIDA
    P1IFG = 0; //LIMPA AS INTERRUPÇOES DA PORTA 1;

    P2SEL &= ~(BIT6 + BIT7); // ALTERA AS FUNÇÕES NATIVAS DA PORTA 2.6 E 2.7 PARA SAIDA DIGITAL
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
    //  BCSCTL3 = XCAP0 + XCAP1; // Capacitor do cristal ~ 12.5pF COMO UTILIZA A PORTA 2.6 DESABILITA-SE A UTILIZAÇÃO DO CRISTAL.
}

#pragma  vector=PORT1_VECTOR //VETOR DE INTERRUPÇÃO DA PORTA 1
__interrupt void P1_RTI(void) //RTI DA PORTA 1
{
    P1IFG &= ~BIT3; // Limpa flag para nao gerar interrupcoes
    unidade++; //INCREMENTA UNIDADE
    if((unidade==9)&&(dezena==9)) //VERIFICA SE AMBOS UNIDADE E DEZENA SAO IGUAIS A NOVE E RESETA OS VALORES
    {
            unidade=0;
            dezena=0;
    }
    if(unidade==10) //VERIFICA UNIDADE SE IGUAL A 10 AUMENTA DEZENA E RESETA UNIDADE A ZERO
    {
        dezena++;
        unidade=0;
    }
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

#pragma vector=WDT_VECTOR
__interrupt void WDT_RTI(void)
{
    flag=flag*-1;
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
           P1OUT=P1OUT&(BIT1+BIT3);
           imprime(unidade);
           P1OUT=P1OUT+BIT0;
       }
       if(flag==-1)
       {
           P1OUT=P1OUT&(BIT0+BIT3);
           imprime(dezena);
           P1OUT=P1OUT+BIT1;

       }
    }while(1);
}
