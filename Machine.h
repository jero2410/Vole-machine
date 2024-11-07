//
// Created by Admin on 10/26/2024.
//

#ifndef VOLEMACHINE_TOMY_MACHINE_H
#define VOLEMACHINE_TOMY_MACHINE_H
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "ALU.h"
#include "CPU.h"
#include "Memory.h"

class Machine {
private:
    CPU processor;
    Memory memory;
    Register registers;
    ALU alu;
    int address;
    vector<char> screen ;

public:
    Machine() : address(16) {}



    void loadProgramFile(const string& fileName) {
        string startLoad ;
        cout << "Enter start location in memory of loading in hex: " ;
        getline(cin , startLoad);
        address = alu.hexToDec(startLoad);
        processor.setPC(alu.hexToDec(startLoad));
        ifstream file(fileName);
        if (!file) {
            throw runtime_error("Could not open file: " + fileName);
        }

        string line;
        while (getline(file, line)) {
            if (address >= 256) {
                throw runtime_error("Program file exceeds memory capacity");
            }

            // Remove whitespace and validate line
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

            if (line.length() != 4 || !alu.isValid(line)) {
                throw runtime_error("Invalid instruction format: " + line);
            }

            try {
                memory.setCell(address++, alu.hexToDec(line.substr(0, 2)));
                memory.setCell(address++, alu.hexToDec(line.substr(2, 2)));
            } catch (const exception& e) {
                throw runtime_error("Error loading instruction: " + line);
            }
        }

        cout << "Program loaded successfully into memory." << endl;
        cout << endl ;
    }

    void enterInstruction(const string& instruction) {
        if (address >= 256) {
            throw runtime_error("Memory capacity exceeded");
        }

        if (instruction.length() != 4 || !alu.isValid(instruction)) {
            throw runtime_error("Invalid instruction format");
        }

        try {
            memory.setCell(address++, alu.hexToDec(instruction.substr(0, 2)));
            memory.setCell(address++, alu.hexToDec(instruction.substr(2, 2)));
        } catch (const exception& e) {
            throw runtime_error("Error storing instruction: " + string(e.what()));
        }
    }

    void outputState() const {
        cout << "\nMachine State:" << endl;
        cout << "Memory Contents:" << endl;
        for (int i = 0; i < 256; i += 1) {

                cout << alu.decToHex(i) << ": "
                     << alu.decToHex(memory.getCell(i)) << endl ;

        }
        processor.outputState(registers);
    }

    void FDEcycle() {
        try {
            processor.runNextStep(memory, registers);
            cout << "\nMachine State:" << endl;
            cout << "Memory Contents:" << endl;
            for (int i = 0; i < 256; i += 1) {
            cout << alu.decToHex(i) << ": "
                 << alu.decToHex(memory.getCell(i)) << endl ;
            }
               processor.outputState(registers);


        }
        catch (const runtime_error& e) {
            if (string(e.what()) == "HALT") {
                cout << "Program halted normally." << endl;
                cout << "\nMachine State:" << endl;
                cout << "Memory Contents:" << endl;
                for (int i = 0; i < 256; i += 1) {
                cout << alu.decToHex(i) << ": "
                     << alu.decToHex(memory.getCell(i)) << endl ;
                }
               processor.outputState(registers);
            }
            cout << "Halted normally" << endl;
            cout << endl ;
        }
    }
   void completeFDE(){

      while(processor.getIR() != "C000" && processor.getIR()!= "0000"){
          try {
            processor.runNextStep(memory, registers);
          }
          catch (const runtime_error& e) {
            if (string(e.what()) == "HALT") {
                cout << "Program halted normally" << endl;
            }
          }
        }
      cout << "\nMachine State:" << endl;
      cout << "Memory Contents:" << endl;
      for (int i = 0; i < 256; i += 1) {
          cout << alu.decToHex(i) << ": "
                 << alu.decToHex(memory.getCell(i)) << endl ;
            }
               processor.outputState(registers);
               cout << "Program halted normally." << endl;
               cout << endl ;
   }
   void resetRAM() {
     memory.resetRAM();
   }
   void resetCPU() {
      processor.resetCPU(registers);
   }
};


#endif //VOLEMACHINE_TOMY_MACHINE_H
