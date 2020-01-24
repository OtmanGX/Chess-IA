#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../textfile.h"
#include "../loaders.h"
#include <vector>
#include <algorithm>

extern GLuint p,f,v,tile;

class Piece;
enum GAMESTATE : int{
    MENU,WHITE_TURN,BLACK_TURN,WHITE_WIN,BLACK_WIN,TIE
};

class GamePlay
{
    public:
        int board[8][8]={0},highlighted_tiles[56][2]={0};
        GAMESTATE gamestate; //enum which stores current state, like player turns and menu
        bool ia = false;
        std::vector<Piece*> pieces,side_pieces;
        float angle = 0.0f;
        //methods
        GamePlay(bool ia=false);
        GamePlay(const GamePlay&);
        void initDLs(void);
        void drawGrid(void);
        Piece* piece_at(int col, int row);
        void remove_piece(int col, int row);
        bool checkSquare(int col, int row);
        int get_index(int col, int row);
        void highlight_tile(int col, int row,unsigned int tile, bool captured_mode = false);
        void highlight_tile_k(int col, int row,unsigned int tile, bool captured_mode = false);
        void clearMovesList(void);
        bool isCheckMate();
        virtual ~GamePlay();

    protected:

    private:
};

#endif // GAMEPLAY_H
