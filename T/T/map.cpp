
#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stdio.h>
#include <string.h>

#include "map.h"

using namespace std;

map::map()
{

}

map::~map()
{

}

//==================================================================
void map::loadTypesList(deque<string> mtok_typ)
{
     map_tok_typ = mtok_typ;
}

//==================================================================
deque<int> map::findSymPositions(string sym)
{
    deque<int> result;
    int i = 0;

    while( i < map_tok_typ.size() ){
       if(map_tok_typ[i] == sym){

       }//if
    }//while

    result.push_back(-1);
    return result;
}
