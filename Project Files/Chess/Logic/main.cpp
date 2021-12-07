#include"Game.hpp"
#include"Bitboard.hpp"
#include"Tests.hpp"
#include<bitset>
#include<iostream>
#include <sstream>      // std::stringstream
#include <ctime>
#include<thread>

/*Copy line below to run in terminal (at least on mac you have to do this...)
g++ main.cpp Bitboard.cpp Game\_GenerateBlockerMoves.cpp Game\_MagicNumberGeneration.cpp Game\_KingKnightMoves.cpp Game\_GeneratePseudoMoves.cpp Game\_InitializeGame.cpp Game\_HelperFunctions.cpp Game\_MakeLegalMove.cpp Game\_MakeAllMoves.cpp Game\_GenerateAttackSets.cpp Game\_Minimax.cpp Game\_EvaluatePosition.cpp Game\_IsOver.cpp -std=c++17
or "g++ *.cpp" should also work
*/



using namespace std;
string input;
bool toRead;
bool done;
bool readingRightNow;

void get_input(){
    getline(cin, input);
    toRead = true;
}

int main() {
    cin >> input;
    Move m;
    std::thread calculation;
    std::thread reading;
    done = false;
    toRead = false;
    readingRightNow = false;
    if(input == "uci"){
        cout << "id name " << Game::name << "\nid author " << Game::author << "\nuciok" << endl;
        cin >> input;
        if(input == "isready"){
            Game* g = new Game;
            g->setMode(UCI);

            cout << "readyok"<<endl;

            while(true){
                
                if(!readingRightNow){ 
                    readingRightNow = true;
                    reading = std::thread(get_input);
                }
                
                while(!toRead && !done);
                
                if(done){
                    done = false;
                    calculation.join();
                    cout << "bestmove " << g->moveToLongNotation(m) << endl;
                    continue;
                }
                else if(toRead){
                    toRead = false;
                    reading.join();
                    readingRightNow = false;
                }

                
                stringstream ss(input);
                ss >> input;
                if(input == "ucinewgame"){

                }
                else if(input == "position"){

                    ss >> input;
                    if(input == "startpos"){
                        string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
                        g->SetupGame(fen);
                    }
                    else{
                        string fen = input;
                        ss >> input;
                        fen.append(" " + input);
                        ss >> input;
                        fen.append(" " + input);
                        ss >> input;
                        fen.append(" " + input);
                        ss >> input;
                        fen.append(" " + input);
                        ss >> input;
                        fen.append(" " + input);
                        g->SetupGame(fen);
                    }
                    bool first = 1;
                    while(ss >> input){
                        if(first){
                            first = 0;
                            continue;
                        }
                        g->MakeGameMove(input);
                    }
                }
                else if(input == "go"){
                    done = false;
                    g->setStop(false);
                    search_parameters params;
                    while(ss >> input){
                        if(input == "searchmoves"){
                            while(ss >> input){
                                params.searchmoves.push_back(input);
                            }
                        }
                        else if(input ==  "ponder"){

                        }
                        else if(input == "wtime"){
                            ss >> input;
                        }
                        else if(input == "btime"){
                            ss >> input;
                        }
                        else if(input == "winc"){
                            ss >> input;
                        }
                        else if(input == "binc"){
                            ss >> input;
                        }
                        else if(input == "movestogo"){
                            ss >> input;
                        }
                        else if(input == "depth"){
                            ss >> params.depth;
                        }
                        else if(input == "nodes"){
                            ss >> params.nodes;
                        }
                        else if(input == "mate"){
                            ss >> input;
                        }
                        else if(input == "movetime"){
                            ss >> params.moveTime;
                        }
                        else if(input == "infinite"){
                            params.depth = 1000; //Meh, good enough for now
                            params.moveTime = -1;
                            params.nodes = -1;
                        }
                    }
                    calculation = std::thread(&Game::AiMove, g, params, std::ref(m), std::ref(done));
                }
                else if(input == "stop"){
                    cout << "bestmove "  << g->moveToLongNotation(m) << endl;
                    g->setStop(true);
                    calculation.join();
                    done = false;
                }
                else if(input == "quit"){
                    return 0;
                }
                else if(input == "isready"){
                    cout << "readyok" << endl;
                }
            }
        }
        else if(input == "quit"){
            return 0;
        }
    }
}