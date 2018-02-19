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
#include <iostream>

#include "cezmqbytedata.h"
#include "EZMQByteData.h"

using namespace ezmq;

CEZMQErrorCode ezmqCreateByteData(ezmqByteDataHandle_t *dataHandle, uint8_t * data, size_t dataLength)
{
    VERIFY_NON_NULL(dataHandle)
    VERIFY_NON_NULL(data)
    *dataHandle = new(std::nothrow) EZMQByteData(data, dataLength);
    ALLOC_ASSERT(*dataHandle)
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqGetByteData(ezmqByteDataHandle_t dataHandle, uint8_t ** data)
{
    VERIFY_NON_NULL(dataHandle)
    VERIFY_NON_NULL(data)
    *data = (uint8_t *)static_cast<ezmq::EZMQByteData*>(dataHandle)->getByteData();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqGetDataLength(ezmqByteDataHandle_t dataHandle, size_t *dataLength)
{
    VERIFY_NON_NULL(dataHandle)
    VERIFY_NON_NULL(dataLength)
    *dataLength = static_cast<ezmq::EZMQByteData *>(dataHandle)->getLength();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqDestroyByteData(ezmqByteDataHandle_t *dataHandle)
{
    VERIFY_NON_NULL(dataHandle)
    VERIFY_NON_NULL(*dataHandle)
    ezmq::EZMQByteData *data = static_cast<ezmq::EZMQByteData *>(*dataHandle);
    delete data;
    *dataHandle = NULL;
    return CEZMQ_OK;
}

