#include "Tour.h"

void Tour::listMoves(void){
    game->clearMovesList();
    createMoveList(1,0,0);
    createMoveList(-1,0,7);
    createMoveList(0,1,14);
    createMoveList(0,-1,21);
}
