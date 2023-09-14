//g++ -std=c++11 -O2 -Wall analysis.cpp -o analysis

#include <bits/stdc++.h>

using namespace std;

#define MAX_DEPTH 10
#define PLAYER_COLOR 1 //1 - white, 0 - black

bool is_number(const string& s)
{
    return( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

string build_fen(char brd[8][8]) {
    int empties = 0;
    string outfen = "";

    for (int rn1 = 0; rn1 < 8; rn1++) {
        for (char c: brd[rn1]) {
            if (c == '_') {
                empties++;
            } else {
                if (empties != 0) {outfen += to_string(empties); empties = 0;}
                outfen += c;
            }
        }
        if (empties != 0) {outfen += to_string(empties); empties = 0;}
        outfen += '/';
    }
}

vector<string> possible_moves(string pos, int turn) {//1 - player, 0 - opponent
    vector<string> ps;
    char fullpos[8][8];
    
    int row = 0;
    int arpos = 0;

    for (char c: pos) {
        if (c == '/') {
            row++;
            arpos = 0;
        } else {
            if (isdigit(c)) {
                for (int j = 0; j < (c - '0'); j++) {
                    fullpos[row][j] = '_';
                    arpos++;
                }
            } else {
                fullpos[row][arpos] = c;
                arpos++;
            }
        } 
    }

    char temppos[8][8];
    int n = 0;
    for (int rn = 0; rn < 8; rn++) {
        n = 0;
        for (char c: fullpos[rn]) {
            if (c == 'p') {
                if (fullpos[rn + 1][n] == '_') {
                    
                }
            }
            n++;
        }
    }

    return ps;
}

int count_material(string str)
{
    map<char, int> pieces = {{'p', 1}, {'n', 3}, {'b', 3}, {'r', 5}, {'q', 9}, {'k', 0}};

    int white = 0, black = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            white += pieces[char(tolower(str[i]))];
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            black += pieces[str[i]];
        }
    }

    if (PLAYER_COLOR == 1) {
        return (white - black);
    } else {
        return (black - white);
    }
}

int analyse_position(string pos, int turn, int depth) {//1 - player, 0 - opponent
    if (depth > MAX_DEPTH) {return count_material(pos);} //change 0 FOR THE ACTUAL QUALITY OF THE POSITION

    int best;
    if (turn == 1) {
        best = -999;
        for (auto p : possible_moves(pos, 1)) {
            best = max(best, analyse_position(p, 0, depth + 1));
        }
    } else {
        best = 999;
        for (auto p : possible_moves(pos, 0)) {
            best = min(best, analyse_position(p, 1, depth + 1));
        }
    }

    return best; //add function to respond with the best move too
}

int main() {
    string chess_pos;
    cin >> chess_pos;

    cout << "Is it your turn? Respond 1 if yes and 0 if no";
    int turn;
    cin >> turn;

    cout << analyse_position(chess_pos, turn, 1);
}