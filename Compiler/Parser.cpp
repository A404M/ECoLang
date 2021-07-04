//
// Created by a404m on 7/2/21.
//

#include "Parser.h"
#include <fstream>

Parser::Parser(Lexer l) : lexer(std::move(l)) {
    std::ifstream opFile{"OPERATORS.syntax"};
    std::string fileLine;
    int rank = 1;
    while(std::getline(opFile,fileLine)){
        if(fileLine.empty()){
            ++rank;
        }else{
            Lexer::Lexed temp{"",Lexer::OP,Lexer::NO};
            std::string::size_type n = fileLine.find(' ');
            opOrder[{fileLine.substr(0,n),Lexer::OP,Lexer::toOpKind(fileLine.substr(n+1,fileLine.size()-n-1))}] = rank;
        }
    }
    fileLine.clear();
    opFile.close();
/*    opOrder[{"-",Lexer::LexKind::OP,Lexer::RIGHT}] = 4;//i.e. -1
    opOrder[{"+",Lexer::LexKind::OP,Lexer::RIGHT}] = 4;//i.e. +1
    opOrder[{"*",Lexer::LexKind::OP,Lexer::BOTH}] = 3;//i.e. 1*2
    opOrder[{"/",Lexer::LexKind::OP,Lexer::BOTH}] = 3;//i.e. 1/2
    opOrder[{"%",Lexer::LexKind::OP,Lexer::BOTH}] = 3;//i.e. 1%2
    opOrder[{"+",Lexer::LexKind::OP,Lexer::BOTH}] = 2;//i.e. 1+2
    opOrder[{"-",Lexer::LexKind::OP,Lexer::BOTH}] = 2;//i.e. 1-2
    opOrder[{"=",Lexer::LexKind::OP,Lexer::BOTH}] = 1;//i.e. var = 1*/
    lexer.lex();
    for(auto& line : lexer.lexedVec) {
        for (auto begin = line.begin(), it = begin, end = line.end() - 1;it <= end; ++it) {//todo change when you did parenthesis
            if (it->kind == Lexer::OP) {
                if ((it == begin || (it - 1)->kind == Lexer::OP)) {
                    if ((it == end || (it + 1)->kind == Lexer::OP)) {
                        it->opKind = Lexer::NO;
                    } else {
                        it->opKind = Lexer::RIGHT;
                    }
                } else if (it == end || (it + 1)->kind == Lexer::OP) {
                    it->opKind = Lexer::LEFT;
                } else {
                    it->opKind = Lexer::BOTH;
                }
            }
        }
    }

}

Parser::ParsedVec Parser::pars() {
    ParsedVec result;

    for(auto& line : lexer.lexedVec){
        std::vector<Parsed> parsedLine;
        parsLine(parsedLine,line);
        result.push_back(parsedLine);
    }

    return result;
}

void Parser::parsLine(std::vector<Parsed> &result,std::vector<Lexer::Lexed> &line) {
    line.erase(line.end()-1);//semicolon
    for(auto it = line.begin();line.size() > 1;/*empty yet*/){
        for(auto temp = line.begin(),end = line.end();temp < end;++temp){
            if(temp->kind == Lexer::OP){
                if(opOrder[*temp] == 0){
                    throw std::runtime_error("Unknown operator \"" + temp->str + "\":\n" + lexer.getERR(*temp));
                }
                if(it->kind != Lexer::OP || opOrder[*temp] < opOrder[*it]){//lower means better
                    it = temp;
                }
            }
        }

        if(it->kind == Lexer::OP) {
            Parsed parsed;
            parsed.it = *it;
            if(it->opKind == Lexer::LEFT) {
                parsed.operands.push_back(*(it-1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it-1);
            }else if(it->opKind == Lexer::RIGHT) {
                parsed.operands.push_back(*(it+1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it+1);
            }else if(it->opKind == Lexer::BOTH) {
                parsed.operands.push_back(*(it-1));
                parsed.operands.push_back(*(it+1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it+1);
                line.erase(it-1);
            }else{
                //todo error in operator kind
            }
            result.push_back(parsed);
        }else if(line.size() == 1 && it->kind == Lexer::OP){
            break;//done
        }else{
            //todo error something went wrong
        }
    }
}
