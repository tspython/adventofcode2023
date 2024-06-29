#include <iostream> 
#include <fstream>
#include <string> 

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

int solve(string input){
    return input.size();
}

int main(){
    string input = readFile("input.txt");
    cout << solve(input) << endl;
    return 0;
}