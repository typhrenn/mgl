#pragma once

#include <cstdio>
#include <iostream>

#define PRINTVEC(x, fmt, size) {printf(fmt); for (int i = 0; i < size; i++) printf("%f ", x[i]); printf("\n");}
#define PRINTMAT(x, fmt, size) {printf(fmt);for (int i = 0; i < size; i++) {for (int j = 0; j < size; j++) {std::cout << x.columns[j][i] << "\t";}std::cout << std::endl;}}
