//
// Created by ronnypc on 05/11/2021.
//

#include <vector>
#include "../include/Trainer.h"
typedef std::pair<int, Workout> OrderPair;

//class Trainer{
//public:
//    Trainer(int t_capacity);
//    int getCapacity() const;
//    void addCustomer(Customer* customer);
//    void removeCustomer(int id);
//    Customer* getCustomer(int id);
//    std::vector<Customer*>& getCustomers();
//    std::vector<OrderPair>& getOrders();
//    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
//    void openTrainer();
//    void closeTrainer();
//    int getSalary();
//    bool isOpen();
//private:
//    int capacity;
//    bool open;
//    std::vector<Customer*> customersList;
//    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
//};
// I think we need to add salary field!

    Trainer::Trainer(int t_capacity): capacity(t_capacity), open(false) {
        //need
    }
    int Trainer::getCapacity() const{
        return capacity;
    }
    void Trainer::addCustomer(Customer* customer){
        if(!isOpen() && hasAvailableSpace())
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
    //for(std::size_t i = 0; i < v.size(); ++i) //Maybe this approach work
    void Trainer::moveCustomer(int id){//delete without heap freeing
        for(int i=0;i<customersList.size();i++){
            if(customersList[i]->getId()==id){
                customersList.erase(customersList.begin() + i);
                return;
            }
        }
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
        open = false; //is that all?
    }
    int Trainer::getSalary(){
        int sum = 0;
        for(OrderPair pair : orderList){
            sum += pair.second.getPrice();
        }
        return sum;
    }
    bool Trainer::isOpen(){
        return open;
    }

