// Created by ronnypc on 05/11/2021.
//
#include "../include/Customer.h"
#include <algorithm>
#include <limits>


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
    return id;
}

SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
    vector<int> swt;
    for(auto it=begin(workout_options);it != end(workout_options);it++){
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
    int minPrice = 0;
    for (auto it= begin(workout_options);it != end(workout_options); it++) {
        if (it->getType() == 2) {
            if(minPrice == 0) {
                chp.push_back(it->getId());
                minPrice = it->getPrice();
            }
            else {
                if(it->getPrice() < minPrice) {
                    minPrice = it->getPrice();
                    chp[0] = it->getId();
                }
            }
        }
    }
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
    vector<Workout> sorted(workout_options);
    sort(sorted.begin(),sorted.end(), byPrice);
    for(auto it=sorted.end();it != begin(sorted);it--){
        if(it->getType() == ANAEROBIC)
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
bool byPrice(const Workout& a, const Workout& b){
    return a.getPrice() < b.getPrice();
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> fbd;
    vector<Workout> sorted(workout_options);
    sort(begin(sorted), end(sorted), byType);
    int minCardio = std::numeric_limits<int>::max();
    int maxMixed = 0;
    int minAnaerobic = std::numeric_limits<int>::max();
    for (auto it = end(sorted); it != begin(sorted); it--) {
        if (it->getType() == CARDIO && it->getPrice() < minCardio) {
            fbd.pop_back();
            fbd.push_back(it->getId());
            minCardio = it->getPrice();
        }
        if (it->getType() == MIXED && it->getPrice() > maxMixed) {
            fbd.pop_back();
            fbd.push_back(it->getId());
            maxMixed = it->getPrice();
        }
        if (it->getType() == ANAEROBIC && it->getPrice() < minAnaerobic) {
            fbd.pop_back();
            fbd.push_back(it->getId());
            minAnaerobic = it->getPrice();
        }
    }
    return fbd;
}
std::string FullBodyCustomer::toString() const {
    return this->getName() + ",fbd";
}
Customer *FullBodyCustomer::clone() const {
    FullBodyCustomer *fbd = new FullBodyCustomer(*this);
    return fbd;
}
bool byType(const Workout &a, const Workout &b) {
    WorkoutType type = a.getType();
    switch (type) {
        case ANAEROBIC:
            return true;
        case MIXED:
            return b.getType()==CARDIO;
        case CARDIO:
            return false;
    }
}

