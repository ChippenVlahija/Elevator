#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "passenger_list.h"
#include "event_list.h"

/*
 Author: Ahmed Abdulkader & Chippen Vlahija
 */

struct elevator {
  int currentPosition;
  int destination;
  int numLevels;
  int numOfpassengers;
  int capacity;
  struct passengerList passengers;

  /* Function ptr*/
  void (*stateFuncPtr)(struct elevator*, struct event*);
};
/* 
 *  state functions
 */
void printElevator(struct elevator *_elevator);
int getDest(struct event* currEvent);
int getDir(struct elevator* _elevator);
void elevatorIdle(struct elevator *_elevator, struct event* curEvent);
void elevatorMoving(struct elevator *_elevator, struct event* curEvent);
void doorsOpen(struct elevator *_elevator, struct event* curEvent);
/*
 * Initialize the elevator, for example, setting the initial position and
 * inital state. 
 * This function from the main function in elevator_simulator.c
 */ 
void initElevator(struct elevator *elevator, int numLevels);
#endif