//
// Created by Carol Hanna on 15/12/2019.
//


#include <iostream>
#include <stack>
#include <vector>
#include "hw3_output.hpp"
extern int yylineno;

using namespace std;
using namespace output;

#define INT_SIZE 1
#define BOOL_SIZE 1
#define startParamOffset = -1;
#define YYSTYPE variableEntry*

namespace scopeTables{

    template <typename t>
        class entry {
            public:
            const string &name;
            t type;
            int offset;
            entry(string name="", t type= t(), int offset=0):name(name), type(type), offset(offset){};
        };

        class functionType {
        public:
            string returnType;
            vector<string> paramTypes;

            functionType(string returnType= "", vector<string> paramTypes= vector<string>():
            returnType(returnType), paramTypes(paramTypes){};

            void addParam(string paramType) {
                paramTypes.push_back(paramType);
            }
        };

        class enumType {
        public:
            vector<string> values;

            enumType(vector<string> values = vector<string>()) : values(values){};
        };


    typedef entry<string> variableEntry;
    typedef entry<functionType> functionEntry;
    typedef entry<enumType> enumEntry; 

    class Scope{
            public:

            vector<variableEntry> variables;
            vector<functionEntry > functions;
            vector<enumEntry> enums;
            bool insideLoop;
            functionType* currentFunc;


            // Constructor
            Scope(){
            variables = vector<variableEntry>();
            functions = vector<functionEntry>();
            insideLoop =false;
            currentFunc = nullptr;
            }

            variableEntry* getVariable(const string &name) {
                for (variableEntry& v : variables) {
                    if (name == v.name) {
                        return &v;
                    }
                }
                return nullptr;
            }

            functionEntry* getFunction(const string &name) {
                for (functionEntry& f : functions) {
                    if (name == f.name) {
                        return &f;
                    }
                }
                return nullptr;
            }
            enumEntry* getEnum(const string &name) {
                for (enumEntry& e : enums) {
                    if (name == e.name) {
                        return &e;
                    }
                }
                return nullptr;
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
            void insertEnum(enumEntry e) {
                if (getEnum(e.name) != nullptr) {
                    errorDef(yylineno, e.name);
                    exit(0);
                }
                enums.push_back(e);
            }



            void printVariables(){
                for(variableEntry v: variables)
                    printID(v.name, v.offset, v.type);
            }
            void printFunctions(){
                for(functionEntry f : functions)
                    printID(f.name, 0, makeFunctionType(f.type.returnType, f.type.paramTypes));
            }
            void printEnums(){
                for(enumEntry e : enums)
                    printEnumType(e.name, e.type.values);
            }


        };

    void addScope (stack<Scope*> scopes, stack<int> offsets){
        scopes.push(new Scope(scopes.top()));
        offsets.push(offsets.top());
    }

    void removeScope (stack<Scope*> scopes, stack<int> offsets){
        endScope();
        scopes.top()->printVariables();
        scopes.top()->printEnums();
        scopes.pop();
        offsets.pop();
    }

}
