#include "Cavalier.h"

void Cavalier::draw(bool side_piece, float pX, float pZ){
    float x = pX, z = pZ;
    glPushMatrix();

    if(!side_piece){
        x = -11.3+(2.5*c_Col);
        z = 11.3-(2.5*c_Row);
    }
    glColor3f(1,1,1);
    glScalef(0.8,0.8,0.8);
    glTranslatef(-7.3+x,-2.25,-0.8+z);
    render();

    glPopMatrix();
}


void Cavalier::listMoves(void){
    game->clearMovesList();
    game->highlight_tile(c_Col-1,c_Row+2,0);
    game->highlight_tile(c_Col+1,c_Row+2,1);
    game->highlight_tile(c_Col-1,c_Row-2,2);
    game->highlight_tile(c_Col+1,c_Row-2,3);
    game->highlight_tile(c_Col-2,c_Row+1,4);
    game->highlight_tile(c_Col-2,c_Row-1,5);
    game->highlight_tile(c_Col+2,c_Row+1,6);
    game->highlight_tile(c_Col+2,c_Row-1,7);
}
