

#ifndef GAMES_CREATION_PYRAMID_TICTAC_H
#define GAMES_CREATION_PYRAMID_TICTAC_H
#include "BoardGame_Classes.h"

class Py_TicTac_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    Py_TicTac_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char> *) {return false;};
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Py_TicTac_UI : public UI<char> {
public:
    Py_TicTac_UI();
    ~Py_TicTac_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif //GAMES_CREATION_PYRAMID_TICTAC_H