//
// Created by a404m on 7/2/21.
//

#include "Lexer.h"
#include <iostream>

using Lexer::LexedVec;

extern LexedVec Lexer::lex(const std::string &str) {
    LexedVec result{{}};//has size 1
    auto line = result.begin();//points to the first line
    Lexed temp;//holds the element to save into line

    for(auto it = str.begin(),end = str.end();it < end;++it){
        auto current = *it;//to avoid dereferencing and improve speed and read ability
        if(isspace(current) && temp.kind != STR){//avoid all of white spaces except in strings
            if(temp.kind != NONE){//push_back and clear temp
                temp.index = it-str.begin();
                line->push_back(temp);
                temp.str.clear();
                temp.kind = NONE;
            }
            continue;//don't push back this character
        }else if(isStr(current)){
            if(temp.kind != STR){//push_back and clear temp
                if(temp.kind != NONE){
                    temp.index = it-str.begin();
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = STR;
            }else if(temp.str[0] == current && *(it-1) != '\\'){
                temp.str += current;//because it usually push in the end of this loop
                temp.index = it-str.begin();
                line->push_back(temp);//push_back and clear temp because the string has been ended
                temp.str.clear();
                temp.kind = NONE;
                continue;//don't push back this character because it happened in here
            }
        }else if(temp.kind == STR){
            //no work to do
        }else if(isId(current) || (isNum(current) && temp.kind == ID)){// names can be a-z,A-Z or have
            if(temp.kind != ID){//push_back and clear temp
                if(temp.kind != NONE) {
                    temp.index = it-str.begin();
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = ID;
            }
        }else if(isNum(current)){
            if(temp.kind != NUM){//push_back and clear temp
                if(temp.kind != NONE) {
                    temp.index = it-str.begin();
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = NUM;
            }
        }else if(isOp(current)){
            if(temp.kind != OP){//push_back and clear temp
                if(temp.kind != NONE) {
                    temp.index = it-str.begin();
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = OP;
            }
        }else if(isEOL(current)){
            if(temp.kind != NONE){//push_back and clear temp
                temp.index = it-str.begin();
                line->push_back(temp);
            }
            temp.str = current;//because it usually push in the end of this loop
            temp.kind = EOL;
            temp.index = it-str.begin();
            line->push_back(temp);//push_back and clear temp because the line has been ended
            temp.str.clear();
            temp.kind = NONE;
            result.push_back({});//create new line
            line = result.end()-1;//go to new line
            continue;
        }else{//the character is unknown
            temp.str = current;
            temp.index = it-str.begin();
            throw std::runtime_error("Unknown character:\n" + getERR(str,temp));
        }
        temp.str += current;
    }

    if(!result.empty()){
        if(result[result.size()-1].empty())//if the last line was empty all are ok
            result.erase(result.end()-1);//delete the last line
        else
            throw std::runtime_error("The last wasn't ended with a end of line character");
    }

    return result;
}

extern inline bool Lexer::isId(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
extern inline bool Lexer::isNum(char c) {
    return (c >= '0' && c <= '9');
}
extern inline bool Lexer::isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=';
}
extern inline bool Lexer::isEOL(char c) {
    return c == ';';
}
extern inline bool Lexer::isStr(char c){
    return c == '"' || c == '\'';
}

extern std::string Lexer::getERR(const std::string& str,const Lexed& lexed){
    std::string result;

    int line = 0;//in which line error is
    for(auto i = 0;i < lexed.index;++i){//loop does find the number of lines
        if(str[i] == '\n'){
            ++line;
        }
    }

    int words = 0;//words means any set of characters between two space
    bool inWord = false;//as you can read

    for(auto i = lexed.index;i < str.size()/*it works for any value between range of 0 to str.size()*/ && words < 3 && str[i] != '\n';--i){//the loop gets three (two + the error) words (if exist) in the same line before the error
        if(!inWord){
            if(!isspace(str[i])){
                inWord = true;
            }
        }else if(isspace(str[i])){
            ++words;
            inWord = false;
        }
        result = str[i] + result;
    }

    auto size = result.size();//for number of spaces before the pointer

    words = 0;
    inWord = false;

    for(auto i = lexed.index+1;i < str.size() && words < 3 && str[i] != '\n';++i){//the loop gets three words (if exist) in the same line after the error
        if(!inWord){
            if(!isspace(str[i])){
                inWord = true;
            }
        }else if(isspace(str[i])){
            ++words;
            inWord = false;
        }
        result += str[i];
    }

    return result+'\n'+std::string(size-1,' ')+"^ at line "+std::to_string(line);
}