#include "Diamond.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Diamond_Board::Diamond_Board() : Board<char>(5, 5) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = ' ';
        }
    }

    initialize_valid_cells();

    for (const auto& cell : valid_cells) {
        board[cell.first][cell.second] = blank_symbol;
    }
}

void Diamond_Board::initialize_valid_cells() {
    valid_cells.insert({ 0, 2 });

    valid_cells.insert({ 1, 1 });
    valid_cells.insert({ 1, 2 });
    valid_cells.insert({ 1, 3 });

    for (int j = 0; j < 5; j++) {
        valid_cells.insert({ 2, j });
    }

    valid_cells.insert({ 3, 1 });
    valid_cells.insert({ 3, 2 });
    valid_cells.insert({ 3, 3 });

    valid_cells.insert({ 4, 2 });
}

bool Diamond_Board::is_valid_cell(int x, int y) const {
    return valid_cells.count({ x, y }) > 0;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5) {
        cerr << "Out of bounds!\n";
        return false;
    }

    if (!is_valid_cell(x, y)) {
        cerr << "Invalid cell! Not in diamond pattern.\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cerr << "Cell already occupied!\n";
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Diamond_Board::check_line(Player<char>* player, int length, vector<string>& directions) {
    char sym = player->get_symbol();
    directions.clear();

    for (int i = 0; i < 5; i++) {
        int count = 0;
        for (int j = 0; j < 5; j++) {
            if (is_valid_cell(i, j) && board[i][j] == sym) {
                count++;
            }
            else {
                count = 0;
            }
            if (count == length) {
                directions.push_back("horizontal");
                break;
            }
        }
    }

    for (int j = 0; j < 5; j++) {
        int count = 0;
        for (int i = 0; i < 5; i++) {
            if (is_valid_cell(i, j) && board[i][j] == sym) {
                count++;
            }
            else {
                count = 0;
            }
            if (count == length) {
                directions.push_back("vertical");
                break;
            }
        }
    }

    for (int start = -2; start <= 2; start++) {
        int count = 0;
        for (int i = 0; i < 5; i++) {
            int j = i + start;
            if (j >= 0 && j < 5 && is_valid_cell(i, j) && board[i][j] == sym) {
                count++;
            }
            else {
                count = 0;
            }
            if (count == length) {
                directions.push_back("diagonal");
                break;
            }
        }
    }

    for (int start = 2; start <= 6; start++) {
        int count = 0;
        for (int i = 0; i < 5; i++) {
            int j = start - i;
            if (j >= 0 && j < 5 && is_valid_cell(i, j) && board[i][j] == sym) {
                count++;
            }
            else {
                count = 0;
            }
            if (count == length) {
                directions.push_back("anti-diagonal");
                break;
            }
        }
    }

    return !directions.empty();
}

bool Diamond_Board::is_win(Player<char>* player) {
    vector<string> dirs_3, dirs_4;

    bool has_3 = check_line(player, 3, dirs_3);
    bool has_4 = check_line(player, 4, dirs_4);

    if (!has_3 || !has_4) return false;

    for (const string& d3 : dirs_3) {
        for (const string& d4 : dirs_4) {
            if (d3 != d4) {
                return true;
            }
        }
    }

    return false;
}

bool Diamond_Board::is_lose(Player<char>* player) {
    return false;
}

bool Diamond_Board::is_draw(Player<char>* player) {
    if (n_moves == 15 && !is_win(player)) {
        return true;
    }
    return false;
}

bool Diamond_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Diamond_UI::Diamond_UI() : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 2), board_ptr(nullptr) {}

Diamond_UI::Diamond_UI(Diamond_Board* p) : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 2), board_ptr(p) {}

Diamond_UI::~Diamond_UI() {
    cout << "Diamond game ended. Thanks for playing!\n";
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << ") - Your turn\n";
        cout << "Enter row and column (0-4): ";
        cin >> x >> y;
    }
    else {
        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board_ptr->get_cell(i, j) == '.') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (!empty_cells.empty()) {
            int idx = rand() % empty_cells.size();
            x = empty_cells[idx].first;
            y = empty_cells[idx].second;
            cout << "Computer chooses: " << x << ", " << y << endl;
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}