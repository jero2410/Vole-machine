#include "Register.h"
#include "Memory.h"
#include "CU.h"
#include "ALU.h"
#include <vector>
#include <sstream>
#include <unordered_map>

#ifndef VOLEMACHINE_TOMY_CPU_H
#define VOLEMACHINE_TOMY_CPU_H

class CPU {
private:
    int programCounter;
    string instructionRegister;
    ALU alu;
    CU cu;
    string opcode;
    int operand1, operand2, operand3, addr;

public:
    CPU() : programCounter(16), operand1(0), operand2(0), operand3(0), addr(0) {}

    void runNextStep(Memory& m, Register& registers) {
        try {
            fetch(m);
            decode();
            execute(registers, m);
        } catch (const runtime_error& e) {
            if (string(e.what()) == "HALT") {
                throw;
            }
            cout << "Error during execution: " << e.what() << endl;
        }
    }



    void outputState(const Register& registers) const {
        cout << "\nCPU State:" << endl;
        cout << "Program Counter: " << alu.decToHex(programCounter) << endl;
        cout << "Instruction Register: " << instructionRegister << endl;

        cout << "\nRegister State:" << endl;
        for (int i = 0; i < 16; i++) {
            cout << "R" << hex << uppercase << i << ": "
                 << alu.decToHex(registers.getCell(i)) << dec << endl;
        }
        cout <<  endl ;
    }


    void setPC(int pc){
      programCounter = pc ;
    }
    string getIR(){
      return instructionRegister ;
    }

    void resetCPU(Register& registers){
      registers.resetRegister();
      programCounter = 0 ;
      instructionRegister = "" ;
      cout << "CPU reseted successfully" << endl ;
      cout << endl ;
    }

private:
    void fetch(Memory& m) {
        if (programCounter >= 255) {
            throw runtime_error("Program counter out of bounds");
        }
        instructionRegister = alu.decToHex(m.getCell(programCounter)) +
                             alu.decToHex(m.getCell(programCounter + 1));
        programCounter += 2;
    }

    void decode() {
        if (instructionRegister.length() != 4) {
            throw runtime_error("Invalid instruction length");
        }

        opcode = instructionRegister.substr(0, 1);


        if (opcode == "1" || opcode == "2" || opcode == "3" || opcode == "B" || opcode == "D") {
            operand1 = alu.hexToDec(instructionRegister.substr(1, 1));
            addr = alu.hexToDec(instructionRegister.substr(2, 2));
        }
        else if (opcode == "4") {
            operand1 = alu.hexToDec(instructionRegister.substr(1, 1));
            operand2 = alu.hexToDec(instructionRegister.substr(2, 1));
        }
        else if (opcode == "5" || opcode == "6" || opcode == "7" || opcode == "8" || opcode == "9") {
            operand1 = alu.hexToDec(instructionRegister.substr(1, 1)); //R
            operand2 = alu.hexToDec(instructionRegister.substr(2, 1)); //S
            operand3 = alu.hexToDec(instructionRegister.substr(3, 1)); //T
        }
        else if (opcode == "A") {
            operand1 = alu.hexToDec(instructionRegister.substr(1, 1));
            operand2 = alu.hexToDec(instructionRegister.substr(3, 1));
        }
        else if(opcode == "C"){
            cout << "Program ended" << endl ;
        }
        else if (opcode != "C") {
            throw runtime_error("Invalid opcode: " + opcode);
        }

    }

    void execute(Register& reg, Memory& mem) {
        if (opcode == "1")
        {
            cu.load(operand1, addr, reg, mem);
        }
        else if (opcode == "2")
        {
            cu.load(operand1, addr, reg);
        }
        else if (opcode == "3")
        {
            cu.store(operand1, addr, reg, mem);
        }
        else if (opcode == "4")
        {
            cu.move(operand1, operand2, reg);
        }
        else if (opcode == "5")
        {
            alu.add(operand1, operand2, operand3, reg);
        }
        else if (opcode == "6")
        {
            alu.addFloating(operand1, operand2, operand3, reg);
        }
        else if (opcode == "7")
        {
            alu.bitwiseOR(operand1, operand2, operand3, reg);
        }
        else if (opcode == "8")
        {
            alu.bitwiseAND(operand1, operand2, operand3, reg);
        }
        else if (opcode == "9")
        {
            alu.bitwiseXOR(operand1, operand2, operand3, reg);
        }
        else if (opcode == "A")
        {
            alu.rotateRight(operand1, operand2, reg);
        }
        else if (opcode == "B")
        {
            cu.jump(operand1, addr, reg, programCounter);
        }
        else if (opcode == "C")
        {
            cu.halt();
        }
        else if (opcode == "D")
        {
            cu.jump2(operand1, addr, reg, programCounter);
        }
    }

};



#endif
