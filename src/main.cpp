//#include "../include/Studio.h"
#include <iostream>
#include <vector>

using namespace std;

//Studio* backup = nullptr;

void func() {
    string s;
    getline(cin,s);
    std::cout << s;
    while (s != "closeall") {
        if (s.substr(0, 2) == "op") {//open
            int tid = s[5];
            int first = 7;
            vector<vector<string>> list;
            for (int i = 7; i < s.length(); i++) {
                if (s[i] == ',') {
                    vector<string> vect(2);
                    vect.push_back(s.substr(first, i - first));
                    vect.push_back(s.substr(i, 3));
                    list.push_back(vect);
                    cout << vect[0] << "    " << vect[1] << endl;
                    i += 3;
                    first = i + 1;
                }
            }
        }
    }
}

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
//    Studio studio(configurationFile);
    func() ;
//    studio.start();
//    if(backup!=nullptr){
//        delete backup;
//        backup = nullptr;
//    }
    return 0;
}

