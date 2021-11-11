
// Created by ronnypc on 05/11/2021.
//
#include "../include/Customer.h"

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
    vector<int> *list = new vector<int>;
    for(Workout w_k : workout_options){
        if(w_k.getType() == 2){
            list->push_back(w_k.getId());
        }
    }
    return *list;
}
std::string SweatyCustomer::toString() const{

}

CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){}
std::string CheapCustomer::toString() const{}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){}
std::string HeavyMuscleCustomer::toString() const{}

FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){}
std::string FullBodyCustomer::toString() const{}