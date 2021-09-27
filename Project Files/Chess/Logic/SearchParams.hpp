#ifndef SEARCH_PARAMS
#define SEARCH_PARAMS

struct search_parameters{
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