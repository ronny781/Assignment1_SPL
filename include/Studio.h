#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
//#include "Workout.h"
#include "Trainer.h"
#include "Action.h"
#include "StudioOperations.h"


class Studio{

public:
    virtual ~Studio();//Destructor
    Studio(const Studio &other);//Copy Constructor
    const Studio& operator=(const Studio &other);//Copy Assignment Operator
    Studio(Studio &&other);//Move Constructor
    const Studio& operator=(Studio&& other);//Move Assignment Operator
    Studio();
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    const std::vector<BaseAction*>& getActionsLog() const;
    std::vector<Workout>& getWorkoutOptions();
//    std::vector<Workout>& getWorkoutOptionsSorted();
    void trainersInitalizer(std::string & line); // added this myself
    void WorkOptionsInitalizer(std::string &line, int WorkoutIdCounter); // added this myself

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
//    std::vector<Workout> sorted_workout_options;
};
#endif