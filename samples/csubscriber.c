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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include<stdint.h>

#include "cezmqapi.h"
#include "cezmqsubscriber.h"
#include "cezmqevent.h"
#include "cezmqbytedata.h"
#include "cezmqreading.h"
#include "cezmqerrorcodes.h"

int g_isStarted = 0;
pthread_cond_t g_cv;
pthread_mutex_t g_mutex;
pthread_condattr_t g_cattr;

/* The commented lines is written for reference purpose.
 *  Uncomment the lines in case you want to see all the fields of
 *  received event and readings.
 */
void printEvent(ezmqMsgHandle_t event)
{
    /* long value;
    ezmqEventGetID(event, &value2);
    printf("\nid: %s",value2);
    ezmqEventGetCreated(event, &value);
    printf("\ncreated: %ld", value);
    ezmqEventGetModified(event, &value);
    printf("\nmodified: %ld", value);
    ezmqEventGetOrigin(event, &value);
    printf("\norigin: %ld", value);
    ezmqEventGetPushed(event, &value);
    printf("\npushed: %ld", value);*/

    char *value2;
    ezmqEventGetDevice(event, &value2);
    printf("\nDevice : %s", value2);
    int count;
    ezmqEventGetReadingCount(event, &count);
    printf("\nReadigs:");
    for (int i =0 ; i <count; i++)
    {
        ezmqReadingHandle_t readingData;
        ezmqEventGetReading(event, i, &readingData);

        /*ezmqReadingGetID(readingData, &value2);
        printf("\nid: %s", value2);
        ezmqReadingGetCreated(readingData, &value);
        printf("\ncreated: %ld", value);
        ezmqReadingGetModified(readingData, &value);
        printf("\nmodified: %ld", value);
        ezmqReadingGetOrigin(readingData, &value);
        printf("\norigin: %ld", value);
        ezmqReadingGetPushed(readingData, &value);
        printf("\npushed: %ld", value);
        ezmqReadingGetDevice(readingData, &value2);
        printf("\ndevice: %s\n", value2);*/
        fflush(stdout);
        ezmqReadingGetName(readingData, &value2);
        printf("\nKey: %s", value2);
        ezmqReadingGetValue(readingData, &value2);
        printf("\nValue: %s", value2);
        fflush(stdout);
    }
}

void printByteData(ezmqMsgHandle_t byteData)
{
    printf("\n--------------------------------------\n");
    size_t size;
    ezmqGetDataLength(byteData, &size);
    printf("Byte data length: %zd\n", size);
    uint8_t *mData;
    ezmqGetByteData(byteData, &mData);
    size_t i=0;
    while (i<size)
    {
        printf("%04x ", mData[i]);
        i++;
    }
    printf("\n----------------------------------------\n");
}

void subCB(ezmqMsgHandle_t event, CEZMQContentType contentType)
{
    printf("\n------ [App] SUB callback  -----\n");
    if(CEZMQ_CONTENT_TYPE_PROTOBUF == contentType)
    {
        printf("Content-Type: CEZMQ_CONTENT_TYPE_PROTOBUF");
        printEvent(event);
    }
    else if(CEZMQ_CONTENT_TYPE_BYTEDATA == contentType)
    {
        printf("Content-Type: CEZMQ_CONTENT_TYPE_BYTEDATA");
        printByteData(event);
    }
}

void subTopicCB(const char * topic, ezmqMsgHandle_t event, CEZMQContentType contentType)
{
    printf("\n----- [App] SUB topic callback -----\n");
    printf("\nTopic: %s\n", topic);
    if(CEZMQ_CONTENT_TYPE_PROTOBUF == contentType)
    {
        printf("Content-Type: CEZMQ_CONTENT_TYPE_PROTOBUF");
        printEvent(event);
    }
    else if(CEZMQ_CONTENT_TYPE_BYTEDATA == contentType)
    {
        printf("Content-Type: CEZMQ_CONTENT_TYPE_BYTEDATA");
        printByteData(event);
    }
}

void printError()
{
    printf("\nRe-run the application as shown in below examples: \n");
    printf("\n  (1) For subscribing without topic: \n");
    printf("      ./csubscriber -ip 107.108.81.116 -port 5562 \n");
    printf("      ./csubscriber -ip localhost -port 5562 \n");
    printf("\n  (2) For subscribing with topic:  \n");
    printf("      ./csubscriber -ip 107.108.81.116 -port 5562 -t topic1 \n");
    printf("      ./csubscriber -ip localhost -port 5562 -t topic1 \n");
}

void sigint(int signal)
{
    printf("\nInterupt signal:  %d\n", signal);
    if (g_isStarted)
    {
        //signal all condition variables
        pthread_mutex_lock(&g_mutex);
        pthread_cond_broadcast(&g_cv);
        pthread_mutex_unlock(&g_mutex);
    }
    else
    {
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    char *ip = NULL;
    int port = 5562;
    char *topic= NULL;
    CEZMQErrorCode result;
    g_isStarted = 0;

    // initialize a condition variable to its default value
    pthread_cond_init(&g_cv, NULL);
    //initialize a condition variable
    pthread_cond_init(&g_cv, &g_cattr);

    // get ip, port and topic from command line arguments
    if(argc != 5 && argc != 7)
    {
        printError();
        return -1;
    }
    int n = 1;
    while (n < argc)
    {
        if (0 == strcmp(argv[n],"-ip"))
        {
            ip = argv[n + 1];
            printf("\nGiven Ip is : %s", ip);
            n = n + 2;
        }
        else if (0 == strcmp(argv[n],"-port"))
        {
            port = atoi(argv[n + 1]);
            printf("\nGiven Port: %d", port);
            n = n + 2;
        }
        else if (0 == strcmp(argv[n],"-t"))
        {
            topic = argv[n + 1];
            printf("\nGiven Topic is : %s", topic);
            n = n + 2;
        }
        else
        {
            printError();
        }
    }

    //this handler is added to check stop API
    signal(SIGINT, sigint);

    //initialize ezmq service
    result = ezmqInitialize();
    printf("\nInitialize API [result]: %d", result);
    if(result != CEZMQ_OK)
    {
        return -1;
    }

    //Create EZMQ Subscriber
    ezmqSubHandle_t subscriber;
    result = ezmqCreateSubscriber(ip, port, subCB, subTopicCB, &subscriber);
     if(result != CEZMQ_OK)
    {
        printf("\nSubscriber creation failed [result] : %d\n", result);
        return -1;
    }

    //Start EZMQ Subscriber
    result= emzqStartSubscriber(subscriber);
    printf("\nSubscriber start [result]: %d", result);
    if(result != CEZMQ_OK)
    {
        return -1;
    }
    g_isStarted = 1;

    //subscribe for events
    if (NULL == topic)
    {
        result =  ezmqSubscribe(subscriber);
    }
    else
    {
        result = ezmqSubscribeForTopic(subscriber, topic);
    }

    if(result != CEZMQ_OK)
    {
        printf("\nsubscribe API: error occured\n");
        return -1;
    }

    printf("\nSuscribed to publisher.. -- Waiting for Events --\n");

    // conditional wait to prevent main loop from exit
    pthread_mutex_lock(&g_mutex);
    pthread_cond_wait(&g_cv, &g_mutex);

    //destroy subscriber
    result =  ezmqDestroySubscriber(&subscriber);
    printf("\nDestroy Subscriber [result]: %d\n", result);

    return 0;
}

