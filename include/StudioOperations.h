//
// Created by lioralon on 13/11/2021.
//

#ifndef HELLO_STUDIOOPERATIONS_H
#define HELLO_STUDIOOPERATIONS_H
#include "Workout.h"
#include "vector"
#include <algorithm>

using namespace std;


static class StudioOperations {
    private:
        static bool byPrice(const Workout& a, const Workout& b) ;
    public:
        static vector<Workout> sortWorkoutsbyPrice(vector<Workout> workouts);
};


#endif //HELLO_STUDIOOPERATIONS_H
