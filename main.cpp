//#define NDEBUG

#include <iostream>
#include "Compiler/Parser.h"
#include <fstream>

using namespace std;

int main() {
    {//should be done by installer; but for now we create each time
        ofstream opFile{"OPERATORS.syntax"};
        opFile.clear();
        opFile << "+ RIGHT\n";
        opFile << "- RIGHT\n";
        opFile << "\n";
        opFile << "* BOTH\n";
        opFile << "/ BOTH\n";
        opFile << "% BOTH\n";
        opFile << "\n";
        opFile << "+ BOTH\n";
        opFile << "- BOTH\n";
        opFile << "\n";
        opFile << "= BOTH";
        opFile.close();
    }

    map<Lexer::LexKind,std::string> kinds{
            {Lexer::NONE,"NONE"},
            {Lexer::ID,"ID"},
            {Lexer::NUM,"NUM"},
            {Lexer::STR,"STR"},
            {Lexer::OP,"OP"},
            {Lexer::EOL,"EOL"},
            {Lexer::HELPER,"HELPER"}
    };
    try {
        auto test = Parser{Lexer{"i = 0;i = 4*2 + 10/2%4;"}}.pars();

        for(auto& line : test){
            for(auto& i : line){
                cout << "{[" << i.it.str << "," << kinds[i.it.kind] << "," << i.it.opKind << "]";
                for(auto& operand : i.operands){
                    cout << "{[" << operand.str << "," << kinds[operand.kind] << "]";
                }
                cout << "}\n";
            }
            cout << endl;
        }

    }catch(const std::exception &error){
        cerr << error.what();
    }
    return 0;
}
