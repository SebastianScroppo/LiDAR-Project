#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "SysTick.h"
#include "PLL.h"

void PortK_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9;  // activate the clock for Port K
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R9) == 0){};  // allow time for clock to stabilize
GPIO_PORTK_DEN_R= 0b111111111;
GPIO_PORTK_DIR_R |= 0b11111111;                           // make PE0 output  //Direction is used for i/o
GPIO_PORTK_DATA_R=0b00000000;                             // setting state to zero to drive the row, one to disable
return;
}

void PortE0_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;  // activate the clock for Port E
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R4) == 0){};  // allow time for clock to stabilize
GPIO_PORTE_DEN_R= 0b00000001;
GPIO_PORTE_DIR_R |= 0b00000001;                           // make PE0 output
GPIO_PORTE_DATA_R=0b00000000;                             // setting state to zero to drive the row, one to disable
return;
}

void PortL2_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;  // activate the clock for Port L
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R10) == 0){};  // allow time for clock to stabilize
GPIO_PORTL_DEN_R= 0b00000100;
GPIO_PORTL_DIR_R |= 0b0000100;                           // make PL2 output
GPIO_PORTL_DATA_R=0b00000000;                             // setting state to zero to drive the row, one to disable
return;
}

void PortM0_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11;                 //activate the clock for Port M
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R11) == 0){};        //allow time for clock to stabilize
GPIO_PORTM_DIR_R |= 0b00000000;        // make PM0 an input, PM0 is reading the column
  GPIO_PORTM_DEN_R |= 0b00000001;
return;
}


//Turns on my LED (D3)
void PortPF4_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;                 //activate the clock for Port F to use LED
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R5) == 0){};
GPIO_PORTF_DIR_R|=0b00010000;
GPIO_PORTF_DEN_R|=0b00010000;
return;
}
void motorruns(void){
//GPIO_PORTN_DATA_R = 0b00000000;
uint32_t t = 5;
SysTick_Wait10ms(t);
GPIO_PORTK_DATA_R = 0b00000011;
SysTick_Wait10ms(t);
GPIO_PORTK_DATA_R = 0b00000110;
SysTick_Wait10ms(t);
GPIO_PORTK_DATA_R = 0b00001100;
SysTick_Wait10ms(t);
GPIO_PORTK_DATA_R = 0b00001001;
SysTick_Wait10ms(t);
}



int main(void){
PortE0_Init();
PortM0_Init();
PortPF4_Init();
PortK_Init();
PortL2_Init();

PLL_Init(); // Default Set System Clock to 120MHz
SysTick_Init(); // Initialize SysTick configuration



while(1){//keep checking if the button is pressed
uint32_t t = 1;
GPIO_PORTL_DATA_R=0b00000100;
GPIO_PORTF_DATA_R = 0b000000000;
//Checks if Button 1 is pressed, if pressed on-board LED lights up
if(((GPIO_PORTM_DATA_R&0b00000001)==0)){
while(t <= 512){
motorruns();
t++;
if(t%64 == 0){
GPIO_PORTF_DATA_R = 0b000010000;
SysTick_Wait10ms(10);
}
GPIO_PORTL_DATA_R = 0b000000000;
GPIO_PORTF_DATA_R = 0b000000000;
}
}else{
GPIO_PORTL_DATA_R=0b00000100;
GPIO_PORTF_DATA_R = 0b000000000;
}
}
}






