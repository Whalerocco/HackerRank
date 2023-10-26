#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

// If AM (12:00-11:59) -> mod 12h
// If PM (12:00-11:59 (23:59)) -> if > 12, do nothing, else add 12

string timeConversion(string s) {
    int int_10 = (s[0]-'0')*10;
    int int_0 = (s[1]-'0');
    int timeInput = int_10 + int_0;
    // printf("TimeInput: %d", timeInput);

    char amPmIndicator = s[8];
    printf("%c", amPmIndicator);

    int timeOutput = 0;
    string s_out(8, '0');

    for(int i = 2; i < 8; i++)
    {
        s_out[i] = s[i];
    }

    if(amPmIndicator == 'A') // AM
    {
        timeOutput = timeInput%12;
    }
    else // PM
    {
        if(timeInput == 12)
        {
            timeOutput = timeInput;
        }
        else
        {
            timeOutput = timeInput + 12;
        }
    }
    // printf("TimeOutput: %d", timeOutput);
    char firstDigit = timeOutput/10 + '0';
    char secondDigit = timeOutput%10 + '0';
    s_out[0] = firstDigit;
    s_out[1] = secondDigit;

    return s_out;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
