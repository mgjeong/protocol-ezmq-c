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

#include "cezmqreading.h"
#include "Event.pb.h"

using namespace ezmq;

CEZMQErrorCode ezmqReadingGetID(ezmqReadingHandle_t readingHandle, char **value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Reading *>(readingHandle)->id().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetCreated(ezmqReadingHandle_t readingHandle, long *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Reading *>(readingHandle)->created();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetModified(ezmqReadingHandle_t readingHandle, long *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Reading *>(readingHandle)->modified();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetOrigin(ezmqReadingHandle_t readingHandle, long *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Reading *>(readingHandle)->origin();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetPushed(ezmqReadingHandle_t readingHandle, long *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Reading *>(readingHandle)->pushed();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetName(ezmqReadingHandle_t readingHandle, char **value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Reading *>(readingHandle)->name().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetValue(ezmqReadingHandle_t readingHandle, char **value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Reading *>(readingHandle)->value().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingGetDevice(ezmqReadingHandle_t readingHandle, char **value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Reading *>(readingHandle)->device().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqCreateReading(ezmqEventHandle_t eventHandle, ezmqReadingHandle_t *readingHandle)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(readingHandle)
    *readingHandle  = static_cast<ezmq::Event *>(eventHandle)->add_reading();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetID(ezmqReadingHandle_t readingHandle, const char *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Reading *>(readingHandle)->set_id(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetCreated(ezmqReadingHandle_t readingHandle, long value)
{
    VERIFY_NON_NULL(readingHandle)
    static_cast<ezmq::Reading *>(readingHandle)->set_created(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetModified(ezmqReadingHandle_t readingHandle,  long value)
{
    VERIFY_NON_NULL(readingHandle)
    static_cast<ezmq::Reading *>(readingHandle)->set_modified(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetOrigin(ezmqReadingHandle_t readingHandle,  long value)
{
    VERIFY_NON_NULL(readingHandle)
    static_cast<ezmq::Reading *>(readingHandle)->set_origin(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetPushed(ezmqReadingHandle_t readingHandle,  long value)
{
    VERIFY_NON_NULL(readingHandle)
    static_cast<ezmq::Reading *>(readingHandle)->set_pushed(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetName(ezmqReadingHandle_t readingHandle, const char *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Reading *>(readingHandle)->set_name(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetValue(ezmqReadingHandle_t readingHandle, const char *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Reading *>(readingHandle)->set_value(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqReadingSetDevice(ezmqReadingHandle_t readingHandle, const char *value)
{
    VERIFY_NON_NULL(readingHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Reading *>(readingHandle)->set_device(value);
    return CEZMQ_OK;
}

