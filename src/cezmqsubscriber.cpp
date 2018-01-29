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

#include "cezmqsubscriber.h"
#include "EZMQSubscriber.h"
#include "Event.pb.h"

using namespace ezmq;

typedef struct subscriber
{
    EZMQSubscriber *handle;
}subscriber;

void subCB(ezmq::Event event, csubCB subcb)
{
    subcb(&event );
}

void subTopicCB(std::string topic, ezmq::Event event, csubTopicCB topiccb)
{
    topiccb(topic.c_str(), &event );
}

static EZMQSubscriber *getSubInstance(ezmqSubHandle_t subHandle)
{
    subscriber *subObj= static_cast<subscriber *>(subHandle);
    return subObj->handle;
}

CEZMQErrorCode ezmqCreateSubscriber(const char *ip, int port, csubCB subcb,
        csubTopicCB topiccb, ezmqSubHandle_t *subHandle)
 {
    VERIFY_NON_NULL(ip)
    if ( port < 0)
    {
        return CEZMQ_ERROR;
    }
    EZMQSubscriber *subscriberObj = nullptr ;
    subscriberObj = new(std::nothrow) EZMQSubscriber(ip, port,
                                        std::bind(subCB, std::placeholders::_1,  subcb),
                                        std::bind(subTopicCB, std::placeholders::_1, std::placeholders::_2, topiccb));

    ALLOC_ASSERT(subscriberObj)
    subscriber *subInstance = new(std::nothrow) subscriber();
    if(!subInstance)
    {
        delete subscriberObj;
        abort();
    }
    subInstance->handle =  subscriberObj;
    *subHandle = subInstance;
    return CEZMQ_OK;
 }

CEZMQErrorCode emzqStartSubscriber(ezmqSubHandle_t subHandle)
{
    VERIFY_NON_NULL(subHandle)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->start());
}

 CEZMQErrorCode ezmqSubscribe(ezmqSubHandle_t subHandle)
 {
    VERIFY_NON_NULL(subHandle)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->subscribe());
 }

 CEZMQErrorCode ezmqSubscribeForTopic(ezmqSubHandle_t subHandle, const char *topic)
 {
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL_TOPIC(topic)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->subscribe(topic));
 }

CEZMQErrorCode ezmqSubscribeForTopicList(ezmqSubHandle_t subHandle, const char ** topicList, int listSize)
{
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL_TOPIC(topicList)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    if(0 == listSize)
    {
        return CEZMQ_INVALID_TOPIC;
    }
    std::list<std::string> topics;
    for (int  i =0; i < listSize; i++)
    {
        topics.push_back(topicList[i]);
    }
    return CEZMQErrorCode(subscriberObj->subscribe(topics));
}

CEZMQErrorCode ezmqUnSubscribe(ezmqSubHandle_t subHandle)
{
    VERIFY_NON_NULL(subHandle)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->unSubscribe());
}

CEZMQErrorCode ezmqUnSubscribeForTopic(ezmqSubHandle_t subHandle, const char *topic)
{
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL_TOPIC(topic)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->unSubscribe(topic));
}

CEZMQErrorCode ezmqUnSubscribeForTopicList(ezmqSubHandle_t subHandle, const char ** topicList , int listSize)
{
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL_TOPIC(topicList)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    if (0 == listSize)
    {
        return CEZMQ_INVALID_TOPIC;
    }
    std::list<std::string> topics;
    for (int  i =0; i < listSize; i++)
    {
        topics.push_back(topicList[i]);
    }
    return CEZMQErrorCode(subscriberObj->unSubscribe(topics));
}

CEZMQErrorCode ezmqStopSubscriber(ezmqSubHandle_t subHandle)
 {
    VERIFY_NON_NULL(subHandle)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    return CEZMQErrorCode(subscriberObj->stop());
 }

CEZMQErrorCode ezmqGetSubIp(ezmqSubHandle_t subHandle, char **ip)
 {
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL(ip)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    *ip = (char *)subscriberObj->getIp().c_str();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqGetSubPort(ezmqSubHandle_t subHandle, int *port)
{
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL(port)
    EZMQSubscriber *subscriberObj = getSubInstance(subHandle);
    *port = subscriberObj->getPort();
    return CEZMQ_OK;
}

CEZMQErrorCode ezmqDestroySubscriber(ezmqSubHandle_t *subHandle)
{
    VERIFY_NON_NULL(subHandle)
    VERIFY_NON_NULL(*subHandle)
    EZMQSubscriber *subscriberObj = getSubInstance(*subHandle);
    delete subscriberObj;
    subscriber *subObj = static_cast<subscriber *>(*subHandle);
    delete subObj;
    *subHandle = NULL;
    return CEZMQ_OK;
}
