#include "application.h"
#include "mcc_generated_files/system/system.h"
#include "util/delay.h"
/**
 * **********************************************************
 *  File Global variables
 * **********************************************************
 **/
volatile uint8_t switchPressed = CLEAR; 


/*******************************************************************************
 * void SwitchPress_InterruptHandler(void)
 *
 * API to handle switch press interrupt
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void SwitchPress_InterruptHandler(void)
{
    switchPressed =  SET;
}

/*******************************************************************************
 * void RTC_Compare_InterruptHandler(void)
 *
 * API to handle RTC Compare interrupt handler, which will generate 
 * interrupt for every 30 sec
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void RTC_Compare_InterruptHandler(void)
{
    LED_ON();
    _delay_ms(10);
    LED_OFF();
}

/*******************************************************************************
 * void  External_Crystal_init(void)
 *
 * API to initialize the external crystal 32.768KHz
 * 
 *
 * @param void 
 * @return void
 ******************************************************************************/
void  External_Crystal_init(void)
{
    uint8_t buffer;
    
    /* Initialize 32.768kHz Oscillator: */
    /* Disable oscillator: */
    buffer = CLKCTRL.XOSC32KCTRLA;
    buffer &= ~CLKCTRL_ENABLE_bm;
    
    /* Writing to protected register */
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, buffer);
    
    while(CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm)
    {
        ; /* Wait until XOSC32KS becomes 0 */
    }
    
    /* SEL = 0 (Use External Crystal): */
    buffer = CLKCTRL.XOSC32KCTRLA;
    buffer &= ~CLKCTRL_SEL_bm;
    
    /* Writing to protected register */
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, buffer);
    
    /* Enable oscillator: */
    buffer = CLKCTRL.XOSC32KCTRLA;
    buffer |= CLKCTRL_ENABLE_bm;
    /* Writing to protected register */
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, buffer);
    
}
