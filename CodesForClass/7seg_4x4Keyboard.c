#include <msp430.h>
#define     CONFIG_WT (WDTPW + WDTTMSEL + WDTCNTCL + WDTIS1)
//DEFINE DA TELA
#define     ZERO    (BIT6)
#define     UM      (BIT0+BIT3+BIT4+BIT5+BIT6)
#define     DOIS    (BIT2+BIT5)
#define     TRES    (BIT4 + BIT5)
#define     QUATRO  (BIT0 + BIT3 + BIT4)
#define     CINCO   (BIT1 + BIT4)
#define     SEIS     (BIT1)
#define     SETE    (BIT3 + BIT4 + BIT5 + BIT6)
#define     OITO    (0)
#define     NOVE    (BIT4)
#define     A       (BIT3)
#define     B       (BIT0 + BIT1)
#define     CC       (BIT1 + BIT2 + BIT6)
#define     D       (BIT0+BIT5)
#define     ERRO    (BIT1 + BIT2)

#define     C1      (BIT0)
#define     C2      (BIT1)
#define     C3      (BIT2)
#define     C4      (BIT3)
#define     R1      (BIT4)
#define     R2      (BIT5)
#define     R3      (BIT6)
#define     R4      (BIT7)

unsigned char P1_FLAGR1=0,P1_FLAGR2=0,P1_FLAGR3=0,P1_FLAGR4=0, valor=0, valora=0;
int pixca=1;
unsigned long int troca=0, i=0;
void config_ini(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer
    DCOCTL = CALDCO_16MHZ; // Freq. Calibrada de 16 MHz
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS0 + DIVS1; // Fator divisao = 8 para SMCLK
    //  BCSCTL3 = XCAP0 + XCAP1; // Capacitor do cristal ~ 12.5pF COMO UTILIZA A PORTA 2.6 DESABILITA-SE A UTILIZAÇÃO DO CRISTAL.
}


void ini_p1p2(void)
{
    P1DIR = C1+C2+C3+C4;
    P1REN = R1+R2+R3+R4;
    P1OUT = C1+C2+C3+C4;
    P1IE = R1+R2+R3+R4;
    P1IES = 0;
    P1IFG=0;


    P2SEL &= ~(BIT6 + BIT7); // ALTERA AS FUNÇÕES NATIVAS DA PORTA 2.6 E 2.7 PARA SAIDA DIGITAL
    P2DIR = 0xFF; // SETA OS BITS 0,1,2,3,4,5,6,7 COMO SAIDA DIGITAL DA PORTA 2
    P2OUT = 0; // SETA TODOS OS BITS DA PORTA 2 COMO SAIDA EM NIVEL BAIXO

    __enable_interrupt();
}

void imprime(char valor)
{
    switch(valor)
    {
        case 0:
            P2OUT = (ZERO+BIT7);
        break;
        case 1:
            P2OUT = UM+BIT7;
        break;
        case 2:
            P2OUT = DOIS+BIT7;
        break;
        case 3:
            P2OUT = TRES+BIT7;
        break;
        case 4:
            P2OUT = QUATRO+BIT7;
        break;
        case 5:
            P2OUT = CINCO+BIT7;
        break;
        case 6:
            P2OUT = SEIS+BIT7;
        break;
        case 7:
            P2OUT = SETE+BIT7;
        break;
        case 8:
            P2OUT = OITO+BIT7;
        break;
        case 9:
            P2OUT = NOVE+BIT7;
        break;
        case 'a':
            P2OUT = A+BIT7;
        break;
        case 'b':
            P2OUT = B+BIT7;
        break;
        case 'c':
            P2OUT = CC+BIT7;
        break;
        case 'd':
            P2OUT = D+BIT7;
        break;
        default:
            P2OUT = (ERRO+BIT7);
        break;
    }
}


int main(void)
{
        ini_p1p2();
        config_ini();
        WDTCTL = CONFIG_WT;
        IE1 |= WDTIE;
        do
        {
            if(pixca==1)
            {
                if(valor!='z')
                    imprime(valor);
                else
                    P2OUT=0;
            }
            else if(pixca==-1)
            {
                imprime(valor);
                for(i=0;i<70000;i++);
                P2OUT=0;
                for(i=0;i<70000;i++);
            }
        }while(1);
}

#pragma  vector=PORT1_VECTOR //VETOR DE INTERRUPÇÃO DA PORTA 1
__interrupt void P1_RTI(void) //RTI DA PORTA 1
{
    P1_FLAGR1=P1IFG&(BIT4);
    P1_FLAGR2=P1IFG&(BIT5);
    P1_FLAGR3=P1IFG&(BIT6);
    P1_FLAGR4=P1IFG&(BIT7);
    P1IFG &= ~(BIT4+BIT5+BIT6+BIT7);
    P1IE &=~(R1+R2+R3+R4);


    WDTCTL = CONFIG_WT;
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_RTI(void)
{
    P1IN=0;
    P1OUT=0;
    P1OUT=C1;
    if(P1_FLAGR1&BIT4)
    {
        if(P1IN&BIT4)
            valor=1;
    }
    P1OUT=C2;
    if(P1_FLAGR1&BIT4)
    {
        if( P1IN&BIT4)
            valor=2;
    }
    P1OUT=C3;
    if(P1_FLAGR1&BIT4)
    {
        if(P1IN&BIT4)
            valor=3;
    }
    P1OUT=C4;
    if(P1_FLAGR1&BIT4)
    {
        if(P1IN&BIT4)
            valor='a';
    }
    P1OUT=0;
    P1OUT=C1;
        if(P1_FLAGR2&BIT5)
        {
            if(P1IN&BIT5)
                valor=4;
        }
        P1OUT=C2;
        if(P1_FLAGR2&BIT5)
        {
            if( P1IN&BIT5)
                valor=5;
        }
        P1OUT=C3;
        if(P1_FLAGR2&BIT5)
        {
            if(P1IN&BIT5)
                valor=6;
        }
        P1OUT=C4;
        if(P1_FLAGR2&BIT5)
        {
            if(P1IN&BIT5)
                valor='b';
        }
        P1OUT=C1;
            if(P1_FLAGR3&BIT6)
            {
                if(P1IN&BIT6)
                    valor=7;
            }
            P1OUT=C2;
            if(P1_FLAGR3&BIT6)
            {
                if( P1IN&BIT6)
                    valor=8;
            }
            P1OUT=C3;
            if(P1_FLAGR3&BIT6)
            {
                if(P1IN&BIT6)
                    valor=9;
            }
            P1OUT=C4;
            if(P1_FLAGR3&BIT6)
            {
                if(P1IN&BIT6)
                    valor='c';
            }
            P1OUT=C1;
                if(P1_FLAGR4&BIT7)
                {
                    if(P1IN&BIT7)
                    {
                        if(valor=='z'){
                            P2OUT=BIT7;
                            valor=valora;}
                        else{
                            valora=valor;
                            valor='z';
                        }
                    }

                }
                P1OUT=C2;
                if(P1_FLAGR4&BIT7)
                {
                    if( P1IN&BIT7)
                        valor=0;
                }
                P1OUT=C3;
                if(P1_FLAGR4&BIT7)
                {
                    if(P1IN&BIT7)
                        pixca=pixca*-1;
                }
                P1OUT=C4;
                if(P1_FLAGR4&BIT7)
                {
                    if(P1IN&BIT7)
                        valor='d';
                }
                P1OUT=0;
                P1IE=BIT4+BIT5+BIT6+BIT7;
}
