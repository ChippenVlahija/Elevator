#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include"event_list.h"
/*
 Author: Ahmed Abdulkader & Chippen Vlahija
 */


void initEventList(struct eventList* list) {
 
	list->firstElement = NULL;
}

unsigned int addEvent(struct eventList* list, int type, unsigned int time, int source, int destination) {
  
  struct eventListElement* newEventListElement = (struct eventListElement*) malloc(sizeof(struct eventListElement));
  (newEventListElement->data).time = time;
  (newEventListElement->data).type = type;
  (newEventListElement->data).source = source;
  (newEventListElement->data).destination = destination;
 

  int comparePass = 0; 

  struct eventListElement *currElem = list->firstElement; 
  
  struct eventListElement *tempElem = NULL;

  unsigned int addedEvent = 0;

    if(list->firstElement == NULL) { 
      
      list->firstElement = newEventListElement;
      newEventListElement->nextElement = NULL;
      printEvents(list);
      return 1;
    } else if(list->firstElement->nextElement == NULL) { 
     
        comparePass = compareEvents(&(newEventListElement->data), &(list->firstElement->data), SORT_TIME); 

        if(comparePass == 0) {
        	tempElem = list->firstElement;
          list->firstElement = newEventListElement;
          newEventListElement->nextElement = tempElem;
          tempElem->nextElement = NULL;
          printEvents(list);
        	return 1;
        } else if(comparePass == 1) {
         
          list->firstElement->nextElement = newEventListElement;
          newEventListElement->nextElement = NULL;
          printEvents(list);
          return 1;
        } else if(comparePass == -1) {
        	tempElem = list->firstElement;
        	list->firstElement = newEventListElement;
        	newEventListElement->nextElement = tempElem;
        	tempElem->nextElement = NULL;
          printEvents(list);
        	return 1;
        }

      } else { 

        while(currElem->nextElement != NULL && (compareEvents(&(newEventListElement->data), &(currElem->nextElement->data), SORT_TIME)) == 1) { // Continue the loop while the new event is larger than the current element pointed too.
        	currElem = currElem->nextElement;
        }
        if(currElem->nextElement == NULL) { 
          currElem->nextElement = newEventListElement;
          newEventListElement->nextElement = NULL;
          printEvents(list);
          return 1;
        }

        if(currElem->nextElement != NULL && currElem != list->firstElement) { 
          newEventListElement->nextElement = currElem->nextElement;
          currElem->nextElement = newEventListElement;
          printEvents(list);
          return 1;
        }

        if(currElem == list->firstElement) {
          comparePass = compareEvents(&(newEventListElement->data), &(currElem->data), SORT_TIME);
          if(comparePass == 1) {
            newEventListElement->nextElement = currElem->nextElement;
            currElem->nextElement = newEventListElement;
            printEvents(list);
            return 1;
          } else {
            tempElem = list->firstElement;
            list->firstElement = newEventListElement;
            newEventListElement->nextElement = tempElem;
            printEvents(list);
            return 1;
          }
          
        }
      }
    

    if(newEventListElement != NULL) {
     printEvents(list);
     return 1;
   } else {
     printEvents(list);
     return 0;
   }
 }

 struct event *getNextEvent(struct eventList* list, struct event *nextEvent){
	if(list->firstElement != NULL) { 
		
    struct eventListElement* tempElem = list->firstElement;
    nextEvent->type = (tempElem->data).type;
    nextEvent->time = (tempElem->data).time;
    nextEvent->source = (tempElem->data).source;
    nextEvent->destination = (tempElem->data).destination;


    list->firstElement = list->firstElement->nextElement;
    free(tempElem);
        
    return nextEvent;



  } else {
    printf("No events.");
    	return NULL; // No events exist.
    }
  }

  void printEvents(struct eventList* _eventList) {
  struct eventListElement* pointer = _eventList->firstElement;
  int count = 0;
  while(pointer != NULL) {
    count++;
    
    printf("Event: %d Time: %d\n", pointer->data.type, pointer->data.time);
    pointer = pointer->nextElement;
  }
}


  struct event* peekNextEvent(struct eventList* list, struct event *nextEvent) {
    if(list->firstElement != NULL) {
      nextEvent = &(list->firstElement)->data;
      return nextEvent;
    } else {
      return NULL;
    }
  }

  int compareEvents(struct event *event1, struct event *event2, int sortOrder) {
   if (sortOrder == SORT_TIME) {

    if (event1->time == event2->time) {

     return 0;
   }
   else if(event1->time < event2->time) {
     return -1;
   }
   else {

     return 1;
   }
 }


 else if(sortOrder == SORT_DESTINATION_ASCENDING) {
  if (event1->destination == event2->destination) {
   return 0;
 }
 else if(event1->destination < event2->destination) {
   return -1;
 }
 else {
   return 1;
 }
}
else if(sortOrder == SORT_DESTINATION_DESCENDING) {
  if (event1->destination == event2->destination) {
   return 0;
 }
 else if(event1->destination < event2->destination) {
   return 1;
 }
 else {
   return -1;
 }
}return 0;
}
