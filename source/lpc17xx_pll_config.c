/**********************************************************************
* $Id$		lpc17xx_pll_config.c		2019-07-25
*//**
* @file		lpc17xx_pll_config.c
* @brief	Contains function to configure pll 
* @version	1.0
* @date		25. july. 2019
* @author	Sergei Gridasov
*

***********************************************************************
* The resulting function "init_clocks_pll" is modified sysinit function
**********************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_pll_config.h"

/** PLL CONFIGUR structure definition **/
// No defines in NXP include files?
enum	{	OSCRANGE = 4, OSCEN = 5, OSCSTAT = 6 };


/* Public Functions ----------------------------------------------------------- */

/*********************************************************************//**
 * @brief		System initialization, configuration of system clock 
 * @param[in]	use_pll		
 * TRUE - PLL is on MCU work on 100MHz 
 * FALSE - PLL is off, MCU work on 12MHz 
 * @return		none
 * TODO: It is necessary to rewrite this in proper way
 **********************************************************************/
void init_clocks_pll(Bool use_pll){
	
	// Enable XTAL osc and wait for stability
	LPC_SC->SCS = (1UL << OSCEN) | (OSCRANGE_VAL << OSCRANGE);
	while( !(LPC_SC->SCS & (1UL << OSCSTAT)) ) ;

	if (use_pll) {
		// 4.5.13 PLL0 setup sequence
		// 1. Disconnect
		if (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLLC) {
			LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_CONNECT;
			LPC_SC->PLL0FEED = 0xAA;
			LPC_SC->PLL0FEED = 0x55;
		}
		// 2. Disable
		LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 4,5. Select source clock for PLL
		LPC_SC->CLKSRCSEL = CLKPWR_CLKSRCSEL_CLKSRC_MAINOSC;
		LPC_SC->PLL0CFG = CLKPWR_PLL0CFG_NSEL(PLL0_N_VALUE)
		                | CLKPWR_PLL0CFG_MSEL(PLL0_M_VALUE);
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 6. Enable PLL
		LPC_SC->PLL0CON |= CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

		// 7. Set clk divider settings
		// 300/3 = 100MHz
		LPC_SC->CCLKCFG  = CCLK_DIVIDER-1;
		// other peripherals 100/4 = 25MHz by default
		LPC_SC->PCLKSEL0 = 0;
		LPC_SC->PCLKSEL1 = 0;

		// 8. Wait for the PLL to achieve lock
		while(! (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLOCK) ) ;

		// 9. Connect
		LPC_SC->PLL0CON |= CLKPWR_PLL0CON_CONNECT;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;

	} else {

		// Disconnect and disable PLL
		if (LPC_SC->PLL0STAT & CLKPWR_PLL0STAT_PLLC) {
			LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_CONNECT;
			LPC_SC->PLL0FEED = 0xAA;
			LPC_SC->PLL0FEED = 0x55;
		}
		LPC_SC->PLL0CON &= ~CLKPWR_PLL0CON_ENABLE;
		LPC_SC->PLL0FEED = 0xAA;
		LPC_SC->PLL0FEED = 0x55;
		// 
		LPC_SC->CLKSRCSEL = CLKPWR_CLKSRCSEL_CLKSRC_MAINOSC;
		// 12/1 = 12MHz
		LPC_SC->CCLKCFG  = 0;
		// other peripherals 12/4 = 3 MHz by default
		LPC_SC->PCLKSEL0 = 0;
		LPC_SC->PCLKSEL1 = 0;
	}
}
