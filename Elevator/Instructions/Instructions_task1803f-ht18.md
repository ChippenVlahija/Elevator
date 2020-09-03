Instructions - task 1803f-ht18
======

_Johan Holmgren, 2018-10-06_

Overview and purpose of task
----

The purpose of this assignment is that you should practice designing and implementing a finite state machine using a state function pointer. 

In particular, you will implement a finite state machine for an elevator controller, and your code will make use of the code you wrote in assignments 1803c and 1803d.

You will then simulate your elevator using so-called discrete event simulation. Don't worry if you are not familiar with discrete event simulation; below you will find a short introduction to simulation and to discrete event simulation. 

You will conduct this assignment in pairs of two students; however, it is also possible to work individually. 





Introduction to computer simulation 
------

Simply speaking, simulation can be described as the process of imitating some important aspects of a real or an imagined system. 
In a simulation model, a set of entities are represented and the actions and
relationships between these entities are studied using a computer, often over some period of 
time. 
For example, a computerized simulation model might represent the traffic in Malmö during rush hours. The central entities in such a model could be cars, bikes, and pedestrians. 
The actions are when the entities move in the transport network, stops at traffic lights and zebra crossings, leaving the origin, arriving to destination, etc. 
The relationships between entities, which directly influence the actions of the entities, include cars stopping for pedestrians at zebra crossings, cars having to adjust speed due to congestion, etc. 

For an example of a traffic simulation, see the following youtube video: [https://www.youtube.com/watch?v=lF_RoSlofyA](https://www.youtube.com/watch?v=lF_RoSlofyA)


In order to simulate entities over a period of time, it is necessary to include a simulation clock in the simulation model. 
In Discrete event simulation (DES), which is a common type of simulation modeling, the simulated actions are represented by events, where each action is often represented by a start time and an end time. For example, a pedestrian crosses a zebra crossing can be represented by the events *start\_crossing* and *end\_crossing*, and an elevator moving between floors in a building might be represented by a *depart* event and an *arrive* event. 
 Each event has a time, and the simulation model stores those future events that are known in a sorted list of future events. The first event in the list is always the event that is closest in the future. 
The simulation model advances by simulating the events in the event list one by one, and it performs related activities whenever needed. 
Whenever an event is processed, the simulation clock is advanced to the time of the event to process. In this way, the simulation model only simulates the points of time where things actually happen, hence the name Discrete Event Simulation. 

Please note that during simulation, future events will be generated continuously, and sorted into the event list to be processed later. 

For example, a pedestrian that starts crossing a zebra crossing might be represented by the _start\_crossing_ event, and when this event is processed it generates an _end\_crossing_ event that is sorted into the list of future known events, i.e., the event list. 



An important motivation for developing a computer-based simulation
model for a system is that the relations between entities might be
too complex to model or analyze mathematically. 
Moreover, experimenting with large real systems might
be too expensive and in some cases, even
impossible.  




Preparation 
------

Complete the following

* Study the powerpoint material about finite state machines.
* Study the finite state machine implementation that was presented during the finite state machine lecture. 
* Make sure that your code for assignments 1803c and 1803d is correct and can be used in this project (however, you will need to make some minor modifications of the previous code). 
* Read this assignment specification carefully before the scheduled laboratory session. It is possible, and recommended, to work on this assignment before the scheduled laboratory session.
* If needed, read the laboratory environment document provided on Canvas. 

 




Description of task
------

As mentioned above, the purpose of this laboratory assignment is that you should implement a finite state machine representing an elevator, where you will use the C programming language.

Based on the requirements specified below, you should design your own elevator controller as a finite state machine. You should then implement your finite state machine using function pointers as we discussed during the lecture on finite state machines.   


You should make the following assumptions about the elevator.  

* The house has 7 floors, referred to as 0, 1, 2, 3, 4, 5, and 6. 
* A maximum of 10 people can be in the elevator at the same time, and it is assumed that you can count the number of passengers entering and leaving the elevator. 
* If the elevator is full and there is people waiting to enter, it is assumed that these persons will push the button again and wait until the elevator comes next time. 
* It always takes 5 seconds for the elevator to travel between two adjacent floors. 
* It always takes 10 seconds from when the elevator stops until it is ready to go again. During these 10 seconds, passenger enters and leaves the elevator. 

 

### Create and clone your assignment git repository
The first thing you need to do is to create your group's git repository for this assignment and clone your repository to your local computer. 

In your git repository you find two folders: `Instructions` and `task`. In the instructions folder you find this assignment instruction, and in the task folder you find all the code needed to work with this assignment. 

In particular, the task folder contains a make file and three subfolders: `src`, `bin`, and `unity`. 


* The `src`folder contains some files that you will modify as part of the assignment. Each of these files will be briefly described below. 
* All the compiled code will be saved in the `bin` folder if you use the provided make file. 
* The `unity` folder contains the unity framework, which you can use in this assignment if you want. 


In the `task` folder, you find a sample make file, which includes two targets: build and clean. 
The build target compiles your program, and the clean target removes all the files that are provided by your compiler. 
It is recommended that you don't add the compiled files to your git repository.  
In the `task` folder you also find a sample button push file named `button_pushes`. 
The `button_pushes` is read when the elevator simulator is started (see `elevator_simulator.c`), and it contains a sequence of passenger's wish to travel. The format of file is described in the file `elevator_simulator.c`. You modify this file in order to create test cases for your simulator. 




### Proved source files 

As mentioned above, you will be given some code to start with, and as part of this assignment, you will use the code that you earlier generated in assignments 1803c and 1803e. However, you will have to make some changes in your existing code. 



##### elevator_simulator.c
This file contains the `main function of your elevator simulator, and it implements the main steps of your simulation software.  

The file (elevator\_simulator.c) is well documented, so you are recommended to read the code and documentation before you start working with the assignment. 



##### event\_list.c and event\_list.h

In the `event_list.c` file you will implement your event list according to the specification in the `event_list.h` file.

The event list is a linked list containing struct type elements with the following definition:

```
struct event {
  unsigned int time;
  int type;
  int source;
  int destination;
};
```

The list should be sorted based on time so that the first element in the list is always the next element in time. 

The type of an event can be one of the following events, or any event that you choose to define yourself. 

```
#define EVENT_BUTTON_PUSH 0
#define EVENT_DEPARTURE 1
#define EVENT_ARRIVE 2
```

The `source` member refers to:

* The waiting location of the passenger in case the event is of type `EVENT_BUTTON_PUSH`
* The level the elevator is departing from if the event is of type `EVENT_DEPARTURE`
* The level the elevator departed from if the event is of type `EVENT_ARRIVE`

The `destination` member refers to the 

* The preferred location of the passenger in case the event is of type `EVENT_BUTTON_PUSH`
* The level the elevator will go to if the event is of type `EVENT_DEPARTURE`
* The level the elevator arrived to if the event is of type `EVENT_ARRIVE`


You need to implement the following function, which are specified in `event.h`:

* `initEventList(...)`
* `addEvent(...)`
* `getNextEvent(...)`


Please note that in order to implement your event list and the necessary functions to work with your event list, you only need to make some minor changes of the single linked list or the double linked list that you created previously in the course. 


##### circular\_buffer.c and circular\_buffer.h
In the `circular_buffer.c` file you will implement a circular buffer according to the specification in the `circular_buffer.h` file.

in particular, you need to implement the following functions, which are specified in `circular_buffer.h`:

* `initCircularBuffer(...)`
* `containsCircularBuffer(...)`
* `addElementCircularBuffer(...)`
* `removeValueCircularBuffer(...)`
* `getElementCircularBuffer(...)`

In your elevator simulator, you will use a circular buffer in order to keep track of which outside elevator buttons have been pushed, hence keeping track of where passengers are waiting to be picked up. 

You are suggested to use the following representation of your button pushes (where different values are used to represent different buttons):

| Value        |  Button |
| ------------- |-------------| 
| 0 | Button push on level 0, going up | 
| 1 | Button push on level 1, going up | 
| -1 | Button push on level 1, going down | 
| 2      | Button push on level 2, going up | 
| -2      | Button push on level 2, going down | 
| ...     | ... | 
| NUM_LEVELS-2 | Button push on level NUM_LEVEL-2, going up | 
| -(NUM_LEVELS-2) | Button push on level NUM_LEVEL-2, going down | 
| -(NUM_LEVEL-1) | Button push on level NUM_LEVEL-1, going down | 

Hence, the following values are used to represent outside elevator button pushes: *   -(NUM_LEVEL-1), -(NUM_LEVEL-2), ..., -2, -1, 0, 1, 2, ..., NUM_LEVEL-2


Please note that you should be able to use the circular buffer that you created earlier in the course. However, you will have to make sure that the `addElementCircularBuffer` function  is implemented so that it discards the element to be added if the buffer is already full. You also have to rename the functions you already implemented. 
In addition, you have to make sure that you do not add values to the buffer that is already in the buffer. 

##### passenger_list.c and passenger_list.h

The elevator simulator needs to keep track of passengers waiting to be picked up, and passengers that are currently located inside the elevator. For each floor, the simulator keeps 1) a linked list of passengers waiting to go up (except for the top floor) and 2) a linked list of passengers that are waiting to go down (except for the bottom floor). These linked lists are stored in the `waitingUp` and `waitingDown` arrays that are declared in `elevator_simulator.c`.
In addition, the elevator keeps a linked list of passengers that are currently inside the elevator. 




In the `passenger_list.c` file you will implement a passenger list as a linked list according to the specification in the `passenger_list.h` file.

In particular, you should implement the following functions, all of which are specified in the `passenger_list.h` file. 

* `addPassenger(...)`
* `passengerListIsEmpty(...)`
* `initPassengerList(...)`
* `getNextPassenger(...)`
* `peekNextPassenger(...)`


You should sort the list either based on time (oldest first) or destination of passengers, depending on the value of the `sortOrder` argument that is provided to the `addPassenger` function. The following sort orders should be supported. 

````
#define SORT_TIME 0
#define SORT_DESTINATION_ASCENDING 1
#define SORT_DESTINATION_DESCENDING 2
````

You are recommended to sort the lists of passengers waiting  to be picked up based on time, and the list of passengers inside the elevator based on destination, ascending or descending based on the direction of the elevator to simplify the process of determining the next stop of the elevator. 
If the list of passengers is sorted based on how close their destination is to the current location of the elevator, you can easily determine the next destination by using the `peekNextPassenger(...)` function. 
When passengers enters the elevator, they are moved to the elevator passenger list from either the `waitingUp`or `waitingDown` queue of the current floor, depending on the direction of the elevator.








Please note that in order to implement your passenger list and the necessary function to work with your passenger list, you only need to make some minor changes of the single linked list or the double linked list that you created previously in the course. 





##### elevator.c and elevator.h

In these files, you should implement your elevator finite state machine. 

In particular, you should implement your elevator controller using a `struct` data type containing all the necessary elevator data, including the current position of the elevator, and a function pointer to the state functions of the elevator. 
Please note that the data included in the elevator struct might depend on how you choose to implement your elevator. 

For each state of your elevator, you need to define the corresponding state function that can be called from the simulator main loop (in `elevator_simulator.c`.

Inside the state functions in elevator.c, you need to create and add new events depending on the functionality of your elevator. This is the reason why `elevator.c`makes use of the global variable `_eventList`. 

For example, adding a new departure event 10 seconds from the current time is done in the following way from inside a state function. 

`addEvent(&_eventList, EVENT_DEPARTURE, time + 10, curEvent->source, curEvent->destination);`
 








### Testing your solution
In addition to designing and implementing an elevator controller, and making the necessary changes in the elevator simulation program, you also need to test your solution. 
You can test your solution in many different ways, and it is up to you to decide how you should test your solution. For example, you can use unity, which is included in the `task/unity` folder of your github repository. 


As mentioned above, the elevator is driven by button pushes, or rather passenger travel wishes, that is specified in the file `button_pushes`, included in the `task` folder of your github repository. As part of your testing, you are expected to create test cases by modifying the `button_pushes` file. 



Submission and examination
------

When you are done with the assignment, you should push your code to your git repository according to the instructions in the document  _DA267A - laboratory environment_. It is important that you do not forget to add any new files that you have created.

You should also demonstrate and discuss your solution with one of the assignment supervisors, which you do during any of the scheduled supervision sessions. During this discussion, you should be able to show that your code works as expected. You should also be able to describe how you have tested your solution, which includes showing the results of the cases you generated as part of testing your solution. All of the students in the group should be able to explain the code and answer some basic questions about the solution. 


In addition, you should write a short report where you briefly describe your solution. In particular, you should describe:

* The design and implementation of your FSM.
* How you tested your solution.

In addition, it is appreciated if you write in the report what you think was good about this assignment, and what you think can be improved. 

Your report should contain a frontpage, where you provide a title, the group number, and the names of all group numbers. The expected length of the report, in addition to the frontpage, is 3-5 a4 pages using normal font size (11pt). 
The report should be submitted using the submission page for assignment 1803f on Canvas. 

The course teachers will look at all reports and code that have been submitted by Wednesday evening the week after the scheduled assignment session. If you submit later, your submission will be evaluated at the end of the course. 

Please note that you should not submit your report if you have not pushed your final code to git. In other words, submitting your report means that both code and report is ready to be evaluated. 















