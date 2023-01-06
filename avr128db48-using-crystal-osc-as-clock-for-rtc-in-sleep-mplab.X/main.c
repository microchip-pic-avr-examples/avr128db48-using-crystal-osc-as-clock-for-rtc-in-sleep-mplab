 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "application.h"
#include "util/delay.h"
#include "avr/sleep.h"

extern volatile uint8_t switchPressed; 

/*
    Main application
*/
int main(void)
{
    SYSTEM_Initialize();

    /*Disable RTC Peripheral*/
    RTC_Stop();
    
    /*External crystal 32.768KHz is initialized*/
    External_Crystal_init();
    
    /*Switch Interrupt Handler*/
    PB2_SetInterruptHandler(SwitchPress_InterruptHandler);
    
    /*RTC Compare Interrupt Handler*/
    RTC_SetCMPIsrCallback(RTC_Compare_InterruptHandler);
    while(1)
    {
        if(switchPressed == SET)
        {
            /*Enable RTC peripheral*/
            RTC_Start();
                        
            /*Enter sleep mode*/
            sleep_cpu();
            
            /*Clear switch pressed flag*/
            switchPressed = CLEAR;   
            
            /*Disable RTC peripheral*/
            RTC_Stop();
        }
    }    
}


