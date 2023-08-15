//
// Created by nylon on 31.07.2023.
//

#include "InputReader.h"
#include "bigint/BigInt.h"
#include "db/DBCore.h"
#include "bigint/bigmath.h"
#include "primes/PrimeHandler.h"

std::ostream &operator<<(std::ostream &output, const BigInt &n) {
    n.print(output);
    return output;
}

std::istream &operator>>(std::istream &input, array<char>& arr) {
    if (arr.getSize()) arr.clear();
    char c;
    while (input.get(c) && c != '\n') arr.pb(c);
    return input;
}

InputReader::InputReader() {
//    input.resize(1024);
}

InputReader::~InputReader() {}

bool InputReader::read() {
    // connect to postgresql
    DBCore db;
    passwords.setKeys(_N, _E, _D);
    db.connect();
    return 0;
}

//bool InputReader::read() {
//    std::cout << "Would you prefer to generate new open and closed keys? [y/n]: ";
//    std::cin >> input;
//    if (input[0] == 'y') {
//        std::cout << "\nEnter the number of bits in the key (it's recommended to have >= 1024): ";
//        std::cin >> input;
//        uint64_t bits = atoll(input.getPointer());
//        std::cout << "\nStarting the algorithm, it might take a while...\n";
//        BigInt p = PrimeHandler::getPrime(bits);
//        BigInt q = PrimeHandler::getPrime(bits-100);
//        BigInt n = p*q;
//        BigInt phi = (p-BigInt("1"))*(q-BigInt("1"));
//        std::cout << "\nGenerated p: " << p << "\nGenerated q: " << q << "\nn: "
//                  << n << "\nEuler's function: " << phi << "\n";
//        BigInt d,y,e = BigInt("2");
//        for (; bm::gcdex(e,phi,d,y) != BigInt("1"); e+=BigInt("1")) {}
//        d = (d % phi + phi) % phi;
//        std::cout << "(" << e << "," << n << ") - open key\n";
//        std::cout << "(" << d << "," << n << ") - closed key\n";
//        std::cout << "Considering you've changed pairs, old passwords are not valid anymore";
//        _N = n;
//        _D = d;
//        _E = e;
//    } else {
//        _N = BigInt("1000000007");
//        _E = BigInt("19");
//        _D = BigInt("157894738");
//    }
//    do {
//        std::cout << "\nWould you prefer to enter another password, quit or see the list of availables? [e/d/q]: ";
//        std::cin >> input;
//        switch (input[0]) {
//            case 'e': {
////                std::cout << "\nEnter the open key: ";
////                std::cin >> input;
////                BigInt e(input.getPointer());
////                std::cin >> input;
////                BigInt n(input.getPointer());
//                std::cout << "\nEnter the password: ";
//                std::cin >> input;
//                BigInt m(input.getPointer());
//                std::cout << "\nEncrypted password: " << bm::powmod(m,_E,_N) << "\n";
//                break;
//            }
//            case 'd': {
////                std::cout << "\nEnter the closed key: ";
////                std::cin >> input;
////                BigInt d(input.getPointer());
////                std::cin >> input;
////                BigInt n(input.getPointer());
//                std::cout << "\nEnter the encrypted password: ";
//                std::cin >> input;
//                BigInt c(input.getPointer());
//                std::cout << "\nDecrypted password: " << bm::powmod(c,_D,_N) << "\n";
//                break;
//            }
//            default:
//                std::cout << "\nInvalid input\n";
//                break;
//        }
//    } while (input[0] != 'q');
//    return true;
//}

//bool InputReader::read() {
//    do {
//        std::cin >> input;
//        BigInt a(input.getPointer());
//        std::cin >> input;
//        BigInt b(input.getPointer());
//        uint64_t c = atoll(input.getPointer());
//        std::cin >> input;
//        switch (input[0]) {
//            case '+':
//                a += b;
//                a.print();
//                break;
//            case '-':
//                a -= b;
//                a.print();
//                break;
//            case '*':
//                a *= b;
//                a.print();
//                break;
//            case '/':
//                a /= b;
//                a.print();
//                break;
//            case '%':
//                a %= b;
//                a.print();
//                break;
//            case 'r': {
//                BigInt c = bm::random(a,b);
//                c.print();
//                break;
//            }
//            case 'v': {
//                a /= c;
//                a.print();
//                break;
//            }
//            case 'c': {
//                a *= c;
//                a.print();
//                break;
//            }
//            case 'x': {
//                a %= c;
//                a.print();
//                break;
//            }
//            case '<':
//                std::cout << (a < b) << std::endl;
//                break;
//            case '>':
//                std::cout << (a > b) << std::endl;
//                break;
//            case '=':
//                std::cout << (a == b) << std::endl;
//                break;
//            case 'a':
//                bm::abs(a).print();
//                break;
//            case 'o': {
//                BigInt prime = PrimeHandler::getPrime(c);
//                prime.print();
//                break;
//            }
//            case '^':
//                bm::power(a, b).print();
//                break;
//            case 'e': { return false; }
//            default:
//                std::cout << "Unknown operation, numbers:\n", a.print(), b.print();
//                break;
//        }
//    } while (input[0] != 'q');
////    std::cout << "You have just written: " << input << std::endl;
//    // ... command building and execution
//    return true;
//}

void InputReader::run() {
    while (!std::cin.eof())
        if (!read()) return;
}