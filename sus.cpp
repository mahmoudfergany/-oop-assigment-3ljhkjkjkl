#include "sus.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Board Implementation
sus_board::sus_board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

void sus_board::set_current_player(Player<char>* p) {
    current_player = p;
}

bool sus_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

bool sus_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == 'S' && b == 'U' && c == 'S' && a != blank_symbol;
        };

    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool sus_board::is_lose(Player<char>* player) {
    return false;
}

bool sus_board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool sus_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

sus_UI::sus_UI() : UI<char>("Welcome to SUS Game", 3), board_ptr(nullptr) {}

sus_UI::sus_UI(sus_board* p) : UI<char>("Welcome to FCAI SUS Game by Dr El-Ramly", 3), board_ptr(p) {}

Player<char>* sus_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* sus_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", please enter your move (row and column 0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {

        for (x = 0; x < 3; x++) {
            for (y = 0; y < 3; y++) {
                if (board_ptr->get_cell(x, y) == '.') {
                    cout << "Computer chooses position (" << x << ", " << y << ")\n";
                    return new Move<char>(x, y, player->get_symbol());
                }
            }
        }
        x = y = 0; 
    }
    return new Move<char>(x, y, player->get_symbol());
}
sus_UI::~sus_UI() {
    cout << "SUS Game finished!" << endl;
}