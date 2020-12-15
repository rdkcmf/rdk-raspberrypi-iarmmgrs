##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2017 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([iarmmgrs-hal], [1.0], [ridish.ra@lnttechservices.com])
AC_CONFIG_SRCDIR([ir/plat-ir.c])

AM_INIT_AUTOMAKE([foreign 1.0])

# Checks for programs.
AC_PROG_CC

# Checks for libtool
LT_INIT

# Libs and cflags
IARMMGRS_HAL_IR_LIBS=""
IARMMGRS_HAL_POWER_LIBS=""
IARMMGRS_HAL_DS_LIBS=""
AC_SUBST(IARMMGRS_HAL_IR_LIBS)
AC_SUBST(IARMMGRS_HAL_POWER_LIBS)
AC_SUBST(IARMMGRS_HAL_DS_LIBS)

# More libs and cflags should using pkg-config later.
# now we just temperary hard coded here.
IARMMGRS_HAL_IR_CFLAGS="-I$PKG_CONFIG_SYSROOT_DIR/usr/include/rdk/iarmmgrs-hal"
IARMMGRS_HAL_POWER_CFLAGS="-I$PKG_CONFIG_SYSROOT_DIR/usr/include/rdk/iarmmgrs-hal \
                           -I$PKG_CONFIG_SYSROOT_DIR/usr/include/rdk/iarmbus"
IARMMGRS_HAL_DS_CFLAGS="-I$PKG_CONFIG_SYSROOT_DIR/usr/include/rdk/iarmmgrs-hal \
                          -I$PKG_CONFIG_SYSROOT_DIR/usr/include/rdk/iarmbus"
AC_SUBST(IARMMGRS_HAL_IR_CFLAGS)
AC_SUBST(IARMMGRS_HAL_POWER_CFLAGS)
AC_SUBST(IARMMGRS_HAL_DS_CFLAGS)

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC


# check if deepsleep is enabled
AC_ARG_ENABLE([dsleep],
[  --enable-dsleep    Enable deepsleep],
[case "${enableval}" in
  yes) dsleep=true ;;
  no)  dsleep=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-dsleep]) ;;
esac],[dsleep=false])
AM_CONDITIONAL([DEEPSLEEP_ENABLED], [test x$dsleep = xtrue])

# check for termal protection
AC_ARG_ENABLE([thermalprotection], [--enable-thermalprotection "Enable thermal protection"],
      [case "${enableval}" in
	       yes) thermalprotection=true ;;
	       no)  thermalprotection=false ;;
	       *) AC_MSG_ERROR([bad value ${enableval} for thermal protection]) ;;
       esac], [thermalprotection=false])
AM_CONDITIONAL([THERMAL_PROTECTION_ENABLED], [test x$thermalprotection = xtrue])

AC_CONFIG_FILES([Makefile ir/Makefile power/Makefile deepsleep/Makefile])
AC_OUTPUT

