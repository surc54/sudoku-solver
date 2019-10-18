#include <stdio.h>
#include <stdlib.h>

void printSudokuTable(int sudoku[9][9]);
void setSudokuTableToNegativeOne(int sudoku[9][9]);
void setOneSquare(int sudoku[9][9], size_t x, size_t y, int value);
int checkHorizontal(int sudoku[9][9], size_t x, size_t y);
int doChecks(int sudoku[9][9], size_t x, size_t y);
int isSolved(int sudoku[9][9]);
int getHowManyEmptySquares(int sudoku[9][9]);

int solveNumberBased(int sudoku[9][9]);
int solveRowCandidacyBased(int sudoku[9][9]);
int solveColumnCandidacyBased(int sudoku[9][9]);
int solveBigBoxCandidacyBased(int sudoku[9][9]);


int main()
{
    int sudoku[9][9];
    setSudokuTableToNegativeOne(sudoku);

    printSudokuTable(sudoku);

    printf("\nFill the table:\n");

    for (int row = 0; row < 9; row++) {
        int col[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        printf("Enter data for row %d: ", row);
        for (int c = 0; c < 9; c++) {
            scanf("%d", &col[c]);
            setOneSquare(sudoku, c, row, (col[c] == 0 ? -1 : col[c]));
        }
    }
    getchar(); // gets rid of last enter

    /*setSudokuTableToNegativeOne(sudoku); // TEST CONDITIONS
    setOneSquare(sudoku, 2, 1, 2);
    setOneSquare(sudoku, 1, 2, 4);
    setOneSquare(sudoku, 2, 3, 1);
    setOneSquare(sudoku, 2, 4, 8);
    setOneSquare(sudoku, 1, 5, 6);
    setOneSquare(sudoku, 0, 6, 7);
    setOneSquare(sudoku, 0, 7, 6);
    setOneSquare(sudoku, 2, 6, 3);
    setOneSquare(sudoku, 2, 7, 5);
    setOneSquare(sudoku, 3, 1, 3);
    setOneSquare(sudoku, 5, 0, 9);
    setOneSquare(sudoku, 4, 2, 1);
    setOneSquare(sudoku, 5, 3, 8);
    setOneSquare(sudoku, 3, 5, 7);
    setOneSquare(sudoku, 4, 6, 5);
    setOneSquare(sudoku, 5, 7, 3);
    setOneSquare(sudoku, 3, 8, 2);
    setOneSquare(sudoku, 6, 1, 6);
    setOneSquare(sudoku, 6, 2, 3);
    setOneSquare(sudoku, 8, 1, 5);
    setOneSquare(sudoku, 8, 2, 2);
    setOneSquare(sudoku, 7, 3, 3);
    setOneSquare(sudoku, 6, 4, 1);
    setOneSquare(sudoku, 6, 5, 4);
    setOneSquare(sudoku, 7, 6, 4);
    setOneSquare(sudoku, 6, 7, 7);*/
    printSudokuTable(sudoku);
    printf("\nReady for solving. Press enter to continue.");

    getchar();


    for (int i = 0; i < 81 && isSolved(sudoku) == 0; i++)
    {
        solveNumberBased(sudoku);
        solveRowCandidacyBased(sudoku);
        solveColumnCandidacyBased(sudoku);
        solveBigBoxCandidacyBased(sudoku);
    }

    printSudokuTable(sudoku);
    getchar();

}


void setSudokuTableToNegativeOne(int sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sudoku[i][j] = -1;
        }
    }
}

void printSudokuTable(int sudoku[9][9])
{
    puts("\n  =============================================================================");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            //puts("\n     ##############################################################");
              puts("  ||=========================================================================||");
        }
        if (row != 0)
        {
            if (row % 3 != 0)
                printf("  ||-------|-------|-------||-------|-------|-------||-------|-------|-------||\n"); // columns in spacing
        }
        printf("  ||"); // FIRST ||, WHERE THE ROW NUMBER USED TO BE
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0 && col != 0) {
                if (col == 3) printf(" ||");
                else if (col == 6) printf(" ||");
            }
            int value = sudoku[row][col];
            printf("   %1c %s", (value == -1 ? ' ' : value + 48), (col % 3 != 0 && (col - 1) % 3 != 0 ? " " : "  |"));
        }
        printf(" ||");

        if (row == 3)
        {
            printf("\tSTATUS: %s", (isSolved(sudoku) == 1 ? "SOLVED" : "UNSOLVED"));
        }
        else if (row == 4)
        {
            printf("\tFILLED: %d / %d", (81 - getHowManyEmptySquares(sudoku)), 81);
        }

        puts("");
    }
    puts("  =============================================================================");
    //puts("   |----------------------------------------------------------------|");
}

// 1 = SOLVED   // 0 = UNSOLVED
int isSolved(int sudoku[9][9])
{
    return (getHowManyEmptySquares(sudoku) == 0 ? 1 : 0);
}

int getHowManyEmptySquares(int sudoku[9][9])
{
    int empty = 0;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku[row][col] == -1)
            {
                empty++;
            }
        }
    }
    return empty;
}

void setOneSquare(int sudoku[9][9], size_t x, size_t y, int value)
{
    sudoku[y][x] = value;
}

/*
1 = OK
0 = BAD
*/
int checkHorizontal(int sudoku[9][9], size_t x, size_t y)
{
    int value = sudoku[y][x];
    for (int i = 0; i < 9; i++)
    {
        if (i == x)
            continue;
        if (sudoku[y][i] == value)
            return 0;

    }
    return 1;
}

int checkVertical(int sudoku[9][9], size_t x, size_t y)
{
    int value = sudoku[y][x];
    for (int i = 0; i < 9; i++)
    {
        if (i == y)
            continue;
        if (sudoku[i][x] == value)
            return 0;
    }
    return 1;
}

int checkBox(int sudoku[9][9], size_t x, size_t y)
{
    int value = sudoku[y][x];
    int groupX = x / 3;
    int groupY = y / 3;

    for (int i = 3*groupY; i < 3*groupY + 3; i++)
    {
        for (int j = 3*groupX; j < 3*groupX + 3; j++)
        {
            if (i == y && j == x)
                continue;
            if (sudoku[i][j] == value)
                return 0;
        }
    }
    return 1;
}

int doChecks(int sudoku[9][9], size_t x, size_t y)
{
    if (checkHorizontal(sudoku, x, y) == 1 &&
            checkVertical(sudoku, x, y) == 1 &&
            checkBox(sudoku, x, y) == 1)
    {
        return 1;
    }
    else
        return 0;
}

int solveNumberBased(int sudoku[9][9])
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            int value = sudoku[y][x];
            if (value != -1)
                continue;

            int possibilities = 0;

            for (int k = 1; k < 10; k++)
            {
                int before = sudoku[y][x];
                sudoku[y][x] = k;

                if (doChecks(sudoku, x, y) == 1)
                {
                    ++possibilities;
                }
                else
                {
                    sudoku[y][x] = before;
                }
            }

            if (possibilities != 1)
            {
                sudoku[y][x] = -1;
            }
        }
    }
}

int solveRowCandidacyBased(int sudoku[9][9])
{
    for (int y = 0; y < 9; y++)
    {
        for (int k = 1; k < 10; k++)
        {
            int good[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

            int possibilities = 0;

            for (int x = 0; x < 9; x++)
            {
                int value = sudoku[y][x];
                if (value != -1)
                {
                    continue;
                }
                sudoku[y][x] = k;

                if (doChecks(sudoku, x, y) == 1)
                {
                    ++possibilities;
                    good[x] = k;
                }
                sudoku[y][x] = -1;
            }

            if (possibilities == 1)
            {
                for (int c = 0; c < 9; c++)
                {
                    if (good[c] != -1)
                    {
                        sudoku[y][c] = good[c];
                    }
                }
            }
        }
    }
}

int solveColumnCandidacyBased(int sudoku[9][9])
{
    for (int x = 0; x < 9; x++)
    {
        for (int k = 1; k < 10; k++)
        {

            int good[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

            int possibilities = 0;

            for (int y = 0; y < 9; y++)
            {
                int value = sudoku[y][x];
                if (value != -1)
                {
                    continue;
                }
                sudoku[y][x] = k;

                if (doChecks(sudoku, x, y) == 1)
                {
                    ++possibilities;
                    good[y] = k;
                }
                sudoku[y][x] = -1;
            }

            if (possibilities == 1)
            {
                for (int c = 0; c < 9; c++)
                {
                    if (good[c] != -1)
                    {
                        sudoku[c][x] = good[c];
                    }
                }
            }
        }
    }
}

int solveBigBoxCandidacyBased(int sudoku[9][9])
{
    for (int groupY = 0; groupY < 3; groupY++)
    {
        for (int groupX = 0; groupX < 3; groupX++)
        {
            for (int k = 1; k < 10; k++)
            {
                int goodX;
                int goodY;
                int possibilities = 0;
                for (int y = 3*groupY; y < 3*groupY + 3; y++)
                {
                    for (int x = 3*groupX; x < 3*groupX + 3; x++)
                    {
                        int value = sudoku[y][x];
                        if (value != -1)
                        {
                            continue;
                        }
                        sudoku[y][x] = k;

                        if (doChecks(sudoku, x, y) == 1)
                        {
                            ++possibilities;
                            goodY = y;
                            goodX = x;
                        }
                        sudoku[y][x] = -1;
                    }
                }
                if (possibilities == 1)
                {
                    sudoku[goodY][goodX] = k;
                }
            }
        }
    }
}
