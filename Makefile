all: compile run

compile:
	g++ -o a -std=c++11 main.cpp Klotski.cpp EightGame.cpp BoardGame2D.cpp PegSolitaire.cpp
run:
	./a