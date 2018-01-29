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

#ifndef UNITTESTHELPER_H
#define UNITTESTHELPER_H

#include <gtest/gtest.h>
#include <HippoMocks/hippomocks.h>

#include "cezmqevent.h"
#include "cezmqreading.h"

class TestWithMock: public testing::Test
{
public:
    MockRepository mocks;

protected:
    virtual ~TestWithMock() noexcept(noexcept(std::declval<Test>().~Test())) {}

    virtual void TearDown() {
        try
        {
            mocks.VerifyAll();
        }
        catch (...)
        {
            mocks.reset();
            throw;
        }
    }
};

ezmqEventHandle_t getezmqEvent()
{
    const char *id = "id";
    const char *device = "device";
    const char *readingId1 = "id1";
    const char *readingName1 = "reading1";
    const char *readingValue1 = "25";
    const char *readingDevice1 = "device";
    const char *readingId2 = "id2";
    const char *readingName2 = "reading2";
    const char *readingValue2 = "20";
    const char *readingDevice2 = "device";

    ezmqEventHandle_t eventHandle; //creation and set event fields
    CEZMQErrorCode  result = ezmqCreateEvent(&eventHandle);
    if(result != CEZMQ_OK)
    {
        printf("\nEvent initialization [Result]: %d\n", result);
        return NULL;
    }
    ezmqEventSetID(eventHandle, id);
    ezmqEventSetCreated(eventHandle, 10);
    ezmqEventSetModified(eventHandle, 20);
    ezmqEventSetOrigin(eventHandle, 20);
    ezmqEventSetPushed(eventHandle, 10);
    ezmqEventSetDevice(eventHandle, device);

    ezmqReadingHandle_t reading1Handle; //creation and set first reading fields
    ezmqCreateReading(eventHandle, &reading1Handle);
    ezmqReadingSetID(reading1Handle, readingId1 );
    ezmqReadingSetCreated(reading1Handle, 25);
    ezmqReadingSetModified(reading1Handle, 20);
    ezmqReadingSetOrigin(reading1Handle, 25);
    ezmqReadingSetPushed(reading1Handle, 1);
    ezmqReadingSetName(reading1Handle, readingName1);
    ezmqReadingSetValue(reading1Handle, readingValue1);
    ezmqReadingSetDevice(reading1Handle, readingDevice1);

    ezmqReadingHandle_t reading2Handle; //creation and set second reading fields
    ezmqCreateReading(eventHandle, &reading2Handle);
    ezmqReadingSetID(reading2Handle, readingId2);
    ezmqReadingSetCreated(reading2Handle, 30);
    ezmqReadingSetModified(reading2Handle, 20);
    ezmqReadingSetOrigin(reading2Handle, 25);
    ezmqReadingSetPushed(reading2Handle, 1);
    ezmqReadingSetName(reading2Handle, readingName2);
    ezmqReadingSetValue(reading2Handle, readingValue2);
    ezmqReadingSetDevice(reading2Handle, readingDevice2);

    return eventHandle;
}

#endif // UNITTESTHELPER_H

