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
            vector<int> workoutPicked = cus->order(studio.getWorkoutOptions());
            trainer->order(cus->getId(),workoutPicked,studio.getWorkoutOptions());
        }
        complete();
    }
    std::string Order::toString() const{}
//private:
//    const int trainerId;


    MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src),dstTrainer(dst),id(customerId) ,BaseAction() {}
    void MoveCustomer::act(Studio &studio){
        Trainer* srcTra = studio.getTrainer(srcTrainer);
        Trainer* dstTra = studio.getTrainer(dstTrainer);
        if(srcTra!= nullptr && srcTra->isOpen() &&
           dstTra!= nullptr && dstTra->isOpen() &&
           srcTra->getCustomer(id)!= nullptr && dstTra->hasAvailableSpace()){
//            Customer* p1 = srcTra->getCustomer(id);
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
    std::string MoveCustomer::toString() const{}
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
    }
    std::string Close::toString() const{}
//private:
//    const int trainerId;



    CloseAll::CloseAll(): BaseAction(){}
    void CloseAll::act(Studio &studio){}
    std::string CloseAll::toString() const{}

    PrintWorkoutOptions::PrintWorkoutOptions():BaseAction(){}
    void PrintWorkoutOptions::act(Studio &studio){}
    std::string PrintWorkoutOptions::toString() const{}


    PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id),BaseAction(){}
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
