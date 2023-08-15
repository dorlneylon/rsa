//#pragma GCC optimize("O3")
//#pragma GCC optimize("avx2")
//#pragma GCC omp parallel for
#include "InputReader.h"
#include "bigint/BigInt.h"

int main() {
    InputReader reader;
    reader.run();
    return 0;
}