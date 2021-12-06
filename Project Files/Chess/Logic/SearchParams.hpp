#ifndef SEARCH_PARAMS
#define SEARCH_PARAMS

#include<vector>
#include<string>

struct search_parameters{
    std::vector<std::string> searchmoves;
    int depth;
    int nodes;
    int mate;
    int moveTime;
    bool infinite;

    search_parameters(){
        searchmoves = std::vector<std::string>();
        depth = -1;
        nodes =-1;
        mate = -1;
        moveTime = -1;
        infinite = false;
    }
};


#endif