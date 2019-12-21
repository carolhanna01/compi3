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

#define INT_SIZE 1
#define BOOL_SIZE 1
#define startParamOffset =1;

namespace scopeTables{
        template <typename t>
        class entry{
            public:
            const string &name;
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

        class variableEntry :
        public entry<string>{
            public:
            int offset;
            variableEntry(string
            type = "", string
            name = "", int
            offset = 0):entry(name, type), offset(offset)
            {}

        };
        class functionEntry :
        public entry<functionType>{
            public:
            int offset;
            functionEntry(functionType
            type, string
            name = "", int
            offset = 0):entry(name, type), offset(offset){};
        };



    class scope{
            public:

            vector<variableEntry> variables;
            vector<functionEntry > functions;
            bool insideLoop;
            functionType* currentFunc;


            // Constructor
            scope(bool inLoop){
            variables = vector<variableEntry>();
            functions = vector<functionEntry>();
            insideLoop =inLoop;
            currentFunc = nullptr;
            }

            variableEntry* getVariable(const string &name) {
                for (variableEntry& v : variables) {
                    if (name == v.name) {
                        return &v;
                    }
                }
            }
            functionEntry* getFunction(const string &name) {
                for (functionEntry& f : functions) {
                    if (name == f.name) {
                        return &f;
                    }
                }
            }

            void insertVariable(variableEntry v) {
                if (getVariable(v.name) != nullptr) {
                    errorDef(yylineno, v.name);
                    exit(0);
                }
                variables.push_back(variableEntry(v.type, v.name, v.offset));
            }
            void insertFunction(functionEntry f) {
                if (getVariable(f.name) != nullptr) {
                    errorDef(yylineno, f.name);
                    exit(0);
                }
                functions.push_back(f);
            }

            void addScope (stack<scope*> scopes, stack<int> offsets){
                scopes.push(new scope(scopes.top()));
                offsets.push(offsets.top());
             }

            void removeScope (stack<scope*> scopes, stack<int> offsets){
                endScope();
                //add impl depending on what you need
            }

        };




}
