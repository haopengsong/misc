all: ai

ai: Bag.o Board.o computerS.o Move.o Player.o Dictionary.o Util.o Game.o ai.cpp
	g++ -g -Wall -o ai Bag.o Board.o computerS.o Move.o Player.o Dictionary.o Util.o Game.o ai.cpp
computerS.o: computerS.cpp computerS.h
	g++ -g -Wall -c computerS.cpp -o computerS.o
