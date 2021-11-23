#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Studio.h"
//#include "../include/StudioOperations.h"


using namespace std;

//class Studio{
//public:
//    Studio();
//    Studio(const std::string &configFilePath);
//    void start();
//    int getNumOfTrainers() const;
//    Trainer* getTrainer(int tid);
//    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
//    std::vector<Workout>& getWorkoutOptions();
//
//private:
//    bool open;
//    std::vector<Trainer*> trainers;
//    std::vector<Workout> workout_options;
//    std::vector<BaseAction*> actionsLog;
//};
int Studio::getNextSkip(string str, int start) {
    for (int i = start; i < str.length(); ++i) {
        if (str[i] == ' ') {
            return i-start;
        }
    }
    return -1;
}
void Studio::trainersInitalizer(string &line){
    //   trainers.push_back(new Trainer(-1));//Using this will assign index 1 to trainer 1.
//    int lineLength = 0;
//    int skip;
//    int next=0;
//    while (lineLength < line.length()) {
//        skip = getNextSkip(line, next);
//        lineLength = next+skip;
//        if (skip == 1)
//            trainers.push_back(new Trainer(line[next] - '0'));
//        else
//            trainers.push_back(new Trainer(stoi(line.substr(next, skip))));
//        next = next + skip;
//    }
    for(int i=0;i<line.size();i++){
        if(line[i]!=','){
            char c = line[i];
            int cNum = c - '0';
//            cout << cNum << endl;

            trainers.push_back(new Trainer(cNum));

        }
    }
}
void Studio::WorkOptionsInitalizer(string &line, int WorkoutIdCounter){
    std::vector<string> vect; //this code wont work without spaces!!
    int first = 0;
    for(int i=1;i<line.size();i++){
        if(line[i]==','){
            string s= line.substr(first,i-first);
            vect.push_back(s);
            std::cout << s<< std::endl;
            first = i + 2;
        }
    }
    vect.push_back(line.substr(first,line.size()));
//    std::cout << line.substr(first,line.size())<< std::endl;
//    std::cout << "vector is at " << vect.at(0) <<" "<< vect.at(1) << " " << vect.at(2) << " " <<std::endl;
    int workType ;
    if(vect.at(1)== "Anaerobic")
        workType = 0;
    else if(vect.at(1)== "Mixed")
        workType = 1;
    else if(vect.at(1)== "Cardio")
        workType = 2;

//    Workout* w_k1 = new Workout(WorkoutIdCounter,vect.at(0),std::stoi(vect.at(2)),WorkoutType(workType));
    workout_options.push_back(Workout(WorkoutIdCounter,vect.at(0),std::stoi(vect.at(2)),WorkoutType(workType)));

    // we might need to check if we need to sort the list, if yes we should do it here.
//
}

Studio::Studio():open(false){}


Studio::Studio(const std::string &configFilePath):open(false){
//Trainer* trainer = new Trainer(3);
//trainer->addCustomer(new CheapCustomer("ronny",2));
//Trainer* trainer1 =new Trainer(*trainer);
//cout << trainer1->isOpen();
//        std::ifstream file(configFilePath);
//        char line[256];
//        int counter = 0;
//        while(file) {
//            file.getline(line, 256);
//            if(line[0] == '#' || line[0] == '\0')
//                continue;
//            if(counter == 0){
//                int numofTrainers = stoi(line);
//                counter++;
//                continue;
//            }
//            if(counter == 1) {
//                for(int i=0;i<getNumOfTrainers();i++){
//                    trainers.push_back(new Trainer(line[i]));
//                    i++;
//                }
//                counter++;
//            }
//        }
//
    string myText;
    int WorkoutIdCounter = 0;
    // Read from the text file
    ifstream f(configFilePath);
    // Use a while loop together with the getline() function to read the file line by line
    bool flag1 = false;
    bool flag2 = false;
    while (getline(f, myText)) {
        // Output the text from the file
        if (myText == "# Traines") { //???
            flag1 = true;
            continue;
        } else if (flag1) {
            trainersInitalizer(myText);
            flag1 = false;
        } else if (myText == "# Work Options") {
            flag2 = true;
            continue;
        }
        if (flag2) {
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
//    other.trainers.clear(); // meytuar
//    other.actionsLog.clear();
}
//Move Assignment Operator
const Studio& Studio::operator=(Studio&& other){
    clear();
    open = other.open;
    workout_options=other.workout_options;
    trainers = other.trainers;
    actionsLog = other.actionsLog;
//    other.trainers.clear(); //meyutar
//    other.actionsLog.clear();
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

            vector<Customer*> cusList ;
            int trainerId = 0, first = 0;
            int skip =  getNextSkip(s, 5);
            if (skip == 1)
                trainerId = s[5] - '0';
            else
                trainerId = stoi(s.substr(5,skip));
            for (int i = 6+skip; i < s.length(); i++) {
                if (s[i] == ',') {
                    string name = s.substr(first, i - first);
                    string type = s.substr(i + 1, 3);
                    if (type == "swt")
                        cusList.push_back(new SweatyCustomer(name,cusCounter));
//                            cout << name << " " << type << cusCounter << endl;
                    else if (type == "mcl")
                        cusList.push_back(new HeavyMuscleCustomer(name,cusCounter));
//                            cout << name << " " << type << cusCounter << endl;
                    else if (type == "chp")
                        cusList.push_back(new CheapCustomer(name,cusCounter));
//                            cout << name << " " << type << cusCounter << endl;
                    else if (type == "fbd"){
                        cusList.push_back(new FullBodyCustomer(name,cusCounter));
//                        cout << cus->toString();
                    }
//                            cout << name << " " << type << cusCounter << endl;
                    cusCounter++;
                    i += 3;
                    first = i + 2;
                }
            }

            BaseAction* open = new OpenTrainer(trainerId,cusList);
            open->act(*this);
            int nextCustId = static_cast<OpenTrainer*>(open)->getNextIdtoBeInserted();
            if(nextCustId!=-1) // there was  at least one customer insertion
                cusCounter = nextCustId;
            else{ // There was none coustumer insertions
                cusCounter -= cusList.size();
            }
            for(Customer* cus : cusList){ //Delete all the customers we couldn't insert
                if(cus->getId()>=nextCustId){
                    delete cus;
                    cus = nullptr;
                }
            }
            actionsLog.push_back(open);
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
                BaseAction* close = new Close(OriginalTrainer);
                close->act(*this);
                actionsLog.push_back(close);
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
//            actionsLog.push_back(log);
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