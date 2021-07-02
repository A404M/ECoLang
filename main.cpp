#include <iostream>
#include <map>
#include "Compiler/Lexer.h"

using namespace std;

int main() {
    map<Lexer::LexKind,std::string> kinds{
            {Lexer::NONE,"NONE"},
            {Lexer::ID,"ID"},
            {Lexer::NUM,"NUM"},
            {Lexer::STR,"STR"},
            {Lexer::OP,"OP"},
            {Lexer::EOL,"EOL"}
    };
    try {
        auto test = Lexer::lex("Int a=0; String b (= \"hello + world\";");
        for(auto& j : test) {
            for (auto &i : j)
                cout << "[" << i.str << "," << kinds[i.kind] << "]" << endl;
            cout << endl;
        }
    }catch(const std::runtime_error &error){
        cerr << error.what();
    }
    return 0;
}
