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
#include<stdint.h>
#include <signal.h>

#include "cezmqapi.h"
#include "cezmqpublisher.h"
#include "cezmqevent.h"
#include "cezmqbytedata.h"
#include "cezmqreading.h"
#include "cezmqerrorcodes.h"

ezmqPubHandle_t gPublisher;
ezmqEventHandle_t gEventHandle;
int gIsStarted = 0;

void startCB(CEZMQErrorCode code)
{
    printf("\nstartCB: %d\n", code);
}

void stopCB(CEZMQErrorCode code)
{
    printf("\nstopCB: %d\n", code);
}

void errorCB(CEZMQErrorCode code)
{
    printf("\nerrorCB: %d\n", code);
}

ezmqEventHandle_t createEvent()
{
    const char *id = "id";
    const char *device = "device";
    const char *readingId1 = "id1";
    const char *readingName1 = "reading1";
    const char *readingValue1 = "25";
    const char *readingDevice1 = "device";
    const char *readingId2 = "id2";
    const char *readingName2 = "reading2";
    const char *readingValue2 = "20";
    const char *readingDevice2 = "device";

    ezmqEventHandle_t eventHandle; //creation and set event fields
    CEZMQErrorCode  result = ezmqCreateEvent(&eventHandle);
    if(result != CEZMQ_OK)
    {
        printf("\nEvent initialization [Result]: %d\n", result);
        return NULL;
    }
    ezmqEventSetID(eventHandle, id);
    ezmqEventSetCreated(eventHandle, 10);
    ezmqEventSetModified(eventHandle, 20);
    ezmqEventSetOrigin(eventHandle, 20);
    ezmqEventSetPushed(eventHandle, 10);
    ezmqEventSetDevice(eventHandle, device);

     ezmqReadingHandle_t reading1Handle; //creation and set first reading fields
    ezmqCreateReading(eventHandle, &reading1Handle);
    ezmqReadingSetID(reading1Handle, readingId1 );
    ezmqReadingSetCreated(reading1Handle, 25);
    ezmqReadingSetModified(reading1Handle, 20);
    ezmqReadingSetOrigin(reading1Handle, 25);
    ezmqReadingSetPushed(reading1Handle, 1);
    ezmqReadingSetName(reading1Handle, readingName1);
    ezmqReadingSetValue(reading1Handle, readingValue1);
    ezmqReadingSetDevice(reading1Handle, readingDevice1);

    ezmqReadingHandle_t reading2Handle; //creation and set second reading fields
    ezmqCreateReading(eventHandle, &reading2Handle);
    ezmqReadingSetID(reading2Handle, readingId2);
    ezmqReadingSetCreated(reading2Handle, 30);
    ezmqReadingSetModified(reading2Handle, 20);
    ezmqReadingSetOrigin(reading2Handle, 25);
    ezmqReadingSetPushed(reading2Handle, 1);
    ezmqReadingSetName(reading2Handle, readingName2);
    ezmqReadingSetValue(reading2Handle, readingValue2);
    ezmqReadingSetDevice(reading2Handle, readingDevice2);

    return eventHandle;
}

void printError()
{
    printf("\nRe-run the application as shown in below examples: \n");
    printf("\n  (1) For publishing without topic: \n");
    printf("      ./cpublisher -port 5562\n");
    printf("\n  (2) For publishing with topic:\n");
    printf("      ./cpublisher -port 5562 -t topic1\n");
}

void sigint(int signal)
{
    printf("\nInterupt signal:  %d\n", signal);
    if(0 == gIsStarted)
    {
        exit(0);
    }

    // stop publisher
    CEZMQErrorCode result = ezmqStopPublisher(gPublisher);
    if(result != CEZMQ_OK)
    {
        printf("\npublish API: error occured\n");
    }
    printf("\nstop API  [result]:  %d", result);

    //Destroy publisher
    result =  ezmqDestroyPublisher(&gPublisher);
    if(result != CEZMQ_OK)
    {
        printf("\nDestroy publisher: error occured\n");
    }
    printf("\nDestroy publisher [result]:  %d", result);

    //Destroy event
    result =  ezmqDestroyEvent(&gEventHandle);
    if(result != CEZMQ_OK)
    {
        printf("\nDestroy event: error occured\n");
    }
    gIsStarted = 0;
}

int main(int argc, char* argv[])
{
    int port = 5562;
    CEZMQErrorCode result;
    char *topic= NULL;

    // get ip, port and topic from command line arguments
    if(argc != 3 && argc != 5)
    {
        printError();
        return -1;
    }
    int n = 1;
    while (n < argc)
    {
        if (0 == strcmp(argv[n],"-port"))
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
    gIsStarted = 0;

    //initialize ezmq service
    result = ezmqInitialize();
    printf("\nInitialize API [result]: %d", result);
    if(result != CEZMQ_OK)
    {
        return -1;
    }

    //Create EZMQ Publisher
    result = ezmqCreatePublisher(port, startCB, stopCB, errorCB, &gPublisher);
    printf("\nCreate Publisher [result]: %d", result);
    if(result != CEZMQ_OK)
    {
        return -1;
    }

    //Start EZMQ Publisher
    result= ezmqStartPublisher(gPublisher);
    printf("\nPublisher start [result]: %d", result);
    if(result != CEZMQ_OK)
    {
        return -1;
    }

    //form an event to publish
    gEventHandle = createEvent();

    // This delay is added to prevent ZeroMQ first packet drop during
    // initial connection of publisher and subscriber.
    sleep(1);

    //Publish events
    printf("\n--------- Will Publish 15 events at interval of 2 seconds --------- \n");
    gIsStarted = 1;
    int i = 1;
    while(i <= 15)
    {
        if(0 == gIsStarted)
        {
            printf("\npublish Stopped\n");
            return -1;
        }
        if (NULL == topic)
        {
            result = ezmqPublish(gPublisher, gEventHandle);
        }
        else
        {
            result = ezmqPublishOnTopic(gPublisher, topic, gEventHandle);
        }

        if(result != CEZMQ_OK)
        {
            printf("\npublish API: error occured\n");
            return -1;
        }
        printf("\nEvent %d Published", i );
        sleep(2);
        i++;
    }

    // stop publisher
    result = ezmqStopPublisher(gPublisher);
    if(result != CEZMQ_OK)
    {
        printf("\npublish API: error occured\n");
        return -1;
    }
    printf("\nstop API  [result]:  %d", result);

    //Destroy publisher
    result =  ezmqDestroyPublisher(&gPublisher);
    if(result != CEZMQ_OK)
    {
        printf("\nDestroy publisher: error occured\n");
        return -1;
    }
    printf("\nDestroy publisher [result]:  %d", result);

    //Destroy event
    result =  ezmqDestroyEvent(&gEventHandle);
    if(result != CEZMQ_OK)
    {
        printf("\nDestroy event: error occured\n");
        return -1;
    }
    printf("\nDestroy event [result]:  %d\n", result);
    return 0;
}

