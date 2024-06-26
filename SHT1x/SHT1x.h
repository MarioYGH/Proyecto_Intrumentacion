/* Define to prevent recursive inclusion ----------------------------------------*/
#ifndef _SHT1X_H_
#define _SHT1X_H_

#ifdef __cplusplus
extern "C"
{
#endif


/* Includes ---------------------------------------------------------------------*/
#include <stdint.h>
#include "SHT1x_config.h"


/* Configurations ---------------------------------------------------------------*/
#ifndef SHT1X_CONFIG_FAHRENHEIT_MEASUREMENT
  #define SHT1X_CONFIG_FAHRENHEIT_MEASUREMENT 1
#endif

#ifndef SHT1X_CONFIG_RESOLUTION_CONTROL
  #define SHT1X_CONFIG_RESOLUTION_CONTROL 1
#endif

#ifndef SHT1X_CONFIG_POWER_VOLTAGE_CONTROL
  #define SHT1X_CONFIG_POWER_VOLTAGE_CONTROL 1
#endif

#ifndef SHT1X_CONFIG_INTERNAL_HEATER_CONTROL
  #define SHT1X_CONFIG_INTERNAL_HEATER_CONTROL 1
#endif


/* Exported Data Types ----------------------------------------------------------*/
/**
 * @brief  Set and Get sensor resolution data type
 */
typedef enum SHT1x_Resolution_e
{
  SHT1x_LowResolution = 0,
  SHT1x_HighResolution = 1
} SHT1x_Resolution_t;

/**
 * @brief  Handler data type
 * @note   User must initialize this this functions before using library:
 *         - DataDeInit
 *         - DataConfigOut
 *         - DataConfigIn
 *         - DataWriteHigh
 *         - DataWriteLow
 *         - DataRead
 *         - SckDeInit
 *         - SckConfigOut
 *         - SckWriteHigh
 *         - SckWriteLow
 *         - DelayMs
 *         - DelayUs
 */
typedef struct SHT1x_Handler_s
{
  float D1Celsius;
  float D1Fahrenheit;
  SHT1x_Resolution_t ResolutionStatus;

  // Initialize the platform-dependent layer
  void (*PlatformInit)(void);
  // Uninitialize the platform-dependent layer
  void (*PlatformDeInit)(void);

  // Config direction of the GPIO that connected to DATA PIN of SHT1x (0:Input, 1:Output)
  void (*DataConfigDir)(uint8_t);
  // Set value of the GPIO that connected to DATA PIN of SHT1x
  void (*DataWrite)(uint8_t);
  // Read the GPIO that connected to DATA PIN of SHT1x
  uint8_t (*DataRead)(void);

  // Set value of the GPIO that connected to DATA PIN of SHT1x
  void (*SckWrite)(uint8_t);

  // Delay (ms)
  void (*DelayMs)(uint8_t);
  // Delay (us)
  void (*DelayUs)(uint8_t);
} SHT1x_Handler_t;

/**
 * @brief  Sample data type
 */
typedef struct SHT1x_Sample_s
{
  uint16_t TempRaw;
  uint16_t HumRaw;
  float TempCelsius;
  float TempFahrenheit;
  float HumidityPercent;
} SHT1x_Sample_t;

/**
 * @brief  Library functions result data type
 */
typedef enum SHT1x_Result_e
{
  SHT1x_OK = 0,
  SHT1x_FAIL = 1,
  SHT1x_TIME_OUT = 2
} SHT1x_Result_t;

/**
 * @brief  Control Heater data type
 */
typedef enum SHT1x_Heater_e
{
  SHT1x_HeaterOff = 0,
  SHT1x_HeaterOn = 1
} SHT1x_Heater_t;



/**
 ==================================================================================
                        ##### Measurement Functions #####                          
 ==================================================================================
 */

/**
 * @brief  Readout of Measurement Results
 * @param  Handler: Pointer to handler
 * @param  Sample: Pointer to sample structure
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 *         - SHT1x_TIME_OUT: Timeout occurred.
 */
SHT1x_Result_t
SHT1x_ReadSample(SHT1x_Handler_t *Handler, SHT1x_Sample_t *Sample);



/**
 ==================================================================================
                    ##### Control and Status Functions #####                       
 ==================================================================================
 */

/**
 * @brief  Initializes platform-independent fields of Handler
 * @param  Handler: Pointer to handler
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 */
SHT1x_Result_t
SHT1x_Init(SHT1x_Handler_t *Handler);


/**
 * @brief  De-initializes the Handler and calls DataDeInit and SckDeInit functions
 * @param  Handler: Pointer to handler
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 */
SHT1x_Result_t
SHT1x_DeInit(SHT1x_Handler_t *Handler);


/**
 * @brief  Resets SHT1x. This takes about 20ms
 * @param  Handler: Pointer to handler
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 */
SHT1x_Result_t
SHT1x_SoftReset(SHT1x_Handler_t *Handler);


#if (SHT1X_CONFIG_RESOLUTION_CONTROL)
/**
 * @brief  Set Resolution of measurement.
 * @param  Handler: Pointer to handler
 * @param  Resolution: Measurement Resolution
 *         - SHT1x_LowResolution: Temperature 12-bit & Humidity 8-bit.
 *         - SHT1x_HighResolution: Temperature 14-bit & Humidity 12-bit.
 * 
 * @note   Low resolution mode is especially useful in high speed or extreme low
 *         power applications.
 * 
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 */
SHT1x_Result_t
SHT1x_SetResolution(SHT1x_Handler_t *Handler, SHT1x_Resolution_t Resolution);


/**
 * @brief  Get Resolution of measurement.
 * @param  Handler: Pointer to handler
 * @param  Resolution: Pointer to get measurement mode
 *         - SHT1x_LowResolution: Temperature 12-bit & Humidity 8-bit.
 *         - SHT1x_HighResolution: Temperature 14-bit & Humidity 12-bit.
 * 
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 */
SHT1x_Result_t
SHT1x_GetResolution(SHT1x_Handler_t *Handler, SHT1x_Resolution_t *Resolution);
#endif


#if (SHT1X_CONFIG_INTERNAL_HEATER_CONTROL)
/**
 * @brief  Set internal heater on or off.
 * @param  Handler: Pointer to handler
 * @param  Heater:
 *         - SHT1x_HeaterOff: Turn off internal heater.
 *         - SHT1x_HeaterOn: Turn on internal heater.
 * 
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 */
SHT1x_Result_t
SHT1x_SetInternalHeater(SHT1x_Handler_t *Handler, SHT1x_Heater_t Heater);


/**
 * @brief  Get internal heater state.
 * @param  Handler: Pointer to handler
 * @param  Heater: Pointer to give internal heater state.
 *         - SHT1x_HeaterOff: Turn off internal heater.
 *         - SHT1x_HeaterOn: Turn on internal heater.
 * 
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 *         - SHT1x_FAIL: Operation failed.
 */
SHT1x_Result_t
SHT1x_GetInternalHeater(SHT1x_Handler_t *Handler, SHT1x_Heater_t *Heater);
#endif


#if (SHT1X_CONFIG_POWER_VOLTAGE_CONTROL == 0)
/**
 * @brief  Set The SHT1x power supply voltage.
 * @param  Handler: Pointer to handler
 * @param  Voltage: Sht1x power supply voltage.
 * @note   The accuracy of temperature measurement is related to the accuracy of the
 *         input voltage.
 * @note   The default power supply voltage is 5V. 
 * @retval SHT1x_Result_t
 *         - SHT1x_OK: Operation was successful.
 */
SHT1x_Result_t
SHT1x_SetPowVoltage(SHT1x_Handler_t *Handler, float Voltage);
#endif



#ifdef __cplusplus
}
#endif

#endif //! _SHT1X_H_
