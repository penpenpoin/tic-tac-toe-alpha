#include <iostream>
#include "board.hpp"


using std::cout;
using std::cin;

bool init_setting();//初期設定します!
void view_board(Board&);//現在の盤面を表示してくれる
int alphabet_to_potision(char);//入力文字座標を数字座標に変換する
int input();//入力を促します.
void finish(Board&);//終わる時
int minimax(const Board&,int=0);//ai

bool empty_board[3][3] = {0};

int main(){
    Board now(empty_board,empty_board,init_setting());//init_settingは良いとは言えないかも
    int aipoint;
    while (now.check_finish() == 0)
    {
        view_board(now);
        if(now.get_now_turn()){//AIのターン
            aipoint = minimax(now);
            cout << "aiはここに置きます:" << aipoint << std::endl;
            now.put(aipoint);//ここにai
        }else{//playerのターン
            now.put(input());
        }
    }
    view_board(now);
    finish(now);
}

