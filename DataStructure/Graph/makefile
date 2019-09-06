###############################################################
# Program:
#     Week 13, Graph
#     Brother Ercanbrack, CS235
# Author:
#	  Daniel Guzman
# Summary:
#     This program will complete a graph to sort some data

# Time:
#     About 9 hours of work
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
	g++ -o a.out week13.o
	tar -cf week13.tar *.h *.cpp makefile sorted.dat

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: week13.cpp
	g++ -c week13.cpp
##############################################################
# Makes clean 
##############################################################
clean:
	rm a.out *.o *.tar
all : a.out
