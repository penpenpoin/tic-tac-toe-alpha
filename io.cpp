#include <iostream>
#include "board.hpp"

/// @brief 初期設定
/// @param b is bool
bool init_setting(){
    bool b;
    do
    {
        std::cout << "先攻か後攻どちらにしますか？0(先攻)/1(後攻)";
        std::cin >> b;
    } while (b != 1 && b != 0);
    std::cout << "あなた(o)は" << (b?"後攻":"先攻") << "です" << std::endl;
    return b;
}


int alphabet_to_potision(char s){
        //switchで実装した方がコンパイル時に早くなるらしい（未検証）し可読性が上がる
    switch(s){
        case 'q': return 0;
        case 'w': return 1;
        case 'e': return 2;
        case 'a': return 3;
        case 's': return 4;
        case 'd': return 5;
        case 'z': return 6;
        case 'x': return 7;
        case 'c': return 8;
        default: return -1;
    }
    /* char str[9] = {'q','w','e','a','s','d','z','x','c'};
    for(int i = 0; i < 9; i++){
        if(s == str[i]){
            return i;
        }
    }
    return -1; */
}

int input(){
    std::cout << "あなたの番です.";
    char str;
    do{
    std::cout << "qweasdzxcの中から入力してください";
    std::cin >> str;
    }while(alphabet_to_potision(str) == -1);
    return alphabet_to_potision(str);
}


void view_board(Board &banmen){//現在のボードを表示
    for(int i = 0; i < 3; i++){
        for(int j= 0;j<3 ; j++){
            if(banmen.get_batu(i,j)){
                std::cout << "x";
            }else if(banmen.get_maru(i,j)){
                std::cout << "o";
            }else{
                std::cout << " ";
            }
            if(j == 2){
                break;
            }
            std::cout << "|";
        }
        if(i == 2){
            break;
        }
        std::cout << std::endl << "-----" << std::endl;
    }
    std::cout << std::endl;
}

void finish(Board &board){
    if(board.check_finish() == 1){
        std::cout << "aiの勝ちです．お疲れさまでした．"<<std::endl;
    }
    else if(board.check_finish() == 2){
        std::cout << "あなたの勝ちです．おめでとうございます．" << std::endl;
    }else{
        std::cout << "error" << std::endl;
    }
}
