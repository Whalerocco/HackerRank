#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &); // Declare a function to trim leading whitespaces
string rtrim(const string &); // Declare a function to trim trailing whitespaces
vector<string> split(const string &); // Declare a function to split a string

/*
 * Complete the 'diagonalDifference' function below.
 * It shall calc the sum of the two diagonals of a matrix and return abs(difference of the sums)
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY arr as parameter.
 */

int diagonalDifference(vector<vector<int>> arr) {
    int rows = arr.size(); // Can take size() of a vector, sizeof() is for arrays!
    int cols = arr[0].size();

    printf("Rows: %d, cols: %d \n", rows, cols);

    int i = 0; // Index of first diagonal (top left to bottom right)
    int sum1 = 0;
    int j = cols-1;
    int sum2 = 0;

    for(vector<int> row : arr){
        printf("Value of diagonal1 item nr %d: %d \n", i, row[i]);
        sum1 += row[i];
        printf("Value of diagonal2 item nr %d: %d\n", i, row[j]);
        sum2 += row[j];
        i++;
        j--;
    }

    return abs(sum1-sum2);
}

int main() 
{
    ofstream fout(getenv("OUTPUT_PATH"));  // Open an output file for writing results

    string n_temp;
    getline(cin, n_temp);  // Read input from the user

    int n = stoi(ltrim(rtrim(n_temp)));  // Convert and store 'n' as an integer

    vector<vector<int>> arr(n);  // Create a 2D vector to store the input array

    for (int i = 0; i < n; i++) {
        arr[i].resize(n);

        string arr_row_temp_temp;
        getline(cin, arr_row_temp_temp);  // Read a row of integers as a string

        vector<string> arr_row_temp = split(rtrim(arr_row_temp_temp));  // Split the row into individual numbers

        for (int j = 0; j < n; j++) {
            int arr_row_item = stoi(arr_row_temp[j]);  // Convert and store each number

            arr[i][j] = arr_row_item;  // Populate the 2D array 'arr' with the numbers
        }
    }

    int result = diagonalDifference(arr);  // Call the 'diagonalDifference' function

    fout << result << "\n";  // Write the result to the output file

    fout.close();  // Close the output file

    return 0;  // Return 0 to indicate successful program execution
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
