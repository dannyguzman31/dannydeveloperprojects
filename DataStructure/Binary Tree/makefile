###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother Ercanbrack, CS235
# Author:
#     Daniel Guzman
# Summary:
#     This is a BST Node
# Time:
#     About 5 Hours of work
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o 
	g++ -o a.out week08.o huffman.o -g
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g

