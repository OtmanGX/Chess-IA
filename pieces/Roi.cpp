#include "Roi.h"

void Roi::listMoves(void){
    game->clearMovesList();
    game->highlight_tile_k(c_Col+1,c_Row,0);
    game->highlight_tile_k(c_Col-1,c_Row,1);
    game->highlight_tile_k(c_Col,c_Row+1,2);
    game->highlight_tile_k(c_Col,c_Row-1,3);
    game->highlight_tile_k(c_Col+1,c_Row+1,4);
    game->highlight_tile_k(c_Col+1,c_Row-1,5);
    game->highlight_tile_k(c_Col-1,c_Row+1,6);
    game->highlight_tile_k(c_Col-1,c_Row-1,7);
    if(!has_moved){
        if(!game->checkSquare(c_Col-3,c_Row) && !game->checkSquare(c_Col-2,c_Row) && !game->checkSquare(c_Col-1,c_Row)){
            game->highlight_tile(c_Col-2,c_Row,8);
        }
        if(!game->checkSquare(c_Col+2,c_Row) && !game->checkSquare(c_Col+1,c_Row)){
            game->highlight_tile(c_Col+2,c_Row,9);
        }
    }
}

void Roi::move(unsigned int col, unsigned int row){
    game->board[c_Row-1][c_Col-1] = 0;
    if(c_Col-col == 2){
        if(color == WHITE){
            game->piece_at(1,1)->move((unsigned int)4,(unsigned int)1);
        }else if(color == BLACK){
            game->piece_at(1,8)->move((unsigned int)4,(unsigned int)8);
        }
    }else if(c_Col-col == -2){
        if(color == WHITE){
            game->piece_at(8,1)->move((unsigned int)6,(unsigned int)1);
        }else if(color == BLACK){
            game->piece_at(8,8)->move((unsigned int)6,(unsigned int)8);
        }
    }
    c_Col = col;
    c_Row = row;
    c_Column = column[col-1];
    game->board[c_Row-1][c_Col-1] = color;
    has_moved = true;
}
