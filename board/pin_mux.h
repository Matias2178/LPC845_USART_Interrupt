/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO0_24 (number 20), RXD0
  @{ */
#define UART0_PINS_RXD0_PORT 0U                   /*!<@brief PORT device index: 0 */
#define UART0_PINS_RXD0_PIN 24U                   /*!<@brief PORT pin number */
#define UART0_PINS_RXD0_PIN_MASK (1U << 24U)      /*!<@brief PORT pin mask */
                                                  /* @} */

/*! @name PIO0_25 (number 19), TXD0
  @{ */
#define UART0_PINS_TXD0_PORT 0U                   /*!<@brief PORT device index: 0 */
#define UART0_PINS_TXD0_PIN 25U                   /*!<@brief PORT pin number */
#define UART0_PINS_TXD0_PIN_MASK (1U << 25U)      /*!<@brief PORT pin mask */
                                                  /* @} */

/*!
 * @brief 
 *
 */
void UART0_Pins(void); /* Function assigned for the Cortex-M0P */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/