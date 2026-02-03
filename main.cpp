#include <iostream>
#include "header.h"
using namespace std;

int main() {
    try {
        std::cout << "\t<================================================================================>" << std::endl;
        std::cout << "\t|                        WELCOME TO SUDOKU Game!                                 |" << std::endl;
        std::cout << "\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << std::endl;
        std::cout << "\t<================================================================================>" << std::endl;
                
        Sudoku game;
        
        while (true) {

            int choice;
            std::cout << std::endl << std::endl;
            std::cout << "\t\t[1] Start the game" << std::endl;
            std::cout << "\t\t[2] Unable to solve? View the solved Sudoku" << std::endl;
            std::cout << "\t\t[3] Exit" << std::endl;
            std::cout << "\t\tEnter your choice: ";
            std::cin >> choice;
            
            switch(choice){
                case 1: 
                    game.loadFromFile("sudoku.txt");        
                    std::cout << "Loaded Sudoku puzzle:" << std::endl;
                    game.playSudoku();
                    break;

                case 2: 
                    game.loadFromFile("sudoku.txt");
                    if(game.solveSudoku(0, 0)){
                            std::cout << "Solved Sudoku is : " << std::endl;
                            game.printBoard();
                            std::cout << std::endl;
                            std::cout << "Better luck next time!!!" << std::endl;
                        } else {
                            std::cout << "No solution found! " << std::endl;
                        }
                        break;
                case 3: 
                    exit(0);
                default: std::cout<<"Invalid choice! " << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; 
    }
    return 0;
}