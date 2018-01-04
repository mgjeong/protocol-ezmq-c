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

class CEZMQReadingTest: public TestWithMock
{
protected:
    void SetUp()
    {
        ASSERT_EQ(CEZMQ_OK, ezmqCreateEvent(&mEventHandle));
        ASSERT_EQ(CEZMQ_OK, ezmqCreateReading(mEventHandle, &mReadingHandle));
        TestWithMock::SetUp();
    }

    void TearDown()
    {
        TestWithMock::TearDown();
    }

    ezmqEventHandle_t mEventHandle;
    ezmqReadingHandle_t mReadingHandle;
    const char *mId = "id";
    const char *mDevice = "device";
    const char *mName = "temperature";
    const char *mValue = "15";
    long mData = 10;
    long mValue1;
    char *mValue2;
};

TEST_F(CEZMQReadingTest, ezmqReadingInitialize)
{
    ASSERT_EQ(CEZMQ_OK, ezmqCreateReading(mEventHandle, &mReadingHandle));
}

TEST_F(CEZMQReadingTest, ezmqReadingId)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetID(mReadingHandle, mId));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetID(mReadingHandle, &mValue2));
    if(0 != strcmp(mId, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQReadingTest, ezmqReadingCreated)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetCreated(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetCreated(mReadingHandle, &mValue1));
    EXPECT_EQ(mData, mValue1);
}

TEST_F(CEZMQReadingTest, ezmqReadingModified)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetModified(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetModified(mReadingHandle, &mValue1));
    EXPECT_EQ(mData, mValue1);
}

TEST_F(CEZMQReadingTest, ezmqReadingOrigin)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetOrigin(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetOrigin(mReadingHandle, &mValue1));
    EXPECT_EQ(mData, mValue1);
}

TEST_F(CEZMQReadingTest, ezmqReadingPushed)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetPushed(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetPushed(mReadingHandle, &mValue1));
    EXPECT_EQ(mData, mValue1);
}

TEST_F(CEZMQReadingTest, ezmqReadingName)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetName(mReadingHandle, mName));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetName(mReadingHandle, &mValue2));
    if(0 != strcmp(mName, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQReadingTest, ezmqReadingValue)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetValue(mReadingHandle, mValue));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetValue(mReadingHandle, &mValue2));
    if(0 != strcmp(mValue, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQReadingTest, ezmqReadingDevice)
{
    ASSERT_EQ(CEZMQ_OK, ezmqReadingSetDevice(mReadingHandle, mDevice));
    ASSERT_EQ(CEZMQ_OK, ezmqReadingGetDevice(mReadingHandle, &mValue2));
    if(0 != strcmp(mDevice, mValue2))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQReadingTest, ezmqReadingNegative)
{
    mEventHandle = NULL;
    ASSERT_EQ(CEZMQ_ERROR, ezmqCreateReading(mEventHandle, &mReadingHandle));
    mReadingHandle = NULL;
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetID(mReadingHandle, mId));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetID(mReadingHandle, &mValue2));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetCreated(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetCreated(mReadingHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetModified(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetModified(mReadingHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetOrigin(mReadingHandle, mData));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetOrigin(mReadingHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetPushed(mReadingHandle, 10));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetPushed(mReadingHandle, &mValue1));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetName(mReadingHandle, mName));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetName(mReadingHandle, &mValue2));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetValue(mReadingHandle, mValue));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetValue(mReadingHandle, &mValue2));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingSetDevice(mReadingHandle, mDevice));
    ASSERT_EQ(CEZMQ_ERROR, ezmqReadingGetDevice(mReadingHandle, &mValue2));
}
