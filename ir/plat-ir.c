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
/*****************************************************************************
*
*   Plat-irRemote.c
*
*   Description: RaspberryPi ir implementation
*
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "comcastIrKeyCodes.h"
#include "plat_ir.h"

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdio.h>
#include "lirc_key_codes.h"

#ifdef DEBUG_PLAT
#define DEBUG_MSG(x,y...) printf(x,##y)
#else
#define DEBUG_MSG(x,y...) {;}
#endif

#define LIRCD_SOCKET_PATH "/var/run/lirc/lircd"
static int lircfd = -1;

//Platform specific control block.
typedef struct _PlatformData
{
    int                   repeats;   //repeat counter.
    int                   last_key;  //Last key cache.
    PLAT_IrKeyCallback_t  key_cb;    //Call back function when key is received.
} PlatformData;

static PlatformData Platform_Data;

void error(char *msg)
{
    perror(msg);
    exit(1);
}


/**
* @brief Register callback function to which IR Key events should be posted.
*
* This function registers the calling applications callback function.  The application
* will then be notified of IR Key events via this callback function.
*
* @param [in]  func    Function reference of the callback function to be registered.
* @return None.
*/
void PLAT_API_RegisterIRKeyCallback(PLAT_IrKeyCallback_t func)
{
    Platform_Data.key_cb = func;
}

/**
* @brief Initialize the underlying IR module.
*
* This function opens the lirc socket and connects to it
*
* @param     None.
* @return    Return Code.
* @retval    0 if successful.
*/
int  PLAT_API_INIT(void)
{
    DEBUG_MSG("<%s, %d>** DEBUG iarmMgr/ir -- %s()\n",__FILE__,__LINE__,__FUNCTION__);
    struct sockaddr_un lircSocket;
    lircSocket.sun_family = AF_UNIX;

    strcpy(lircSocket.sun_path, LIRCD_SOCKET_PATH);
    lircfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (lircfd == -1) {
        perror("socket");
    }
    if (connect(lircfd, (struct sockaddr *)&lircSocket, sizeof(lircSocket)) == -1) {
        perror("connect");
    }
    return 0;
}

/**
* @brief Close the IR device module.
*
* This function closes the LIRC socket
*
* @param None.
* @return None.
*/
void PLAT_API_TERM(void)
{
    close(lircfd);
    DEBUG_MSG("<%s, %d>** DEBUG iarmMgr/ir -- %s()\n",__FILE__,__LINE__,__FUNCTION__);
}

/**
* @brief Execute key event loop.
*
* This function executes the platform-specific key event loop.
* This function reads from the LIRC socket, gets the keys from the message and maps the keys into Comcast keys
*
* @param None.
* @return None.
*/
void PLAT_API_LOOP()
{
    int messageLen, bytesRead  = 0;
    char *messageBuffer;

    uint32_t keyCode = 0;
    uint32_t keyCodeComcast = 0;
    char keyCodeLirc[17];
    char keyCodeStr[7];
    char keyName[40];  //
    int keyRepeatCount = 0;
    DEBUG_MSG("<%s, %d>** DEBUG iarmMgr/ir -- %s()\n",__FILE__,__LINE__,__FUNCTION__);
    while (1) {
        ioctl(lircfd, FIONREAD, &messageLen);
        if (messageLen > 0) {
            messageBuffer = (char *) malloc( sizeof(char) * ( messageLen + 1 ) );
            memset(messageBuffer, 0 , messageLen + 1);
            memset(keyName, 0 , 40);
            memset(keyCodeLirc, 0 , 17);
            memset(keyCodeStr, 0 , 7);
            bytesRead = read(lircfd, messageBuffer, messageLen);
            if (bytesRead > 0) // key
            {
                sscanf(messageBuffer, "%s %02d %40s ", keyCodeLirc, &keyRepeatCount, keyName);

                memcpy(keyCodeStr, &keyCodeLirc[8], 6);
             
                keyCode = (int)strtoul(keyCodeStr, NULL, 16);
               
                switch(keyCode){
                    case LIRC_KEY_1: keyCodeComcast = KED_DIGIT1; break;
                    case LIRC_KEY_2: keyCodeComcast = KED_DIGIT2; break;
                    case LIRC_KEY_3: keyCodeComcast = KED_DIGIT3; break;
                    case LIRC_KEY_4: keyCodeComcast = KED_DIGIT4; break;
                    case LIRC_KEY_5: keyCodeComcast = KED_DIGIT5; break;
                    case LIRC_KEY_6: keyCodeComcast = KED_DIGIT6; break;
                    case LIRC_KEY_7: keyCodeComcast = KED_DIGIT7; break;
                    case LIRC_KEY_8: keyCodeComcast = KED_DIGIT8; break;
                    case LIRC_KEY_9: keyCodeComcast = KED_DIGIT9; break;
                    case LIRC_KEY_0: keyCodeComcast = KED_DIGIT0; break;

                    case LIRC_KEY_OK:          keyCodeComcast = KED_SELECT;      break;// and key Enter also have the same key code
                    case LIRC_KEY_POWER:       keyCodeComcast = KED_POWER;       break;
                    case LIRC_KEY_UP:          keyCodeComcast = KED_ARROWUP;     break;
                    case LIRC_KEY_DOWN:        keyCodeComcast = KED_ARROWDOWN;   break;
                    case LIRC_KEY_LEFT:        keyCodeComcast = KED_ARROWLEFT;   break;
                    case LIRC_KEY_RIGHT:       keyCodeComcast = KED_ARROWRIGHT;  break;
                    case LIRC_KEY_REWIND:      keyCodeComcast = KED_REWIND;      break;
                    case LIRC_KEY_PLAY:        keyCodeComcast = KED_PLAY;        break;
                    case LIRC_KEY_FASTFORWARD: keyCodeComcast = KED_FASTFORWARD; break;
                    case LIRC_KEY_RECORD:      keyCodeComcast = KED_RECORD;      break;
                    case LIRC_KEY_REPLAY:      keyCodeComcast = LIRC_KEY_REPLAY; break;// this key is not in the comcastIrKeyCodes
                    case LIRC_KEY_A:           keyCodeComcast = KED_KEYA;        break;
                    case LIRC_KEY_B:           keyCodeComcast = KED_KEYB;        break;
                    case LIRC_KEY_C:           keyCodeComcast = KED_KEYC;        break;
                    case LIRC_KEY_D:           keyCodeComcast = KED_KEYD;        break;
                    case LIRC_KEY_PAGE_UP:     keyCodeComcast = KED_PAGEUP;      break;
                    case LIRC_KEY_PAGE_DOWN:   keyCodeComcast = KED_PAGEDOWN;    break;
                    case LIRC_KEY_GUIDE:       keyCodeComcast = KED_GUIDE;       break;
                    case LIRC_KEY_VOLUME_UP:   keyCodeComcast = KED_VOLUMEUP;    break;
                    case LIRC_KEY_VOLUME_DOWN: keyCodeComcast = KED_VOLUMEDOWN;  break;
                    case LIRC_KEY_KPPLUS:      keyCodeComcast = LIRC_KEY_KPPLUS; break;// this key is not in the comcastIrKeyCodes.h
                    case LIRC_KEY_KPMINUS:     keyCodeComcast = LIRC_KEY_KPMINUS;break;// this key is not in the comcastIrKeyCodes.h
                    case LIRC_KEY_MUTE:        keyCodeComcast = KED_MUTE;        break;
                    default:                   keyCodeComcast = keyCode;         break;
                }

                    //check if it was KEY_PRESSED or KEY_RELEASE event
                    if(strstr(keyName, keyReleaseString) != NULL ) // key release event received
                       Platform_Data.key_cb(KET_KEYUP, keyCodeComcast);
                   else
                       Platform_Data.key_cb(KET_KEYDOWN, keyCodeComcast);
            }
            free(messageBuffer);
        }
	usleep(1000);
    }
}
