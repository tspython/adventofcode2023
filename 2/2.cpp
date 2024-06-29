#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define red 12
#define green 13
#define blue 14

using namespace std;

string readFile(string filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        exit(0);
    }
    
    string content;
    string line;
    while(getline(file, line)) {
        content += line + "\n";
    }
    
    file.close();
    return content;
}

bool isValidGame(string gameDetails) {
    vector<string> subsets;
    string delim = "; ";
    size_t pos = 0;
    
    while ((pos = gameDetails.find(delim)) != string::npos) {
        subsets.push_back(gameDetails.substr(0, pos));
        gameDetails.erase(0, pos + delim.length());
    }
    subsets.push_back(gameDetails);  
    
    for(auto& subset : subsets ) {
        stringstream ll(subset);
        string s;
        while (getline(ll, s, ',')) {
            stringstream ss(s);
            int count = 0;
            string color;
            ss >> count >> color; 
            
            color.erase(0, color.find_first_not_of(' '));
            color.erase(color.find_last_not_of(' ') + 1);
            
            if ((color == "red" && count > red) ||
                (color == "green" && count > green) ||
                (color == "blue" && count > blue)) {
                return false;
            }
        }
    }
    
    return true;
}

int sumOfValidGames(string games) {
    int sum = 0;
    stringstream ss(games);
    string gameEntry;
    
    while (getline(ss, gameEntry, '\n')) {
        size_t colonPos = gameEntry.find(':');
        if (colonPos == string::npos) {
            continue;
        }
        
        string gameIdStr = gameEntry.substr(5, colonPos - 5);
        int gameId = stoi(gameIdStr);
        
        string gameDetails = gameEntry.substr(colonPos + 2);
        
        if (isValidGame(gameDetails)) {
            sum += gameId;
        }
    }
    
    return sum;
}

int main() {
    // string input = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\nGame 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\nGame 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\nGame 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\nGame 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    string input = readFile("input.txt");
    cout << sumOfValidGames(input) << endl;
    return 0;
}
