//
// Created by ronnypc on 05/11/2021.
//


//enum ActionStatus{
//    COMPLETED, ERROR
//};

#include "../include/Action.h"
#include "../include/Trainer.h" // I added myself, is that good?
#include "../include/Studio.h" // I added myself, is that good?

using namespace std;

    BaseAction::BaseAction(){}
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


    OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id), customers(customersList){
   //this opens session
    }
    void OpenTrainer::act(Studio &studio){
        if(studio.getTrainer(trainerId)== nullptr || !studio.getTrainer(trainerId)->isOpen() || studio.getTrainer(trainerId)->getCapacity() < customers.size()){
            // Action cant be completed
            error("Workout session does not exist or is already open.");
            return;
        }
        Trainer* train = studio.getTrainer(trainerId);
        for(Customer *cus : customers){
            train->addCustomer(cus);
        }
        train->openTrainer();
        complete();
    }
    std::string OpenTrainer::toString() const{
    }
//private:
//    const int trainerId;
//    std::vector<Customer *> customers;


    Order::Order(int id):trainerId(id){}
    void Order::act(Studio &studio){
        if(studio.getTrainer(trainerId)== nullptr || !studio.getTrainer(trainerId)->isOpen()){
            error("Workout session does not exist or is already open.");
            return;
        }
            Trainer* train = studio.getTrainer(trainerId);
        vector<Customer*> customerList = train->getCustomers();
        for(Customer* cus : customerList){
            cus->order(studio.getWorkoutOptions());
        }
        complete();
    }
    std::string Order::toString() const{}
//private:
//    const int trainerId;


    MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src),dstTrainer(dst),id(customerId){}
    void MoveCustomer::act(Studio &studio){}
    std::string MoveCustomer::toString() const{}
//private:
//    const int srcTrainer;
//    const int dstTrainer;
//    const int id;

    Close::Close(int id):trainerId(id){}
    void Close::act(Studio &studio){}
    std::string Close::toString() const{}
//private:
//    const int trainerId;



    CloseAll::CloseAll(){}
    void CloseAll::act(Studio &studio){}
    std::string CloseAll::toString() const{}

    PrintWorkoutOptions::PrintWorkoutOptions(){}
    void PrintWorkoutOptions::act(Studio &studio){}
    std::string PrintWorkoutOptions::toString() const{}


    PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id){}
    void PrintTrainerStatus::act(Studio &studio){}
    std::string PrintTrainerStatus::toString() const{}
//private:
//    const int trainerId;



    PrintActionsLog::PrintActionsLog(){}
    void PrintActionsLog::act(Studio &studio){}
    std::string PrintActionsLog::toString() const{}


    BackupStudio::BackupStudio(){}
    void BackupStudio::act(Studio &studio){}
    std::string BackupStudio::toString() const{}

    RestoreStudio::RestoreStudio(){}
    void RestoreStudio::act(Studio &studio){}
    std::string RestoreStudio::toString() const{}
