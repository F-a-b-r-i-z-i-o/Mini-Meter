# Mini-Meter
In Perugia, to go from the station to the historic center, the mini metro 'acts as a means of travel for tourists.
Let's consider a single cabin with a capacity of 4 tourists and only two stops: Stazione, CentroStorico.
The cabin is stopped in one of the two stations, the tourists get on, when the maximum capacity is reached (ie 4 tourists) the cabin leaves and moves to the other stop.
The cabin always moves exactly 4 tourists at a time from one stop to another.

Booth: Repeat the 0-4 procedure indefinitely
0) Warn tourists waiting at that stop that they can get on
1) Awaits 4 tourists ascent
1.1) when the cabin is full print "cabin composition": print the ids of the 4 tourists on board on stdout
2) It moves to the other stop (taking 2 seconds)
2.1) the booth prints on stdout that it is restarting
2.2) print on stdout arrival at the Station / CentroStorico stop
3) Warn tourists that they can get off
3.1) when a tourist goes down he writes on stdout that he has gone down
4) Wait for everyone to get off
Tourist:
After getting out of the cabin, a tourist "takes a lap" of 2 seconds and then gets back in line to return to the other stop. Repeat this process over and over.

Initialization:
- The car leaves from the Station stop
- There are 5 tourists in total
- At the beginning 4 tourists leave from the Station and 1 from the CentroStorico

Implementation:
1) Implementation of the described system, using POSIX threads to model Cabina and Turista
2) Data structures for synchronization
3) The project consists of 3 files
3.1) file containing the main and the Cabin and Tourist functions, e.g., minimetro.c
3.2) files containing the library / SC function calls with relative error handling, e.g., utilities.c utilities.h, or if defined via macros a single utilities.h file
3.3) Makefile
4) Handling of eventual errors in library / SC function calls. In the event of a serious error, terminate the program by producing a warning on the screen of the error.
5) the Makefile to compile and link the sources.
