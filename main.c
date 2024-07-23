#include <stdio.h>
#include <stdlib.h>

int printBoard(int [9][9]);
char* getRow();
void manual_sudoku(int [9][9]);
void generate_sudoku(int [9][9]);
int sudoku_solver(int [9][9], int, int);
int is_valid(int [9][9],int ,int ,int );

int main(int argc, char **argv){
    
    int array[9][9] = {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        };
    int result;
    char question;
    printf("Do you want to enter a sudoku manually? Saying no will generate one. (Y/N) ");
    scanf(" %c",&question);
    getchar();

    if (question == 'Y')
    {
        manual_sudoku(array);
    }
    else if (question == 'N')
    {
        generate_sudoku(array);
    }
    else{
        printf("Not valid");
    }

    result = sudoku_solver(array, 0, 0);
    if (result == 1)
    {
        printBoard(array);
    }
    else{
        printf("Invalid config");
    }
    
    
    return 0;
}

char* getRow(){
    static char numList[20];
    printf(": ");
    fgets(numList, sizeof(numList), stdin);
    return numList;

}


int printBoard(int array[9][9]){
    
    int i, j;
    for (i = 0; i < 9; i++)
    {
        printf("\n");
        if ((i)%3 == 0){
                printf(" ___________________________________");
                printf("\n");
            }

        for (j = 0; j < 9; j++){
            if ((j)%3 == 0){printf(" | ");}

            printf(" %d ", array[i][j]);
        }
        printf("|");
        
    } 
    printf("\n");
    printf(" ___________________________________"); 
    printf("\n\n");

    return 0;
}


void manual_sudoku(int array[9][9]){
    char *numbers;
    int i, j;
    printf("Enter your sudoku row by row in the format:\n: 1,2,3,4,5,6,7,8,9 (put 0 if empty)\n\n");

    for (i = 0; i < 9; i++){
        numbers = getRow();
        for (j = 0; j < 18; j++)
        {
            array[i][j/2] = numbers[j]-48;
            j++;
        }
    }
}


void generate_sudoku(int array[9][9]){
    printf("Implementation pending");
}

int sudoku_solver(int array[9][9], int r, int c){
    int i;
    if (r == 9)
    {
        return 1;
    }
    else if (c == 9)
    {
        return sudoku_solver(array, r+1, 0);
    }
    else if (array[r][c] != 0)
    {
        return sudoku_solver(array, r, c+1);
    }
    else{
        for (i = 1; i < 10; i++)
        {
            if (is_valid(array, r, c, i))
            {
                array[r][c] = i;
                if (sudoku_solver(array, r, c+1))
                {
                    return 1;
                }
                array[r][c] = 0;
            }
            
        }
        return 0;
    }
    
    
    

}

/*returns 0 if not valid*/
int is_valid(int array[9][9], int row, int column, int number){ 

    int i, r, c;
    for (i = 0; i < 9; i++){
        if (number == array[row][i]){
            return 0;
        }  
    }

    for (i = 0; i < 9; i++){
        if (number == array[i][column]){
            return 0;
        }  
    }

    row = row - row % 3;
    column = column - column % 3;
    for (r = 0; r < 3; r++){
        for (c = 0; c < 3; c++){
            if (number == array[r + row][c + column]){
                return 0;
            } 
        }
    }
    return 1;
}