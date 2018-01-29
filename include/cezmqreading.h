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
 * @file   cezmqreading.h
 *
 * @brief   This file contains apis for creating readings and getting/setting reading fields.
 */

#ifndef __EZMQ_READING_H_INCLUDED__
#define __EZMQ_READING_H_INCLUDED__

#include "cezmqerrorcodes.h"
#include "cezmqevent.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Reading handle
 */
typedef void *  ezmqReadingHandle_t;

/**
 * Get Id field of given reading handle.
 * Note: Application should not free value.
 *
 * @param readingHandle - Reading handle.
 * @param value - Id will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetID(ezmqReadingHandle_t readingHandle, char **value);

/**
 * Get created field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - Created will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetCreated(ezmqReadingHandle_t readingHandle, long *value);

/**
 * Get modified field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - Modified will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetModified(ezmqReadingHandle_t readingHandle, long *value);

/**
 * Get origin field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - Origin will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetOrigin(ezmqReadingHandle_t readingHandle, long *value);

/**
 * Get pushed field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - Pushed will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetPushed(ezmqReadingHandle_t readingHandle, long *value);

/**
 * Get name field of given reading handle.
 * Note: Application should not free value.
 *
 * @param readingHandle - Reading handle.
 * @param value - Name will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetName(ezmqReadingHandle_t readingHandle, char **value);

/**
 * Get value field of given reading handle.
 * Note: Application should not free value.
 *
 * @param readingHandle - Reading handle.
 * @param value - Value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetValue(ezmqReadingHandle_t readingHandle, char **value);

/**
 * Get device field of given reading handle.
 * Note: Application should not free value.
 *
 * @param readingHandle - Reading handle.
 * @param value - Device will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingGetDevice(ezmqReadingHandle_t readingHandle, char **value);

/**
 * Initialize reading handle for the given event handle. Application needs to call this API to create ezmq reading
 * in given event.
 *
 * @param eventHandle - Event handle in which reading needs to be initialized/created.
 * @param readingHandle - Given Reading handle will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqCreateReading(ezmqEventHandle_t eventHandle, ezmqReadingHandle_t *readingHandle);

/**
 * Set id field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetID(ezmqReadingHandle_t readingHandle, const char *value);

/**
 * Set created field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetCreated(ezmqReadingHandle_t readingHandle, long value);

/**
 * Set modified field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetModified(ezmqReadingHandle_t readingHandle, long value);

/**
 * Set origin field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetOrigin(ezmqReadingHandle_t readingHandle, long value);

/**
 * Set pushed field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetPushed(ezmqReadingHandle_t readingHandle, long value);

/**
 * Set name field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetName(ezmqReadingHandle_t readingHandle, const char *value);

/**
 * Set value field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetValue(ezmqReadingHandle_t readingHandle, const char *value);

/**
 * Set device field of given reading handle.
 *
 * @param readingHandle - Reading handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqReadingSetDevice(ezmqReadingHandle_t readingHandle, const char *value);

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_READING_H_INCLUDED__

