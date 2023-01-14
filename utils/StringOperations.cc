#include <regex>
#include <iostream>

#include "StringOperations.hh"
#include "common.hh"

//WILL DELETE
#include "../include/StringOperations.hh"
#include "../include/common.hh"

using namespace std;

bool isAddrString(string& addrString) {
    regex ipFormat("(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}):(\\d{1,5})");
    return regex_match(addrString, ipFormat);
}

std::string getIpAddr(std::string input) {
    int colonIdx = -1;
    for(int i = input.size() - 1; i >= 0; i--) {
        if(input[i] == ':') {
            colonIdx = i;
            break;
        }
    }
    return input.substr(0, colonIdx);
}

int getPort(std::string input) {
    int colonIdx = -1;
    for(int i = input.size() - 1; i >= 0; i--) {
        if(input[i] == ':') {
            colonIdx = i;
            break;
        }
    }
    return stoi(input.substr(colonIdx + 1, input.size() - colonIdx));
}

bool isCommand(std::string& msg) {
    return msg[0] == '/';
}

/*
void printWithCRLF(const char* str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\r') {
            printf("<CR>");
        }
        if(str[i] == '\n') {
            printf("<LF>");
        }
        printf("%c", str[i]);
    }
}*/

void printWithCRLF(string& str) {
    for (char c : str) {
        if (c == '\r') {
            cout << "<CR>";
        }
        else if (c == '\n') {
            cout << "<LF>";
        }
        else {
            cout << c;
        }
    }
    cout << endl;
}

std::string getCommand(std::string& str) {
    if(str.size() < 5) {
        return "";
    }
    return str.substr(0, 5);
}

std::string getArgs(std::string& str) {
    if (str.size() <= 6) {
        return "";
    }

    if (str[5] != ' ') {
        return "";
    }

    return str.substr(6, str.size() - 6);
}