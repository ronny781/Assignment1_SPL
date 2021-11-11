#
#
#all: clean compile link
#
#link:
#	g++ -o bin/studio bin/main.o bin/Studio.o bin/Trainer.o bin/workout.o bin/Action.o bin/Customer.o config
#
#
#compile:
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/main.o src/main.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Studio.o src/Studio.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Action.o src/Action.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Workout.o src/Workout.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Trainer.o src/Trainer.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Customer.o src/Customer.cpp
#
#clean:
#	rm -f bin/*

all: clean compile link run

run:
	bin/studio config
link:
	g++ -o bin/studio bin/main.o bin/Workout.o


compile:
	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Workout.o src/Workout.cpp
	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/main.o src/main.cpp



clean:
	rm -f bin/*
