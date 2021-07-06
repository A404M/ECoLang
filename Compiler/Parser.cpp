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
    lexer.lex();

    std::map<std::string,Lexer::Lexed> identifiers{};
    std::vector<std::string> keywords{
        "class","fun","var","extern"
    };

    for(auto& line : lexer.lexedVec) {
        for (auto begin = line.begin(), it = begin, end = line.end() - 1;it <= end; ++it) {
            if(it->kind == Lexer::ID){
                if(isExist(keywords,it->str)){//it's a keyword ; it->str == any element of keywords
                    it->specialKind = Lexer::KEYWORD;
                }else if(identifiers.find(it->str) != identifiers.end()){//the identifier was exist
                    it->specialKind = identifiers[it->str].specialKind;
                }else if(it != begin){
                    if((it-1)->specialKind == Lexer::KEYWORD){
                        std::string temp = (it-1)->str;
                        if(temp == "var"){
                            it->specialKind = Lexer::VAR;
                        }else if(temp == "fun"){
                            it->specialKind = Lexer::FUN;
                        }else if(temp == "class"){
                            it->specialKind = Lexer::CLASS;
                        }else{
                            goto ID_UNDEF;
                        }
                        identifiers[it->str] = *it;
                    }else{
                        goto ID_UNDEF;
                    }
                }else{
                    ID_UNDEF:;//todo error identifier is not defined here
                }
            }
            if(it->kind == Lexer::OP){
                if(it != begin && (it-1)->kind != Lexer::OP){
                    if(it != end && (it+1)->kind != Lexer::OP){
                        it->specialKind = Lexer::OP_BOTH;
                    }else{
                        it->specialKind = Lexer::OP_LEFT;
                    }
                }else if(it != end && (it+1)->kind != Lexer::OP){
                    it->specialKind = Lexer::OP_RIGHT;
                }else{
                    it->specialKind = Lexer::NO;
                }
            }
        }
    }
}

Parser::ParsedVec Parser::pars() {
    ParsedVec result;
    for(auto& line : lexer.lexedVec){
        std::vector<Parsed> parsedLine;
        line.erase(line.end()-1);//semicolon
        parsLine(parsedLine,line);
        result.push_back(parsedLine);
    }
    return result;
}

void Parser::parsLine(std::vector<Parsed> &result,std::vector<Lexer::Lexed> &line) {
    for(auto it = line.begin();line.size() > 1;/*empty yet*/){
        for(auto temp = line.begin(),end = line.end();temp < end;++temp){
            if(it->specialKind == Lexer::KEYWORD){
                if(temp->str == "var" || temp->str == "fun" || temp->str == "class"){
                    it = temp;
                    break;
                }
            }else if(temp->kind == Lexer::BLOCK){
                if(it->kind != Lexer::BLOCK) {
                    if (temp->str == "(") {
                        it = temp;
                        break;
                    } else if (temp->str == ")") {
                        throw std::runtime_error("UnMatched Parenthesis:\n" + lexer.getERR(*temp));
                    }
                }
            }else if(temp->kind == Lexer::OP){
                if(opOrder[*temp] == 0){
                    throw std::runtime_error("Unknown operator:\n" + lexer.getERR(*temp));
                }
                if(it->kind != Lexer::OP || opOrder[*temp] < opOrder[*it]){//lower means better
                    it = temp;
                }
            }
        }
        if(it->specialKind == Lexer::KEYWORD){
            Parsed temp;
            temp.it = *it;
            if(it->str == "var"){
                if(it != line.begin() && (it-1)->specialKind == Lexer::KEYWORD){
                    if((it-1)->str == "extern"){
                        temp.operands.push_back(*(it-1));
                    }
                }
            }//todo for class and function
        }else if(it->kind == Lexer::BLOCK){
            int in = 0;
            auto temp = *it;
            std::vector<Lexer::Lexed> subLine;
            for(;it < line.end();++it){
                if(it->kind == Lexer::BLOCK){
                    if(it->str == "("){
                        ++in;
                    }else if(it->str == ")"){
                        --in;
                    }
                }
                if(!in){
                    break;
                }
                subLine.push_back(*it);
                --it;
                line.erase(it+1);
            }
            subLine.erase(subLine.begin());
            parsLine(result,subLine);
            *it = subLine[0];
        }else if(it->kind == Lexer::OP) {
            Parsed parsed;
            parsed.it = *it;
            if(it->specialKind == Lexer::OP_LEFT) {
                parsed.operands.push_back(*(it-1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it-1);
            }else if(it->specialKind == Lexer::OP_RIGHT) {
                parsed.operands.push_back(*(it+1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it+1);
            }else if(it->specialKind == Lexer::OP_BOTH) {
                parsed.operands.push_back(*(it-1));
                parsed.operands.push_back(*(it+1));
                *it = Lexer::Lexed{std::to_string(result.size()),Lexer::HELPER,Lexer::NO};
                line.erase(it+1);
                line.erase(it-1);
            }else{
                throw std::runtime_error("Unknown operator:\n" + lexer.getERR(*it));
            }
            result.push_back(parsed);
        }else if(line.size() == 1 && it->kind == Lexer::OP){
            break;//done
        }else{
            //todo show error
        }
    }
}

bool Parser::isExist(const std::vector<std::string> &vec,const std::string& item) {
    for(const auto& i : vec)
        if(item == i)
            return true;
    return false;
}
