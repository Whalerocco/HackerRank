#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/* https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem?isFullScreen=true
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    vector<int> playerRankings; // The rankings of the player 

    
    int rank = 1;
    int lastPoints = ranked[0];

    vector<int> denseRanking;
    for(int i = 0; i < ranked.size(); i++)
        {
            
            if(ranked[i] != lastPoints)
            {
                lastPoints = ranked[i];
                rank++;
            }
            denseRanking.push_back(rank);
        } 
    
    for(int ranking : denseRanking)
    {
        printf("%c ", (ranking+'0'));
    }
    
    // One loop only
    int playerInd = 0;

    // the ranked list is in descending order
    // go through it from the back
    // Assumes that the player always gets positive points
    int i = ranked.size()-1; // start with last item
    
    while(playerInd < player.size()) // Until all the different player points have been evaluated
    {
        if(player[playerInd] < ranked[i]) // The player's points are less than the ranked player comparing with, the rank will be +1 of the ranked one's
        {
            playerRankings.push_back(denseRanking[i]+1); // The rank will be one larger than the larger value's rank
            printf("\nPlayer points (p = %d) lower than ranked[%d] (p = %d), Pushing rank: %d", player[playerInd], i, ranked[i], playerRankings[playerInd]);
            playerInd++;
            
        }
        else if(player[playerInd] >= ranked[i] && i == 0) // Only happens last loop(s), compare if larger than or equal to top ranked score
        {
            playerRankings.push_back(1);
            printf("\nHighscore! Player points: %d > ranked points: %d, Pushing rank: %d", player[playerInd], ranked[i], playerRankings[playerInd]);
            playerInd++;
        }
        else // if the player's score is larger than the ranked one's, compare with the next one's
        {
            printf("\n player[%d] (points = %d) Larger or equal to ranked[%d] (points = %d), decreasing i", playerInd, player[playerInd], i, ranked[i]);
            i--;
        }
        
    } 
   
    return playerRankings;
}

// vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
//     vector<int> playerRankings; // The rankings of the player 

//     // the ranked list is in descending order

//     // One loop for each of the player's different points
//     for(int playerPoints : player) 
//     {
//         int rank = 1;  // Rank of the current investigated position
//         int lastPoints = -1;

//         for(int i = 0; i < ranked.size(); i++)
//         {
//             if(playerPoints >= ranked[i])
//             {
//                 break;
//             }
            
//             // Update the rank of the ranked player if it has a new point
//             if (ranked[i] != lastPoints)
//             {
//                 rank++;
//                 lastPoints = ranked[i];
//             }
//         } 
        
//         playerRankings.push_back(rank);
//     }

//     return playerRankings;
// }


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string ranked_count_temp;
    getline(cin, ranked_count_temp);

    int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));

    string ranked_temp_temp;
    getline(cin, ranked_temp_temp);

    vector<string> ranked_temp = split(rtrim(ranked_temp_temp));

    vector<int> ranked(ranked_count);

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = stoi(ranked_temp[i]);

        ranked[i] = ranked_item;
    }

    string player_count_temp;
    getline(cin, player_count_temp);

    int player_count = stoi(ltrim(rtrim(player_count_temp)));

    string player_temp_temp;
    getline(cin, player_temp_temp);

    vector<string> player_temp = split(rtrim(player_temp_temp));

    vector<int> player(player_count);

    for (int i = 0; i < player_count; i++) {
        int player_item = stoi(player_temp[i]);

        player[i] = player_item;
    }

    vector<int> result = climbingLeaderboard(ranked, player);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
