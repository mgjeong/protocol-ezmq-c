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
 * @file   cezmqpublisher.h
 *
 * @brief This file provides APIs for publisher: start, subscribe, stop.
 */

#ifndef __EZMQ_PUB_H_INCLUDED__
#define __EZMQ_PUB_H_INCLUDED__

#include "cezmqerrorcodes.h"
#include "cezmqevent.h"

#define EZMQ_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Publisher handle
 */
typedef void * ezmqPubHandle_t;

/**
 * Callbacks to get error codes for start/stop of EZMQ publisher.
 * Note: As of now not being used.
 */
typedef void (*ezmqStartCB)(CEZMQErrorCode code);
typedef void (*ezmqStopCB)(CEZMQErrorCode code);
typedef void (*ezmqErrorCB)(CEZMQErrorCode code);

/**
 *  Create ezmq Publisher with given port and callbacks.
 *
 * @param port - Port to be used for publisher socket.
 * @param startCb - Start callback.
 * @param stopCb - Stop Callback.
 * @param errorCb - Error Callback.
  * @param pubHandle  - Handle to be filled.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqCreatePublisher(int port, ezmqStartCB startCb,
        ezmqStopCB stopCb, ezmqErrorCB errorCb, ezmqPubHandle_t *pubHandle);

/**
 * Starts PUB instance.
 *
 * @param pubHandle - Publisher handle
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqStartPublisher(ezmqPubHandle_t pubHandle);

/**
 * Publish events on the socket for subscribers.
 *
 * @param pubHandle - Publisher handle
 * @param event - event to be published.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqPublish(ezmqPubHandle_t pubHandle, ezmqEventHandle_t event);

/**
 * Publish events on a specific topic on socket for subscribers.
 *
 * @param pubHandle - Publisher handle
 * @param topic - Topic on which event needs to be published.
 * @param event - event to be published.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 * @note (1) Topic name should be as path format. For example:
 *       home/livingroom/ (2) Topic name can have letters [a-z, A-z],
 *       numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqPublishOnTopic(ezmqPubHandle_t pubHandle, const char *topic,
        ezmqEventHandle_t event);

/**
 * Publish an events on list of topics on socket for subscribers. On any of
 * the topic in list, if it failed to publish event it will return
 * CEZMQ_ERROR/CEZMQ_INVALID_TOPIC.
 *
 * @param pubHandle - Publisher handle
 * @param topicList - List of Topics on which event needs to be published.
 * @param listSize - Size of topicList.
 * @param event - event to be published.
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 *
 *  @note (1) Topic name should be as path format. For example:
 *       home/livingroom/ (2) Topic name can have letters [a-z, A-z],
 *       numerics [0-9] and special characters _ - . and /
 */
EZMQ_EXPORT CEZMQErrorCode ezmqPublishOnTopicList(ezmqPubHandle_t pubHandle, const char ** topicList,
        int listSize, ezmqEventHandle_t event);

/**
 * Stops PUB instance.
 *
 * @param pubHandle - Publisher handle
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqStopPublisher(ezmqPubHandle_t pubHandle);

/**
* Get the port of the publisher.
*
* @param pubHandle - Publisher handle
* @param port - Port will be filled as return value.
*
* @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
*/
EZMQ_EXPORT CEZMQErrorCode ezmqGetPubPort(ezmqPubHandle_t pubHandle, int *port);

/**
 * Destroy ezmq publisher. Application needs to call this API to delete/free publisher.
 *
 * @param pubHandle - Publisher handle
 *
 * @return CEZMQErrorCode - CEZMQ_OK on success, otherwise appropriate error code.
 */
EZMQ_EXPORT CEZMQErrorCode ezmqDestroyPublisher(ezmqPubHandle_t *pubHandle);

#ifdef __cplusplus
}
#endif

#endif //__EZMQ_PUB_H_INCLUDED__

