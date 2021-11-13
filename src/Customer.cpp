
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
    vector<int> *swt = new vector<int>;
    for(Workout w_k : workout_options){
        if(w_k.getType() == 2){
            swt->push_back(w_k.getId());
        }
    }
    return *swt;
}
std::string SweatyCustomer::toString() const{
    return this->getName() + ",swt";
}
static bool byPrice(const Workout& a, const Workout& b){
    return a.getPrice() < b.getPrice();
}

CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> chp;
    chp.push_back(workout_options[0].getId());
    return chp;
}


std::string CheapCustomer::toString() const{
    return this->getName() + ",chp";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> mcl;
    for(int i=workout_options.size();i >= 0; i--){
        if(workout_options[i].getType() == 0)
            mcl.push_back(workout_options[i].getId());
    }
    return mcl;
}
std::string HeavyMuscleCustomer::toString() const{
    return this->getName() + ",mcl";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> fbd;
    for(int i=0;i<workout_options.size();i++) {
        if(workout_options[i].getType() == 2){
            fbd.push_back(workout_options[i].getId());
            break;
        }
    }
    for(int i=workout_options.size();i >= 0; i--){
        if(workout_options[i].getType() == 1) {
            fbd.push_back(workout_options[i].getId());
            break;
        }
    }
    for(int i=0;i<workout_options.size();i++) {
        if(workout_options[i].getType() == 0){
            fbd.push_back(workout_options[i].getId());
            break;
        }
    }
    return fbd;
}
std::string FullBodyCustomer::toString() const{
    return this->getName() + ",fbd";
}