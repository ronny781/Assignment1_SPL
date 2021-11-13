//
// Created by lioralon on 13/11/2021.
//

#include "../include/StudioOperations.h"

 bool StudioOperations::byPrice(const Workout& a, const Workout& b) {
    return a.getPrice() < b.getPrice();
}
 vector<Workout> StudioOperations::sortWorkoutsbyPrice(vector<Workout> workouts){
      sort(workouts.begin(),workouts.end(), byPrice);
      return workouts;
}


