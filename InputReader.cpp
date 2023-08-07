//
// Created by nylon on 31.07.2023.
//

#include "InputReader.h"
#include "bigint/BigInt.h"
#include "bigint/bigmath.h"
#include "primes/PrimeHandler.h"

InputReader::InputReader() {
    input = new char[2048];
}

InputReader::~InputReader() {
    delete[] input;
}

bool InputReader::read() {
    while (strcmp(input,"e")) {
        std::cin >> input;
        BigInt a(input);
        std::cin >> input;
        BigInt b(input);
        uint64_t c = atoll(input);
        std::cin >> input;
        switch (input[0]) {
            case '+':
                a += b;
                a.print();
                break;
            case '-':
                a -= b;
                a.print();
                break;
            case '*':
                a *= b;
                a.print();
                break;
            case '/':
                a /= b;
                a.print();
                break;
            case '%':
                a %= b;
                a.print();
                break;
            case 'r': {
                BigInt c = bm::random(a,b);
                c.print();
                break;
            }
            case 'v': {
                a /= c;
                a.print();
                break;
            }
            case 'c': {
                a *= c;
                a.print();
                break;
            }
            case 'x': {
                a %= c;
                a.print();
                break;
            }
            case '<':
                std::cout << (a < b) << std::endl;
                break;
            case '>':
                std::cout << (a > b) << std::endl;
                break;
            case '=':
                std::cout << (a == b) << std::endl;
                break;
            case 'a':
                bm::abs(a).print();
                break;
            case 'o': {
                BigInt prime = PrimeHandler::getPrime(c);
                prime.print();
                break;
            }
            case '^':
                bm::power(a, b).print();
                break;
            case 'e': { return false; }
            default:
                std::cout << "Unknown operation, numbers:\n", a.print(), b.print();
                break;
        }
    }

//    std::cout << "You have just written: " << input << std::endl;
    // ... command building and execution
    return true;
}

void InputReader::run() {
    while (!std::cin.eof())
        if (!read()) return;
}