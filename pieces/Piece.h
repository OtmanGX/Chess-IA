#ifndef PIECE_H
#define PIECE_H
#include "GamePlay.h"
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

#define BLACK 1337
#define WHITE 6969

//class GamePlay;
//global variables
extern int grid_row, grid_col;
extern char grid_column,column[9];


//global functions
extern void setShaders(void);
extern void drawGrid(void);
extern void initDLs(void);
extern void clearMovesList(void);

class Piece{
    public:
        int c_Row, c_Col, color, textureNumber, value, numVerts; //c_Row = current row c_Col = current column
        char c_Column, type;
        GLfloat *vertexArray,*normalArray,*uvArray;
        float var_swag;
	    bool picked = false, en_passant = false, has_moved = false;
	    GamePlay *game;

        explicit Piece(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay* game,char type);
        ~Piece(){free(vertexArray);free(normalArray);free(uvArray);};

        virtual void draw(bool side_piece = false, float x = 0.0f, float y = 0.0f);
	    virtual void listMoves(void);
        virtual void move(unsigned int col, unsigned int row);
        virtual void move(char col, unsigned int row);

	    void pick(void);
	    void unpick(void);
        void createMoveList(int col_inc, int row_inc, int min_array);
        void render(void);
};




//
#endif // PION_H
