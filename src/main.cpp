#include "../include/Studio.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

//Studio* backup = nullptr;

void func() {
    cout << "Studio is now open!" << endl;
    string s;

    getline(cin,s);
        while(s!="closeall"){

    if(s.substr(0,2)=="op") {//open
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
                vector<string> vect(2);
                string name = s.substr(first, i - first);
                string type = s.substr(i + 1, 3);
                if (type == "swt")
                    cout << name << " " << type << cusCounter << endl;
                else if (type == "mcl")
                    cout << name << " " << type << cusCounter << endl;
                else if (type == "chp")
                    cout << name << " " << type << cusCounter << endl;
                else if (type == "fbd")
                    cout << name << " " << type << cusCounter << endl;
                cusCounter++;
                i += 3;
                first = i + 2;
            }
        }
    }
            getline(cin,s);

}
}
Studio* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
//    if(backup!= nullptr){
//        delete backup;
//        backup = nullptr;
//    }



    return 0;
}
void func2(){
    Customer *one = new SweatyCustomer("Shalom",1);
}

