#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Studio.h"
//#include "../include/StudioOperations.h"


using namespace std;

int Studio::getNextSkip(string str, int start) {
    if(start == str.size())
        return 1;
    for (int i = start; i < str.length(); ++i) {
        if(i == str.length() -1)
            return i-start+1;
        if (str[i] == ' ') {
            return i-start;
        }
        if(str[i] == ',')
            return i-start;
    }
    return -1;
}
void Studio::trainersInitalizer(string &line){
    //   trainers.push_back(new Trainer(-1));//Using this will assign index 1 to trainer 1.
    int skip;
    int next=0;
    while (next < line.size()) {
        skip = getNextSkip(line, next);
        if (skip == 1)
            trainers.push_back(new Trainer(line[next] - '0'));
        else
            trainers.push_back(new Trainer(stoi(line.substr(next, skip))));
        next = next + skip+1;
    }
}
void Studio::WorkOptionsInitalizer(string &line, int WorkoutIdCounter){
    std::vector<string> vect; //this code wont work without spaces!!
    int first = 0;
    for(int i=1;i<line.size();i++){
        if(line[i]==','){
            string s= line.substr(first,i-first);
            vect.push_back(s);
            first = i + 2;
        }
    }
    vect.push_back(line.substr(first,line.size()));
    int workType ;
    if(vect.at(1)== "Anaerobic")
        workType = 0;
    else if(vect.at(1)== "Mixed")
        workType = 1;
    else if(vect.at(1)== "Cardio")
        workType = 2;
    workout_options.push_back(Workout(WorkoutIdCounter,vect.at(0),std::stoi(vect.at(2)),WorkoutType(workType)));
}

Studio::Studio():open(false){}


Studio::Studio(const std::string &configFilePath):open(false){
    string myText;
    int WorkoutIdCounter = 0;
    // Read from the text file
    ifstream f(configFilePath);
    // Use a while loop together with the getline() function to read the file line by line
    bool firstHash = false;
    bool secondHash = false;
    bool thirdHash = false;
    while (getline(f, myText)) {
        // Output the text from the file
        if (myText[0] == '#') { //???
            if(!firstHash && !secondHash) {
                firstHash = true;
                continue;
            }
            else if (!secondHash){
                secondHash = true;
                firstHash = false;
                continue;
            }
            else if (!thirdHash){
                thirdHash = true;
                continue;
            }
        }
        else if (firstHash)
            continue;
        else if (secondHash && !thirdHash){
            trainersInitalizer(myText);
        }
        else if (thirdHash) {
            WorkOptionsInitalizer(myText, WorkoutIdCounter++);
        }
    }
    // Close the file
    f.close();
}

//Destructor
Studio::~Studio(){
    clear();
}
//Copy constructor
Studio::Studio(const Studio &other){
    open = other.open;
    workout_options = other.workout_options;
    actionsLog.clear(); // Added myself
    trainers.clear(); // Added myself
    for(BaseAction* act: other.actionsLog){
        actionsLog.push_back(act->clone());
    }
    for(Trainer* trainer: other.trainers){
        trainers.push_back(new Trainer(*trainer));
    }
}
//Copy Assignment Operator
const Studio& Studio::operator=(const Studio &other) {
    if(this!=&other){
        clear();
        open = other.open;
        workout_options = other.workout_options;
        for (Trainer* trainer: other.trainers) {
            trainers.push_back(new Trainer(*trainer));
        }
        for (BaseAction* action: other.actionsLog) {
            actionsLog.push_back(action->clone());
        }
    }
    return *this;
}
//Move Constructor
Studio::Studio(Studio &&other){
    open = other.open;
    workout_options = other.workout_options;
    trainers = other.trainers;
    actionsLog = other.actionsLog;
}
//Move Assignment Operator
const Studio& Studio::operator=(Studio&& other){
    clear();
    open = other.open;
    workout_options=other.workout_options;
    trainers = other.trainers;
    actionsLog = other.actionsLog;
    return *this;
}
void Studio::clear() {
    for(Trainer* trainer:trainers){
        if(trainer) {
            delete trainer;
            trainer = nullptr;
        }
    }
    trainers.clear();
    for(BaseAction* act:actionsLog){
        if(act) {
            delete act;
            act = nullptr;
        }
    }
    actionsLog.clear();
}

void Studio::start(){
    cout << "Studio is now open!" << endl;
    open = true;
    string s;
    int cusCounter = 0;
    getline(cin,s);
    while(true){
        if(s == "closeall") {
            BaseAction* act = new CloseAll();
            act->act(*this);
            actionsLog.push_back(act);
            break;
        }
        else if(s.substr(0,2)=="op") {//open
            vector<Customer *> cusList;
            int trainerId = 0, next = 5, skip = getNextSkip(s, next);
            if (skip == 1)
                trainerId = s[next] - '0';
            else
                trainerId = stoi(s.substr(5, skip));
            next = next + skip + 1;
            for (int i = next; i < s.length(); i++) {
                if (s[i] == ',') {
                    string name = s.substr(next, i - next);
                    string type = s.substr(i + 1, 3);
                    if (type == "swt")
                        cusList.push_back(new SweatyCustomer(name, cusCounter));
                    else if (type == "mcl")
                        cusList.push_back(new HeavyMuscleCustomer(name, cusCounter));
                    else if (type == "chp")
                        cusList.push_back(new CheapCustomer(name, cusCounter));
                    else if (type == "fbd") {
                        cusList.push_back(new FullBodyCustomer(name, cusCounter));
                    }
                    cusCounter++;
                    i += 3;
                    next = i + 2;
                }
            }
            if (cusList.size() != 0) {
                BaseAction *open = new OpenTrainer(trainerId, cusList);
                open->act(*this);
                int nextCustId = static_cast<OpenTrainer *>(open)->getNextIdtoBeInserted();
                if (nextCustId != -1) // there was  at least one customer insertion
                    cusCounter = nextCustId;
                else { // There was none coustumer insertions
                    cusCounter -= cusList.size();
                }
                for (Customer *cus: cusList) { //Delete all the customers we couldn't insert
                    if (cus->getId() >= nextCustId) {
                        delete cus;
                        cus = nullptr;
                    }
                }
                actionsLog.push_back(open);
            }
        }
        if(s.substr(0,2)=="or") {// order
            int trainerId;
            int skip =  getNextSkip(s, 6);
            if (skip == 1)
                trainerId = s[6] - '0';
            else
                trainerId = stoi(s.substr(6,skip));
            BaseAction *order = new Order(trainerId);
            order->act(*this);
            actionsLog.push_back(order);

        }
        else if(s.substr(0,2)=="st") {// status
            int trainerId;
            int skip =  getNextSkip(s, 7);
            if (skip == 1)
                trainerId = s[7] - '0';
            else
                trainerId = stoi(s.substr(7,skip));
            BaseAction *status = new PrintTrainerStatus(trainerId);
            status->act(*this);
            actionsLog.push_back(status);

        }
        else if(s.substr(0,2)=="mo"){// move
            int customer;
            int OriginalTrainer;
            int dstTrainer;
            int next =5;
            int skip =  getNextSkip(s, next);
            if (skip == 1)
                OriginalTrainer = s[next] - '0';
            else
                OriginalTrainer = stoi(s.substr(next,skip));
            next = next+skip+1;
            skip = getNextSkip(s, next);
            if (skip == 1)
                dstTrainer = s[next] - '0';
            else
                dstTrainer = stoi(s.substr(next,skip));
            next = next+skip+1;
            skip = getNextSkip(s, next);
            if (skip == 1)
                customer = s[next] - '0';
            else
                customer = stoi(s.substr(next,skip));
            BaseAction* move = new MoveCustomer(OriginalTrainer, dstTrainer, customer);
            move->act(*this);
            // need to close session if there no customers left

            if(trainers[OriginalTrainer]->getCustomers().empty()){
                trainers[OriginalTrainer]->closeTrainer();
            }
            actionsLog.push_back(move);
        }
        else if(s.substr(0,2)=="cl"){// close
            int trainerId;
            int skip =  getNextSkip(s, 6);
            if (skip == 1)
                trainerId = s[6] - '0';
            else
                trainerId = stoi(s.substr(6,skip));
            BaseAction* close = new Close(trainerId);
            close->act(*this);
            actionsLog.push_back(close);
        }
        else if(s.substr(0,2)=="wo"){
            BaseAction* printWorkoutOptions = new PrintWorkoutOptions();
            printWorkoutOptions->act(*this);
            actionsLog.push_back(printWorkoutOptions);
        }
        else if(s.substr(0,3)=="log"){
            BaseAction* log = new PrintActionsLog;
            log->act(*this);
            actionsLog.push_back(log);
        }
        else if(s.substr(0,3)=="bac"){
            BaseAction* backup = new BackupStudio; //Maybe we should add backup first to the list!
            backup->act(*this);
            actionsLog.push_back(backup);
        }
        else if(s.substr(0,3)=="res"){
            BaseAction* restore = new RestoreStudio;
            restore->act(*this);
            actionsLog.push_back(restore);
        }
        getline(cin,s);
    }

}


int Studio::getNumOfTrainers() const{
    return trainers.size();
}

Trainer* Studio::getTrainer(int tid){
    return tid > getNumOfTrainers() ? nullptr : trainers[tid];
}
const std::vector<BaseAction*>& Studio::getActionsLog() const{
    return  actionsLog;
} // Return a reference to the history of actions

std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
}


//std::vector<Workout>& Studio::getWorkoutOptionsSorted(){
//    return sorted_workout_options;
//}