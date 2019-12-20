//
// Created by Carol Hanna on 15/12/2019.
//


#include <iostream>
#include <stack>
#include <vector>
#include "../../Desktop/compi3/hw3_output.hpp"
extern int yylineno;

using namespace std;
using namespace output;

#define functionEntry entry<functionType>

template <typename t>
class entry{
public:
    const string& name;
    t type;
    entry(string name, t type):name(name), type(type){};
};

class functionType{
public:
    string returnType;
    vector<string> paramTypes;

    void addParam(string paramType) {
        paramTypes.push_back(paramType);
    }
};

class variableEntry : public entry<string>{
public:
    int offset;
    variableEntry(string type = "", string name = "", int offset = 0):entry(name, type), offset(offset){}

};


class scope{
public:
    vector<variableEntry> variables;
    vector<functionEntry> functions;

    variableEntry* getVariable(const string& name){
        for(int i = 0; i < variables.size(); i++){
            if(name == variables[i].name){
                return &variables[i];
            }
        }
    }
    functionEntry* getFunction(const string& name){
        for(int i = 0; i < functions.size(); i++){
            if(name == functions[i].name){
                return &functions[i];
            }
        }
    }

    void insertVariable(string type, string name, int offset){
        if(getVariable(name) != NULL){
            errorDef(yylineno, name);
            exit(0);
        }
        variables.push_back(variableEntry(type, name, offset));
    }
    void insertFunction(functionEntry f) {
        if(getVariable(f.name) != NULL){
            errorDef(yylineno, f.name);
            exit(0);
        }
        functions.push_back(f);
    }

};

