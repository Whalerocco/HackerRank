#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/* https://www.hackerrank.com/challenges/day-of-the-programmer/
 * Complete the 'dayOfProgrammer' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER year as parameter.
 */

// Output the date of the day of the programmer (DOTP) for a given year
string dayOfProgrammer(int year) {
    const int DAY_OF_THE_PROGRAMMER_IN_DAYS = 256;
    const int FIRST_EIGHT_MONTHS_IN_DAYS = 243;
    int normalDOTPInSeptember = DAY_OF_THE_PROGRAMMER_IN_DAYS - FIRST_EIGHT_MONTHS_IN_DAYS;
    int leapDay = 0; // 1 day must be removed in the final date for leap day
    const int OFFSET_FOR_1918 = 13; // 13 days less in february in 1918, add 13 days to the final date
    int daysInSeptember = 0;

    if(year < 1919) // Julian calender
    {
        if(year%4 == 0)
        {
            leapDay = 1;
        }
    }
    else            // Gregorian calender
    {
        if(((year%4 == 0) && (year%100 > 0)) || (year%400 == 0))
        {
            leapDay = 1;
        }
    }

    if(year == 1918)
    {
        daysInSeptember = normalDOTPInSeptember - leapDay + OFFSET_FOR_1918;
    }
    else
    {
        daysInSeptember = normalDOTPInSeptember - leapDay;
    }

    // Init an output string
    string dateOutput = "00.09.";
    dateOutput.append(to_string(year));
    printf("Init date: %s \n", dateOutput.c_str());

    // Convert the date from int to string
    char firstDigit = daysInSeptember/10 + '0';
    char secondDigit = daysInSeptember%10 + '0';
    dateOutput[0] = firstDigit;
    dateOutput[1] = secondDigit;
    printf("Date: %s \n", dateOutput.c_str());

    return dateOutput;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string year_temp;
    getline(cin, year_temp);

    int year = stoi(ltrim(rtrim(year_temp)));

    string result = dayOfProgrammer(year);

    fout << result << "\n";

    fout.close();

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
