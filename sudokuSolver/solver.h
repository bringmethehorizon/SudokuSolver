#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

extern int matrix[9][9];
void init();
void print_matrix();
int sudokuHelper(int puzzle[][9], int row, int column);
int solveSudoku(int puzzle[][9]);
bool isOk(int num, int x, int y);

#endif