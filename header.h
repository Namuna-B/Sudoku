#ifndef HEADER_H
#define HEADER_H

#include <iostream> 
#include <fstream>  // library for file handling: read and write to file.
#include <stdexcept>// library for error handling.

const int G = 9;

class Sudoku {
private:
     // board has 9 cell each row and each column
    int** board; // Dynamic 2D array for the Sudoku board(but filled with anything)
        
    bool isCorrect(int row, int col, int num) const;
    bool findEmptyCell(int &row, int &col) const;

public:
    Sudoku(); // constructor
    ~Sudoku(); // destructor
    void loadFromFile(const std::string& filename);
    void printBoard() const;
    bool playSudoku();
    bool solveSudoku(int row, int col); 
};

#endif // SUDOKU_H

