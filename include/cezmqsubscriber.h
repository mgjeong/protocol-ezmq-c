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

/**
 * @file   cezmqsubscriber.h
 *
 * @brief This file provides APIs for subscriber: start, subscribe, stop.
 */

#ifndef __EZMQ_SUB_H_INCLUDED__
#define __EZMQ_SUB_H_INCLUDED__

#include "cezmqerrorcodes.h"
#include "cezmqevent.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Subscriber handle
 */
typedef void * ezmqSubHandle_t;

/**
 * Callbacks to get all the subscribed events.
 */
typedef void (*csubCB)(const ezmqMsgHandle_t event, CEZMQContentType contentType);

/**
 * Callbacks to get all the subscribed events for a specific topic.
 */
typedef void (*csubTopicCB)(const char * topic, const ezmqMsgHandle_t event, CEZMQContentType contentType);

/**
 *  Create ezmq Subscriber with given ip, port and callbacks.
 *
 * @param ip - IP to be used for Subscriber socket.
 * @param port - Port to be used for Subscriber socket.
 * @param subcb - Callback to recieve events from socket.
 * @param topiccb - Callback to recieve events from socket on a particular topic.
 * @param subHandle  -Handle will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqCreateSubscriber(const char *ip, int port, csubCB subcb,
        csubTopicCB topiccb, ezmqSubHandle_t *subHandle);

/**
 * Set the security keys of client/its own.
 *
 * @param subHandle - Subscriber handle
 * @param clientPrivateKey - Client private/secret key.
 * @param clientPublicKey - Client public key.
 *
 * @return EZMQErrorCode - EZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) Key should be 40-character string encoded in the Z85 encoding format <br>
 * (2) This API should be called before start() API. <br>
 * (3) This API should be called, if and only if ezmq is built in secured mode otherwise it will return CEZMQ_ERROR.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqSetClientKeys(ezmqSubHandle_t subHandle,
        const char *clientPrivateKey, const char *clientPublicKey);

/**
 * Set the server public key.
 *
 * @param subHandle - Subscriber handle
 * @param key - Server public key.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) Key should be 40-character string encoded in the Z85 encoding format <br>
 * (2) This API should be called before start() API.
 * (3) If using the following API in secured mode: <br>
 *     ezmqSubscribeWithIpPort( ezmqSubHandle_t subHandle, const char *ip, const int port, const char *topic) then,
 *     ezmqSetServerPublicKey API needs to be called before that.<br>
 * (4) This API should be called, if and only if ezmq is built in secured mode otherwise, it will return CEZMQ_ERROR.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqSetServerPublicKey(ezmqSubHandle_t subHandle,
        const char *key);

/**
 * Starts Sub instance.
 *
 * @param subHandle - Subscriber handle.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode  emzqStartSubscriber(ezmqSubHandle_t subHandle);

/**
 * Subscribe for event/messages.
 *
 * @param subHandle - Subscriber handle.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode  ezmqSubscribe(ezmqSubHandle_t subHandle);

/**
 * Subscribe for event/messages on a particular topic.
 *
 * @param subHandle - Subscriber handle.
 * @param topic - Topic to be subscribed.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) Topic name should be as path format. For example: home/livingroom/  <br>
 * (2) Topic name can have letters [a-z, A-z], numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqSubscribeForTopic(ezmqSubHandle_t subHandle, const char *topic);

/**
 * Subscribe for event/messages on given list of topics. On any of the topic
 * in list, if it failed to subscribe events it will return
 * CEZMQ_ERROR/CEZMQ_INVALID_TOPIC.
 *
 * @param subHandle - Subscriber handle.
 * @param topicList - List of topics to be subscribed.
 * @param listSize - Size of topicList.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) Topic name should be as path format. For example: home/livingroom/  <br>
 * (2) Topic name can have letters [a-z, A-z], numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqSubscribeForTopicList(ezmqSubHandle_t subHandle,
        const char ** topicList, int listSize);

/**
 * Subscribe for event/messages from given IP:Port on the given topic.
 *
 * @param subHandle - Subscriber handle.
 * @param ip - Target[Publisher] IP address.
 * @param port - Target[Publisher] Port number.
 * @param topic - Topic to be subscribed.
 *
 * @return EZMQErrorCode - EZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) It will be using same Subscriber socket for connecting to given ip:port. <br>
 * (2) To unsubcribe use un-subscribe API with the same topic. <br>
 * (3) Topic name should be as path format. For example: home/livingroom/ <br>
 * (4) Topic name can have letters [a-z, A-z], numerics [0-9] and special characters _ - . and / <br>
 * (5) Topic will be appended with forward slash [/] in case, if application has not appended it <br>
 * (6) If using in secured mode: Call ezmqSetServerPublicKey(ezmqSubHandle_t subHandle, const char *key)
 *      API with target server public key before calling this API.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqSubscribeWithIpPort( ezmqSubHandle_t subHandle, const char *ip,
        const int port, const char *topic);

/**
 * Un-subscribe all the events from publisher.
 *
 * @param subHandle - Subscriber handle.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqUnSubscribe(ezmqSubHandle_t subHandle);

/**
 * Un-subscribe specific topic events.
 *
 * @param subHandle - Subscriber handle.
 * @param topic - topic to be unsubscribed.
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 * @note
 * (1) Topic name should be as path format. For example: home/livingroom/  <br>
 * (2) Topic name can have letters [a-z, A-z], numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqUnSubscribeForTopic(ezmqSubHandle_t subHandle, const char *topic);

/**
 * Un-subscribe event/messages on given list of topics. On any of the topic
 * in list, if it failed to unsubscribe events it will return
 * CEZMQ_ERROR/CEZMQ_INVALID_TOPIC.
 *
 * @param subHandle - Subscriber handle.
 * @param topicList - List of topics to be subscribed.
 * @param listSize - Size of topicList.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 *  @note
 * (1) Topic name should be as path format. For example: home/livingroom/  <br>
 * (2) Topic name can have letters [a-z, A-z], numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqUnSubscribeForTopicList(ezmqSubHandle_t subHandle, const char ** topicList,
        int listSize);

/**
 * Stops SUB instance.
 *
 * @param subHandle - Subscriber handle
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqStopSubscriber(ezmqSubHandle_t subHandle);

/**
 * Get the IP address.
 * Note: Application should not free ip.
 *
 * @param subHandle - Subscriber handle
 * @param ip - ip will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqGetSubIp(ezmqSubHandle_t subHandle, char **ip);

/**
 * Get the port of the subscriber.
 *
 * @param subHandle - Subscriber handle
 * @param port - Port will be filled as return value.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqGetSubPort(ezmqSubHandle_t subHandle, int *port);

/**
 * Destroy ezmq subscriber. Application needs to call this API to delete/free subscriber.
 *
 * @param subHandle - Subscriber handle
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqDestroySubscriber(ezmqSubHandle_t *subHandle);

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_SUB_H_INCLUDED__

