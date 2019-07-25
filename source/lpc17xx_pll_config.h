/**********************************************************************
* $Id$		lpc17xx_pll_config.h		2019-07-25
*//**
* @file		lpc17xx_pll_config.h
* @brief	Contains function to configure pll 
* @version	1.0
* @date		25. july. 2019
* @author	Sergei Gridasov
*

***********************************************************************

**********************************************************************/

#ifndef LPC17XX_PLL_CONFIG_H_
#define LPC17XX_PLL_CONFIG_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_clkpwr.h"

/*********************************************************************//**
 * Macro defines for PLL CONFIGURE Register
 **********************************************************************/

#define USE_PLL 1

#define OSCRANGE_VAL 0 // 1..20 MHz
#define XTAL_FREQ 12000000UL
#define PLL0_FIN_FREQ XTAL_FREQ
#define PLL0_CCO_FREQ 300000000UL

// TODO: Auto calculations ?
// CCO = (2 * FIN * M) / N
#define PLL0_N_VALUE (2-1)
#define PLL0_M_VALUE (25-1)
#define CCLK_DIVIDER 3
/**
 * @}
 */
  
 
/* Public Functions ----------------------------------------------------------- */
/** @defgroup PLL_CONFIGURE_Public_Functions PLL CONFIGURE Public Functions
 * @{
 */
 
void init_clocks_pll(Bool);

/**
 * @}
 */

#endif /* LPC17XX_PLL_CONFIG_H_ */
