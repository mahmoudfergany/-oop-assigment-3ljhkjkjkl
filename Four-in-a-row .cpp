#include "Four-in-a-row.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Four_in_a_row_board::Four_in_a_row_board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

void Four_in_a_row_board::set_current_player(Player<char>* p) {
    current_player = p;
}

int Four_in_a_row_board::get_lowest_empty_row(int col) {    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }
    return -1;
}

bool Four_in_a_row_board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) {
        return false;
    }

    int row = get_lowest_empty_row(col);
    if (row == -1) {
        return false;
    }

    board[row][col] = mark;
    n_moves++;
    return true;
}

bool Four_in_a_row_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == sym &&
                board[row][col + 1] == sym &&
                board[row][col + 2] == sym &&
                board[row][col + 3] == sym) {
                return true;
            }
        }
    }

     for (int col = 0; col < columns; col++) {
        for (int row = 0; row <= rows - 4; row++) {
            if (board[row][col] == sym &&
                board[row + 1][col] == sym &&
                board[row + 2][col] == sym &&
                board[row + 3][col] == sym) {
                return true;
            }
        }
    }

    for (int row = 0; row <= rows - 4; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == sym &&
                board[row + 1][col + 1] == sym &&
                board[row + 2][col + 2] == sym &&
                board[row + 3][col + 3] == sym) {
                return true;
            }
        }
    }

    for (int row = 0; row <= rows - 4; row++) {
        for (int col = 3; col < columns; col++) {
            if (board[row][col] == sym &&
                board[row + 1][col - 1] == sym &&
                board[row + 2][col - 2] == sym &&
                board[row + 3][col - 3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool Four_in_a_row_board::is_lose(Player<char>* player) {
    return false;
}

bool Four_in_a_row_board::is_draw(Player<char>* player) {
    for (int col = 0; col < columns; col++) {
        if (board[0][col] == blank_symbol) {
            return false;
        }
    }
    return !is_win(player);
}

bool Four_in_a_row_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Four_in_a_row_UI::Four_in_a_row_UI()
    : UI<char>("Welcome to Four-in-a-row Game!", 2), board_ptr(nullptr) {}

Four_in_a_row_UI::Four_in_a_row_UI(Four_in_a_row_board* p)
    : UI<char>("Welcome to Four-in-a-row Game!", 2), board_ptr(p) {}

Player<char>* Four_in_a_row_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Four_in_a_row_UI::get_move(Player<char>* player) {
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter column (0-6) to drop your "
            << player->get_symbol() << ": ";
        cin >> col;

        while (col < 0 || col > 6) {
            cout << "Invalid column! Please enter a number between 0 and 6: ";
            cin >> col;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        vector<int> available_columns;
        for (int c = 0; c < 7; c++) {
            if (board_ptr->get_cell(0, c) == '.') { 
                available_columns.push_back(c);
            }
        }

        if (!available_columns.empty()) {
            col = available_columns[rand() % available_columns.size()];
            cout << "Computer chooses column " << col << endl;
        }
        else {
            col = 0;
        }
    }

   return new Move<char>(0, col, player->get_symbol());
}



Four_in_a_row_UI::~Four_in_a_row_UI() {
    cout << "Four-in-a-row Game finished!" << endl;
}