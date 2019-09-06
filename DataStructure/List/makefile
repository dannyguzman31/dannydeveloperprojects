###############################################################
# Program:
#     Week 07, LIST
#     Brother Ercanbrack, CS235
# Author:
#     Daniel Guzman
# Summary:
#     This is a list .
# Time:
#     About 8 hours of work, Only test 1 and 2 pass. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp

