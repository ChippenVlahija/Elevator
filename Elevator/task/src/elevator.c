#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"elevator.h"
#include"event_list.h"
#include"circular_buffer.h"

/*
 Author: Ahmed Abdulkader & Chippen Vlahija
 */

extern struct passengerList waitingDown[];
extern int waitingDownSize;
extern struct eventList _eventList;

extern unsigned int time;
extern struct passengerList waitingUp[];
extern int waitingUpSize;
extern struct circularBuffer pushedButtonsQueue;


void initElevator(struct elevator *_elevator, int numLevels) {
  _elevator->currentPosition = 0;
  _elevator->destination = 0;
  _elevator->stateFuncPtr = elevatorIdle;
  _elevator->numLevels = numLevels;
  _elevator->numOfpassengers = 0;
  _elevator->capacity = 10;
  initPassengerList(&(_elevator->passengers));
}

/* 
 * Example of state function for idle state. This shows how things work, and 
 * you are expected to modify this function.
 */
void elevatorIdle(struct elevator *_elevator, struct event* currentEvent) {
  if(currentEvent->type == EVENT_BUTTON_PUSH) {

   
    if (_elevator->currentPosition == currentEvent->source) { 
      _elevator->stateFuncPtr = doorsOpen;

    }    
   
    else {
      addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, currentEvent->source);
      _elevator->destination = currentEvent->source;
      _elevator->stateFuncPtr = elevatorMoving;
    }
  }
}
void elevatorMoving(struct elevator *_elevator, struct event* currentEvent) {
  printf("Elevator moving\n");

  if(currentEvent->type == EVENT_BUTTON_PUSH) {
   
    if(_elevator->numOfpassengers > 0) {
      struct passenger* nextPassenger = NULL;
      

      if(peekNextPassenger(&(_elevator->passengers), nextPassenger)->destinationLevel < currentEvent->destination) {
        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, currentEvent->source);
        _elevator->destination = currentEvent->source;
        _elevator->stateFuncPtr = elevatorMoving;
      } else { 
        int desPassenger = peekNextPassenger(&(_elevator->passengers), nextPassenger)->destinationLevel;
        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, desPassenger);
        _elevator->destination = desPassenger;
        _elevator->stateFuncPtr = elevatorMoving;
      }
    } else { 
     
      int destination = getDest(currentEvent);
      if(currentEvent->destination < destination) {
        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, currentEvent->source);
        _elevator->destination = currentEvent->source;
        _elevator->stateFuncPtr = elevatorMoving;
      } else { 

        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->destination, currentEvent->source);
        _elevator->destination = _elevator->destination;
        _elevator->stateFuncPtr = elevatorMoving;
      }
    }
  }
  if(currentEvent->type == EVENT_DEPARTURE) {
    _elevator->destination = currentEvent->destination;
    addEvent(&_eventList, EVENT_ARRIVE, time, _elevator->currentPosition, _elevator->destination);
    _elevator->currentPosition = _elevator->destination;
    _elevator->stateFuncPtr = doorsOpen;
  }

 int getDir(struct elevator* _elevator) {
    struct event* eventPointer = peekNextEvent(&_eventList, eventPointer);
    if(_elevator->currentPosition < eventPointer->destination) {
      return 1;
    } else {
      return 0;
    }

  }
}
void printElevator(struct elevator *_elevator) {

  printf("Current floor: %d \n", _elevator->currentPosition);
  printf("Next floor: %d \n", _elevator->destination);
  printf("Amount of Passengers: %d \n", _elevator->numOfpassengers);
}
void doorsOpen(struct elevator *_elevator, struct event* currentEvent) {
  printf("Elevator doors open.\n");
  struct passenger* passenger = NULL;
  int desPassenger;
  if(currentEvent->type == EVENT_ARRIVE) {

    if(_elevator->numOfpassengers > 0) {
      struct passenger* nextPassenger = NULL;
      

      if(peekNextPassenger(&(_elevator->passengers), nextPassenger)->destinationLevel < currentEvent->destination) {
        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, currentEvent->source);
        _elevator->destination = currentEvent->source;
        _elevator->stateFuncPtr = elevatorMoving;
      } else { 
        
       
        int desPassenger = peekNextPassenger(&(_elevator->passengers), nextPassenger)->destinationLevel;
        addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, desPassenger);
        _elevator->destination = desPassenger;
        _elevator->stateFuncPtr = elevatorMoving;
      }
    } 
    if(peekNextPassenger(&(waitingUp[_elevator->currentPosition]), passenger) != NULL) {
      desPassenger = peekNextPassenger(&(waitingUp[_elevator->currentPosition]), passenger)->destinationLevel;
      addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, desPassenger);
      _elevator->destination = desPassenger;
      _elevator->stateFuncPtr = elevatorMoving;
    } else if(peekNextPassenger(&(waitingDown[_elevator->currentPosition]), passenger) != NULL) {
      desPassenger = peekNextPassenger(&(waitingDown[_elevator->currentPosition]), passenger)->destinationLevel;
      addEvent(&_eventList, EVENT_DEPARTURE, time, _elevator->currentPosition, desPassenger);
      _elevator->destination = desPassenger;
      _elevator->stateFuncPtr = elevatorMoving;
    } else {
      _elevator->stateFuncPtr = elevatorIdle;
    }
  }

  if(currentEvent->type == EVENT_DEPARTURE) {
    _elevator->destination = currentEvent->destination;
    addEvent(&_eventList, EVENT_ARRIVE, time, _elevator->currentPosition, _elevator->destination);
    _elevator->currentPosition = _elevator->destination;
    _elevator->stateFuncPtr = doorsOpen;
  }
}
int getDest(struct event* currentEvent) {
  int buttonPush;
  if(currentEvent->destination > currentEvent->source) {

     
    buttonPush = INT_MAX;
    int waitingListLength = waitingUpSize;
    for(int i = 0; i < waitingListLength; i++) {
      if(waitingUp[i].firstElement != NULL) {
  int buttonPush;
        if(i < buttonPush) {
          buttonPush = i;
        }
      }
    }
    } else if(currentEvent->destination < currentEvent->source) {
      buttonPush = INT_MIN;
      int waitingListLength = waitingDownSize;
      for(int i = 0; i < waitingListLength; i++) {
        if(waitingDown[i].firstElement != NULL) {
          if(i > buttonPush) {
            buttonPush = i;
          }
        }
      }
    }
    return buttonPush;
  }

