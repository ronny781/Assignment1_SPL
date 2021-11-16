
// Created by ronnypc on 05/11/2021.
//
#include "../include/Customer.h"
#include <algorithm>

using namespace std;
//class Customer{
//public:
//    Customer(std::string c_name, int c_id);
//    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
//    virtual std::string toString() const = 0;
//    std::string getName() const;
//    int getId() const;
//private:
//    const std::string name;
//    const int id;
//};
//
//
Customer::Customer(std::string c_name, int c_id): name(c_name), id(c_id){}
std::string Customer::getName() const{
    return name;
}
int Customer::getId() const{
    return getId();
}

SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> swt;
    for(auto it=end(sorted_workout_options);it != begin(sorted_workout_options);it--){
        if(it->getType() == 2){
            swt.push_back(it->getId());
        }
    }
    return swt;
}
std::string SweatyCustomer::toString() const{
    return this->getName() + ",swt";
}
Customer* SweatyCustomer::clone() const{
    SweatyCustomer* swt = new SweatyCustomer(*this);
    return swt;
}


CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> chp;
    chp.push_back(sorted_workout_options[0].getId());
    return chp;
}
std::string CheapCustomer::toString() const{
    return this->getName() + ",chp";
}
Customer* CheapCustomer::clone() const{
    CheapCustomer* chp = new CheapCustomer(*this);
    return chp;
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> mcl;
    for(auto it=end(sorted_workout_options);it != begin(sorted_workout_options);it--){
        if(it->getType() == 0)
            mcl.push_back(it->getId());
    }
    return mcl;
}
std::string HeavyMuscleCustomer::toString() const{
    return this->getName() + ",mcl";
}
Customer* HeavyMuscleCustomer::clone() const{
    HeavyMuscleCustomer* mcl = new HeavyMuscleCustomer(*this);
    return mcl;
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> fbd;
    for(auto it=begin(sorted_workout_options);it != end(sorted_workout_options);it++) {
        if(it->getType() == 2){
            fbd.push_back(it->getId());
            break;
        }
    }
    for(auto it=end(sorted_workout_options);it != begin(sorted_workout_options);it--){
        if(it->getType() == 1) {
            fbd.push_back(it->getId());
            break;
        }
    }
    for(auto it=begin(sorted_workout_options);it != end(sorted_workout_options);it++) {
        if(it->getType() == 0){
            fbd.push_back(it->getId());
            break;
        }
    }
    return fbd;
}
std::string FullBodyCustomer::toString() const{
    return this->getName() + ",fbd";
}
Customer* FullBodyCustomer::clone() const{
    FullBodyCustomer* fbd = new FullBodyCustomer(*this);
    return fbd;
}