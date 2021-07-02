//
// Created by a404m on 7/2/21.
//

#include "Lexer.h"
#include <iostream>

using Lexer::LexedVec;

extern LexedVec Lexer::lex(std::string str) {
    LexedVec result{{}};//has size 1
    Lexed temp;
    auto line = result.begin();

    for(auto it = str.begin(),end = str.end();it < end;++it){
        auto current = *it;
        if(isspace(current) && temp.kind != STR){
            if(temp.kind != NONE){
                line->push_back(temp);
                temp.str.clear();
                temp.kind = NONE;
            }
            continue;//don't push back this character
        }else if(isStr(current)){
            if(temp.kind != STR){
                if(temp.kind != NONE){
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = STR;
            }else if(temp.str[0] == current && *(it-1) != '\\'){
                temp.str += current;
                line->push_back(temp);
                temp.str.clear();
                temp.kind = NONE;
            }
        }else if(temp.kind == STR){
            //no work to do
        }else if(isId(current) || (isNum(current) && temp.kind == ID)){// names can be a-z,A-Z or have
            if(temp.kind != ID){
                if(temp.kind != NONE) {
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = ID;
            }
        }else if(isNum(current)){
            if(temp.kind != NUM){
                if(temp.kind != NONE) {
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = NUM;
            }
        }else if(isOp(current)){
            if(temp.kind != OP){
                if(temp.kind != NONE) {
                    line->push_back(temp);
                    temp.str.clear();
                }
                temp.kind = OP;
            }
        }else if(isEOL(current)){
            if(temp.kind != NONE){
                line->push_back(temp);
            }
            temp.str = current;
            temp.kind = EOL;
            line->push_back(temp);
            temp.str.clear();
            temp.kind = NONE;
            result.push_back({});//create new line
            line = result.end()-1;//go to new line
            continue;
        }else{
            throw std::runtime_error("Unknown character = '" + std::string(1,current) + "'");
        }
        temp.str += current;
    }

    if(!result.empty() && result[result.size()-1].empty()){
        result.erase(result.end()-1);
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