////////////////////////////////////////////////
// 
// Made of by Dexne
// If you are working in a linux operative system
// you can execute the code with the following 
// commands
// Go to the project
// open a new terminal and write
// g++ main.cpp
// ./a.out
//
////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

// Definition of tokens to be analyzed
// We use enumerations to make the associations between token and value
enum TokenType {
    IDENTIFIER,
    INTEGER,
    REAL,
    STRING,
    TYPE,
    ADD_SUB,
    MULTIPLY,
    DIVIDE,
    RELATIONAL,
    OR,
    AND,
    NOT,
    EQUALITY,
    SEMICOLON,
    COMMA,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    ASSIGN,
    IF,
    WHILE,
    RETURN,
    ELSE,
    DOLLAR,
    INVALID
};

// Receive the string to be analyzed
// make comparations
TokenType analyzeToken(const string& token) {
    if (token == "int" || token == "float" || token == "void" || token == "char") {
        return TYPE;
    } else if (token == "+" || token == "-") {
        return ADD_SUB;
    } else if (token == "*") {
        return MULTIPLY;
    } else if (token == "/") {
        return DIVIDE;
    } else if (token == "<" || token == ">" || token == "<=" || token == ">=") {
        return RELATIONAL;
    } else if (token == "||") {
        return OR;
    } else if (token == "&&") {
        return AND;
    } else if (token == "!") {
        return NOT;
    } else if (token == "==") {
        return EQUALITY;
    } else if (token == ";") {
        return SEMICOLON;
    } else if (token == ",") {
        return COMMA;
    } else if (token == "(") {
        return LEFT_PAREN;
    } else if (token == ")") {
        return RIGHT_PAREN;
    } else if (token == "{") {
        return LEFT_BRACE;
    } else if (token == "}") {
        return RIGHT_BRACE;
    } else if (token == "=") {
        return ASSIGN;
    } else if (token == "if") {
        return IF;
    } else if (token == "while") {
        return WHILE;
    } else if (token == "return") {
        return RETURN;
    } else if (token == "else") {
        return ELSE;
    } else if (token == "$") {
        return DOLLAR;
    } else if (isdigit(token[0])) {
        bool isReal = false;
        for (char c : token) {
            if (c == '.') {
                if (isReal) {
                    return INVALID;
                }
                isReal = true; 
            } else if (!isdigit(c)) {
                return INVALID;
            }
        }
        return isReal ? REAL : INTEGER; // Integer or float
    } else if (isalpha(token[0]) || token[0] == '_') {// May begin with _
        for (char c : token) {
            if (!isalnum(c) && c != '_') {
                return INVALID;
            }
        }
        return IDENTIFIER;
    } else if (token[0] == '"' && token.back() == '"') {
        return STRING;
    }
    return INVALID;
}

int main() {
     // String to be analyzed
    string input = "mi_variable _12345 \"esto es una cadena\" 42 3.1416 cadena int float void char + - * / <= >= || && ! = != ; , ( ) { } = if while return else $";
    string token;
    for (char c : input) {
        if (c == ' ' || c == '\n' || c == '\t' || c == '$') {
            if (!token.empty()) {// if not empty
                TokenType type = analyzeToken(token);
                switch (type) {
                    // print results
                    case IDENTIFIER: cout << "IDENTIFIER = 0" << endl; break;
                    case INTEGER: cout << "INTEGER = 1" << endl; break;
                    case REAL: cout << "REAL = 2" << endl; break;
                    case STRING: cout << "STRING = 3" << endl; break;
                    case TYPE: cout << "TYPE = 4" << endl; break;
                    case ADD_SUB: cout << "ADD_SUB = 5" << endl; break;
                    case MULTIPLY: cout << "MULTIPLY = 6" << endl; break;
                    case DIVIDE: cout << "DIVIDE = 6" << endl; break;
                    case RELATIONAL: cout << "RELATIONAL = 7" << endl; break;
                    case OR: cout << "OR = 8" << endl; break;
                    case AND: cout << "AND = 9" << endl; break;
                    case NOT: cout << "NOT = 10" << endl; break;
                    case EQUALITY: cout << "EQUALITY = 11" << endl; break;
                    case SEMICOLON: cout << "SEMICOLON = 12" << endl; break;
                    case COMMA: cout << "COMMA = 13" << endl; break;
                    case LEFT_PAREN: cout << "LEFT_PAREN = 14" << endl; break;
                    case RIGHT_PAREN: cout << "RIGHT_PAREN = 15" << endl; break;
                    case LEFT_BRACE: cout << "LEFT_BRACE = 16" << endl; break;
                    case RIGHT_BRACE: cout << "RIGHT_BRACE = 17" << endl; break;
                    case ASSIGN: cout << "ASSIGN = 18" << endl; break;
                    case IF: cout << "IF = 19" << endl; break;
                    case WHILE: cout << "WHILE = 20" << endl; break;
                    case RETURN: cout << "RETURN = 21" << endl; break;
                    case ELSE: cout << "ELSE = 22" << endl; break;
                    case DOLLAR: cout << "DOLLAR = 23" << endl; break;
                    default: cout << "INVALID" << endl; break;
                }
                token.clear();
            }
            if (c == '$') {
                cout << "DOLLAR = 23" << endl;
            }
        } else {
            token += c;
        }
    }
    return 0;
}
