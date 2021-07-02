//
// Created by a404m on 7/2/21.
//

#ifndef ECOLANG_LEXER_H
#define ECOLANG_LEXER_H

#include <vector>
#include <string>

namespace Lexer {
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
    };

    typedef std::vector<std::vector<Lexed>> LexedVec;

    extern LexedVec lex(std::string);

    extern inline bool isId(char);
    extern inline bool isNum(char);
    extern inline bool isOp(char);
    extern inline bool isEOL(char);
    extern inline bool isStr(char);
}


#endif //ECOLANG_LEXER_H
