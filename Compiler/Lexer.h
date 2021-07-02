//
// Created by a404m on 7/2/21.
//

#ifndef ECOLANG_LEXER_H
#define ECOLANG_LEXER_H

#include <vector>
#include <string>

namespace Lexer {//encapsulation
    enum LexKind{
        NONE,
        ID,//Identifier
        NUM,//Number
        STR,//String
        OP,//Operator
        EOL//End Of Line
    };

    struct Lexed{
        std::string str{};
        LexKind kind = NONE;
        std::string::size_type index = 0;//only for debugging
    };

    /*
     * each element of the first vector is a sentence (or line) of codes
     * the second vector holds each operator or identifier of the sentence (or line)
    */
    typedef std::vector<std::vector<Lexed>> LexedVec;

    extern LexedVec lex(const std::string&);//call this for doing lex

    extern inline bool isId(char);//is an Identifier character
    extern inline bool isNum(char);//is an number character
    extern inline bool isOp(char);//is an operator character
    extern inline bool isEOL(char);//is an end of line character
    extern inline bool isStr(char);//is an string or character marker character

    extern std::string getERR(const std::string&,const Lexed&);
}


#endif //ECOLANG_LEXER_H
