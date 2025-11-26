#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
using namespace std;

class sus_board : public Board<char> {
private:
    char blank_symbol = '.';
    Player<char>* current_player = nullptr;

public:
    sus_board();
    void set_current_player(Player<char>* p);
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class sus_UI : public UI<char> {
private:
    sus_board* board_ptr;

public:
    sus_UI();
    sus_UI(sus_board* p);
    ~sus_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif