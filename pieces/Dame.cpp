#include "Dame.h"


void Dame::listMoves(void){
    game->clearMovesList();
    createMoveList(1,0,0);
    createMoveList(-1,0,7);
    createMoveList(0,1,14);
    createMoveList(0,-1,21);
    createMoveList(1,1,28);
    createMoveList(-1,1,35);
    createMoveList(-1,-1,42);
    createMoveList(1,-1,48);
}
