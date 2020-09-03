#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include"passenger_list.h"

/*
 Author: Ahmed Abdulkader & Chippen Vlahija
 */
int comparePassengers(struct passenger *passenger1, struct passenger *passenger2, int sortOrder);
int comparePassengers(struct passenger *passenger1, struct passenger *passenger2, int sortOrder) {
  if (sortOrder == SORT_TIME) {
    if (passenger1->time == passenger2->time) {
      return 0;
    }
    else if(passenger1->time < passenger2->time) {
      return -1;
    }
    else {
      return 1;
    }
  }
  else if(sortOrder == SORT_DESTINATION_ASCENDING) {
    if (passenger1->destinationLevel == passenger2->destinationLevel) {
      return 0;
    }
    else if(passenger1->destinationLevel < passenger2->destinationLevel) {
      return -1;
    }
    else {
      return 1;
    }
  }
  else if(sortOrder == SORT_DESTINATION_DESCENDING) {
    if (passenger1->destinationLevel == passenger2->destinationLevel) {
      return 0;
    }
    else if(passenger1->destinationLevel < passenger2->destinationLevel) {
      return 1;
    }
    else {
      return -1;
    }
  }
  return 0;
} /* End comparePassengers  */
  void initPassengerList(struct passengerList* list) {
    list->firstElement = NULL;
  }
  void printPass(struct passengerList* list) {
  struct passengerListElement* passengerPointer = list->firstElement;
  while(passengerPointer != NULL) {

    printf("Passenger: %d D: %d\n", passengerPointer->data.sourceLevel, passengerPointer->data.destinationLevel);
    passengerPointer = passengerPointer->nextElement;
  }
}
struct passenger *peekNextPassenger(struct passengerList* list, struct passenger *nextPassenger) {
  if(list->firstElement != NULL) {
    nextPassenger = &(list->firstElement)->data;
    return nextPassenger;
  } else {
    return NULL; 
     }
  }

  unsigned int addPassenger(struct passengerList* list, unsigned int time, int sourceLevel, int destinationLevel, int sortOrder) {

    struct passengerListElement *newElement = (struct passengerListElement*)malloc(sizeof(struct passengerListElement));
    (newElement->data).time = time;
    (newElement->data).sourceLevel = sourceLevel;
    (newElement->data).destinationLevel = destinationLevel;

  int comparePass; 

  struct passengerListElement *currElem = list->firstElement; 
  struct passengerListElement *ptrElem = NULL;
  int addPassenger = 0;

  if(sortOrder == 1) {

    if(list->firstElement == NULL) { 
      list->firstElement = newElement;
      newElement->nextElement = NULL;
      printPass(list);
      return 1;

    } else if(list->firstElement->nextElement == NULL) {  
    
        comparePass = comparePassengers(&(newElement->data), &(list->firstElement->data), SORT_DESTINATION_ASCENDING); 
        printf("Compare value: %d\n", comparePass);
        if(comparePass == 0) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        } else if(comparePass = 1) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        } else if(comparePass = -1) {
          ptrElem = list->firstElement;
          list->firstElement = newElement;
          newElement->nextElement = ptrElem;
          ptrElem->nextElement = NULL;
          printPass(list);
          return 1;
        }

      } else { 

        while(currElem->nextElement != NULL && (comparePassengers(&(newElement->data), &(currElem->nextElement->data), SORT_DESTINATION_ASCENDING)) == 1) { 
          currElem = currElem->nextElement;
        }

        if(currElem->nextElement == NULL) { 
          currElem->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        }

        if(currElem->nextElement != NULL && currElem != list->firstElement) { 
          newElement->nextElement = currElem->nextElement;
          currElem->nextElement = newElement;
          printPass(list);
          return 1;
        }

        if(currElem == list->firstElement) { 
          if(comparePassengers(&(newElement->data), &(currElem->data), SORT_DESTINATION_ASCENDING) == 1) { 
            newElement->nextElement = currElem->nextElement;
            currElem->nextElement = newElement;
            printPass(list);
            return 1;
          } else {
            ptrElem = currElem->nextElement;
            list->firstElement = newElement;
            newElement->nextElement = ptrElem;
            printPass(list);
            return 1;
          }
        }

      }
  } else if(sortOrder == 2) { 

    if(list->firstElement == NULL) { 
      list->firstElement = newElement;
      newElement->nextElement = NULL;
      printPass(list);
      return 1;

    } else if(list->firstElement->nextElement == NULL) { 
        comparePass = comparePassengers(&(newElement->data), &(list->firstElement->data), SORT_DESTINATION_DESCENDING); 
        printf("Compare value: %d\n", comparePass);
        if(comparePass == 0) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        } else if(comparePass = 1) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        } else if(comparePass = -1) {
          ptrElem = list->firstElement;
          list->firstElement = newElement;
          newElement->nextElement = ptrElem;
          ptrElem->nextElement = NULL;
          printPass(list);
          return 1;
        }
     } else { 

        while(currElem->nextElement != NULL && (comparePassengers(&(newElement->data), &(currElem->nextElement->data), SORT_DESTINATION_DESCENDING)) == 1) { 
          currElem = currElem->nextElement;
        }

        if(currElem->nextElement == NULL) { 
          currElem->nextElement = newElement;
          newElement->nextElement = NULL;
          printPass(list);
          return 1;
        }
		// Middle
        if(currElem->nextElement != NULL && currElem != list->firstElement) { 
          newElement->nextElement = currElem->nextElement;
          currElem->nextElement = newElement;
          printPass(list);
          return 1;
        }
		// Beginning 
        if(currElem == list->firstElement) { 
          if(comparePassengers(&(newElement->data), &(currElem->data), SORT_DESTINATION_DESCENDING) == 1) { 
            newElement->nextElement = currElem->nextElement;
            currElem->nextElement = newElement;
            printPass(list);
            return 1;
          } else {
            ptrElem = currElem->nextElement;
            list->firstElement = newElement;
            newElement->nextElement = ptrElem;
            printPass(list);
            return 1;
          }
        }

      }
  } else if(sortOrder == SORT_TIME) {
    if(list->firstElement == NULL) {
      list->firstElement = newElement;
      newElement->nextElement = NULL;
      addPassenger = 1;

    } else { 
      if(list->firstElement->nextElement == NULL) { 

        comparePass = comparePassengers(&(newElement->data), &(list->firstElement->nextElement->data), SORT_TIME);  

        if(comparePass == 0) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          addPassenger = 1;
        } else if(comparePass = 1) {
          list->firstElement->nextElement = newElement;
          newElement->nextElement = NULL;
          addPassenger = 1;
        } else if(comparePass = -1) {
          list->firstElement = currElem;
          list->firstElement = newElement;
          newElement->nextElement = currElem;
          currElem->nextElement = NULL;
          addPassenger = 1;
        }

      } else { 
        while(currElem->nextElement != NULL && (comparePassengers(&(newElement->data), &(currElem->nextElement->data), SORT_TIME)) == 1) {
          currElem = currElem->nextElement;
        }
        if(currElem == list->firstElement) {
          if(comparePassengers(&(newElement->data), &(currElem->nextElement->data), SORT_TIME) == 1) { 
            ptrElem = list->firstElement;
            list->firstElement = newElement;
            newElement->nextElement = ptrElem;
            addPassenger = 1;
          } else {
            ptrElem = currElem->nextElement;
            list->firstElement = newElement;
            newElement->nextElement = ptrElem;
            addPassenger = 1;
          }
        }
        if(currElem->nextElement == NULL) {
          if(comparePassengers(&(newElement->data), &(currElem->nextElement->data), SORT_TIME) == 1) { 
            currElem->nextElement = newElement;
            newElement->nextElement = NULL;
            addPassenger = 1;
          } else {
            ptrElem = currElem->nextElement;
            currElem->nextElement = newElement;
            newElement->nextElement = ptrElem;
            addPassenger = 1;
          }
        }
        if(currElem->nextElement != NULL) { 
          newElement->nextElement = currElem->nextElement;
          currElem->nextElement = newElement;
          addPassenger = 1;
        }

      }
    }
  }
  if(newElement != NULL) {
    return addPassenger;
  } else {
    return INT_MIN;
  } 
}
struct passenger *getNextPassenger(struct passengerList* list, struct passenger *nextPassenger) {
  if(list->firstElement != NULL) {
    struct passengerListElement* ptrElem = list->firstElement;

   nextPassenger->time = (ptrElem->data).time;
   nextPassenger->destinationLevel = (ptrElem->data).destinationLevel;
   nextPassenger->sourceLevel = (ptrElem->data).sourceLevel;
   list->firstElement = list->firstElement->nextElement;
  
    free(ptrElem);
  return nextPassenger; 
  } else  {
    return NULL;
  } 
}