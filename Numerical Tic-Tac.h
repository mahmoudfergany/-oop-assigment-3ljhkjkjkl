

#ifndef GAMES_CREATION_NUMERICAL_TIC_TAC_H
#define GAMES_CREATION_NUMERICAL_TIC_TAC_H

#include "OOP-ASSIGMENT-3-GAMES-/BoardGame_Classes.h"


class num_TicTac_board : public Board<int> {
private:
    int blank_symbol = 0;
public:
    num_TicTac_board();
    bool is_lose(Player<int> *) {return false;};
    bool is_win(Player<int> *) override;
    bool is_draw(Player<int> *) override;
    bool update_board(Move<int> *move) override;
    bool game_is_over(Player<int> *) override;
};

class num_TicTac_UI : public UI<int> {
public:
    num_TicTac_UI();
    ~num_TicTac_UI();
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
};

#endif //GAMES_CREATION_NUMERICAL_TIC_TAC_H