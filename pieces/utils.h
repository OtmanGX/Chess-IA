#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

int get_index(int col, int row){
    auto it = std::find(pieces.begin(), pieces.end(), piece_at(col,row));
    if (it == pieces.end()){
        return -1;
    }else{
        return std::distance(pieces.begin(), it);
    }
}

bool checkSquare(int col, int row){
    if(grid_pieces[row-1][col-1] >= 1){
        return true;
    }
    return false;
}

void highlight_tile(int col, int row,unsigned int tile, bool captured_mode = false){
    if((col <= 8 && row <= 8 && col > 0 && row > 0) && ((gamestate == WHITE_TURN && grid_pieces[row-1][col-1] != WHITE) ||(gamestate == BLACK_TURN && grid_pieces[row-1][col-1] != BLACK))){
        highlighted_tiles[tile][0] = row;
        highlighted_tiles[tile][1] = col;
    }
}

void highlight_tile_k(int col, int row,unsigned int tile, bool captured_mode = false){
    highlight_tile(col, row, tile, captured_mode);
}

#endif // UTILS_H_INCLUDED
