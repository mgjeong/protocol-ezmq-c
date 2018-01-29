/*******************************************************************************
 * Copyright 2017 Samsung Electronics All Rights Reserved.
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
 *
 *******************************************************************************/

/**
 * @file   cezmqapi.h
 *
 * @brief This file provides APIs for ezmq: initialize, terminate.
 */

#ifndef __EZMQ_H_INCLUDED__
#define __EZMQ_H_INCLUDED__

#include "cezmqerrorcodes.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initialize required EZMQ components.
 * This API should be called first, before using any EZMQ APIs.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqInitialize();

/**
 * Perform cleanup of EZMQ components.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqTerminate();

/**
 * Return status of EZMQ service.
 *
 * @return CEZMQStatusCode - ezmq status code
 */
EZMQ_EXPORT CEZMQStatusCode ezmqGetStatus();

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_H_INCLUDED__

