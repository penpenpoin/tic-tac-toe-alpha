#pragma once
/*
ルール
ただの三目並べ．ただし，
盤面に存在できる自分の駒の数は3つまで．3つを超えたときは1番古い駒が消える

座標の扱い
ただし，数字は内部では０～８で扱う
123
456
789

qwe
asd
zxc
 */

/// @brief ×●のボードの実装，番人なし
class Board
{
public:
    //なぜか急にパブリックで定義しないといけなくなった
    static const int BOARD_SIZE = 3;//board sizeの定義
private:
    bool maru[BOARD_SIZE][BOARD_SIZE];
    bool batu[BOARD_SIZE][BOARD_SIZE];
    bool now_turn = 0;//1=×/0=o
    int old_batu[3]= { -1 , -1, -1};
    int old_maru[3]= { -1 , -1, -1};

    void next_turn(){//次のターンに
        now_turn = !now_turn;
    }
public:
    //コンストラクタ
    Board(bool b[BOARD_SIZE][BOARD_SIZE]={0},bool m[BOARD_SIZE][BOARD_SIZE] = {0},bool = 0);
    Board(const Board&);//ディープコピーコンストラクタ


    //inline関数たち
    //maruを返す
    bool get_maru(int i, int j) const{
        return maru[i][j];
    }
    //batuを返す
    bool get_batu(int i, int j) const{
        return batu[i][j];
    }
    //今どっちの番か教える
    bool get_now_turn() const{
        return now_turn;
    }
    int check_finish() const;//勝敗が決まったかを確認する(0未決着/1×の勝ち/2〇の勝ち)
    void put(int);//ox置きます．
    bool isPlceable(int) const;//おけるときにtrueおけない時false
    void num_to_point(int,int&,int&) const;//0~8の数字を配列で参照できるようにする
};
