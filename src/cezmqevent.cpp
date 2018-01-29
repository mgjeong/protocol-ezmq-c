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

#include "cezmqevent.h"
#include "Event.pb.h"

using namespace ezmq;

CEZMQErrorCode ezmqEventGetID(ezmqEventHandle_t eventHandle, char **value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Event *>(eventHandle)->id().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetCreated(ezmqEventHandle_t eventHandle, long *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Event *>(eventHandle)->created();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetModified(ezmqEventHandle_t eventHandle, long *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Event *>(eventHandle)->modified();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetOrigin(ezmqEventHandle_t eventHandle, long *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Event *>(eventHandle)->origin();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetPushed(ezmqEventHandle_t eventHandle, long *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Event *>(eventHandle)->pushed();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetDevice(ezmqEventHandle_t eventHandle, char **value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = (char *) static_cast<ezmq::Event *>(eventHandle)->device().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode  ezmqEventGetReadingCount(ezmqEventHandle_t eventHandle, int *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    *value = static_cast<ezmq::Event *>(eventHandle)->reading_size();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventGetReading(ezmqEventHandle_t eventHandle, int index, void **value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    try
    {
        *value =  static_cast<ezmq::Event *>(eventHandle)->mutable_reading(index);
    }
    catch(std::exception e)
    {
        return CEZMQ_ERROR;
    }
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqCreateEvent(ezmqEventHandle_t*eventHandle)
{
    VERIFY_NON_NULL(eventHandle)
    *eventHandle = new(std::nothrow) Event();
    ALLOC_ASSERT(eventHandle)
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqDestroyEvent(ezmqEventHandle_t *eventHandle)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(*eventHandle)
    ezmq::Event *event = static_cast<ezmq::Event *>(*eventHandle);
    delete event;
    *eventHandle = NULL;
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetID(ezmqEventHandle_t eventHandle, const char *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Event *>(eventHandle)->set_id(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetCreated(ezmqEventHandle_t eventHandle, long value)
{
    VERIFY_NON_NULL(eventHandle)
    static_cast<ezmq::Event *>(eventHandle)->set_created(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetModified(ezmqEventHandle_t eventHandle,  long value)
{
    VERIFY_NON_NULL(eventHandle)
    static_cast<ezmq::Event *>(eventHandle)->set_modified(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetOrigin(ezmqEventHandle_t eventHandle,  long value)
{
    VERIFY_NON_NULL(eventHandle)
    static_cast<ezmq::Event *>(eventHandle)->set_origin(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetPushed(ezmqEventHandle_t eventHandle,  long value)
{
    VERIFY_NON_NULL(eventHandle)
    static_cast<ezmq::Event *>(eventHandle)->set_pushed(value);
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqEventSetDevice(ezmqEventHandle_t eventHandle, const char *value)
{
    VERIFY_NON_NULL(eventHandle)
    VERIFY_NON_NULL(value)
    static_cast<ezmq::Event *>(eventHandle)->set_device(value);
    return CEZMQ_OK;
}

