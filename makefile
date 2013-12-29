###############################################################
# Program:
#     Project 03, Object-Oriented Chess
#     Brother Helfrich, CS165
# Author:
#     Adam Harris
#     Jared Wadsworth
# Summary:
#     This is chess, much like Porject 1, only this time we used
#     objects...and it took longer. This will play almost exactly like
#     Project 1 did. We ran out of time before we could implement the rules
#     of the game, or any other major extra credit opportunities.
#     EXTRA CREDIT:
#       -Display Rules of Smith Notation
#       -Test mode can now be turned off 
#     Estimated:  20.0 hrs
#     Actual:     30.0 hrs a piece
#        The most difficult part was starting, and knowing how to use
#      the provided MOVE class. The whole project, however, proved to
#      be very difficult and time consuming.
###############################################################
FLAGS=-g
###############################################################
# Programs:
#    chess:         The playable game
###############################################################
chess : chess.o move.o position.o board.o piece.o
	g++ $(FLAGS) -o chess $^
	#tar -cf chess.tar *.cpp *.h makefile

moveTest : moveTest.o move.o position.o
	g++ $(FLAGS) -o moveTest $^

boardTest : boardTest.o board.o piece.o position.o
	g++ $(FLAGS) -o boardTest $^

###############################################################
# Individual files
#    
###############################################################
chess.o : chess.cpp board.h piece.h chess.h
	g++ $(FLAGS) -c chess.cpp

moveTest.o : moveTest.o move.h position.h
	g++ $(FLAGS) -c moveTest.cpp

boardTest.o : boardTest.cpp board.cpp board.h piece.h
	g++ $(FLAGS) -c boardTest.cpp

move.o : move.cpp move.h position.h
	g++ $(FLAGS) -c move.cpp 

board.o : board.cpp board.h piece.h
	g++ $(FLAGS) -c board.cpp

position.o : position.cpp position.h
	g++ $(FLAGS) -c position.cpp

piece.o : piece.cpp piece.h
	g++ $(FLAGS) -c piece.cpp

###############################################################
# General rules
###############################################################
clean :
	rm moveTest chess boardTest *.o *.tar *~ *.gch *#

all :  moveTest chess

