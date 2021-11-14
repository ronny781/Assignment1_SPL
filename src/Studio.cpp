
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../include/Studio.h"


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

    void Studio::trainersInitalizer(string &line){
        int first = 0;
     for(int i=1;i<line.size();i++){
         if(line[i]!=','){
             string s = line.substr(first,i-first);
             trainers.push_back(new Trainer(std::stoi(s)));
             first = i + 1;
             cout << line[i] << std::endl;

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
     std::cout << line.substr(first,line.size())<< std::endl;
     std::cout << "vector is at " << vect.at(0) <<" "<< vect.at(1) << " " << vect.at(2) << " " <<std::endl;
     int workType ;
     if(vect.at(1)== "Anaerobic")
         workType = 0;
     else if(vect.at(1)== "Mixed")
         workType = 1;
     else if(vect.at(1)== "Cardio")
         workType = 2;

//    Workout* w_k1 = new Workout(WorkoutIdCounter,vect.at(0),std::stoi(vect.at(2)),WorkoutType(workType));
        workout_options.push_back(Workout(WorkoutIdCounter,vect.at(0),std::stoi(vect.at(2)),WorkoutType(workType)));
//     cout << w_k1->getId() << " " << w_k1->getName() << " " << w_k1->getPrice() << " " << w_k1->getType() << endl;
        // we might need to check if we need to sort the list, if yes we should do it here.
//
 }

    Studio::Studio(){}
    Studio::Studio(const std::string &configFilePath):open(false){

        string myText;
        int WorkoutIdCounter = 0;
        // Read from the text file
        ifstream f(configFilePath);
        // Use a while loop together with the getline() function to read the file line by line
        bool flag1 = false;
        bool flag2 = false;
        while (getline(f, myText)) {
            // Output the text from the file
            if (myText == "# Traines") {
                flag1 = true;
                continue;
            } else if (flag1) {
                trainersInitalizer(myText);
                cout << myText << endl;
                flag1 = false;
            } else if (myText == "# Work Options") {
                flag2 = true;
                continue;
            }
            if (flag2) {
                WorkOptionsInitalizer(myText, WorkoutIdCounter++);
                cout << myText << endl;

            }
        }
        // Close the file
        f.close();
    }

    void Studio::start(){
        cout << "Studio is now open!" << endl;
        string s;

        getline(cin,s);
        while(s!="closeall"){

            if(s.substr(0,2)=="op") {//open

                vector<Customer*> cusList ;
                int trainerId = 0, first = 0;
                for(int i=5;i<s.length();i++){ // find  where first name starts.
                    if(s[i]==' '){
                        trainerId = stoi(s.substr(5,i-5));
                        first = i+1;
                        break;
                    }
                }

                int cusCounter = 0;
                for (int i = first; i < s.length(); i++) {
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
                        else if (type == "fbd")
                            cusList.push_back(new FullBodyCustomer(name,cusCounter));
//                            cout << name << " " << type << cusCounter << endl;
                        cusCounter++;
                        i += 3;
                        first = i + 2;
                    }
                }
                BaseAction* open = new OpenTrainer(trainerId,cusList);
                open->act(*this);//Wonder if that works.
                // if open.getstatus
//                if(cusList->size()> trainers.ge)
            }
            if(s.substr(0,2)=="or"){// order

            }
            if(s.substr(0,2)=="st"){// status

            }
            if(s.substr(0,2)=="mo"){// move

            }
            if(s.substr(0,2)=="cl"){// close

            }
            getline(cin,s);

        }

    }


    int Studio::getNumOfTrainers() const{
        return trainers.size();
    }

    Trainer* Studio::getTrainer(int tid){
        return tid >= trainers.size() ? nullptr : trainers[tid];
    }
    const std::vector<BaseAction*>& Studio::getActionsLog() const{
        return  actionsLog;
    } // Return a reference to the history of actions

    std::vector<Workout>& Studio::getWorkoutOptions(){
        return workout_options;
    }