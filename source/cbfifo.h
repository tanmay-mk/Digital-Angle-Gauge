/************************************************************************************************
PES Assignment 6
File Name: cbfifo.h
Author: Tanmay Mahendra Kothale - tanmay.kothale@colorado.edu - GitHub: tanmay-mk
		& Howdy Pierce - howdy.pierce@colorado.edu
*************************************************************************************************/
#ifndef _CBFIFO_H_
#define _CBFIFO_H_

/*	LIBRARY FILES	*/
#include <stdlib.h>  // for size_t
#include <string.h>
#include <stdint.h>

/*	ENUMERATION TO SET ARRAY INDEX OF CBFIFO	*/
enum {
	TRANSMIT	= 0,
	RECEIVE		= 1
};

/*	FUNCTION PROTOTYPES	*/

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf     	Pointer to the data
 *   nbyte   	Max number of bytes to enqueue
 *   buf_type	Type of buffer (transmit or receive)
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 */
size_t cbfifo_enqueue(int buf_type, void *buf, size_t nbyte);

//define an enum - no initialization function - modify to take one more argument - statically allocate 2 of the arrays
/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      	Destination for the dequeued data
 *   nbyte    	Bytes of data requested
 *   buf_type	Type of buffer (transmit or receive)
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 */
size_t cbfifo_dequeue(int buf_type, void *buf, size_t nbyte);


/*
 * Returns the number of bytes currently on the FIFO.
 *
 * Parameters:
 *    buf_type	Type of buffer (transmit or receive)
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */
size_t cbfifo_length(int buf_type);


/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   buf_type	Type of buffer (transmit or receive)
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */
size_t cbfifo_capacity(int buf_type);

/*
* Dump function: Prints the entire circular buffer as a string
*
* Parameters:
* 	buf_type	Type of buffer (transmit or receive)
*
* Returns: none
*/
void cbfifo_dump_state(int buf_type);

/*
* Reset function: Resets the entire circular buffer values
*
* Parameters:
* 	buf_type	Type of buffer (transmit or receive)
*
* Returns: none
*/
void cbfifo_reset(int buf_type);

#endif /* _CBFIFO_H_ */
