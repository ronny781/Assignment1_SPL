//
// Created by ronnypc on 05/11/2021.
//

#include <vector>
#include "../include/Trainer.h"


Trainer::Trainer(int t_capacity): capacity(t_capacity), open(false),salary(0) {
}
//Destructor:
Trainer::~Trainer() {
    clear();
}
//Copy Constructor:
Trainer::Trainer(const Trainer &other) {
    capacity = other.capacity;
    open = other.open;
    orderList = other.orderList;
    for(Customer* cust:other.customersList){
        customersList.push_back(cust->clone());
    }

}
//Copy Assignment Operator
const Trainer& Trainer::operator=(const Trainer &other){
    if(this!=&other) {
        clear();
        capacity = other.capacity;
        open = other.open;
        orderList = other.orderList;
        for (Customer *cust: other.customersList) {
            customersList.push_back(cust->clone());
        }
    }
    return *this;

}
//Move Constructor
Trainer::Trainer(Trainer &&other){
    capacity = other.capacity;
    open = other.open;
    orderList = other.orderList;
    customersList = other.customersList;
    other.customersList.clear();//meyutar
}
//Move Assignment Operator
const Trainer& Trainer::operator=(Trainer&& other){
    clear();
    capacity = other.capacity;
    open = other.open;
    orderList = other.orderList;
    customersList = other.customersList;
    other.customersList.clear();//meyutar
    return *this;
}
void Trainer::clear() {
    for (Customer *cust: customersList) {
        if (cust) {
            delete cust;
            cust = nullptr;
        }
    }
    customersList.clear();
}
int Trainer::getCapacity() const{
    return capacity;
}
void Trainer::addCustomer(Customer* customer){
    if(hasAvailableSpace())
        customersList.push_back(customer);
}

void Trainer::removeCustomer(int id){//Wonder if it works.
    for(int i=0;i<customersList.size();i++){
        if(customersList[i]->getId()==id){
            delete customersList[i]; // Is that right?
            customersList.erase(customersList.begin() + i);
            return;
        }
    }
}
void Trainer::updateSalary(int addToSalary) {
    salary += addToSalary;
}
Customer* Trainer::getCustomer(int id){
    for(Customer *cus : customersList){
        if(cus->getId()==id){
            return cus;
        }
    }
    return nullptr; //if not found return null?
}
std::vector<Customer*>& Trainer::getCustomers(){
    return customersList;
}
std::vector<OrderPair>& Trainer::getOrders(){
    return orderList;
}
void Trainer::updateOrderList(std::vector<OrderPair> &list){
    orderList.clear();
    orderList = list;
}
void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    for(int id : workout_ids){ //only works with workout list being unsorted!
        orderList.push_back(OrderPair (customer_id,workout_options[id]));
    }
}
bool Trainer::hasAvailableSpace(){ //Added myself
    return getCapacity()-customersList.size()>0;
}
void Trainer::openTrainer(){
    open = true; //is that all?
}
void Trainer::closeTrainer(){
    for(Customer* cus : getCustomers()){ // Wonder if that works because I delete from my iterable.
        delete cus;
    }
    getCustomers().clear();
    open = false; //is that all?
}
int Trainer::getSalary(){
    return salary;
}
bool Trainer::isOpen(){
    return open;
}



