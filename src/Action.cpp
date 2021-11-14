//
// Created by ronnypc on 05/11/2021.
//


//enum ActionStatus{
//    COMPLETED, ERROR
//};

#include "../include/Action.h"
#include "../include/Trainer.h" // I added myself, is that good?
#include "../include/Studio.h" // I added myself, is that good?
#include <sstream>
#include <string>
using namespace std;

    BaseAction::BaseAction(){
        errorMsg = nullptr;
    }
    ActionStatus BaseAction::getStatus() const{
        return status;
    }
    void BaseAction::complete(){
        status = ActionStatus(0);
    }
    void BaseAction::error(std::string errorMsg){
        this->errorMsg = errorMsg;
        status = ActionStatus(1);
    }
    std::string BaseAction::getErrorMsg() const{
        return errorMsg;
    }
    //private:
    //std::string errorMsg;
    //ActionStatus status;


    OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id), customers(customersList), BaseAction() { //need to add rule of 5
   //this opens session
    }
    void OpenTrainer::act(Studio &studio){
        Trainer* trainer = studio.getTrainer(trainerId);
        if(trainer== nullptr || !trainer->isOpen() || trainer->getCapacity() < customers.size()){
            // Action can't be completed
            error("Workout session does not exist or is already open.");
            cout << getErrorMsg() << endl; //Printing error
            return;
        }

        for(Customer *cus : customers){
            trainer->addCustomer(cus);
        }
        trainer->openTrainer();
        complete();
    }
    std::string OpenTrainer::toString() const{
    }
//private:
//    const int trainerId;
//    std::vector<Customer *> customers;


    Order::Order(int id):trainerId(id) ,BaseAction() {}
    void Order::act(Studio &studio){
        Trainer* trainer = studio.getTrainer(trainerId);
        if(trainer== nullptr || !trainer->isOpen()){
            error("Workout session does not exist or is already open.");
            return;
        }
        vector<Customer*> customerList = trainer->getCustomers();
        for(Customer* cus : customerList){
            vector<Workout> workoutOptions = studio.getWorkoutOptions();
            vector<int> workoutPicked = cus->order(workoutOptions);
            trainer->order(cus->getId(),workoutPicked,workoutOptions);
            for(int i=0;i<workoutPicked.size();i++){
                 cout << cus->getName() << " is Doing " << workoutOptions[workoutPicked[i]].getName() << endl;
            }
        }
        complete();
    }
    std::string Order::toString() const{
        std::stringstream toString;
        if(getStatus() == COMPLETED)
            toString << "order " << trainerId << " Completed" ;
        else
            toString << "order " << trainerId << " Error: " << getErrorMsg();
        std::string s = toString.str();
        return s;
    }
//private:
//    const int trainerId;


    MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src),dstTrainer(dst),id(customerId) ,BaseAction() {}
    void MoveCustomer::act(Studio &studio){
        Trainer* srcTra = studio.getTrainer(srcTrainer);
        Trainer* dstTra = studio.getTrainer(dstTrainer);
        if(srcTra!= nullptr && srcTra->isOpen() &&
           dstTra!= nullptr && dstTra->isOpen() &&
           srcTra->getCustomer(id)!= nullptr && dstTra->hasAvailableSpace()){
//            SweatyCustomer p1 = *(srcTra->getCustomer(id));
            dstTra->addCustomer(srcTra->getCustomer(id));
            srcTra->moveCustomer(id); //Need to check if there is better solution!!!!

            vector<OrderPair> srcList = srcTra->getOrders();
            vector<OrderPair> dstList = dstTra->getOrders();
            vector<int> indicesForDelete; // Stores where we need to delete old elements
            for(std::vector<int>::size_type i = 0; i != srcList.size(); i++) {
                if(srcList[i].first==id){
                    dstList.push_back(srcList[i]);
                    indicesForDelete.push_back(i);
                }
            }
            for(int indice : indicesForDelete)
                srcList.erase(srcList.begin()+indice);
            complete();

        }
        else{
            error("Cannot move customer");
        }
    }
    std::string MoveCustomer::toString() const{
        std::stringstream toString;
        toString << "move " << srcTrainer << " " << dstTrainer << " " << id;
        std::string s = toString.str();
        return s;
    }
//private:
//    const int srcTrainer;
//    const int dstTrainer;
//    const int id;

    Close::Close(int id):trainerId(id) ,BaseAction() {}
    void Close::act(Studio &studio){
        Trainer* trainer = studio.getTrainer(trainerId);
        if(trainer== nullptr || !trainer->isOpen()){
            error("Workout session does not exist or is already open.");
            return;
        }
        trainer->closeTrainer();
        complete();
        cout << "Trainer " << trainerId << " closed. Salary " << trainer->getSalary() << "NIS" << endl;
    }
    std::string Close::toString() const{
        std::stringstream toString;
        if(getStatus() == COMPLETED)
            toString << "close " << trainerId << " Completed" ;
        else
            toString << "close " << trainerId << " Error: " << getErrorMsg();
        std::string s = toString.str();
        return s;
    }
//private:
//    const int trainerId;



    CloseAll::CloseAll(): BaseAction(){}
    void CloseAll::act(Studio &studio){
        for(int i=0;i<studio.getNumOfTrainers();i++){
            Close act(i);
            act.act(studio);
        }
        cout << "Studio is now closed." << endl; //Need to make sure we need this output
        complete();
    }
    std::string CloseAll::toString() const{
        return "closeall Completed";
    }

    PrintWorkoutOptions::PrintWorkoutOptions():BaseAction(){}
    void PrintWorkoutOptions::act(Studio &studio){
        vector<Workout> workout_option = studio.getWorkoutOptions();
        for(Workout wk: workout_option){
            string out = wk.toString();
            cout << out << endl;
        }
        complete();
    }
    std::string PrintWorkoutOptions::toString() const{
        return "workout_options Completed";
    }


    PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id),BaseAction(){} // What about checking if trainer exist??
    void PrintTrainerStatus::act(Studio &studio){
        Trainer* trainer = studio.getTrainer(trainerId);
        if(trainer->isOpen())
            cout << "Trainer" << trainerId << " status: " << "open" << endl;
        else{
            cout << "Trainer" << trainerId << " status: " << "closed" << endl;
            return;
        }
        cout << "Customers:" << endl;
        vector<Customer*> customersList = trainer->getCustomers();
        for(Customer* cus : customersList){
            cout << cus->getId() << " " << cus->getName() << endl;
        }
        cout << "Orders:" << endl;
        vector<OrderPair> orders = trainer->getOrders();
        for(OrderPair pair : orders){
            cout << pair.second.getName() << " " << pair.second.getPrice() << "NIS " << pair.first;
        }
        cout << "Current Trainer's Salary: " << trainer->getSalary() << "NIS " << endl;
        complete();
    }
    std::string PrintTrainerStatus::toString() const{
        std::stringstream toString;
        toString << "status " << trainerId << " Completed";
        std::string s = toString.str();
        return s;
    }
//private:
//    const int trainerId;



    PrintActionsLog::PrintActionsLog():BaseAction(){}
    void PrintActionsLog::act(Studio &studio){
        vector<BaseAction*> actionsLog = studio.getActionsLog();
        for(BaseAction* act : actionsLog){
            cout << act->toString() << endl;
        }
        complete();
    }
    std::string PrintActionsLog::toString() const{
        return "log Completed";
    }


    BackupStudio::BackupStudio():BaseAction(){}
    void BackupStudio::act(Studio &studio){}
    std::string BackupStudio::toString() const{}

    RestoreStudio::RestoreStudio():BaseAction(){}
    void RestoreStudio::act(Studio &studio){}
    std::string RestoreStudio::toString() const{}
