
#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
using namespace std;

int main() {
    unordered_set<string> keywordList = {
        "int", "float", "if", "else", "while", "return", "char", "double", "for"
    };

    string line;
    cout << "Type a line of C++ code: ";
    getline(cin, line);

    cout << "\n--- Tokens Found ---\n";

    int idx = 0;
    int length = line.length();

    while (idx < length) {
        char current = line[idx];

        // Ignore spaces and tabs
        if (isspace(current)) {
            idx++;
            continue;
        }

        // Keywords or identifiers
        if (isalpha(current) || current == '_') {
            string word = "";
            while (idx < length && (isalnum(line[idx]) || line[idx] == '_'))
                word += line[idx++];
            if (keywordList.count(word))
                cout << "KEYWORD: " << word << endl;
            else
                cout << "IDENTIFIER: " << word << endl;
        }

        // Numeric literals
        else if (isdigit(current)) {
            string num = "";
            while (idx < length && isdigit(line[idx]))
                num += line[idx++];
            cout << "NUMBER: " << num << endl;
        }

        // Operators: single or double character
        else if (string("+-*/%=!<>&|^").find(current) != string::npos) {
            string op(1, current);
            if (idx + 1 < length) {
                string doubleOp = op + line[idx + 1];
                if (doubleOp == "==" || doubleOp == "!=" || doubleOp == "<=" || 
                    doubleOp == ">=" || doubleOp == "&&" || doubleOp == "||") {
                    cout << "OPERATOR: " << doubleOp << endl;
                    idx += 2;
                    continue;
                }
            }
            cout << "OPERATOR: " << op << endl;
            idx++;
        }

        // Delimiters
        else if (string("();{},[]").find(current) != string::npos) {
            cout << "DELIMITER: " << current << endl;
            idx++;
        }

        // Any unrecognized character
        else {
            cout << "UNKNOWN: '" << current << "'\n";
            idx++;
        }
    }

    return 0;
}
