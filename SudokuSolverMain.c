#include<stdio.h>
#include<stdlib.h>

// Board Matrix 
int board[9][9];


void printBoard(){
    int i,j;
    for(i=0; i<9; i++){

        if(i % 3 == 0 && i != 0 ){
                printf("---------------------------\n");        // For horizontal lines
        }


        for(j=0; j<9; j++){
            
            if(j % 3 == 0 && j != 0 ){          // As we need vertical lines 
                printf(" | ");
            }
            printf("%d ", board[i][j]);
        }

        
        printf("\n");
    }
}



void getBoardData(){

    // Get sudoku matrix from th user.  
            
    printf("Enter the sudoku puzzle\n use '0' to indicate empty element\n");
    printf("A to I indicates the columns\n");
    printf("ABCDEFGHI\n");
    int row;
    int i;
    int br=0, bc; // Board row and column indexes 
    for(i=0;i<9;i++){

        
        bc=8;  // start from last column 

        scanf("%d", &row);

        // Split row elements.
        while(row != 0){
            board[br][bc] = row % 10;  // last bit.
            row /= 10;
            bc--;
        }
        br++;
    }
}





int isSafe(int row, int col, int number){
    int i;
    for(i=0; i<9; i++){
        // check for row and column 
        if(board[row][i] == number || board[i][col] == number){
            return 0;
        }

        // Check in the same 3*3 matrix..
        if(board[3*(row/3) + i/3][3*(col/3) + i%3] == number){
            return 0;
        }
    } 

    return 1;
}




int solve(){
    int n = 9;
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            
            // Find empty cell 
            if(board[row][col] == 0){
                int val;
                for(val=0; val<=9; val++){
                    if(isSafe(row, col, val)){
                        board[row][col] = val;

                        // Recursive call
                        if(solve()){
                            return 1;
                        } else{
                            // No futher solution found,, therefore backtracking.
                            board[row][col] = 0;
                        } 
                    }
                }

                return 0;
            }
        }
    }
    return 1; // Solution found
}



void main(){

     // Driver code
    int exit = 0;
    while(exit!=1){
        
        
        printf("[1] Generate solution for sodoku puzzle\n");
        printf("[2] Exit\n");
        printf("Enter a choice: ");
        int choice;
        scanf("%d", &choice);
        
        // Check user input..
        if(choice == 1){

            getBoardData();
            printf("You have entered:\n");
            printBoard();
            solve();
            printf("\nSolution\n");
            printBoard();
        }
        else if(choice==2)
        {
            exit = 1;
            
        }
        else
        {
            printf("Invalid input!\n");
        }
    }   
}