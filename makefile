#
#
#all: clean compile link
#
#link:
#	g++ -o bin/studio bin/main.o bin/Studio.o bin/Trainer.o bin/workout.o bin/Action.o bin/Customer.o bin/StudioOperations.o config
#
#
#compile:
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/StudioOperations.o src/StudioOperations.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/main.o src/main.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Studio.o src/Studio.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Action.o src/Action.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Workout.o src/Workout.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Trainer.o src/Trainer.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Customer.o src/Customer.cpp
#
#clean:
#	rm -f bin/*

#all: clean compile link run
#
#run:
#	bin/studio config
#link:
#	g++ -o bin/studio bin/main.o bin/Workout.o bin/Customer.o config
#
#
#compile:
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Workout.o src/Workout.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/Customer.o src/Customer.cpp
#	g++ -g -Wall --std=c++11 -Weffc++ -c -o bin/main.o src/main.cpp
#
#
#
#
#clean:
#	rm -f bin/*
#
# All Targets
all: clean bin/studio config

bin/studio: bin/main.o bin/Customer.o bin/Workout.o bin/Trainer.o bin/Workout.o bin/Action.o bin/Studio.o
	@echo 'Building target: main'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/studio bin/main.o bin/Customer.o bin/Workout.o bin/Trainer.o bin/Action.o bin/Studio.o
	@echo 'Finished building target: main'
	@echo ' '

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Customer.o: src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp

bin/Trainer.o: src/Trainer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Trainer.o src/Trainer.cpp

bin/Workout.o: src/Workout.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Workout.o src/Workout.cpp

bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp

bin/Studio.o: src/Studio.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Studio.o src/Studio.cpp

clean:
	@echo 'Cleaning'
	rm -f bin/*