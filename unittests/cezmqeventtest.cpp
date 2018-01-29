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

#include "unittesthelper.h"
#include "cezmqevent.h"
#include "cezmqreading.h"
#include "cezmqerrorcodes.h"

class CEZMQEventTest: public TestWithMock
{
protected:
    void SetUp()
    {
        ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mEventHandle));
        TestWithMock::SetUp();
    }

    void TearDown()
    {
        ASSERT_EQ(CEZMQ_OK, ezmqDestroyEvent(&mEventHandle));
        TestWithMock::TearDown();
    }
    ezmqEventHandle_t mEventHandle;
    ezmqReadingHandle_t mReadingHandle;
    const char *mId = "id";
    const char *mDevice = "device";
    long mValue = 10;
    long mValue1;
    char *mValue2;
    int mCount;
};

TEST_F(CEZMQEventTest, ezmqEventInitialize)
{
    ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mEventHandle));
}

TEST_F(CEZMQEventTest, ezmqEventId)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetID(mEventHandle, mId));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetID(mEventHandle, &mValue2));
    if(0 != strcmp(mId, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQEventTest, ezmqEventCreated)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetCreated(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetCreated(mEventHandle, &mValue1));
    EXPECT_EQ(mValue, mValue1);
}

TEST_F(CEZMQEventTest, ezmqEventModified)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetModified(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetModified(mEventHandle, &mValue1));
    EXPECT_EQ(mValue, mValue1);
}

TEST_F(CEZMQEventTest, ezmqEventOrigin)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetOrigin(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetOrigin(mEventHandle, &mValue1));
    EXPECT_EQ(mValue, mValue1);
}

TEST_F(CEZMQEventTest, ezmqEventPushed)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetPushed(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetPushed(mEventHandle, &mValue1));
    EXPECT_EQ(mValue, mValue1);
}

TEST_F(CEZMQEventTest, ezmqEventDevice)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventSetDevice(mEventHandle, mDevice));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetDevice(mEventHandle, &mValue2));
    if(0 != strcmp(mDevice, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQEventTest, ezmqEventReadingCount)
{
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetReadingCount(mEventHandle, &mCount));
    EXPECT_EQ(0, mCount);
}

TEST_F(CEZMQEventTest, ezmqEventReading)
{
    ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mEventHandle));
    ASSERT_EQ(CEZMQ_OK, ezmqCreateReading(mEventHandle, &mReadingHandle));
    ASSERT_EQ(CEZMQ_OK, ezmqEventGetReading(mEventHandle, 0, &mReadingHandle));
}

TEST_F(CEZMQEventTest, ezmqEventDestroy)
{
    ezmqEventHandle_t mHandle;
    ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mHandle));
    ASSERT_EQ(CEZMQ_OK, ezmqDestroyEvent(&mHandle));
}

TEST_F(CEZMQEventTest, ezmqEventNegative)
{
    mEventHandle = NULL;
    mReadingHandle = NULL;
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetID(mEventHandle, mId));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetID(mEventHandle, &mValue2));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetCreated(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetCreated(mEventHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetModified(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetModified(mEventHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetOrigin(mEventHandle, mValue));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetOrigin(mEventHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetPushed(mEventHandle, 10));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetPushed(mEventHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventSetDevice(mEventHandle, mDevice));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetDevice(mEventHandle, &mValue2));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetReadingCount(mEventHandle, &mCount));
    ASSERT_EQ(CEZMQ_ERROR, ezmqEventGetReading(mEventHandle, 0, &mReadingHandle));
    ASSERT_EQ(CEZMQ_ERROR, ezmqDestroyEvent(NULL));
    ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mEventHandle));
}

