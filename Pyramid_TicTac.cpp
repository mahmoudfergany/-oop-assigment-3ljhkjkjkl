#include "Pyramid_TicTac.h"
#include <vector>
#include <set>


class PyTicTac_legalMoves {
    vector<pair<int,int>> moves;
public:

    PyTicTac_legalMoves() {
        moves = {
            {0,2},
            {1,1},
            {1,2},
            {1,3},
            {2,0},
            {2,1},
            {2,2},
            {2,3},
            {2,4},
        };
    }
    bool remove(int x, int y);
    bool exists(int x, int y) const;
    pair<int,int> get_random() const;
    bool empty() const;
};


bool PyTicTac_legalMoves::remove(int x, int y) {
    for (int i = 0; i < moves.size(); i++) {
        if (x == moves[i].first && y == moves[i].second) {
            moves.erase(moves.begin()+i);

            return true;
            break;
        }
    }
    return false;
}

bool PyTicTac_legalMoves::exists(int x, int y) const {
    bool statment = false;
    for (int i = 0; i < moves.size(); i++) {
        if (x == moves[i].first && y == moves[i].second) {
            return true;
        }
    }
    return false;
}

pair<int, int> PyTicTac_legalMoves::get_random() const {
    int i = rand() % moves.size();
    return moves[i];
}


bool PyTicTac_legalMoves::empty() const {
    return moves.empty();
}


PyTicTac_legalMoves legal;


Py_TicTac_Board::Py_TicTac_Board() : Board<char>(3,5) {
    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            board[0][i] = blank_symbol;
        }
        else {
            board[0][i] = '/';
        }
    }

    board [1][0] = '/';
    board [1][4] = '/';

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == '/') {
                continue;
            }
            else {
                board[i][j] = blank_symbol;
            }
        }
    }
}

bool Py_TicTac_Board::update_board(Move<char> *move) {
    int x,y;
    x = move->get_x();
    y = move->get_y();

    if (!legal.exists(x,y)) {
        cerr << "Wrong position." << endl;
        return false;
    }
    else {
        board[x][y] = move->get_symbol();
        n_moves++;
        legal.remove(x,y);
    }
    return true;
}

bool Py_TicTac_Board::is_win(Player<char> *) {
    set<char> check;
    int p = 0;
    for (int i = 0; i < 3; i++) {
        check.insert(board[p+i][2]);
    }
    if (check.size() == 1 && *check.begin() != '.' && *check.begin() != '/') {
        return true;
    }

    check.clear();
    p = 1;
    for (int i = 0; i < 3; i++) {
        check.insert(board[1][p+i]);
    }
    if (check.size() == 1 && *check.begin() != '.' && *check.begin() != '/') {
        return true;
    }

    check.clear();
    p = 0;
    int q = 2;
    for (int i = 0; i < 3; i++) {
        check.insert(board[p+i][q+i]);
    }
    if (check.size() == 1 && *check.begin() != '.' && *check.begin() != '/') {
        return true;
    }

    check.clear();
    p = 0;
    q = 2;
    for (int i = 0; i < 3; i++) {
        check.insert(board[p+i][q-i]);
    }
    if (check.size() == 1 && *check.begin() != '.' && *check.begin() != '/') {
        return true;
    }

    check.clear();
    for (int i = 0; i < 3; i++) {
        char first = board[2][i+1];
        if (first == '/' || first == '.') continue;

        if (board[2][i+2] == first && board[2][i] == first) {
            return true;
        }
    }
    return false;
}

bool Py_TicTac_Board::is_draw(Player<char> *player) {
    return n_moves == 9 && !is_win(player);
}

bool Py_TicTac_Board::game_is_over(Player<char> *player) {
    if (is_win(player) || is_draw(player)) {
        return true;
    }
    return false;
}

Py_TicTac_UI::Py_TicTac_UI() : UI<char>("Welcome to Pyramid TicTac game.",3){}

Player<char> *Py_TicTac_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Py_TicTac_UI::get_move(Player<char>* player) {
    int x,y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter the position (x,y) : " << endl;
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        pair<int,int> p = legal.get_random()  ;
        x = p.first;
        y = p.second;
        cout << "Computer chooses " << x << " & " << y;
    }

    return new Move(x,y,player->get_symbol());
}

Py_TicTac_UI::~Py_TicTac_UI() {
    cout << "Game has finished." << endl;
}





