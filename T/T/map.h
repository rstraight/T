#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class map
{
    public:

        map();
       ~map();

        void loadTypesList(deque<string> mtok_typ);

        deque<int> findSymPositions(string sym);

    private:
        deque<string> map_tok_typ;       //list of token types
        deque<string> map_tok_val;       //list of token values
};

#endif // MAP_H
