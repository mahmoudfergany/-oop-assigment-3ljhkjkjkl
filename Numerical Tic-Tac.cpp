#include "Numerical Tic-Tac.h"
using namespace std;


class legal_numbers {
private:
    vector<int> legal;
public:
    void set_legal (vector<int> x) {
        legal = x;
    }
    bool is_legal(int x) {
        for (int i = 0; i < legal.size(); i++) {
            if (legal[i] == x) {
                return true;
            }
        }
        return false;
    }
    void remove(int x) {
        for (int i = 0; i < legal.size(); i++) {
            if (legal[i] == x) {
                legal.erase(legal.begin()+i);
                return;
            }
        }
    }
    int get_random() {
        int i = rand() % legal.size();
        return legal[i];
    }
    int get_size() {
        return legal.size();
    }
    void display_numbers() {
        for (int i = 0; i < legal.size(); i++) {
            cout << legal[i] << " ";
        }
    }
};

legal_numbers play1 , play2;

class empty_pos {
private:
    vector<pair<int,int>> empty;
public:
    void set_empty(vector<pair<int,int>> x) {
        empty = x;
    }
    void remove(int x, int y) {
        for (int i = 0; i < empty.size(); i++) {
            if (empty[i].first == x && empty[i].second == y) {
                empty.erase(empty.begin()+i);
                return;
            }
        }
    }
    bool is_exist(int x, int y) {
        for (int i = 0; i < empty.size(); i++) {
            if (empty[i].first == x && empty[i].second == y) {
                return true;
            }
        }
        return false;
    }
    pair<int,int> get_random() {
        int i = rand() % empty.size();
        return empty[i];
    }
    bool is_empty() {
        return empty.empty();
    }
};

empty_pos empt;

num_TicTac_board::num_TicTac_board() : Board<int>(3,3) {
    vector<pair<int,int>> t;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = blank_symbol;
            t.push_back({i,j});
        }
    }
    play1.set_legal({1,3,5,7,9});
    play2.set_legal({2,4,6,8});
    empt.set_empty(t);
}

bool num_TicTac_board::update_board(Move<int> *move) {
    int x = move->get_x();
    int y = move->get_y();
    int sym = move->get_symbol();

    if (sym == 3) {
        int i = play1.get_random();
        board[x][y] = i;
        play1.remove(i);
        return true;
    }

    if (sym == 4) {
        int i = play2.get_random();
        board[x][y] = i;
        play2.remove(i);
        return true;
    }

    cout << "Enter a number : " << endl;
    int x1;
    while (true) {
        if (move->get_symbol() == 1) {
            cout << "Choose from : ";
            play1.display_numbers();
            cout << endl;
            cin >> x1;
            if (play1.is_legal(x1)) {
                board[x][y] = x1;
                play1.remove(x1);
                break;
            }
            else {
                cout << "Illegal number, try again" << endl;
            }
        }
        else if (move->get_symbol() == 2) {
            cout << "Choose from : ";
            play2.display_numbers();
            cout << endl;
            cin >> x1;
            if (play2.is_legal(x1)) {
                board[x][y] = x1;
                play2.remove(x1);
                break;
            }
            else {
                cout << "Illegal number, try again" << endl;
            }
        }
    }
    return true;
}

bool num_TicTac_board::is_win(Player<int> *player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] + board[i][1] + board[i][2] == 15 && board[i][0] != blank_symbol && board[i][1] != blank_symbol && board[i][2] != blank_symbol )
            || ( board[0][i] + board[1][i] + board[2][i] == 15 && board[0][i] != blank_symbol && board[1][i] != blank_symbol && board[2][i] != blank_symbol)) {
            return true;
        }
    }

    if ((board[0][0] + board[1][1] + board[2][2] == 15 && board[0][0] != blank_symbol && board[1][1] != blank_symbol && board[2][2] != blank_symbol)
        || (board[0][2] + board[1][1] + board[2][0] == 15 && board[2][0] != blank_symbol && board[1][1] != blank_symbol && board[0][2] != blank_symbol)) {
        return true;
    }

    return false;
}

bool num_TicTac_board::is_draw(Player<int> *player) {
    if (empt.is_empty() && !is_win(player)) {
        return true;
    }
    return false;
}


bool num_TicTac_board::game_is_over(Player<int> *player) {
    return is_win(player) || is_draw(player);
}



num_TicTac_UI::num_TicTac_UI() : UI<int>("Hello in numerical Tic Tac Teo game." , 3){}

Move<int> *num_TicTac_UI::get_move(Player<int> *player) {
    int x,y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Player " << player->get_name() << " turn." << endl;
        cout << "Enter the position you want to put number in : ";
        while (true){
            cin >> x >> y;
            if (empt.is_exist(x,y)) {
                empt.remove(x,y);
                break;
            }
            else {
                cout << "Wrong position, try again" << endl;
            }
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        pair<int,int> t = empt.get_random();
        x = t.first;
        y = t.second;
        empt.remove(x,y);
    }

    return new Move<int>(x, y, player->get_symbol());
}

Player<int>* num_TicTac_UI::create_player(std::string &name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}


num_TicTac_UI::~num_TicTac_UI() {
    cout << "Game has finished. " << endl;
}





