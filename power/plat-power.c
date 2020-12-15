/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include "plat_power.h"

static IARM_Bus_PWRMgr_PowerState_t power_state;

/**
 * @brief Initialize the underlying Power Management module.
 *
 * This function must initialize all aspects of the CPE's Power Management module.
 *
 * @param None.
 * @return    Return Code.
 * @retval    0 if successful.
 */
int PLAT_INIT(void)
{
    power_state = IARM_BUS_PWRMGR_POWERSTATE_ON;
    return 0;
}

/**
 * @brief Set the CPE Power State.
 *
 * This function sets the CPE's current power state to the specified state.
 *
 * @param [in]  newState    The power state to which to set the CPE.
 * @return    Return Code.
 * @retval    0 if successful.
 */
int PLAT_API_SetPowerState(IARM_Bus_PWRMgr_PowerState_t newState)
{
    /* TODO: Add standby mode */
    power_state = newState;
    return 0;
}

/**
 * @brief Get the CPE Power State.
 *
 * This function returns the current power state of the CPE.
 *
 * @param [in]  curState    The address of a location to hold the current power state of
 *                          the CPE on return.
 * @return    Return Code.
 * @retval    0 if successful.
 */
int PLAT_API_GetPowerState(IARM_Bus_PWRMgr_PowerState_t *curState)
{
    *curState = power_state;
    return 0;
}

#ifdef ENABLE_THERMAL_PROTECTION

static float g_fTempThresholdHigh = 60.0f;
static float g_fTempThresholdCritical = 75.0f;

/**
 * @brief Get the  current temperature of the core.
 *
 * @param[out] state            The current state of the core temperature
 * @param[out] curTemperature   Raw temperature value of the core
 *                              in degrees Celsius
 * @param[out] wifiTemperature  Raw temperature value of the wifi chip
 *                              in degrees Celsius
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
*/
int PLAT_API_GetTemperature(IARM_Bus_PWRMgr_ThermalState_t *curState, float *curTemperature, float *wifiTemperature)
{
    if ( curState == NULL || curTemperature == NULL || wifiTemperature == NULL )
        return IARM_RESULT_INVALID_PARAM;

    int value = 0;
    float temp = 0.0f;
    IARM_Bus_PWRMgr_ThermalState_t state = IARM_BUS_PWRMGR_TEMPERATURE_NORMAL;

    FILE* fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if( fp != NULL )
    {
        fscanf (fp, "%d", &value);
        fclose(fp);
    }

    temp = value / 1000;
    *curTemperature = temp;

    if( temp >= g_fTempThresholdHigh )
        state = IARM_BUS_PWRMGR_TEMPERATURE_HIGH;
    if( temp >= g_fTempThresholdCritical )
        state = IARM_BUS_PWRMGR_TEMPERATURE_CRITICAL;

    *curState = state;
    return IARM_RESULT_SUCCESS;
}

/**
 * @brief Set temperature thresholds which will determine the state returned from a call to mfrGetTemperature.
 *
 * @param[in] tempHigh       Temperature threshold at which mfrTEMPERATURE_HIGH
 *                           state will be reported.
 * @param[in] tempCritical   Temperature threshold at which mfrTEMPERATURE_CRITICAL
 *                           state will be reported.
 *
 * @return  Returns the status of the operation.
 * @retval  0 if successful, appropiate error code otherwise.
 */
int PLAT_API_SetTempThresholds(float tempHigh, float tempCritical)
{
    g_fTempThresholdHigh     = tempHigh;
    g_fTempThresholdCritical = tempCritical;

    return IARM_RESULT_SUCCESS;
}

/**
 * @brief Get temperature thresholds which will determine the state returned from a call to mfrGetTemperature.
 *
 * @param[out] tempHigh      Temperature threshold at which mfrTEMPERATURE_HIGH
 *                           state will be reported.
 * @param[out] tempCritical  Temperature threshold at which mfrTEMPERATURE_CRITICAL
 *                           state will be reported.
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 */
int PLAT_API_GetTempThresholds(float *tempHigh, float *tempCritical)
{
    if( tempHigh == NULL || tempCritical == NULL )
        return IARM_RESULT_INVALID_PARAM;

    *tempHigh     = g_fTempThresholdHigh;
    *tempCritical = g_fTempThresholdCritical;

    return IARM_RESULT_SUCCESS;
}

/**
 * @brief Get clock speeds for this device for the given states
 *
 * @param [out] cpu_rate_Normal  The clock rate to be used when in the 'normal' state
 * @param [out] cpu_rate_Scaled  The clock rate to be used when in the 'scaled' state
 * @param [out] cpu_rate_Minimal The clock rate to be used when in the 'minimal' state
 *
 * @return 1 if operation is attempted 0 otherwise
 */
int PLAT_API_DetemineClockSpeeds(uint32_t *cpu_rate_Normal, uint32_t *cpu_rate_Scaled, uint32_t *cpu_rate_Minimal)
{
    return IARM_RESULT_SUCCESS;
}

/**
 * @brief This API sets the clock speed of the CPU.
 * @param [in] speed  One of the predefined parameters to set the clock speed.
 *
 * @return Returns the status of the operation
 * @retval returns 1, if operation is attempted and 0 otherwise
 */
int PLAT_API_SetClockSpeed(uint32_t speed)
{
    return IARM_RESULT_SUCCESS;
}

/**
 * @brief This API returns the clock speed of the CPU
 *
 * @param [out] speed One of the predefined parameters
 * @return Returns the current clock speed.
 */
int PLAT_API_GetClockSpeed(uint32_t *speed)
{
    return IARM_RESULT_SUCCESS;
}

#endif //ENABLE_THERMAL_PROTECTION

/**
 * @brief Close the IR device module.
 *
 * This function must terminate the CPE Power Management module. It must reset any data
 * structures used within Power Management module and release any Power Management
 * specific handles and resources.
 *
 * @param None.
 * @return None.
 */
void PLAT_TERM(void)
{
    return;
}

void PLAT_Reset(IARM_Bus_PWRMgr_PowerState_t newState)
{
    system("reboot");
}

void PLAT_WHReset()
{
    return;
}

void PLAT_FactoryReset()
{
    return;
}

