/************************************************************************************************
PES Assignment 6
File Name: cbfifo.c
Author: Tanmay Mahendra Kothale - tanmay.kothale@colorado.edu - GitHub: tanmay-mk
*************************************************************************************************/

/*	LIBRARY FILES	*/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.h>

/*	OTHER FILES TO BE INCLUDED	*/
#include "cbfifo.h"

/*	MACROS	*/
#define BUFFER_SIZE 256				//max size of the circular buffer

/*	STRUCTURE TO IMPLEMENT MULTIPLE INSTANCES OF CBFIFO	*/
typedef struct {
	uint32_t bufferLength;
	uint32_t readLocation;
	uint32_t writeLocation;
	uint8_t circularBuffer[BUFFER_SIZE];
}cbfifo;

/*	GLOBAL VARIABLES	*/
cbfifo fifo[2];		//array of structure to implement multiple instances of cbfifo
uint32_t i;			//loop variable

size_t cbfifo_capacity(int buf_type)
{
    return BUFFER_SIZE;
}

size_t cbfifo_length(int buf_type)
{
    return fifo[buf_type].bufferLength;
}

size_t cbfifo_enqueue(int buf_type, void *buf, size_t nbyte)
{
	uint32_t masking_state;
    size_t TOTAL_BYTES_ENQUEUED=0;              //a variable to check the number of bytes enqueued in one enqueue cycle
    if (fifo[buf_type].bufferLength == BUFFER_SIZE)
    {
        return 0;                               //returns 0 if buffer is full, since there are no more spaces left to fill
    }

    else if (buf == NULL)
    {
        return -1;                              //if no data is encountered, the function returns -1
    }

    else if (nbyte >= BUFFER_SIZE-fifo[buf_type].bufferLength)
    {
        nbyte = BUFFER_SIZE-fifo[buf_type].bufferLength;       //checking for available spaces in the circular buffer.
    }                                           //if nbytes is higher than available spaces, remaining elements
                                                //will be discarded
    else {}

    masking_state = __get_PRIMASK();
    __disable_irq();
    for (i=0; i<nbyte; i++)
    {
    	fifo[buf_type].circularBuffer[fifo[buf_type].writeLocation] = *(char*) buf;        //writing element in the buffer
        buf++;
        fifo[buf_type].bufferLength++;                                     //increasing buffer length
        fifo[buf_type].writeLocation++;                                    //increasing write location
        TOTAL_BYTES_ENQUEUED++;                             //updating total bytes enqueued

        if (fifo[buf_type].writeLocation >= BUFFER_SIZE)                   //checking if the write pointer has reached to the
        {                                                   //end of the buffer, if so, it starts pointing to 0 again
        	fifo[buf_type].writeLocation = 0;
        }
    }
    __set_PRIMASK(masking_state);
    return TOTAL_BYTES_ENQUEUED;                            //returning the total number of bytes enqueued in this cycle
}

size_t cbfifo_dequeue(int buf_type, void *buf, size_t nbyte)
{
	uint32_t masking_state;
    size_t TOTAL_BYTES_DEQUEUED=0;                           //a variable to check the number of bytes dequeued in one queue cycle

    if (buf == NULL)                                         //if no data is encountered, the function returns -1
    {
        return -1;
    }

    else if (fifo[buf_type].bufferLength == 0)                                //if buffer is empty, the function will return 0
    {
        return 0;
    }

    else if (nbyte > fifo[buf_type].bufferLength)                              //checking whether the number of bytes to be removed are
    {                                                           //higher than the available bytes, if so, only the bytes
        nbyte = fifo[buf_type].bufferLength;                                   //that are currently in the fifo will be removed.
    }

    else{}

    masking_state = __get_PRIMASK();
    __disable_irq();
    for (i=0; i<nbyte; i++)
    {
        *(char *) buf = fifo[buf_type].circularBuffer[fifo[buf_type].readLocation];             //removing the element from the buffer
        buf++;
        fifo[buf_type].bufferLength--;                                            //updating buffer length
        fifo[buf_type].readLocation++;                                             //updating read location
        TOTAL_BYTES_DEQUEUED++;                                     //updating total bytes dequeued

        if (fifo[buf_type].readLocation == BUFFER_SIZE)                        //if read location reaches the end of the buffer
        {                                                       //it will wrap around and will start pointing at 0 again
        	fifo[buf_type].readLocation = 0;
        }
    }
    __set_PRIMASK(masking_state);
    return TOTAL_BYTES_DEQUEUED;
}

void cbfifo_dump_state(int buf_type)
{
    printf("circular buffer: %s\n\n", fifo[buf_type].circularBuffer);
    printf("%Read Location: %d\nWrite Location: %d\n\n", fifo[buf_type].readLocation, fifo[buf_type].writeLocation);
}

void cbfifo_reset(int buf_type)
{
	fifo[buf_type].bufferLength = 0;
	fifo[buf_type].readLocation = 0;
	fifo[buf_type].writeLocation = 0;

	for (int i = 0; i<BUFFER_SIZE; i++)
	{
		fifo[buf_type].circularBuffer[i] = (char)0;
	}

}
