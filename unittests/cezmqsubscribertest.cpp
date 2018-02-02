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
#include "cezmqsubscriber.h"
#include "cezmqerrorcodes.h"

static bool isStarted;

void subCB(const ezmqMsgHandle_t /*event*/, CEZMQContentType /*contentType*/)
{
    printf("SUB callback \n");
}

void subTopicCB(const char * topic, const ezmqMsgHandle_t /*event*/, CEZMQContentType /*contentType*/)
{
    printf("\nSUB topic callback\n");
    printf("\nTopic: %s\n", topic);
}

class CEZMQSubscriberTest: public TestWithMock
{
protected:
    void SetUp()
    {
        EXPECT_EQ(CEZMQ_OK, ezmqInitialize());
        EXPECT_EQ(CEZMQ_OK, ezmqCreateSubscriber(mIp, mPort, subCB, subTopicCB, &mSubscriber));
        isStarted = false;
        TestWithMock::SetUp();
    }

    void TearDown()
    {
        if (isStarted)
        {
            EXPECT_EQ(CEZMQ_OK, ezmqStopSubscriber(mSubscriber));
        }
        EXPECT_EQ(CEZMQ_OK, ezmqDestroySubscriber(&mSubscriber));
        EXPECT_EQ(CEZMQ_OK, ezmqTerminate());
        TestWithMock::TearDown();
    }
    ezmqSubHandle_t mSubscriber;
    const char * mTopic = "topic";
    const char * mIp = "localhost";
    int mPort = 5562;
};

TEST_F(CEZMQSubscriberTest, subCreateSubscriber)
{
    ezmqSubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_OK, ezmqCreateSubscriber(mIp, mPort, subCB, subTopicCB, &instance));
    ASSERT_NE(nullptr, instance);
}

TEST_F(CEZMQSubscriberTest, subCreateSubscriber1)
{
    ezmqSubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_ERROR, ezmqCreateSubscriber(mIp, -1, subCB, subTopicCB, &instance));
    ASSERT_EQ(nullptr, instance);
}

TEST_F(CEZMQSubscriberTest, subDestroySubscriber)
{
    ezmqSubHandle_t instance = NULL;
    EXPECT_EQ(CEZMQ_OK, ezmqCreateSubscriber(mIp, mPort, subCB, subTopicCB, &instance));
    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(CEZMQ_OK, ezmqDestroySubscriber(&instance));
}

TEST_F(CEZMQSubscriberTest, subDestroySubscriber1)
{
    EXPECT_EQ(CEZMQ_ERROR, ezmqDestroySubscriber(NULL));
}

TEST_F(CEZMQSubscriberTest, subStart)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
}

TEST_F(CEZMQSubscriberTest, subStartstop)
{
    for( int i =1; i<=10; i++)
    {
        EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
        EXPECT_EQ(CEZMQ_OK, ezmqStopSubscriber(mSubscriber));
    }
}

TEST_F(CEZMQSubscriberTest, subSubscribe)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribe(mSubscriber));
}

TEST_F(CEZMQSubscriberTest, subSubscribeTopic)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, mTopic));
}

TEST_F(CEZMQSubscriberTest, subSubscribeTopicList)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, mTopic));

    const char **topicList = NULL;
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 0));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 5 ));

    topicList = (const char **)calloc(3, sizeof(char *));
    topicList[0] = "topic1";
    topicList[1] = "";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 2));

    topicList[0] = "topic1";
    topicList[1] = "topic2";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 0));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopicList(mSubscriber, topicList, 2));
}

TEST_F(CEZMQSubscriberTest, subSubscribeTopics)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, mTopic));

      // Empty topic test
    const char * testingTopic = "";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Numeric test
    testingTopic = "123";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Alpha-Numeric test
    testingTopic = "1a2b3";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Alphabet forward slash test
    testingTopic = "topic/";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Alphabet-Numeric, forward slash test
    testingTopic = "topic/13/4jtjos/";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Alphabet-Numeric, forward slash test
    testingTopic = "123a/1this3/4jtjos";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Topic contain forward slash at last
    testingTopic = "topic/122/livingroom/";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Topic contain -
    testingTopic = "topic/122/livingroom/-";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Topic contain _
    testingTopic = "topic/122/livingroom_";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));

    // Topic contain .
    testingTopic = "topic/122.livingroom.";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, testingTopic));
}

TEST_F(CEZMQSubscriberTest, subUnSubscribe)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribe(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqUnSubscribe(mSubscriber));
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopic(mSubscriber, mTopic));
    EXPECT_EQ(CEZMQ_OK, ezmqUnSubscribeForTopic(mSubscriber, mTopic));
}


TEST_F(CEZMQSubscriberTest, subUnSubscribeTopicList)
{
    EXPECT_EQ(CEZMQ_OK, emzqStartSubscriber(mSubscriber));

    const char **topicList = NULL;
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 0));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqUnSubscribeForTopicList(mSubscriber, topicList, 0));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 5 ));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqUnSubscribeForTopicList(mSubscriber, topicList, 5 ));

    topicList = (const char **)calloc(3, sizeof(char *));
    topicList[0] = "topic1";
    topicList[1] = "";
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopicList(mSubscriber, topicList, 2));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqUnSubscribeForTopicList(mSubscriber, topicList, 2));

    topicList[0] = "topic1";
    topicList[1] = "topic2";
    EXPECT_EQ(CEZMQ_OK, ezmqSubscribeForTopicList(mSubscriber, topicList, 2));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqUnSubscribeForTopicList(mSubscriber, topicList, 0));
    EXPECT_EQ(CEZMQ_OK, ezmqUnSubscribeForTopicList(mSubscriber, topicList, 2));
}

TEST_F(CEZMQSubscriberTest, subGetIp)
{
    char *ip;
    EXPECT_EQ(CEZMQ_OK, ezmqGetSubIp(mSubscriber, &ip));
    if(0 != strcmp(mIp, ip))
    {
        EXPECT_EQ(CEZMQ_OK, CEZMQ_ERROR);
    }
}

TEST_F(CEZMQSubscriberTest, subGetPort)
{
    int port;
    EXPECT_EQ(CEZMQ_OK, ezmqGetSubPort(mSubscriber, &port));
    EXPECT_EQ(mPort, port);
}

TEST_F(CEZMQSubscriberTest, subNegative)
{
    const char **topicList = NULL;
    int port;
    char *ip;
    EXPECT_EQ(CEZMQ_ERROR, emzqStartSubscriber(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqSubscribe(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqSubscribeForTopic(NULL, "topic"));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqSubscribeForTopic(mSubscriber, NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqSubscribeForTopicList(NULL, topicList, 0));
    EXPECT_EQ(CEZMQ_ERROR, ezmqUnSubscribe(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqUnSubscribeForTopic(NULL, "topic"));
    EXPECT_EQ(CEZMQ_INVALID_TOPIC, ezmqUnSubscribeForTopic(mSubscriber, NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqUnSubscribeForTopicList(NULL, topicList, 0));
    EXPECT_EQ(CEZMQ_ERROR, ezmqStopSubscriber(NULL));
    EXPECT_EQ(CEZMQ_ERROR, ezmqGetSubIp(NULL, &ip));
    EXPECT_EQ(CEZMQ_ERROR, ezmqGetSubPort(NULL, &port));
}
