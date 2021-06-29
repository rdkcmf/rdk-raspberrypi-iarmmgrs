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
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>


#include <stdint.h>

#include "deepSleepMgr.h"

#define DEBUG_PLAT

#ifdef DEBUG_PLAT
#define DEBUG_MSG(x,y...) printf(x,##y)
#else
#define DEBUG_MSG(x,y...) {;}
#endif


/**
 * @brief Initialize the underlying DeepSleep module.
 *
 * This function must initialize all aspects of the DeepSleep Management module.
 *
 * @param None.
 * @return    Return Code.
 * @retval    0 if successful.
 */
int PLAT_DS_INIT(void)
{
    return 0;
}



void PLAT_DS_TERM(void)
{
}

/**
 * @brief Set the Deep Sleep mode.
 *
 * This function sets the current power state to Deep Sleep
 *
 * @param [in]  deep_sleep_timeout timeout for the deepsleep in seconds
 * @return    Return Code.
 * @retval    0 if successful.
 */
int PLAT_DS_SetDeepSleep(uint32_t deep_sleep_timeout)
{
    DEBUG_MSG("PLAT_DS_SetDeepSleep: putting to sleep, wakeup %d..\r\n", deep_sleep_timeout);
    return 0;
}


/**
 * @brief Wake up from DeepSleep
 *
 * Function to exit from deepsleep
 *
 * @param None
 * @return None
 */
void PLAT_DS_DeepSleepWakeup(void)
{
   DEBUG_MSG("PLAT_DS_DeepSleepWakeup: waking up from deep sleep\r\n");
}

int PLAT_DS_GetLastWakeupReason(DeepSleep_WakeupReason_t *wakeupReason)
{
    DEBUG_MSG("PLAT_DS_GetLastWakeupReason: Get Last Wakeup Reason: DEEPSLEEP_WAKEUPREASON_UNKNOWN");
    *wakeupReason = DEEPSLEEP_WAKEUPREASON_UNKNOWN;
}

int PLAT_DS_GetLastWakeupKeyCode(IARM_Bus_DeepSleepMgr_WakeupKeyCode_Param_t *wakeupKeyCode)
{
    DEBUG_MSG("PLAT_DS_GetLastWakeupKeyCode: Get Last Wakeup KeyCode: 0");
    wakeupKeyCode->keyCode = 0;
    return 0;
}
