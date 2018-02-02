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
 * @file   cezmqbytedata.h
 *
 * @brief This file provides APIs for ezmq bytedata.
 */

#ifndef __EZMQ_BYTEDATA_H_INCLUDED__
#define __EZMQ_BYTEDATA_H_INCLUDED__

#include "cezmqerrorcodes.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Byte data handle
 */
typedef void * ezmqByteDataHandle_t;

/**
 * Create ezmq byte data.
 *
 * @param dataHandle -Given byte data handle will be filled as return value.
 *
 * @return CEZMQErrorCode -CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqCreateByteData(ezmqByteDataHandle_t *dataHandle, uint8_t * data,
        size_t dataLength);

/**
 * Get data field of given byte data handle.
 * Note: Application should not free data.
 *
 * @param dataHandle -byte data handle.
 * @param data -data will be filled as return value.
 *
 * @return CEZMQErrorCode -CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqGetByteData(ezmqByteDataHandle_t dataHandle, uint8_t ** data);

/**
 * Get byte data length for the given byte data handle.
 *
 * @param dataHandle -byte data handle.
 * @param dataLength -Data length will be filled as return value.
 *
 * @return CEZMQErrorCode -CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqGetDataLength(ezmqByteDataHandle_t dataHandle, size_t *dataLength);

/**
 * Destroy ezmq byte data. Application needs to call this API to delete/free ezmq byte data.
 *
 * @param dataHandle -byte data handle.
 *
 * @return CEZMQErrorCode -CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqDestroyByteData(ezmqByteDataHandle_t *dataHandle);

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_BYTEDATA_H_INCLUDED__

