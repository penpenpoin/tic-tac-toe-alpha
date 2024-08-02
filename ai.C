#include <vector>
#include <algorithm>
#include <iostream>
#include "board.hpp"

//int ai(const Board& now){}

//ai目線の評価値を返す
int evaluation_board(const Board &now){
    const int WEIGHT[9] = {30,10,30,10,50,10,30,10,30};
    int score = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(now.get_maru(i,j) == 1 ){
                score -= WEIGHT[i*3 + j];
            }else if(now.get_batu(i,j) == 1){
                score += WEIGHT[i*3 + j];
            }
        }
    }
    if(now.check_finish() == 1){
        score += 10;
    }else if(now.check_finish() == 2){
        score -= 10;
    }
    // std::cout <<"score is " <<score << std::endl;
    return score;
}


//minimaxの雑な実装
int minimax(const Board &now, int depth = 0){

    if(depth >= 10){
        return evaluation_board(now);
    }
    if(now.check_finish() > 0){
        return evaluation_board(now);
    }

    Board next(now);
    std::vector<int> scores{0,1,2,3,4,5,6,7,8};
    depth++;
    for(int i = 0 ; i < 9; i++){
        if(next.isPlceable(i)){
            next.put(i);
            scores[i] = minimax(next,depth);
        }
    }
    int nice_choice = 0;
    int point = 0;
    if(depth%2 == 0){
        nice_choice = *std::min_element(scores.begin(),scores.end());
    }else{
        nice_choice = *std::max_element(scores.begin(),scores.end());
    }
    //同じ点数の場合におけないところを指定する可能性があることに注意.今回は雑に重みを10倍して元の値を０～８にすることで回避．
    point = std::distance(scores.begin(), std::find(scores.begin(), scores.end(), nice_choice));

    // std::cout << "the point is "<< point << std::endl;
    if(depth == 1){
        return point;
    }else{
        return nice_choice;
    }
}
