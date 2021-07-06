//
// Created by a404m on 7/2/21.
//

#ifndef ECOLANG_LEXER_H
#define ECOLANG_LEXER_H

#include <iostream>
#include <vector>
#include <string>

class Lexer {
    friend class Parser;
public:
    //data types
    enum LexKind{
        NONE = 0,
        ID,//Identifier
        NUM,//Number
        STR,//String
        OP,//Operator
        BLOCK,//Blocks and Parenthesis
        EOL,//End Of Line
        HELPER,//used in parser
    };
    enum SpecialKind{//needing of an operator (used in parser) | kind of identifier ...
        NO = 0,//none
        OP_LEFT,//operator left
        OP_RIGHT,//operator right
        OP_BOTH,//operator left and right
        FUN,//function
        CLASS,//class
        VAR,//variable
        KEYWORD//keywords
    };

    static SpecialKind toOpKind(const std::string&);

    struct Lexed{
        std::string str{};
        LexKind kind = NONE;
        SpecialKind specialKind = NO;//for parser
        std::string::size_type index = 0;//only for debugging

        Lexed() = default;
        Lexed(std::string s, LexKind l, SpecialKind o, std::string::size_type si = 0): str(std::move(s)), kind(l), specialKind(o), index(si){/*empty*/}

        bool operator==(const Lexed& lexed) const{
            return this->str == lexed.str &&
                   this->kind == lexed.kind &&
                   this->specialKind == lexed.specialKind;
        }
        friend bool operator<(const Lexed& lexed1,const Lexed& lexed2){//used in std::map
            return lexed1.str < lexed2.str ||
                   (lexed1.str == lexed2.str && lexed1.kind < lexed2.kind) ||
                    (lexed1.str == lexed2.str && lexed1.kind == lexed2.kind && lexed1.specialKind < lexed2.specialKind);
        }
        friend bool operator>(const Lexed& lexed1,const Lexed& lexed2){//used in std::map
            return lexed1.str > lexed2.str ||
                   (lexed1.str == lexed2.str && lexed1.kind > lexed2.kind) ||
                   (lexed1.str == lexed2.str && lexed1.kind == lexed2.kind && lexed1.specialKind > lexed2.specialKind);
        }
        friend bool operator<=(const Lexed& lexed1,const Lexed& lexed2){//used in std::map
            return lexed1 < lexed2 || lexed1 == lexed2;
        }
        friend bool operator>=(const Lexed& lexed1,const Lexed& lexed2){//used in std::map
            return lexed1 > lexed2 || lexed1 == lexed2;
        }
    };

    /*
     * each element of the first vector is a sentence (or line) of codes
     * the second vector holds each operator or identifier of the sentence (or line)
    */
    typedef std::vector<std::vector<Lexed>> LexedVec;
private:
    //data members
    std::string str{};
    LexedVec lexedVec;

    //functions
    static inline bool isId(char);//is an Identifier character
    static inline bool isNum(char);//is an number character
    static inline bool isOp(char);//is an operator character
    static inline bool isBlock(char);//is an block
    static inline bool isEOL(char);//is an end of line character
    static inline bool isStr(char);//is an string or character marker character

public:
    explicit Lexer(std::string);

    void lex();//call this for doing lex

    std::string getERR(const Lexed&);
};


#endif //ECOLANG_LEXER_H
