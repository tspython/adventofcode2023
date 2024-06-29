#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cctype>

using namespace std;

const string symbolStr = "!@#$%^&*()_+-=[]{}|;:,<>?/`~";
unordered_set<char> symbols(symbolStr.begin(), symbolStr.end());

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

bool hasAdjacentSymbol(const vector<vector<char>>& document, int row, int col) {
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
    };
    
    for (const auto& direction : directions) {
        int newRow = row + direction.first;
        int newCol = col + direction.second;
        
        if (newRow >= 0 && newRow < document.size() && newCol >= 0 && newCol < document[row].size()) {
            if (symbols.find(document[newRow][newCol]) != symbols.end()) {
                return true;
            }
        }
    }
    return false;
}

int solve(const string& input) {
    vector<vector<char>> document;
    istringstream iss(input);
    string line;
    while (getline(iss, line)) {
        vector<char> lineChars(line.begin(), line.end());
        document.push_back(lineChars);
    }
    
    int sum = 0;
    for (int i = 0; i < document.size(); i++) {
        for (int j = 0; j < document[i].size(); j++) {
            if (isdigit(document[i][j])) {
                string currentNum;
                int startJ = j;
                while (j < document[i].size() && isdigit(document[i][j])) {
                    currentNum += document[i][j];
                    j++;
                }
                
                bool valid = false;
                for (int k = startJ; k < j; k++) {
                    if (hasAdjacentSymbol(document, i, k)) {
                        valid = true;
                        break;
                    }
                }
                
                if (valid) {
                    cout << "Valid number: " << currentNum << endl;
                    sum += stoi(currentNum);
                }
                j--; 
            }
        }
    }
    
    return sum;
}

int main() {
    string input = readFile("input1.txt");
    cout << "Sum of valid numbers: " << solve(input) << endl;
    return 0;
}
