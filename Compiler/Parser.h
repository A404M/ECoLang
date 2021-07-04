//
// Created by a404m on 7/2/21.
//

#ifndef ECOLANG_PARSER_H
#define ECOLANG_PARSER_H

#include "Lexer.h"
#include <map>

class Parser {
public:
    //data types
    struct Parsed{
        Lexer::Lexed it{"",Lexer::NONE,Lexer::NO};//default value
        std::vector<Lexer::Lexed> operands{};//with zero members yet
    };
    typedef std::vector<std::vector<Parsed>> ParsedVec;//like Lexer::LexedVec
private:
    //data members
    std::map<Lexer::Lexed,int> opOrder;//for operator rank and needing; lower means better
    Lexer lexer;
public:
    explicit Parser(Lexer);

    ParsedVec pars();
private:
    void parsLine(std::vector<Parsed>&,std::vector<Lexer::Lexed>&);
};


#endif //ECOLANG_PARSER_H
