Maxim Joel Carbonell-Kiamtia
mjcarbon


---------------------
DESCRIPTION: This directory is for the purposes of generating a queue that is capable of handling multiple threads(simultaneous pushes and pops to the same queue while keeping the same order). 
2. Enter "make"
3. Use the generated queue.o file in test_files. 
---------------------
FILES
Makefile
queue.c
queue.h
README.md

-----------------------
queue.c contains the c program to perform all of the logic needed to set up a queue that takes in a given size... it has the capability to push any void element(while handling cases of element being NULL), pop any void element(while handling cases of queue being empty), and deleting itself. This queue can also support multiple threads.

---------------------
DESIGN
queue.c has a design that outlines the following functions... i.e. queue_new(takes in a given size and returns a the pointer to the queue), queue_delete(takes in a queue to clear all of the elements and free the allocated memory), length(returns the length of the queue/amount of elements in the queue), clear(clears/deletes all of the elements in the queue), queue_push(checks if queue is null, and if it isnt it locks the initiates a mutex lock, conditionals, and signals before it unlocks at the very end), queue_pop(initiates a mutex lock, a conditional wait, checks if the queue/element is null, iniates a conditional signal, and lastly unlocks). 

---------------------
TESTING AND ERROR HANDLING 

To operate the program the user types... "make"... With the object file "queue.o" now generated we can move it into the test_scripts directory and run our bash/c scripts. 

1.) The user can type "./basic-push-pop.sh" to test the basic functionality of queue_push() and queue_pop()
2.) The user can type "./create-free.sh" to test the basic functionality of if we free the allocated memory of our queue correctly 
3.) The user can type "./pop-busy.sh" to test the basic functionality of popping with multiple threads. 
4.) The user can type "./push-order.sh" to test the basic functionality of pushing with multiple threads.
5.) The user can type "./thread-push-pop.sh"to test the basic functionality of pushing and popping with multiple threads. 

NOTE: tests on versions of ubuntu greater than 20.0, do not work with the given tests... Thus changes were made syntactically to the test (NOT SEMANTICALLY) to workaround this issue of casting an integer. All casts that had "(int)" were converted to "(ptrdiff_t)" and required the <stddef.h> library. 

