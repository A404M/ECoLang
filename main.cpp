//#define NDEBUG

#include <iostream>
#include "Compiler/Parser.h"
#include <fstream>

using namespace std;

int main() {
    {//should be done by installer; but for now we create each time
        ofstream opFile{"OPERATORS.syntax"};
        opFile.clear();
        opFile << "+ OP_RIGHT\n";
        opFile << "- OP_RIGHT\n";
        opFile << "\n";
        opFile << "* OP_BOTH\n";
        opFile << "/ OP_BOTH\n";
        opFile << "% OP_BOTH\n";
        opFile << "\n";
        opFile << "+ OP_BOTH\n";
        opFile << "- OP_BOTH\n";
        opFile << "\n";
        opFile << "= OP_BOTH";
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
        auto test = Parser{Lexer{"i = (5+3)*2;"}}.pars();

        for(auto& line : test){
            for(auto& i : line){
                cout << "{[" << i.it.str << "," << kinds[i.it.kind] << "," << i.it.specialKind << "]";
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
