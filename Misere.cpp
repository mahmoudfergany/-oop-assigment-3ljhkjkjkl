#include <iostream>
#include <cstdlib>
#include " Misere.h"

using namespace std;

Misere_Board::Misere_Board() : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = blank_symbol;
        }
    }
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        return false;
    }

    if (board[x][y] != blank_symbol) {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Misere_Board::is_win(Player<char>* player) {
    return false;
}

bool Misere_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) {
            return true;
        }
    }

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) {
        return true;
    }

    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) {
        return true;
    }

    return false;
}

bool Misere_Board::is_draw(Player<char>* player) {
    return (n_moves == 9);
}

bool Misere_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}

Misere_UI::Misere_UI() : UI<char>("Welcome to Misere Tic-Tac-Toe!", 3), board_ptr(nullptr) {}

Misere_UI::Misere_UI(Misere_Board* p) : UI<char>("Welcome to Misere Tic-Tac-Toe!", 3), board_ptr(p) {}

Misere_UI::~Misere_UI() {
    cout << "Misere game ended!" << endl;
}

Move<char>* Misere_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") - Enter row and column (0-2): ";
        cin >> x >> y;
    }
    else {
        for (x = 0; x < 3; x++) {
            for (y = 0; y < 3; y++) {
                if (board_ptr->get_cell(x, y) == '.') {
                    cout << "Computer chooses: " << x << ", " << y << endl;
                    return new Move<char>(x, y, player->get_symbol());
                }
            }
        }
        x = y = 0;
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}