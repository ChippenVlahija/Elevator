#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"

/*
	Author: Ahmed Abdulkader & Chippen Vlahija
	Laboration 3 
*/


void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLength, int sizeofElements) {
  bufferPtr->data = data;
  bufferPtr->head = 0;
  bufferPtr->tail = 0;
  bufferPtr->maxLength = maxLength;
  bufferPtr->sizeofElements = 0;
}


/* 
 * This function should check if the buffer pointed to by bufferPtr
 * contains one or more elements with the value specified by the 
 * 'value' argument.
 *
 * The function should return:
 *  - 'value' if the an element with the argument value was found in the queue.
 *  - INT_MIN (defined in limits.h) if value was not found.
 */ 
int containsCircularBuffer(struct circularBuffer* bufferPtr, int value){
	for(int i=0; i<= bufferPtr->maxLength; i++){
	if(bufferPtr->data[i] == value){
		
			return value;
		}
	}
	return INT_MIN;	
}
/*
 * This function should add the value specified by the 'value' 
 * argument at the tail of the buffer.
 *
 * The function should return:
 *  - 'value' if the value was successfully added to the queue.
 *  - INT_MIN (defined in limits.h) if the value was not added.
 */
 
int addElementCircularBuffer(struct circularBuffer* bufferPtr, int value){	
	int next = ((bufferPtr-> tail +1) % bufferPtr->maxLength);
	if(bufferPtr->sizeofElements < bufferPtr->maxLength){
		bufferPtr->sizeofElements++;
		bufferPtr->data[bufferPtr->tail] = value;
		bufferPtr->tail = next;
		return value;
	}
	return INT_MIN;
}


/* 
 * This function should remove all elements in the buffer whose
 * value matches the 'value' argument.
 * 
 * The function should return:
 *  The argument value: if at least one element was removed from queue.
 *  INT_MIN (defined in limits.h) if no element was removed. 
 */

 int removeValueCircularBuffer(struct circularBuffer* bufferPtr, int value){
	int next = ((bufferPtr-> tail+1) % bufferPtr->maxLength);
	
	while(containsCircularBuffer(bufferPtr,value == value)){
		for(int i=0; i<=bufferPtr->maxLength; i++){
			if(bufferPtr->data[i] == value){
				bufferPtr->data[i] = INT_MIN;
				bufferPtr->sizeofElements--;
				if(next == -1){
					next = 3;
					bufferPtr->tail = next;
				} else{
					bufferPtr->tail = next;
				}
			}
		}
		for(int o=0; o<=bufferPtr->sizeofElements; o++){
			if(bufferPtr->data[o] == INT_MIN){
				while(o <= bufferPtr->sizeofElements){
					bufferPtr->data[o] = bufferPtr->data[o+1];
					o++;
				}
			}
		}
		return value;
	}
	return INT_MIN;
}
int removeHeadCircularBuffer(struct circularBuffer* bufferPtr){
	int value = bufferPtr->data[bufferPtr->head];
	bufferPtr->sizeofElements--;
	int next = ((bufferPtr-> head+1) % bufferPtr->maxLength);
	bufferPtr->data[bufferPtr->head] = 0;
	bufferPtr->head = next;
	return value;
}

int getElementCircularBuffer(struct circularBuffer* bufferPtr) {
	if (bufferPtr->maxLength == 0)
	{
		return INT_MIN;
	}
	return bufferPtr->data[bufferPtr->head];
}

