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
 * @file   cezmqerrorcodes.h
 *
 * @brief   This file contains error codes of CEZMQ service possibly return to application.
 */

#ifndef __EZMQ_ERRORCODES_H_INCLUDED__
#define __EZMQ_ERRORCODES_H_INCLUDED__

#define VERIFY_NON_NULL(PARAM) if (!PARAM){ return CEZMQ_ERROR; }
#define VERIFY_NON_NULL_TOPIC(PARAM) if (!PARAM){ return CEZMQ_INVALID_TOPIC; }
#define ALLOC_ASSERT(PARAM) if (!PARAM){ abort(); }

typedef void * ezmqMsgHandle_t;

/**
* @enum CEZMQErrorCode
* ezmq service error codes.
*/
typedef enum
{
    CEZMQ_OK = 0,
    CEZMQ_ERROR,
    CEZMQ_INVALID_TOPIC,
    CEZMQ_INVALID_CONTENT_TYPE
} CEZMQErrorCode;

/**
* @enum CEZMQStatusCode
* ezmq Service status codes.
*/
typedef enum
{
    CEZMQ_UNKNOWN = 0,
    CEZMQ_CONSTRUCTED,
    CEZMQ_INITIALIZED,
    CEZMQ_TERMINATED
} CEZMQStatusCode;

/**
* @enum CEZMQContentType
* EZMQ message's content types.
*/
typedef enum
{
    CEZMQ_CONTENT_TYPE_PROTOBUF = 0,
    CEZMQ_CONTENT_TYPE_BYTEDATA,
    CEZMQ_CONTENT_TYPE_AML,  //Not in use as of now
    CEZMQ_CONTENT_TYPE_JSON  //Not in use as of now
} CEZMQContentType;

#endif //__EZMQ_ERRORCODES_H_INCLUDED__

