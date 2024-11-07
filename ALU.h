#include <iostream>
#include "Register.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bitset>


using namespace std;

#ifndef VOLEMACHINE_TOMY_ALU_H
#define VOLEMACHINE_TOMY_ALU_H


class ALU {
private:

  int binToDec(string bin){
    int dec = 0 ;
    int power = 0 ;
    for(int i = 7 ; i >= 0 ; --i){
      dec += (stoi(bin.substr(i,1)) * (pow(2,power)));
      power++;
    }
    return dec ;
  }

    string decToBin(int dec) {
      string bin = "00000000";
      for (int i = 7; i >= 0; --i) {
        bin[i] = (dec % 2) + '0';
        dec = dec / 2;
      }
      return bin;
    }

    float binToFlo(const string& bin) {
     int sign = bin[0] - '0';


    bitset<3> exponentBits(bin.substr(1, 3));
    int biasedExponent = (int)(exponentBits.to_ulong());
    int bias = 4;
    int exponent = biasedExponent - bias;


    bitset<4> mantissaBits(bin.substr(4, 4));
    float mantissa = 1.0; // 1 (normalized)


    for (int i = 0; i < 4; i++) {
        if (mantissaBits[i] == 1) {
            mantissa += pow(2, -(i + 1));
        }
    }


    float result = mantissa * pow(2, exponent);


    if (sign == 1) {
        result = -result;
    }

    return result;
}


   string floToBin(float num) {
    int sign ;

    if(num < 0){
      sign = 1 ;
    }
    else{
      sign = 0 ;
    }

    if (sign) {
        num = -num;
    }


    int exp = 0;


    while (num >= 2.0) {
        num /= 2.0;
        exp++;
    }
    while (num < 1.0) {
        num *= 2.0;
        exp--;
    }

    int b = 4;
    int bExp = exp + b;

    bitset<4> mantissaBits;
    num -= 1.0;

    for (int i = 0; i < 4; i++) {
        num *= 2.0;
        if (num >= 1.0) {
            mantissaBits[i] = 1;
            num -= 1.0;
        } else {
            mantissaBits[i] = 0;
        }
    }

    string result = to_string(sign) + bitset<3>(bExp).to_string() +  mantissaBits.to_string();
    return result;
}

public:
    int hexToDec(const string& h) const {

            return stoi(h, nullptr, 16);

    }

    string decToHex(int decimal) const {
        stringstream ss;
        ss << uppercase << setfill('0') << setw(2) << hex << (decimal & 0xFF);
        return ss.str();
    }



    bool isValid(const string& value) const {
        if (value.empty() || value.length() > 4) return false;
        return all_of(value.begin(), value.end(), [](char c) {
            return (c >= '0' && c <= '9') || (toupper(c) >= 'A' && toupper(c) <= 'F');
        });
    }

    void add(int idx1, int idx2, int idx3, Register& reg) {
        try {
            int result = reg.getCell(idx2) + reg.getCell(idx3);
            reg.setCell(idx1, result);
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid register index in ADD operation");
        }
    }

    void addFloating(int idx1, int idx2, int idx3, Register& reg) {
    try {

        string binS = decToBin(reg.getCell(idx2));
        string binT = decToBin(reg.getCell(idx3));


        float s_value = binToFlo(binS);
        float t_value = binToFlo(binT);


        float result = s_value + t_value;
        string resultBin = floToBin(result);


        reg.setCell(idx1, binToDec(resultBin));

    }
    catch (const exception& e) {
        throw runtime_error("Error in floating point addition" );
    }
}

    void bitwiseOR(int idx1, int idx2, int idx3 , Register& reg){
      string z ="00000000" ;
      string x , y ;
      x = decToBin(reg.getCell(idx2));
      y = decToBin(reg.getCell(idx3));
      for(int i = 7 ; i >= 0 ; --i){
        if(x[i] == '0' && y[i] == '0' )
          z[i] = '0';
        else
          z[i] = '1' ;
      }
       reg.setCell(idx1 , binToDec(z));
    }

    void bitwiseAND(int idx1, int idx2, int idx3 , Register& reg){
      string z ="00000000" ;
      string x , y ;
      x = decToBin(reg.getCell(idx2));
      y = decToBin(reg.getCell(idx3));
      for(int i = 7 ; i >= 0 ; --i){
        if(x[i] == '1' && y[i] == '1' )
          z[i] = '1';
        else
          z[i] = '0' ;
      }
      reg.setCell(idx1 , binToDec(z));
    }

    void bitwiseXOR(int idx1, int idx2, int idx3 , Register& reg){
      string z ="00000000" ;
      string x , y ;
      x = decToBin(reg.getCell(idx2));
      y = decToBin(reg.getCell(idx3));
      for(int i = 7 ; i >= 0 ; --i){
        if((x[i] == '1' && y[i] == '1') || ((x[i] == '0' && y[i] == '0')) ){
          z[i] = '0';
        }
        else{
         z[i] = '1' ;
        }
      }
      reg.setCell(idx1 , binToDec(z));
    }

    void rotateRight(int idxReg, int steps , Register& reg ) {
      string registerValue ;
      registerValue = decToBin(reg.getCell(idxReg));
      int l = registerValue.length();
      steps = steps % l;
      reg.setCell(idxReg , binToDec(registerValue.substr(l - steps) + registerValue.substr(0, l - steps)));
}

};


#endif //VOLEMACHINE_TOMY_ALU_H
