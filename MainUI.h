//
// Created by Admin on 10/26/2024.
//
#ifndef VOLEMACHINE_TOMY_MAINUI_H
#define VOLEMACHINE_TOMY_MAINUI_H

#include "Machine.h"

class MainUI {
private:
    Machine machine;

public:
    void DisplayMenu() const {
        cout << "\VOLE Machine Menu:" << endl
             << "1) Load file of instructions" << endl
             << "2) Enter only one instruction" << endl
             << "3) Display machine state" << endl
             << "4) Execute next instruction (FDE one cycle)" << endl
             << "5) Execute the whole program" << endl
             << "6) Reset RAM" << endl
             << "7) Reset CPU" << endl
             << "8) Exit" << endl
             << "Choose an option: ";
    }

    void run() {
        while (true) {
            DisplayMenu();
            string input;
            getline(cin, input);
            switch (input[0]) {
                case '1': {
                    cout << "Enter the program file name: ";
                    getline(cin, input);
                    machine.loadProgramFile(input);
                    break;
                }
                case '2': {
                    cout << "Enter instruction (4 hex digits): ";
                    getline(cin, input);
                    machine.enterInstruction(input);
                    break;
                }
                case '3': {
                    machine.outputState();
                    break;
                }
                case '4': {
                    machine.FDEcycle();
                    break;
                }
                case '5': {
                    machine.completeFDE();
                    break;
                }
                case '6': {
                    machine.resetRAM();
                    break;
                }
                case '7': {
                    machine.resetCPU();
                    break;
                }
                case '8': {
                    cout << "Bye bye ya user ya habibi" << endl ;
                    cout << "Exiting program." << endl;
                    return;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }

        }
    }
};

#endif //VOLEMACHINE_TOMY_MAINUI_H
