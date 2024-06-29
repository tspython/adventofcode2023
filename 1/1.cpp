#include <iostream>
#include <cctype>
#include <fstream> 
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

int calibrationSum(string calDoc) {
    int sum = 0;
    string currentCalVal = "";
    
    for (auto it = calDoc.begin(); it != calDoc.end(); ++it) {
        char c = *it;
        
        if (c == '\n' || it + 1 == calDoc.end()) { 
            string num = "";
            num += currentCalVal[0];
            num += currentCalVal[currentCalVal.length() - 1];
            cout << num << endl;
            sum += stoi(num);
            currentCalVal = "";
        } 
        else {
            if (isdigit(c)) {
                currentCalVal += c;
            }
        }
    }
    
    return sum;
}

int main() {
    // string input = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet";
    string input = readFile("input.txt");
    cout << calibrationSum(input) << endl;
    return 0;
}