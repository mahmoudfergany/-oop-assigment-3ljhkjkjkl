#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
using namespace std;

class Four_in_a_row_board : public Board<char> {
private:
    char blank_symbol = '.';
    Player<char>* current_player = nullptr;

public:
    Four_in_a_row_board();
    void set_current_player(Player<char>* p);
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

private:
    int get_lowest_empty_row(int col);
};

class Four_in_a_row_UI : public UI<char> {
private:
    Four_in_a_row_board* board_ptr;

public:
    Four_in_a_row_UI();
    Four_in_a_row_UI(Four_in_a_row_board* p);
    ~Four_in_a_row_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

};

#endif