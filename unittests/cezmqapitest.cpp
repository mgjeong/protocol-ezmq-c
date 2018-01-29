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

class CEZMQAPITest: public TestWithMock
{
protected:
    void SetUp()
    {
        TestWithMock::SetUp();
    }

    void TearDown()
    {
        TestWithMock::TearDown();
    }
};

TEST_F(CEZMQAPITest, ezmqInitialize)
{
    ASSERT_EQ(ezmqInitialize(), CEZMQ_OK);
}

TEST_F(CEZMQAPITest, ezmqTerminate)
{
    ASSERT_EQ(ezmqTerminate(), CEZMQ_OK);
}

TEST_F(CEZMQAPITest, ezmqInitializeTerminate)
{
    ASSERT_EQ(ezmqInitialize(), CEZMQ_OK);
    ASSERT_EQ(ezmqTerminate(), CEZMQ_OK);
}

TEST_F(CEZMQAPITest, ezmqGetStatus)
{
    ASSERT_EQ(ezmqInitialize(), CEZMQ_OK);
    ASSERT_EQ(ezmqGetStatus(), CEZMQ_INITIALIZED);
    ASSERT_EQ(ezmqTerminate(), CEZMQ_OK);
    ASSERT_EQ(ezmqGetStatus(), CEZMQ_TERMINATED);
}

