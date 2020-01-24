#include "Piece.h"
#include "GamePlay.h"
#include <iostream>
GLuint texture[32];
using namespace std;

int grid_row, grid_col;
char grid_column;
char column[9] = {'a','b','c','d','e','f','g','h','z'};

Piece::Piece(const char* modelFile, const char* textureFile,int textureNum,char col,int row, GamePlay* game, char type){
    this->game = game;
    this->type = type;
    game->angle = 0.0f;
    loadOBJ(modelFile,vertexArray,normalArray,uvArray,numVerts);
    textureNumber = textureNum;
    loadGLTexture(textureFile,textureNumber,texture);
    c_Row = row;
    for(unsigned int i = 0; i <= sizeof(column)/sizeof(char); i++){
        if(tolower(column[i]) == tolower(col)){
            c_Col = i+1; //letter to int
        }
    }
    c_Column = col;
    if(strstr(textureFile,"black")){
        color = BLACK;
        game->board[c_Row-1][c_Col-1] = color;
    }else if(strstr(textureFile,"white")){
        color = WHITE;
        game->board[c_Row-1][c_Col-1] = color;
    }else{
        color = -1;
    }
}

void Piece::render(void){
    glBindTexture(GL_TEXTURE_2D,texture[textureNumber]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,vertexArray);
    glNormalPointer(GL_FLOAT,0,normalArray);

    glTexCoordPointer(2,GL_FLOAT,0,uvArray);

    glDrawArrays(GL_TRIANGLES,0,numVerts);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Piece::draw(bool side_piece, float pX, float pZ){
    float x = pX, z = pZ;
    glPushMatrix();

    if(!side_piece){
        x = -11.3+(2.5*c_Col);
        z = 11.3-(2.5*c_Row);
    }
    if(c_Column != 'z'){ //normal pieces
        glColor3f(1,1,1);
        glScalef(0.8,0.8,0.8);
        glTranslatef(x,-1.25,z);
    }else if(c_Column == 'z'){ //board
        glColor4ub(238,221,187,255);
        glTranslatef(0,-2,0);
    }
    render();

    glPopMatrix();
}


void Piece::pick(void){
    picked = true;
    listMoves();
    grid_row = c_Row;
    grid_col = c_Col;
    grid_column = c_Column;
}

void Piece::unpick(void){
    picked = false;
}


void Piece::createMoveList(int col_inc, int row_inc, int min_array){ //column increment,row increment
    int r = c_Row, c = c_Col;
    for(int i = 0; i < 7; i++){
        c = c_Col-(col_inc*(i+1));
        r = c_Row-(row_inc*(i+1));
        if(game->checkSquare(c,r)){ //if the square has a piece in it
            if(!((game->board[r-1][c-1] == BLACK && game->gamestate == BLACK_TURN) || (game->board[r-1][c-1] == WHITE && game->gamestate == WHITE_TURN))){
                game->highlight_tile(c,r,min_array+i,true);
            }
            break;
        }
        game->highlight_tile(c,r,min_array+i);
    }
}

void Piece::listMoves(void){
    game->clearMovesList();
}


void Piece::move(unsigned int col, unsigned int row){
    game->board[c_Row-1][c_Col-1] = 0;
    cout << "c_Col" << c_Col << endl;
    cout << "c_Row" << c_Row << endl;
    c_Col = col;
    c_Row = row;
    c_Column = column[col-1];
    game->board[c_Row-1][c_Col-1] = color;
    has_moved = true;
}

std::vector<Position*> Piece::getPossibleMoves(){
    std::vector<Position*> possiblePositions;
    possiblePositions.push_back(new Position(0,0));
    return possiblePositions;
}

void Piece::move(char col, unsigned int row){
    game->board[c_Row-1][c_Col-1] = 0;
    for(unsigned int i = 0; i <= sizeof(column)/sizeof(char); i++){
        if(tolower(column[i]) == tolower(col)){
            c_Col = i+1;
        }
    }
    c_Row = row;
    c_Column = col;
    game->board[c_Row-1][c_Col-1] = color;
    for(int i = 0; i <= game->pieces.size()-1; i ++){
        game->pieces.at(i)->en_passant = false;
    }
    has_moved = true;
}
