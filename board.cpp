#include "board.hpp"

/// @brief board classのコンストラクタ
/// @param b　×のボード
/// @param m　●のボード
Board::Board(bool b[BOARD_SIZE][BOARD_SIZE],bool m[BOARD_SIZE][BOARD_SIZE],bool turn){
    for(int i =0 ; i < BOARD_SIZE; i++){//メンバイニシャライザをつかう
        for(int j = 0; j< BOARD_SIZE; j++){
            maru[i][j] = m[i][j];
            batu[i][j] = b[i][j];
        }
    }
    if(turn){
        next_turn();
    }
}

Board::Board(const Board& other){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            batu[i][j] = other.batu[i][j];
            maru[i][j] = other.maru[i][j];
        }
    }
    now_turn = get_now_turn();
    for (int i = 0; i < 3; i++)
    {
        this -> old_batu[i] = other.old_batu[i];
        this -> old_maru[i] = other.old_maru[i];
    }

}

void Board::num_to_point(int point,int &x,int &y) const{
    y = point / 3;
    x = point % 3;
}

bool Board::isPlceable(int point) const{
    int x,y;
    num_to_point(point,x,y);
    return (maru[y][x] || batu[y][x]);
}

void Board::put(int point){
    int x,y;
    num_to_point(point,x,y);
    if(!isPlceable(point)){
        if(now_turn){
            if(old_batu[2] != -1){
                int t,v;
                num_to_point(old_batu[2],t,v);
                batu[v][t] = 0;
            }
            batu[y][x] = 1;
            old_batu[2] = old_batu[1];
            old_batu[1] = old_batu[0];
            old_batu[0] = point;
            next_turn();
        }else{
            if(old_maru[2] != -1){
                int t,v;
                num_to_point(old_maru[2],t,v);
                maru[v][t] = 0;
            }
            maru[y][x] = 1;
            old_maru[2] = old_maru[1];
            old_maru[1] = old_maru[0];
            old_maru[0] = point;
            next_turn();
        }
    }

}

int Board::check_finish() const{
    int batuCount=0;
    int maruCount=0;
    //横方向の確認
    for(int i = 0; i < BOARD_SIZE ; i++){
        batuCount = 0; maruCount = 0;
        for(int j = 0; j < BOARD_SIZE ; j++){
            batuCount += static_cast<int>(batu[i][j]);
            maruCount += static_cast<int>(maru[i][j]);
        }
        if(batuCount == BOARD_SIZE){
            return 1;
        }else if(maruCount == BOARD_SIZE){
            return 2;
        }
    }
    //縦方向の確認
    for(int i = 0; i < BOARD_SIZE ; i++){
        batuCount = 0; maruCount = 0;
        for(int j = 0; j < BOARD_SIZE ; j++){
            batuCount += static_cast<int>(batu[j][i]);
            maruCount += static_cast<int>(maru[j][i]);
        }
        if(batuCount == BOARD_SIZE){
            return 1;
        }else if(maruCount == BOARD_SIZE){
            return 2;
        }
    }
    //斜め方向の確認
    batuCount = 0; maruCount = 0;
    for(int i = 0; i < BOARD_SIZE; i++){//左上から右下
        batuCount += static_cast<int>(batu[i][i]);
        maruCount += static_cast<int>(maru[i][i]);
    }
    if(batuCount == BOARD_SIZE){
        return 1;
    }else if(maruCount == BOARD_SIZE){
        return 2;
    }
    batuCount = 0; maruCount = 0;

    for(int i = 0; i < BOARD_SIZE ; i++){
        batuCount += static_cast<int>(batu[i][BOARD_SIZE-1-i]);
        maruCount += static_cast<int>(maru[i][BOARD_SIZE-1-i]);
    }
    if(batuCount == BOARD_SIZE){
        return 1;
    }else if(maruCount == BOARD_SIZE){
        return 2;
    }
    return 0;//ゲーム続行！
}
