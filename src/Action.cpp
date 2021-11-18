//enum ActionStatus{
//    COMPLETED, ERROR
//};

#include "../include/Action.h"
#include "../include/Trainer.h" // I added myself, is that good?
#include "../include/Studio.h" // I added myself, is that good?
#include <sstream>
#include <string>
using namespace std;

BaseAction::BaseAction():errorMsg(""){}


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

    if(trainer== nullptr || trainer->isOpen() || !trainer->hasAvailableSpace()){
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
    std::stringstream toString;
    toString << "open " << trainerId;
    for(Customer* cus : customers){ //Wonder if that works!
        toString << " " << cus->toString();
    }
    std::string s = toString.str();
    return s;
}
BaseAction* OpenTrainer::clone() const{
    OpenTrainer* op = new OpenTrainer(*this);
    return op;
}
//private:
//    const int trainerId;
//    std::vector<Customer *> customers;


Order::Order(int id):trainerId(id) ,BaseAction() {}
void Order::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer== nullptr || !trainer->isOpen()){
        error("Workout session does not exist or is already open.");
        cout << getErrorMsg() << endl; //Printing error
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
BaseAction* Order::clone() const{
    Order* ord = new Order(*this);
    return ord;
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
        dstTra->addCustomer(srcTra->getCustomer(id)->clone());
        srcTra->removeCustomer(id); //Need to check if there is better solution!!!!

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
        cout << getErrorMsg() << endl; //Printing error
    }
}
std::string MoveCustomer::toString() const{
    std::stringstream toString;
    if(getStatus() == COMPLETED)
        toString << "move " << srcTrainer << " " << dstTrainer << " " << id << "Completed";
    else
        toString << "move " << srcTrainer << " " << dstTrainer << " Error: " << getErrorMsg();
    std::string s = toString.str();
    return s;
}
BaseAction* MoveCustomer::clone() const{
    MoveCustomer* move= new MoveCustomer(*this);
    return move;
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
        cout << getErrorMsg() << endl; //Printing error
        return;
    }
    for(Customer* cus : trainer->getCustomers()){ // Wonder if that works because I delete from my iterable.
        delete cus;
        cus = nullptr;
    }
    trainer->getCustomers().clear();
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
BaseAction* Close::clone() const{
    Close* close= new Close(*this);
    return close;
}

CloseAll::CloseAll(): BaseAction(){}
void CloseAll::act(Studio &studio){
    for(int i=0;i<studio.getNumOfTrainers();i++){
        Trainer* trainer = studio.getTrainer(i);
        if(trainer!= nullptr && trainer->isOpen()){
            Close act(i);
            act.act(studio);
        }
    }
    cout << "Studio is now closed." << endl; //Need to make sure we need this output
    complete();
}
std::string CloseAll::toString() const{
    return "closeall Completed";
}
BaseAction* CloseAll::clone() const{
    CloseAll* closeall= new CloseAll(*this);
    return closeall;
}
PrintWorkoutOptions::PrintWorkoutOptions():BaseAction(){}
void PrintWorkoutOptions::act(Studio &studio){
    vector<Workout> workout_option = studio.getWorkoutOptions();
//    std::stringstream toString;
    for(Workout wk: workout_option){
       cout << wk.toString() ;
    }
//    std::string s = toString.str();
    complete();
}
std::string PrintWorkoutOptions::toString() const{
    return "workout_options Completed";
}
BaseAction* PrintWorkoutOptions::clone() const{
    PrintWorkoutOptions* printoptions= new PrintWorkoutOptions(*this);
    return printoptions;
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
        cout << pair.second.getName() << " " << pair.second.getPrice() << "NIS " << pair.first << endl;
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
BaseAction* PrintTrainerStatus::clone() const{
    PrintTrainerStatus* printstatus= new PrintTrainerStatus(*this);
    return printstatus;
}
//private:
//    const int trainerId;



PrintActionsLog::PrintActionsLog():BaseAction(){}
void PrintActionsLog::act(Studio &studio){
    const vector<BaseAction*> actionsLog = studio.getActionsLog();
    for(BaseAction* act : actionsLog){
        cout << act->toString() << endl;
    }
    complete();
}
std::string PrintActionsLog::toString() const{
    return "log Completed";
}
BaseAction* PrintActionsLog::clone() const{
    PrintActionsLog* printactions= new PrintActionsLog(*this);
    return printactions;
}


BackupStudio::BackupStudio():BaseAction(){ }
void BackupStudio::act(Studio &studio){
    if(backup!=nullptr) {
        delete backup;
    }
    backup = new Studio(studio); //Maybe we just need to use copy assignment operator differently?
    complete();
}
std::string BackupStudio::toString() const{
    return "backup Completed";
}
BaseAction* BackupStudio::clone() const{
    BackupStudio* backup= new BackupStudio(*this);
    return backup;
}

RestoreStudio::RestoreStudio():BaseAction(){}
void RestoreStudio::act(Studio &studio){//Do we need to close our working studio first?
    if(backup== nullptr){
        error("No backup available");
        cout << getErrorMsg() << endl; //Printing error
        return;
    }
    studio = *backup; //Need to make sure no memory leak created here.
    complete();
}
std::string RestoreStudio::toString() const{
    std::stringstream toString;
    if(getStatus() == COMPLETED)
        toString << "restore "  << "Completed" ;
    else
        toString << "restore " << "Error: " << getErrorMsg();
    std::string s = toString.str();
    return s;
}
BaseAction* RestoreStudio::clone() const{
    RestoreStudio* restore= new RestoreStudio(*this);
    return restore;
}