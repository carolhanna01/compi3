//
// Created by Carol Hanna on 15/12/2019.
//

#ifndef HW3_OUTPUT_CPP_SCOPES_H
#define HW3_OUTPUT_CPP_SCOPES_H
#include <stack>
#include <vector>
#include "hw3_output.hpp"
using std;
using output;


#typedef vector<tableEntry> scope;
#define INT_SIZE 1
#define BOOL_SIZE 1

class tableEntry{
public:
    string name;
    string type;
    int offset;
    tableEntry(string name = "", string type = "", int offset = 0) : name(name), string(string), offset(offset) { }
};
class scopeTables{
public:
    stack<scope> scopesTable;
    stack<int> offsetsTable;

    void openScope(){
        scope newScope;
        scopesTable.push_back(newScope);
        int curr_Offset = offsetsTable.top()
        offsets_Stack.push_back(curr_Offset);
    }

    void closeScope(){
        scope toRemove = scopesTable.top();
        for (int i = 0; i < toRemove.size(); i++){

            printId(toRemove[i].name, )
            void printID(const string& id, int offset, const string& type);

        }
        scopesTable
        endScope();


    }
};

#endif //HW3_OUTPUT_CPP_SCOPES_H
