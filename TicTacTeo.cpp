#include "TicTacTeo.h"
#include <iostream>
#include <iomanip>

using namespace std;

TicTac_board::TicTac_board() : Board<char>(4,4) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = blank_symbol;
        }
    }
    board[0][0] = 'O';
    board[0][2] = 'O';
    board[3][1] = 'O';
    board[3][3] = 'O';
    board[0][1] = 'X';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][2] = 'X';
}

bool TicTac_board::update_board(Move<char>* move ) {
    int x1,y1;
    x1 = move->get_x();
    y1 = move->get_y();
    cout << "Enter the position you want to move to: ";
    int x2, y2;
    cin >> x2 >> y2;

    if (x1 >= 4 || x2 >= 4 || y1 >= 4 || y2 >= 4) {
        cerr << "Wrong position , Try again." << endl;
        return false;
    }

    if (x1 <= -1 || x2 <= -1 || y1 <= -1 || y2 <= -1) {
        cerr << "Wrong position , Try again." << endl;
        return false;
    }

    if (abs(x1 - x2) == 1 && x1 >= 0 && x2 >= 0 && y1 == y2 &&
        x1 <= 3 && x2 <= 3 && y1 <= 3 && y2 <= 3 && board[x2][y2] == blank_symbol) {
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = blank_symbol;
        return true;
    }
    else if (abs(y1 - y2) == 1 && y1 >= 0 && y2 >= 0 && x1 == x2 &&
             x1 <= 3 && x2 <= 3 && y1 <= 3 && y2 <= 3 && board[x2][y2] == blank_symbol) {
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = blank_symbol;
        return true;
    }
    else {
        cerr << "Wrong Move" << endl;
        return false;
    }
}

bool TicTac_board::is_win(Player<char>* player) {
    // Check rows, columns, and diagonals for 3 in a row
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if ((board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]) ||
                (board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]) ||
                (board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2])) {
                if (board[i][j] != blank_symbol) return true;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 2; j < 4; j++) {
            if ((board[i][j] == board[i+1][j-1] && board[i][j] == board[i+2][j-2]) &&
                board[i][j] != blank_symbol) return true;
        }
    }
    return false;
}

bool TicTac_board::is_lose(Player<char>* player) {
    return false;
}

bool TicTac_board::is_draw(Player<char>* player) {
    return false; // Simplified, can implement logic later
}

bool TicTac_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

TicTac_UI::TicTac_UI() : UI<char>("Welcome to Tic Tac game." , 3) {}

Player<char>* TicTac_UI:: create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* TicTac_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") turn.\n";
        cout << "Enter the position you want to move from :" <<endl;
        cin >> x >> y;
    } else { // COMPUTER
        x = rand() % 4;
        y = rand() % 4;
        cout << "Computer chooses: " << x << ", " << y << endl;
    }
    return new Move<char>(x, y, player->get_symbol());
}

TicTac_UI::~TicTac_UI() {
    cout << "Game has finished." << endl;
}



//#include "TicTacTeo.h"

