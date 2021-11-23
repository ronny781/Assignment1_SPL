// Created by ronnypc on 05/11/2021.
//
#include "../include/Customer.h"
#include <algorithm>
#include <limits>
#include <list>

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
    vector<Workout> mclOnly;
    for (int i = 0; i < workout_options.size(); ++i) {
        if (workout_options[i].getType() == ANAEROBIC) {
            mclOnly.push_back(workout_options[i]);
        }

    }
    int max = -1;
    int position;
    int size = mclOnly.size();
    while(mcl.size() != size) {
        for (int i = 0; i < mclOnly.size(); ++i) {
            if (mclOnly[i].getPrice() > max) {
                max = mclOnly[i].getPrice();
                position = i;
            }
        }
        mcl.push_back(mclOnly[position].getId());
        mclOnly.erase(mclOnly.begin()+position);
        max = -1;
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
std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> fbd;
    int minCardio = INT32_MAX;
    int maxMixed = 0;
    int minAnaerobic = INT32_MAX;
    int cardioId = -1;
    int mixedId = -1;
    int aerobicId = -1;

    for (int i = 0 ; i < workout_options.size(); i++) {
//        Workout wk1 = workout_options[i];
        if (workout_options[i].getType() == CARDIO && workout_options[i].getPrice()  < minCardio) {
            minCardio =  workout_options[i].getPrice();
            cardioId = workout_options[i].getId();
        }
        else if (workout_options[i].getType()  == MIXED && workout_options[i].getPrice()  > maxMixed) {
            maxMixed =  workout_options[i].getPrice();
            mixedId = workout_options[i].getId();
        }
        else if (workout_options[i].getType() == ANAEROBIC && workout_options[i].getPrice() < minAnaerobic) {
            minAnaerobic = workout_options[i].getPrice();
            aerobicId = workout_options[i].getId();
        }
    }
    if(cardioId != -1)
        fbd.push_back(cardioId);
    if(mixedId!=-1)
        fbd.push_back(mixedId);
    if(aerobicId != -1)
        fbd.push_back(aerobicId);
    return fbd;
}
std::string FullBodyCustomer::toString() const {
    return this->getName() + ",fbd";
}
Customer *FullBodyCustomer::clone() const {
    FullBodyCustomer *fbd = new FullBodyCustomer(*this);
    return fbd;
}



