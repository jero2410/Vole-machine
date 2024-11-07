//
// Created by Admin on 10/26/2024.
//

#ifndef VOLEMACHINE_TOMY_REGISTER_H
#define VOLEMACHINE_TOMY_REGISTER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std ;

class Register {
private:
    vector<int> memory;
public:
    Register() : memory(16, 0) {} // Use vector with initialization

    int getCell(int address) const {
        if (address < 0 || address >= memory.size()) {
            throw out_of_range("Register address out of bounds");
        }
        return memory[address];
    }

    void setCell(int address, int value) {
        if (address < 0 || address >= memory.size()) {
            throw out_of_range("Register address out of bounds");
        }
        memory[address] = value;
    }
    void resetRegister() {
     for(int i = 0 ; i < 16 ; ++i)
     memory[i] = 0 ;
   }
};

#endif //VOLEMACHINE_TOMY_REGISTER_H
