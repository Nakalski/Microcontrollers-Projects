#include <msp430.h> 
#include <stdio.h>

void ini_P1_P2(void);
void ini_uCOn(void);
void ini_TA0(void);
void ini_USCI_A0_UART(void);

unsigned char RX_DATA[3];
unsigned char rx_index = 0;
unsigned char i=0, j=0, dce=0, toffd=0,toffe=0, k=0, l=0, n, m, dcd=0, r=0;
int at=-1, pc=-1;

void main(void) {

    ini_P1_P2();
    ini_uCOn();
    ini_TA0();
    ini_USCI_A0_UART();
    do{
    }while(1);
}


//-----------------------------------------------------------------------------


// RTI de RX pela USCI - A0
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RTI_USCI_RX(void)
{

    RX_DATA[rx_index] = UCA0RXBUF;
    if(UCA0RXBUF=='$')
    {
        dcd=0;
        dce=0;
        rx_index=0;
        pc=pc*-1;
    }
    if(pc==1)
    {
            if(UCA0RXBUF=='&')
            {
                dcd=15;
                dce=15;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            if(UCA0RXBUF=='(')
            {
                dcd=15;
                dce=15;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            if(UCA0RXBUF=='%')
            {
                dce=15;
                dcd=1;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;

            }
            if(UCA0RXBUF==39)
            {
                dce=1;
                dcd=15;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            if(UCA0RXBUF=='q')
            {
                P1OUT=0;
            }

    }
    else if (pc==-1)
    {
        if( RX_DATA[rx_index] == '.')
        {
            rx_index = 0;
            if(RX_DATA[0]=='0'&&RX_DATA[1]=='0')
            {
                at=at*-1;
            }
            else{
            if(RX_DATA[0]=='6'&&RX_DATA[1]=='5')
            {
                dcd=5;
                dce=5;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            if(RX_DATA[0]=='8'&&RX_DATA[1]=='5')
            {
                        dcd=10;
                        dce=10;
                        P1OUT &= ~BIT4;
                        P1OUT |= BIT3 + BIT6;
                        P2OUT &= ~BIT1;
                        P2OUT |= BIT2;
           }
            if(RX_DATA[0]=='9'&&RX_DATA[1]=='1')
            {
                dce=7;
                dcd=14;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }

            else if(RX_DATA[0]=='9'&&RX_DATA[1]=='5'){
                dcd=14;
                dce=14;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='9'&&RX_DATA[1]=='9'){
                dce=14;
                dcd=7;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='7'&&RX_DATA[1]=='3'){
                dce=4;
                dcd=8;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='7'&&RX_DATA[1]=='7'){
                dce=8;
                dcd=4;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='5'&&RX_DATA[1]=='1'){
                dce=1;
                dcd=12;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='5'&&RX_DATA[1]=='9'){
                dce=12;
                dcd=1;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='3'&&RX_DATA[1]=='3'){
                dce=7;
                dcd=1;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='3'&&RX_DATA[1]=='7'){
                dce=8;
                dcd=4;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='1'&&RX_DATA[1]=='1'){
                dce=14;
                dcd=7;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='1'&&RX_DATA[1]=='5'){
                dcd=15;
                dce=15;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;

            }
            else if(RX_DATA[0]=='1'&&RX_DATA[1]=='9'){
                dce=7;
                dcd=14;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='7'&&RX_DATA[1]=='5')
            {
                dcd=8;
                dce=8;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }

            else if(RX_DATA[0]=='3'&&RX_DATA[1]=='5')
            {
                dcd=7;
                dce=7;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='4'&&RX_DATA[1]=='5')
            {
                dcd=5;
                dce=5;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }
            else if(RX_DATA[0]=='2'&&RX_DATA[1]=='5')
            {
                dcd=10;
                dce=10;
                P1OUT &= ~BIT3;
                P1OUT |= BIT4 + BIT6;
                P2OUT &= ~BIT2;
                P2OUT |= BIT1;
            }

            else if(RX_DATA[0]=='5'&&RX_DATA[1]=='5')
            {
                P1OUT=0;
            }
            else if(RX_DATA[0]=='5'&&RX_DATA[1]=='3')
            {
                dce=1;
                dcd=7;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
            else if(RX_DATA[0]=='5'&&RX_DATA[1]=='7')
            {
                dce=7;
                dcd=1;
                P1OUT &= ~BIT4;
                P1OUT |= BIT3 + BIT6;
                P2OUT &= ~BIT1;
                P2OUT |= BIT2;
            }
        }
    }
    else
    {
        rx_index++;
    }
    }
}


//--------------------------------------------------------------

void ini_USCI_A0_UART(void)
{
    UCA0CTL1 = UCSSEL1 + UCSWRST;
    UCA0CTL0 = 0;
    UCA0BR0 = 0x41;
    UCA0BR1 = 0x03;
    UCA0MCTL = UCBRS1;
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    UCA0CTL1 &= ~UCSWRST;
    IFG2 &= ~UCA0TXIFG;
    IE2 |= UCA0TXIE + UCA0RXIE;
}


#pragma  vector=TIMER0_A0_VECTOR
__interrupt void Timer0A_CCR12C_RTI(void)
{
    TA0CCR0 +=200;
   if(i<dce)
   {
       P2OUT|=BIT0;
       i++;
   }
   if(i>=dce)
   {
       toffe=16-dce;
   }
   if(j<=toffe && i>=dce && dce!=16)
   {
       j++;
       P2OUT &= ~BIT0;
   }
   if (j>=toffe && i>=dce)
   {
       j=0;
       i=0;
   }
     if(k<dcd)
     {
         P1OUT|=BIT5;
         k++;
     }
     if(k>=dcd)
     {
         toffd=16-dcd;
     }
     if(l<=toffd && k>=dcd && dcd!=16)
     {
         l++;
         P1OUT&=~BIT5;
     }
     if (l>=toffd && k>=dcd)
     {
         k=0;
         l=0;
     }
}

void ini_TA0(void)
{
    TA0CTL = TASSEL1 + MC1;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 200;
}


void ini_P1_P2(void)
{
    P1DIR = 0xFF;
    P1OUT = BIT6;
    P2DIR = 0xFF;
    P2OUT = 0;
}


void ini_uCOn(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL3 = XCAP0 + XCAP1;
    BCSCTL2 = DIVS0;

    while(BCSCTL3 & LFXT1OF);

     __enable_interrupt();
}
