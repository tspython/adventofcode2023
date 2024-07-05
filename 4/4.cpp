#include <iostream> 
#include <fstream>
#include <string> 
#include <unordered_set>
#include <vector>
#include <sstream>

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

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

pair<vector<int>, vector<int>> processString(const string& input) {
    size_t colonPos = input.find(':');
    if (colonPos == string::npos) {
        return {{}, {}};
    }
    
    string numbersPart = input.substr(colonPos + 1);
    vector<string> parts = split(numbersPart, '|');
    
    if (parts.size() != 2) {
        return {{}, {}};
    }
    
    vector<int> beforePipe;
    vector<int> afterPipe;
    
    vector<string> beforeStrings = split(parts[0], ' ');
    for (const string& numStr : beforeStrings) {
        if (!numStr.empty()) {
            beforePipe.push_back(stoi(numStr));
        }
    }
    
    vector<string> afterStrings = split(parts[1], ' ');
    for (const string& numStr : afterStrings) {
        if (!numStr.empty()) {
            afterPipe.push_back(stoi(numStr));
        }
    }
    
    return {beforePipe, afterPipe};
}

int solveCard(string card){
    int total = 0;
    
    pair<vector<int>, vector<int>> nums = processString(card);
    
    unordered_set<int> set(nums.first.begin(), nums.first.end());
    
    for(auto& num : nums.second) {
        if(set.find(num) != set.end()) {
            if (total == 0) total++;
            else total*=2;
        }
    }
    
    return total;
}

int solve(string input){
    int sum = 0;
    istringstream iss(input);
    string line;
    
    while(getline(iss, line)){
        sum += solveCard(line);
    }
    
    return sum;
}

int main(){
    string input = readFile("input1.txt");
    cout << solve(input) << endl;
    return 0;
}
