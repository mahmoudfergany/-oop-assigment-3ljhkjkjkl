#ifndef DIAMOND_H
#define DIAMOND_H

#include "BoardGame_Classes.h"
#include <set>
using namespace std;

class Diamond_Board : public Board<char> {
private:
    char blank_symbol = '.';
    set<pair<int, int>> valid_cells;

    void initialize_valid_cells();
    bool is_valid_cell(int x, int y) const;
    bool check_line(Player<char>* player, int length, vector<string>& directions);

public:
    Diamond_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Diamond_UI : public UI<char> {
private:
    Diamond_Board* board_ptr;

public:
    Diamond_UI();
    Diamond_UI(Diamond_Board* p);
    ~Diamond_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif