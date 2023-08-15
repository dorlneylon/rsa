//
// Created by nylon on 31.07.2023.
//

#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>
#include "structures/array.h"
#include "bigint/BigInt.h"
#include "structures/PasswordCollection.h"

class InputReader {
public:
    InputReader();
    bool read();
    void run();
    ~InputReader();
private:
    BigInt _N, _E, _D;
    array<char> input;
    PasswordCollection passwords;
};


#endif //INPUTREADER_H
