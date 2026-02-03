#include "header.h"

// Constructor
Sudoku::Sudoku() {
    board = new int*[G]; // allocating memory we need
    for (int i = 0; i < G; ++i) {
        board[i] = new int[G];// we allocate memory for both row and column separately.
        for (int j = 0; j < G; ++j) {
            board[i][j] = 0;// fill the every cell by 0.
        }
    }
}

// Destructor: 
Sudoku::~Sudoku() {
    for (int i = 0; i < G; ++i) { // deallocate(free) the memory
        delete[] board[i];
    }
    delete[] board;
}

// Load the Sudoku puzzle from a file to a board
void Sudoku::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Error occured to open file.");
    }

    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < G; ++j) {
            inFile >> board[i][j]; // copy from file to board
            if (inFile.fail()) {
                throw std::runtime_error("Invalid input in file.");
            }
        }
    }
    inFile.close();// close the file.
}

// print sudoku board
void Sudoku::printBoard() const {
        std::cout << "\t<================================================================================>" << std::endl;
        std::cout << "\t|                        WELCOME TO SUDOKU Game!                                 |" << std::endl;
        std::cout << "\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << std::endl;
        std::cout << "\t<================================================================================>" << std::endl;

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            if(j == 3 || j == 6){
                std::cout << " | ";
            }
            std::cout << board[i][j] << " ";
        }
        if(i == 2 || i == 5){
            std::cout << std::endl;
            for(int k = 0; k < G; k++){
                std::cout << "---";
            }
        }
        std::cout << std::endl;
    }
}

// Find an empty cell in the Sudoku board
bool Sudoku::findEmptyCell(int &row, int &col) const { 

    for (row = 0; row < G; ++row) {
        for (col = 0; col < G; ++col) {
            if (board[row][col] == 0) { //find the value 0 which is an empty space
                return true;
            }
        }
    }
    return false;
}

// Check if a entered number from user is correct or not
bool Sudoku::isCorrect(int row, int col, int num) const {

    for(int i = 0; i < G; i++){
        if(board[row][i] == num){
            return false;
        }
    }

    for(int i = 0; i < G; i++){
        if(board[i][col] == num){
            return false;
        }
    }

    int subRow = row - row % 3;
    int subCol = col - col % 3;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i + subRow][j + subCol] == num){
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solveSudoku(int row, int col){ // program will solve sudoku here
    //If all cells are filled, the sudoku is solved
    if( row == G - 1 && col == G){
        return true;
    }

    //move the next row if the current column is G
    if(col == G){
        row++;
        col = 0;
    }

    //skip the cells that have a value
    if(board[row][col] != 0){
        return solveSudoku( row, col +1);
    }

    // filling the current cell with the numbers 1 to 9
    for(int number = 1; number <= 9; number++){
        if(isCorrect(row, col, number)){
            board[row][col] = number;

            if(solveSudoku(row, col +1)){
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

// Solve the Sudoku puzzle using backtracking
bool Sudoku::playSudoku() { // user will solve sudoku here
    
    int row, col, num;

    while(true){
        Sudoku::printBoard();
        std::cout << "Not easy to solve? Enter minus number as row, column, and number to see the solved sudoku"<<std::endl;
        std::cout << "Enter row value: ";
        std::cin >> row;
        std::cout << "Enter column value: ";
        std::cin >> col;
        std::cout << "Enter the number value: ";
        std::cin >> num;
        std::cout << std::endl;

        if(row < 0 || col < 0 || num < 0){
            solveSudoku(0, 0);
            printBoard();
            std::cout << std::endl;
            std::cout << "Good luck next time!" << std::endl;
            break; 
        }

        if(row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9){
            std::cout << "Invalid input. enter numbers on each: row/column/value -> 1 to 9" << std::endl;
            continue; 
        }
        

        row--;
        col--;

        if(board[row][col] != 0){
            std::cout << "Cell is already filled. Try another cell. " << std::endl;
            continue; 
        }

        if(!isCorrect(row, col, num)){
            std::cout<<"Invalid move. Try again! " << std::endl;
            continue;
        } 

        board[row][col] = num;     

        if(!findEmptyCell(row, col)){
            break;
        }
    }

    bool solved = true;
       for(int i = 0; i < G; i++){
           for(int j = 0; j < G; j++){
               if(board[i][j] == 0){
                   solved = false;
                   break;
               }
           }
       }    

    if(solved) {
        std::cout << "Congratulations. you successfully solved the sudoku." << std::endl;
        printBoard();
    } else {
        std::cout << "Puzzle not solved." << std::endl; 
    }
    return true;
}