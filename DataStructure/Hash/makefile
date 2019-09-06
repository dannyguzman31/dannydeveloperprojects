###############################################################
# Program:
#     Week 12, Hash
#     Brother Ercanbrack, CS235
# Author:
#     Daniel Guzman
# Summary:
#     This is a Hash took about 6 hours of work
# 	
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week12.o spellCheck.o
	g++ -o a.out week12.o spellCheck.o -g
	tar -cf week12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week12.o: hash.h week12.cpp list.h
	g++ -c week12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g

