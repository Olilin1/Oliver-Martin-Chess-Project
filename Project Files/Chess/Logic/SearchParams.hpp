#ifndef SEARCH_PARAMS
#define SEARCH_PARAMS

#include<vector>
#include<string>

struct search_parameters{
    std::vector<std::string> searchmoves;
    bool ponder;
    int wtime;
    int btime;
    int winc;
    int binc;
    int movesToGo;
    int depth;
    int nodes;
    int mate;
    int moveTime;
    bool infinite;

    search_parameters(){
        searchmoves = std::vector<std::string>();
        ponder = false;
        wtime = -1;
        btime = -1;
        winc = -1;
        binc = -1;
        movesToGo = -1;
        depth = -1;
        nodes =-1;
        mate = -1;
        moveTime = -1;
        infinite = false;
    }
};


#endif