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
#include "cezmqapi.h"
#include "cezmqerrorcodes.h"

class CEZMQByteDataTest: public TestWithMock
{
protected:
    void SetUp()
    {
        TestWithMock::SetUp();
    }

    void TearDown()
    {
        if(mByteDataHandle != NULL)
        {
            ASSERT_EQ(CEZMQ_OK, ezmqDestroyByteData(&mByteDataHandle));
        }
        TestWithMock::TearDown();
    }
    ezmqEventHandle_t mByteDataHandle;
};

TEST_F(CEZMQByteDataTest, constructByteData)
{
    char byteArray[] = { 0x40, 0x05, 0x10, 0x11, 0x12 };
    CEZMQErrorCode result = ezmqCreateByteData(&mByteDataHandle, (uint8_t *) byteArray,
                                                    sizeof(byteArray));
    ASSERT_EQ(CEZMQ_OK, result);
}

TEST_F(CEZMQByteDataTest, DISABLED_constructNullByteData)
{
    char byteArray[] = { 0x40, 0x05, 0x10, 0x11, 0x12 };
    CEZMQErrorCode result = ezmqCreateByteData(&mByteDataHandle, NULL, 0);
    ASSERT_EQ(CEZMQ_ERROR, result);
    result = ezmqCreateByteData(NULL, (uint8_t *) byteArray, sizeof(byteArray));
    ASSERT_EQ(CEZMQ_ERROR, result);
}

TEST_F(CEZMQByteDataTest, getEzmqByteData)
{
    mByteDataHandle = getezmqByteData();
    uint8_t *mData;
    CEZMQErrorCode result = ezmqGetByteData(mByteDataHandle, &mData);
    ASSERT_EQ(CEZMQ_OK, result);
    result = ezmqGetByteData(NULL, &mData);
    ASSERT_EQ(CEZMQ_ERROR, result);
    result = ezmqGetByteData(mByteDataHandle, NULL);
    ASSERT_EQ(CEZMQ_ERROR, result);
}

TEST_F(CEZMQByteDataTest, getEzmqByteDataLength)
{
    mByteDataHandle = getezmqByteData();
    size_t size;
    size_t expected = 5;
    ezmqGetDataLength(mByteDataHandle, &size);
    ASSERT_EQ(expected, size);
    CEZMQErrorCode result = ezmqGetDataLength(mByteDataHandle, NULL);
    ASSERT_EQ(CEZMQ_ERROR, result);
    result = ezmqGetDataLength(NULL, &size);
    ASSERT_EQ(CEZMQ_ERROR, result);
}

TEST_F(CEZMQByteDataTest, destroyByteData)
{
    char byteArray[] = { 0x40, 0x05, 0x10, 0x11, 0x12 };
    CEZMQErrorCode result = ezmqCreateByteData(&mByteDataHandle, (uint8_t *) byteArray,
                                                   sizeof(byteArray));
    ASSERT_EQ(CEZMQ_OK, result);
    result = ezmqDestroyByteData(&mByteDataHandle);
    ASSERT_EQ(CEZMQ_OK, result);
    mByteDataHandle = NULL;
}

TEST_F(CEZMQByteDataTest, destroyNullByteData)
{
    mByteDataHandle = NULL;
    CEZMQErrorCode result = ezmqDestroyByteData(&mByteDataHandle);
    ASSERT_EQ(CEZMQ_ERROR, result);
    result = ezmqDestroyByteData(NULL);
    ASSERT_EQ(CEZMQ_ERROR, result);
    mByteDataHandle = NULL;
}

