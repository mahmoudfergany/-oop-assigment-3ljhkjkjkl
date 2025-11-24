#include "TicTacTeo.h"
#include <iostream>
#include <iomanip>
#include <ranges>

using namespace std;

class legalMoves {
    vector<pair<int,int>> moves;
public:

    void set_vector(vector<pair<int,int>> v) {moves = v;}
    bool remove(int x, int y);
    bool exists(int x, int y) const;
    pair<int,int> get_random() const;
    bool empty() const;
};


bool legalMoves::exists(int x, int y) const {
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].first == x && moves[i].second == y ) {
            return true;
        }
    }
    return false;
}

pair<int, int> legalMoves::get_random() const {
    int i = rand() % moves.size();
    return moves[i];
}


legalMoves X_symbol;
legalMoves O_symbol;
legalMoves empty_positions;



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


    X_symbol.set_vector({{0,1},{0,3},{3,0},{3,2}});
    O_symbol.set_vector({{0,0},{0,2},{3,1},{3,3}});
    vector<pair<int,int>> empty;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == blank_symbol) {
                empty.push_back({i,j});
            }
        }
    }
    empty_positions.set_vector(empty);
}

void TicTac_board::set_current_player(Player<char>* p) {
    current_player = p;
}


bool TicTac_board::update_board(Move<char>* move ) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    // board[x][y] = blank_symbol;

    cout << "Enter new position : ";
    int x2 , y2;

    if (current_player->get_type() == PlayerType::HUMAN) {
        cout << "Enter the new position : ";
        int t3, t4;
        bool statment = true;
        while (statment) {
            cin >> t3 >> t4;
            if (abs(t3-x) == 1 && t4 == y && board[t3][t4] == blank_symbol) {
                board[t3][t4] = current_player->get_symbol();
                board[x][y] = blank_symbol;
                statment = false;
            }
            else if (abs(t4-y) == 1 && t3 == x && board[t3][t4] == blank_symbol) {
                board[t3][t4] = current_player->get_symbol();
                board[x][y] = blank_symbol;
                statment = false;
            }
            else {
                cout << "Wrong position. Try again" << endl;
            }
        }
    }

    else if (current_player->get_type() == PlayerType::COMPUTER) {
        vector<pair<int,int>> possible_moves;

        // نجيب كل الخانات الممكن يتحرك لها الرمز (يمين، يسار، فوق، تحت)
        if (x > 0 && board[x-1][y] == blank_symbol) possible_moves.push_back({x-1, y});
        if (x < 3 && board[x+1][y] == blank_symbol) possible_moves.push_back({x+1, y});
        if (y > 0 && board[x][y-1] == blank_symbol) possible_moves.push_back({x, y-1});
        if (y < 3 && board[x][y+1] == blank_symbol) possible_moves.push_back({x, y+1});

        if (!possible_moves.empty()) {
            pair<int,int> i = possible_moves[rand() % possible_moves.size()];
            x2 = i.first;
            y2 = i.second;

            board[x2][y2] = board[x][y];
            board[x][y] = blank_symbol;
        }
    }


    vector<pair<int,int>> sym_x, sym_y, newEmpty;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 'X') {
                sym_x.push_back({i,j});
            }
            else if (board[i][j] == 'O') {
                sym_y.push_back({i,j});
            }
        }
    }
    X_symbol.set_vector(sym_x);
    O_symbol.set_vector(sym_y);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == blank_symbol) {
                newEmpty.push_back({i,j});
            }
        }
    }
    empty_positions.set_vector(newEmpty);

    return true;
}

bool TicTac_board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= 1; j++) {
            if (board[i][j] == sym && board[i][j+1] == sym && board[i][j+2] == sym)
                return true;
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i <= 1; i++) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym)
                return true;
        }
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (board[i][j] == sym && board[i+1][j+1] == sym && board[i+2][j+2] == sym)
                return true;
        }
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 2; j < 4; j++) {
            if (board[i][j] == sym && board[i+1][j-1] == sym && board[i+2][j-2] == sym)
                return true;
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

TicTac_UI::TicTac_UI()
    : UI<char>("Welcome to Tic Tac game.", 3), board_ptr(nullptr) {}

TicTac_UI::TicTac_UI(TicTac_board* p)
    : UI<char>("Welcome to Tic Tac game.", 3), board_ptr(p) {}

Player<char>* TicTac_UI:: create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* TicTac_UI::get_move(Player<char>* player) {
    board_ptr->set_current_player(player);

    int x1 , y1;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter the position you want move from :";
        bool statment = false;
        while (!statment) {
            int t1,t2;
            cin >> t1 >> t2;
            if (X_symbol.exists(t1,t2) && player->get_symbol() == 'X') {
                statment = true;
                x1 = t1;
                y1 = t2;
            }
            else if (O_symbol.exists(t1,t2) && player->get_symbol() == 'O') {
                statment = true;
                x1 = t1;
                y1 = t2;
            }
            else {
                cout << "Wrong position , Try again" << endl;
            }
        }
    }

    else if (player->get_type() == PlayerType::COMPUTER) {
        if (player->get_symbol() == 'X') {
            pair<int,int> i = X_symbol.get_random();
            x1 = i.first;
            y1 = i.second;
        }
        else {
            pair<int,int> i = O_symbol.get_random();
            x1 = i.first;
            y1 = i.second;
        }
    }

    return new Move<char>(x1, y1, player->get_symbol());
}

TicTac_UI::~TicTac_UI() {
    cout << "Game has finished." << endl;
}



//#include "TicTacTeo.h"

