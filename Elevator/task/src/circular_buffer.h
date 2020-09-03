#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

/*
	Author: Ahmed Abdulkader & Chippen Vlahija
	Laboration 3 
*/

/* 
 * Data structure used to hold a circular buffer.
 */
struct circularBuffer{
  int * data;
  int head;
  int tail;
  int maxLength;
  int sizeofElements;
  };


/*
 * Initialize an empty buffer.
 */
void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLen, int sizeofElements);


/* 
 * This function should check if the buffer pointed to by bufferPtr
 * contains one or more elements with the value specified by the 
 * 'value' argument.
 *
 * The function should return:
 *  - 'value' if the an element with the argument value was found in the queue.
 *  - INT_MIN (defined in limits.h) if value was not found.
 */ 
int containsCircularBuffer(struct circularBuffer* bufferPtr, int value);

/*
 * This function should add the value specified by the 'value' 
 * argument at the tail of the buffer.
 *
 * The function should return:
 *  - 'value' if the value was successfully added to the queue.
 *  - INT_MIN (defined in limits.h) if the value was not added.
 */
int addElementCircularBuffer(struct circularBuffer* bufferPtr, int value);



/* 
 * This function should remove all elements in the buffer whose
 * value matches the 'value' argument.
 * 
 * The function should return:
 *  The argument value: if at least one element was removed from queue.
 *  INT_MIN (defined in limits.h) if no element was removed. 
 */
int removeValueCircularBuffer(struct circularBuffer* bufferPtr, int value);


/* 
 * Remove the oldest element, which is at the head of the queue. 
 * 
 * The function should return:
 *   - 'value' if the head element was successfully removed
 *   - INT_MIN (defined in limits.h) if no element was removed (i.e., the
 *     queue was empty when the function was called.       
 */
int removeHeadCircularBuffer(struct circularBuffer* bufferPtr);

int getElementCircularBuffer(struct circularBuffer* bufferPtr);


#endif

