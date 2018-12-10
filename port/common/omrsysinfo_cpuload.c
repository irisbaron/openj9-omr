/*******************************************************************************
 * Copyright (c) 1991, 2018 IBM Corp. and others
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
#include "omrport.h"
#include <string.h>

/**
 * Obtain the cumulative CPU load (utilization as percentage) of all CPUs on the system.
 * The cpuLoad value represent system utilization in percentage. 
 *
 * @param[in] OMRPortLibrary portLibrary The port library.
 * @param[out] OMRSysinfoCPULoad cpuLoad  struct to receive the CPU load 
 *
 * @return 0 on success, negative portable error code on failure.
 *
 */
intptr_t
omrsysinfo_get_CPU_load_helper(struct OMRPortLibrary *portLibrary,  struct OMRSysinfoCPULoad *systemCpuLoad)
{
    intptr_t ret;
    J9SysinfoCPUTime latestSystemCpuTime;
	ret = omrsysinfo_get_CPU_utilization(portLibrary,&latestSystemCpuTime);
	if (ret < 0) {
        //propogate the error
        /* not supported on this platform or user does not have sufficient rights */
        return ret;
	}
    
	if (NULL == oldestSystemCpuTime) { /* first call to this method */
        memcpy(&oldestSysteCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCpuTime));
        memcpy(&interimSystemCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCpuTime));
        return OMRPORT_ERROR_OPFAILED;
	}

	/* calculate using the most recent value in the history */
	if ((latestSystemCpuTime.timestamp - interimSystemCpuTime.timestamp) >= MINIMUM_INTERVAL) {
		
		ret = omrsysinfo_calculateCpuLoad(&latestSystemCpuTime, &interimSystemCpuTime, systemCpuLoad);

		if (ret == 0) //systemCpuLoad >= 0.0) { /* no errors detected in the statistics */
            /* discard the oldestSystemCpuTime, replace it with interimSystemCpuTime and save newestSystemCpuTime as the new interimSystemCpuTime. */
            memcpy(&oldestSysteCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCpuTime));
            memcpy(&interimSystemCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCpuTime));
		} else {
            /*
             * either the latest time or the interim time are bogus.
             * Discard the interim value and replace with the latest value.
             */
                memcpy(&interimSystemCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCPUTime));
      
            /* attempt to recompute using the oldestSystemCpuTime. */
            
            if ((latestSystemCpuTime.timestamp - oldestSystemCpuTime.timestamp) >= MINIMUM_INTERVAL) {
	
                ret = omrsysinfo_calculateCpuLoad(latestSystemCpuTime, oldestSystemCpuTime, systemCpuLoad);
                if (ret != 0) {
                    /* the stats look bogus.  Discard them */
                    /* discard oldSystemCpuLoad and replace it with newestSystemCpuTime. */
                    memcpy(&oldestSystemCpuTime, &latestSystemCpuTime, sizeof(J9SysinfoCPUTime));

                }
         
            }
        }

	return ret;
    

}


int32_t omrsysinfo_calculateCpuLoad(J9SysinfoCPUTime *endRecord, J9SysinfoCPUTime *startRecord, struct OMRSysinfoCPULoad *cpuLoad)
{
    
    int32_t rc = 0;
    double timestampDelta = endRecord.getTimestamp() - startRecord.getTimestamp();

    double cpuDelta = endRecord.getCpuTime() - startRecord.getCpuTime();
    if ((timestampDelta <= 0) || (cpuDelta < 0)) {
        return OMRPORT_ERROR_SYSINFO_OPFAILED; /* the stats are invalid */ 
    }
    /* ensure the load can't go over 1.0 */
    cpuLoad.cpuLoad = OMR_MIN(cpuDelta / (endRecord.getNumberOfCpus() * timestampDelta),
    return rc;
}
