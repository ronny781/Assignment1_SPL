cmake_minimum_required(VERSION 3.20)
project(Hello)

set(CMAKE_CXX_STANDARD 11)

add_executable(Hello src/main.cpp src/Workout.cpp include/Workout.h src/Studio.cpp include/Studio.h include/Trainer.h src/Trainer.cpp src/Customer.cpp include/Customer.h src/Action.cpp include/Action.h src/StudioOperations.cpp include/StudioOperations.h)
