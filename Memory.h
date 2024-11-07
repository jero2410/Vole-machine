//
// Created by Admin on 10/26/2024.
//

#ifndef VOLEMACHINE_TOMY_MEMORY_H
#define VOLEMACHINE_TOMY_MEMORY_H

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

class Memory {
private:
    vector<int> memory;
public:
    Memory() : memory(256, 0) {} // Use vector with initialization

    int getCell(int address) const {
        if (address < 0 || address >= memory.size()) {
            throw out_of_range("Memory address out of bounds");
        }
        return memory[address];
    }

    void setCell(int address, int value) {
        if (address < 0 || address >= memory.size()) {
            throw out_of_range("Memory address out of bounds");
        }
        memory[address] = value;
    }
    void resetRAM() {
      for(int i = 0 ; i < 256 ; ++i){
      memory[i] = 0 ;
      }
      cout << "RAM reseted successfully" << endl ;
      cout << endl ;
   }
};



#endif
