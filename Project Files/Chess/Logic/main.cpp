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
    if(input == "uci"){ //If the engine is supposed to run in UCI mode, this will be the first input
        cout << "id name " << Game::name << "\nid author " << Game::author << endl; //According to protocoll we have to identify the engine. 
        cout << "\nuciok" << endl; //After the identification process we print available settings, (none currently), and then print uciok
        cin >> input;
        if(input == "isready"){ //Time to start the engine
            Game* g = new Game;
            g->setMode(UCI);

            cout << "readyok"<<endl; //Tell GUI that we are done intializing

            while(true){
                
                if(!readingRightNow){ 
                    readingRightNow = true;
                    reading = std::thread(get_input);
                }
                
                while(!toRead && !done); //Wait until we get input from GUI OR engine is done calculating
                
                if(done){ //Print the best move and cleanup threads.
                    done = false;
                    calculation.join();
                    cout << "bestmove " << g->moveToLongNotation(m) << endl;
                    continue;
                }
                else if(toRead){ //Cleanup threads
                    toRead = false;
                    reading.join();
                    readingRightNow = false;
                }

                
                stringstream ss(input);
                ss >> input;
                if(input == "ucinewgame"){ //The gui tells us the next position command is a new game. Currently we don't care

                }
                else if(input == "position"){ //The gui tells us what position to setup

                    ss >> input;
                    if(input == "startpos"){
                        string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
                        g->SetupGame(fen);
                    }
                    else{ //This is ugly and should be rewritten in the future
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
                        if(first){ //The first word after the fen string will be "moves", so we skip it
                            first = 0;
                            continue;
                        }
                        g->MakeGameMove(input); //Make the move the GUI tells us to make
                    }
                }
                else if(input == "go"){ //The GUI tells the engine to start calculating.
                    done = false;
                    g->setStop(false);
                    search_parameters params;
                    while(ss >> input){
                        if(input == "searchmoves"){ //Limit search to following moves. (Currently unimplemented)
                            while(ss >> input){
                                params.searchmoves.push_back(input);
                            }
                        }
                        else if(input ==  "ponder"){ //Start search in ponder mode. (Currently unimplemented)

                        }
                        else if(input == "wtime"){ //How much time does white have remaining (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "btime"){ //how much time does black have remaining (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "winc"){ //The time increase per move for white (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "binc"){ //The time increase per move for black (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "movestogo"){ //The amount of moves left until the next time controll (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "depth"){ //How many plies (halfmoves) to search
                            ss >> params.depth;
                        }
                        else if(input == "nodes"){ //How many nodes to search
                            ss >> params.nodes;
                        }
                        else if(input == "mate"){ //Search for mate in N moves (Currently unimplemented)
                            ss >> input;
                        }
                        else if(input == "movetime"){ //Search for N milliseconds.
                            ss >> params.moveTime;
                        }
                        else if(input == "infinite"){ //Search until a stop command is sent.
                            params.depth = -1; 
                            params.moveTime = -1;
                            params.nodes = -1;
                        }
                    }
                    calculation = std::thread(&Game::AiMove, g, params, std::ref(m), std::ref(done)); //Start the calculation on a new thread so we can still recieve input
                }
                else if(input == "stop"){ //Immediately stop calculating and print the best move
                    cout << "bestmove "  << g->moveToLongNotation(m) << endl;
                    g->setStop(true);
                    calculation.join();
                    done = false;
                }
                else if(input == "quit"){ //Quit the engine
                    delete g;
                    return 0;
                }
                else if(input == "isready"){ //Check if the engine is ready for input
                    cout << "readyok" << endl;
                }
            }
            delete g;
        }
        else if(input == "quit"){ //Quit the engine
            return 0;
        }
    }
}