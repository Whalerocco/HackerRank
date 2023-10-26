#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */

// https://www.hackerrank.com/challenges/matrix-rotation-algo/problem?isFullScreen=true
// Rotate matrix anti-clockwise
void matrixRotation(vector<vector<int>> matrix, int r) {
    // "constants"
    int rows = matrix.size();
    int cols = matrix[0].size();
    int nrOuterElements = 2*rows+(2*(cols-2));
    int nrRotations;

    // Variables
    int elementToMove = 0;  // The value of the element that is moved
    int startRow = 0;       // Start row of the loop
    int startCol = 0;       // Start col of the loop
    int endRow = 0;         // End row of the loop
    int endCol = 0;         // End col of the loop
    int currentNrRows = 0;
    int currentNrCols = 0;
    int rr = 0;             // row index, indicates to where to move the element
    int cc = 0;             // col index, indicates to where to move the element
    int rr_old = 0;         // Used to know from where to move the element
    int cc_old = 0;         // Used to know from where to move the element
    int n = 0;              // nr of steps taken in the loop around the matrix

    vector<vector<int>> mirrorMatrix; // TempMatrix of same size as matrix
    vector<vector<int>> outputMatrix; // TempMatrix of same size as matrix
    outputMatrix = matrix;

    startRow = 0;
    startCol = 0;
    endRow = rows;
    endCol = cols;
    currentNrRows = endRow-startRow;
    currentNrCols = endCol-startCol;
    int layer = 0;

    while(currentNrRows > 1 && currentNrCols > 1) // Have gone through all the elements in the matrix when this is not true. Rotate one layer at a time
    {
        layer++;
        printf("\n\nLayer: %d", layer);
        nrOuterElements = 2*currentNrRows+(2*(currentNrCols-2)); // Total elements in a loop in the matrix
        nrRotations = r % nrOuterElements; //If r == 17, the result will be the same if the matrix is rotated 1 time if there are 16 outer elements
        printf("\nNrRotations (for layer): %d", nrRotations);
        
        currentNrRows = endRow-startRow;
        currentNrCols = endCol-startCol;

        // Move each element nrRotations times
        for(int rotation = 0; rotation < nrRotations; rotation++)
        {
            rr = 0;     // row index, indicates to where to move the element
            cc = 0;     // col index, indicates to where to move the element
            rr_old = 0; // Used to know from where to move the element
            cc_old = 0; // Used to know from where to move the element
            n = 0;      // nr of steps taken in the loop around the matrix
            mirrorMatrix = outputMatrix;
            printf("\n\nRotation nr: %d", rotation);

            while(n < nrOuterElements) // For doing a lap around the matrix, for example the inner most lap or the outer most lap
            {
                printf("\nElement nr (counter clockwise): %d", n);
                rr_old = rr;
                cc_old = cc;

                if((startCol + cc) == startCol) // Left-most column
                {
                    if((startRow + rr) == endRow-1)
                    {
                        cc++;
                    }
                    else
                    {
                        rr++;
                    }
                    
                }
                else if((startRow + rr) == endRow-1) // Bottom row in loop
                {   
                    if((startCol + cc) == endCol-1)
                    {
                        rr--;
                    }
                    else
                    {
                        cc++;
                    }
                    
                }
                else if((startCol + cc) == endCol-1) //Right-most column
                {
                    if((startRow + rr) == startRow)
                    {
                        cc--;
                    }
                    else
                    {
                        rr--;
                    }
                }
                else if((startRow + rr) == startRow) // Top row in loop
                {
                    cc--;
                }
                
                printf("\nrr: %d, cc: %d", rr,cc);
                elementToMove = mirrorMatrix[startRow+rr_old][startCol+cc_old];   
                outputMatrix[startRow+rr][startCol+cc] = elementToMove;
                n++; // Keeps track of the amount of loops done
            }  
        }

        // Update dimension parameters
        startRow++;
        endRow--;
        startCol++;
        endCol--;
        currentNrRows = endRow-startRow;
        currentNrCols = endCol-startCol;
    }

    printf("\n");

    for(vector<int> row: outputMatrix){
        for(int element : row){
            printf("%d ", element);
        }
        printf("\n");
    }

}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
