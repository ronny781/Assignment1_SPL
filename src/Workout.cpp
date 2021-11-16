//
// Created by ronnypc on 05/11/2021.
//
#include <iostream>
#include "../include/Workout.h"
#include <sstream>
using namespace std;
//enum WorkoutType{
//    ANAEROBIC, MIXED, CARDIO
//};
//
//class Workout{
//public:
//    Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type);
//    int getId() const;
//    std::string getName() const;
//    int getPrice() const;
//    WorkoutType getType() const;
//private:
//    const int id;
//    const std::string name;
//    const int price;
//    const WorkoutType type;
//};


    Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):id(w_id), name(w_name), price(w_price), type(w_type){

    }
    int Workout::getId() const{
        return id;
    }
    std::string Workout::getName() const {
        return name;
    }
    int Workout::getPrice() const{
        return price;
    }
    WorkoutType Workout::getType() const {
        return type;
    }
    std::string Workout::toString() const{
        std::stringstream str;
        if (getType() == 0)
            str << getName() << ", Anaerobic, " << getPrice() << endl;
        if (getType() == 1)
            str << getName() << ", Mixed, " << getPrice() << endl;
        if (getType() == 2)
            str << getName() << ", Cardio, " << getPrice() << endl;
        std::string s = str.str();
        return s;

    };


