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

//Key codes sent by LIRC
//the codes in this file are for Infinity XR2 remote control, for other remotes please change the key codes

// Numeric Keys
#define LIRC_KEY_1 0x1E0001UL
#define LIRC_KEY_2 0x1D0002UL
#define LIRC_KEY_3 0x1C0003UL
#define LIRC_KEY_4 0x1B0004UL
#define LIRC_KEY_5 0x1A0005UL
#define LIRC_KEY_6 0x190006UL
#define LIRC_KEY_7 0x180007UL
#define LIRC_KEY_8 0x170008UL
#define LIRC_KEY_9 0x160009UL
#define LIRC_KEY_0 0x1F0000UL

// Other Keys
#define LIRC_KEY_ENTER 0x180025UL
#define LIRC_KEY_OK 0x180025UL
#define LIRC_KEY_POWER 0x10000FUL
#define LIRC_KEY_UP 0x1C0021UL
#define LIRC_KEY_DOWN 0x1B0022UL
#define LIRC_KEY_LEFT 0x1A0023UL
#define LIRC_KEY_RIGHT 0x190024UL
#define LIRC_KEY_REWIND 0x190033UL
#define LIRC_KEY_PLAY 0x1C0030UL
#define LIRC_KEY_FASTFORWARD 0x180034UL
#define LIRC_KEY_RECORD 0x170035UL
#define LIRC_KEY_REPLAY 0x170053UL
#define LIRC_KEY_A 0x190060UL
#define LIRC_KEY_B 0x180061UL
#define LIRC_KEY_C 0x170062UL
#define LIRC_KEY_D 0x160063UL
#define LIRC_KEY_PAGE_UP 0x150028UL
#define LIRC_KEY_PAGE_DOWN 0x140029UL
#define LIRC_KEY_GUIDE 0x160027UL
#define LIRC_KEY_MENU 0x1D0020UL
#define LIRC_KEY_EXIT 0x13002AUL
#define LIRC_KEY_INFO 0x170026UL
#define LIRC_KEY_LAST 0x190051UL
#define LIRC_KEY_VOLUME_UP 0x15000AUL
#define LIRC_KEY_KPPLUS 0x12000DUL
#define LIRC_KEY_VOLUME_DOWN 0x14000BUL
#define LIRC_KEY_KPMINUS 0x11000EUL
#define LIRC_KEY_MUTE 0x13000CUL

// this is the substring append by LIRC
// when a key is released, change according to lircd configuration
const char* keyReleaseString = "RELEASE";
