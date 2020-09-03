#ifndef EVENT_LIST_H
#define EVENT_LIST_H

/*
 Author: Ahmed Abdulkader & Chippen Vlahija
 */

/* 
 * Example of event types. You might need to add or remove event types depending on
 * your implementation
 */
#define EVENT_BUTTON_PUSH 0
#define EVENT_DEPARTURE 1
#define EVENT_ARRIVE 2

#define SORT_TIME 0
#define SORT_DESTINATION_ASCENDING 1
#define SORT_DESTINATION_DESCENDING 2



/*
 * Suggestion of how an event should be defined. Suggested use of the type, source, 
 * and destination members are given in the instructions file. 
 */
struct event {
  unsigned int time;
  int type;
  int source;
  int destination;
};


struct eventListElement{
  struct event data; 
  struct eventListElement *nextElement;
};

struct eventList{
  struct eventListElement *firstElement;
};


/* 
 * The event list should be implemented as a linked list, where the elements are 
 * sorted based on  time, meaning that the first element in the linked list is 
 * always the next event to occur.
 */
unsigned int addEvent(struct eventList* list, int type, unsigned int time, int source, int destination);

/*
 * Initialize an empty event list. 
 */
void initEventList(struct eventList* list);



/* 
 * This function should get and remove next event from the event queue (implemented as 
 * a linked list). 
 *
 * 
 * It takes the following arguments as input:
 *   list - A pointer to the event list
 *   nextEvent - A pointer to a event instance where the data of the next event  
 *               should be stored.  
 *
 * Return values: 
 *   NULL - If the event list was empty at the time of calling the function. 
 *   nextEvent - The next event pointer otherwise. 
 *  
 * Don't forget to free memory of the element that was removed from the linked list.
 *
 * Otherwise you have created a memory leak. 
 */
struct event *getNextEvent(struct eventList* list, struct event *nextEvent);

int compareEvents(struct event *event1, struct event *event2, int sortOrder);
void printEvents(struct eventList* _eventList);
struct event* peekNextEvent(struct eventList* list, struct event *nextEvent);


#endif
