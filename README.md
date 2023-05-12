# fullyAssociative
A fullyAssociative Cache simulator using the C programming language

A FIFO cache simulator that has been implemented using structs 

To run the simulator build the source file fullyAssociative.c using either gcc, or your preffered compiler. This will create a working programm that is run with one command line argument, the source of a memory trace file. Some have been provided in the tests directory.

The output of the programm is the total number of hits, misses and evictions made.

A sample run would be:
	> ./fullyAssociative tests/trace_1.txt

This will run the simulator with test cases present in the tests/trace_1.txt file

Answers to the test files are availabe in the answers directory

Enjoy...
