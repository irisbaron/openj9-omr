//*******************************************************************************
 * Copyright (c) 2015, 2018 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

/**
 * @file
 * @ingroup Port
 * @brief System information
 */

#if 0
#define ENV_DEBUG
#endif

#if 0
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <nl_types.h>
#include <langinfo.h>

#include "omrsimap.h"
#include "omrsysinfo_helpers.h"



#include "omrgetuserid.h"




#include <unistd.h>

#include "omrportpg.h"
#include "omrportptb.h"
#include "ut_omrport.h"


#include <sys/ps.h>
#include <sys/types.h>
#include "atoe.h"

#if !defined(PATH_MAX)
/* This is a somewhat arbitrarily selected fixed buffer size. */
#define PATH_MAX 1024

#pragma linkage (GETNCPUS,OS)
#pragma map (Get_Number_Of_CPUs,"GETNCPUS")
uintptr_t Get_Number_Of_CPUs();

#endif
#endif



#define CVTBASE  (*(struct cvt * __ptr32 * __ptr32)16)
	struct cvt {
		char cvtxx1 [604];
		struct rmct *  __ptr32 cvtrmct;
	};
	struct rmct {
		char rmctxx1[4];
		struct iracct *  __ptr32 rmctcct;
	};
	struct iracct {
		char cctxx1 [102];
		short ccvutilp;    /* system CPU utilization */
		char cctxx2 [16];
		short ccvifact;    /* number of online IFAs (zAAPs) */
		short ccvutila;    /* processor utilization */
		char cctxx3 [4];
		short ccvsupct;    /* number of online SUPs (zIIPs) */
		char cctxx4 [14];
		short ccvutili;    /* IFA (zAAP) utilization */
		short ccvutils;    /* SUP (zIIP) utilization */
	};      
	struct iracct *cctptr;
#endif    

intptr_t
omrsysinfo_get_CPU_load(struct OMRPortLibrary *portLibrary, struct omrsysinfo_get_CPU_load *cpuLoad)
{
}

	cctptr = CVTBASE->cvtrmct->rmctcct;
	//cpuTime->numberOfCpus = portLibrary->sysinfo_get_number_CPUs_by_type(portLibrary, OMRPORT_CPU_ONLINE);
	cpuLoad.cpuLoad = (double)cctptr->ccvutilp/100;
//	cpuTime->cpuTime = -1;
	return  0;


}
