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
 * @file   cezmqevent.h
 *
 * @brief   This file contains apis for creating events and getting/setting event fields.
 */

#ifndef __EZMQ_EVENT_H_INCLUDED__
#define __EZMQ_EVENT_H_INCLUDED__

#include "cezmqerrorcodes.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Event handle
 */
typedef void * ezmqEventHandle_t;

/**
 * Get Id field of given event handle.
 * Note: Application should not free value.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetID(ezmqEventHandle_t eventHandle, char ** value);

/**
 * Get created field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetCreated(ezmqEventHandle_t eventHandle, long *value);

/**
 * Get modified field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetModified(ezmqEventHandle_t eventHandle, long *value);

/**
 * Get origin field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetOrigin(ezmqEventHandle_t eventHandle, long *value);

/**
 * Get pushed field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetPushed(ezmqEventHandle_t eventHandle, long *value);

/**
 * Get device field of given event handle.
 * Note: Application should not free value.
 *
 * @param eventHandle - Event handle.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetDevice(ezmqEventHandle_t eventHandle, char **value);

/**
 * Get reading count for the given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - Number of readings will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetReadingCount(ezmqEventHandle_t eventHandle, int *value);

/**
 * Get reading for the given index in the given event handle.
 *
 * @param eventHandle - Event handle.
 * @param index - Index for which reading is required.
 * @param value - value will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventGetReading(ezmqEventHandle_t eventHandle, int index, void **value);

/**
 * Initialize ezmq event. Application needs to call this API to create ezmq event.
 *
 * @param eventHandle - Given Event handle will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqCreateEvent(ezmqEventHandle_t *eventHandle);

/**
 * Destroy ezmq event. Application needs to call this API to delete/free ezmq event.
 * It will also free internal reading/s.
 *
 * @param eventHandle - Event handle.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqDestroyEvent(ezmqEventHandle_t *eventHandle);

/**
 * Set id field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetID(ezmqEventHandle_t eventHandle, const char *value);

/**
 * Set created field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetCreated(ezmqEventHandle_t eventHandle, long value);

/**
 * Set modified field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetModified(ezmqEventHandle_t eventHandle, long value);

/**
 * Set origin field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetOrigin(ezmqEventHandle_t eventHandle, long value);

/**
 * Set pushed field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetPushed(ezmqEventHandle_t eventHandle, long value);

/**
 * Set device field of given event handle.
 *
 * @param eventHandle - Event handle.
 * @param value - value to be set.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqEventSetDevice(ezmqEventHandle_t eventHandle, const char *value);

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_EVENT_H_INCLUDED__

