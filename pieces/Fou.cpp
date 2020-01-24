#include "Fou.h"

void Fou::listMoves(void){
    game->clearMovesList();
    createMoveList(1,1,0);
    createMoveList(-1,1,7);
    createMoveList(-1,-1,14);
    createMoveList(1,-1,21);
}
