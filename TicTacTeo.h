#ifndef TICTACTEO_H
#define TICTACTEO_H

#include "BoardGame_Classes.h"
using namespace std;

class TicTac_board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    TicTac_board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class TicTac_UI : public UI<char> {
public:
    TicTac_UI();
    ~TicTac_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif // TICTACTEO_H
