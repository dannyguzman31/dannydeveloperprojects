###############################################################
# Program:
#     Week 10, Map
#     Brother Ercanbrack, CS235
# Author:
#     Daniel Guzman
# Summary: You need to write a program that uses the STL Map 
# to count the number of occurrences of words from a data 
# file. The program must prompt the user for the filename.
#
# Time: 6 Hours 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week10.o 
	g++ -o a.out week10.o 
	tar -cf week10.tar *.cpp makefile

make clean:
	rm *.o *.out *.tar

##############################################################
# The individual components
#      week10.o       : the driver program
##############################################################
week10.o:  week10.cpp
	g++ -c week10.cpp