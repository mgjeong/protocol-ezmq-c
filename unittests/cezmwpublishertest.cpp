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
#include "cezmqpublisher.h"
#include "cezmqerrorcodes.h"

static int mPort = 5562;
static bool isStarted;

void startCB(CEZMQErrorCode /*code*/){}
void stopCB(CEZMQErrorCode /*code*/){}
void errorCB(CEZMQErrorCode /*code*/){}

class CEZMQPublisherTest: public TestWithMock
{
    protected:
        void SetUp()
        {
            mPort = mPort +1;
            EXPECT_EQ(CEZMQ_OK, ezmqInitialize());
            EXPECT_EQ(CEZMQ_OK, ezmqCreatePublisher(mPort, startCB, stopCB, errorCB, &mPublisher));
            isStarted = false;
            TestWithMock::SetUp();
        }

        void TearDown()
        {
            if (isStarted)
            {
                EXPECT_EQ(CEZMQ_OK, ezmqStopPublisher(mPublisher));
            }
            EXPECT_EQ(CEZMQ_OK, ezmqDestroyPublisher(&mPublisher));
            EXPECT_EQ(CEZMQ_OK, ezmqTerminate());
            TestWithMock::TearDown();
        }
        ezmqPubHandle_t mPublisher;
        const char * mTopic = "topic";
};

TEST_F(CEZMQPublisherTest, pubCreatePublisher)
{
    ezmqPubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_OK,ezmqCreatePublisher(mPort, startCB, stopCB, errorCB, &instance));
    ASSERT_NE(nullptr, instance);
}

TEST_F(CEZMQPublisherTest, pubCreatePublisher1)
{
    ezmqPubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_ERROR,ezmqCreatePublisher(-1, startCB, stopCB, errorCB, &instance));
    ASSERT_EQ(nullptr, instance);
}

TEST_F(CEZMQPublisherTest, pubDestroyPublisher)
{
    ezmqPubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_OK,ezmqCreatePublisher(mPort, startCB, stopCB, errorCB, &instance));
    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(CEZMQ_OK, ezmqDestroyPublisher(&instance));
}

TEST_F(CEZMQPublisherTest, pubDestroyPublisher1)
{
    EXPECT_EQ(CEZMQ_ERROR, ezmqDestroyPublisher(NULL));
}

TEST_F(CEZMQPublisherTest, pubStartstop)
{
    for( int i =1; i<=10; i++)
    {
        EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));
        EXPECT_EQ(CEZMQ_OK, ezmqStopPublisher(mPublisher));
    }
}

TEST_F(CEZMQPublisherTest, pubStart)
{
    EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));
}

TEST_F(CEZMQPublisherTest, pubPublish)
    {
    void *event = getezmqEvent();
    ASSERT_NE(nullptr, event);
    EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));
    EXPECT_EQ(CEZMQ_OK, ezmqPublish(mPublisher, event));
}

TEST_F(CEZMQPublisherTest, pubPublishOnTopic)
{
    void *event = getezmqEvent();
    ASSERT_NE(nullptr, event);
    EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, mTopic, event));
}

TEST_F(CEZMQPublisherTest, pubPublishOnTopic1)
{
    void *event = getezmqEvent();
    ASSERT_NE(nullptr, event);
    EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));

    // Empty topic test
    const char * testingTopic = "";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Numeric test
    testingTopic = "123";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Alpha-Numeric test
    testingTopic = "1a2b3";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Alphabet forward slash test
    testingTopic = "topic/";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Alphabet-Numeric, forward slash test
    testingTopic = "topic/13/4jtjos/";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Alphabet-Numeric, forward slash test
    testingTopic = "123a/1this3/4jtjos";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Topic contain forward slash at last
    testingTopic = "topic/122/livingroom/";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Topic contain -
    testingTopic = "topic/122/livingroom/-";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Topic contain _
    testingTopic = "topic/122/livingroom_";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));

    // Topic contain .
    testingTopic = "topic/122.livingroom.";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopic(mPublisher, testingTopic, event));
}

TEST_F(CEZMQPublisherTest, pubPublishTopicList)
{
    void *event = getezmqEvent();
    ASSERT_NE(nullptr, event);
    EXPECT_EQ(CEZMQ_OK, ezmqStartPublisher(mPublisher));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopic(mPublisher, "", event));
    const char **topicList = NULL;
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopicList(mPublisher, topicList, 0,  event));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopicList(mPublisher, topicList, 5,  event));
    topicList = (const char **)calloc(3, sizeof(char *));
    topicList[0] = "topic1";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopicList(mPublisher, topicList, 0,  event));
    topicList[1] = "";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopicList(mPublisher, topicList, 2,  event));

    topicList[0] = "topic1";
    topicList[1] = "topic2";
    EXPECT_EQ(CEZMQ_OK, ezmqPublishOnTopicList(mPublisher, topicList, 2,  event));
}

TEST_F(CEZMQPublisherTest, pubGetPort)
{
    int port;
    EXPECT_EQ(CEZMQ_OK, ezmqGetPubPort(mPublisher, &port));
    EXPECT_EQ(mPort, port);
}

TEST_F(CEZMQPublisherTest, pubNegative)
{
    void *event = getezmqEvent();
    const char **topicList = NULL;
    int port;
    EXPECT_EQ(CEZMQ_ERROR, ezmqStartPublisher(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqPublish(mPublisher, NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqPublishOnTopic(mPublisher, "topic", NULL));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqPublishOnTopic(mPublisher, NULL, event));
    EXPECT_EQ(CEZMQ_ERROR, ezmqPublishOnTopicList(mPublisher, topicList, 1, NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqStopPublisher(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqGetPubPort(NULL, &port));
}

