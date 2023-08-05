//
// Created by nylon on 31.07.2023.
//

#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>


class InputReader {
public:
    InputReader();
    bool read();
    void run();
    ~InputReader();
private:
    char* input;
};


#endif //INPUTREADER_H
