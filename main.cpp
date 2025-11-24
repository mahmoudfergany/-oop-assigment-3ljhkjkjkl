//--------------------------------------- main.cpp

#include <iostream>
#include "XO_Classes.h"
#include "TicTacTeo.h"
#include "BoardGame_Classes.h"
#include "Pyramid_TicTac.h"

using namespace std;

void menu () {
    cout << "🎮 CS213 Board Games Menu 🎮" << endl;
    cout << "There are many games , choose one please " << endl;
    cout << "1-SUS" << endl;
    cout << "2-Four-in-a-row" << endl;
    cout << "3-5x5 Tic Tac Toe" << endl;
    cout << "4-Word Tic Tac Toe" << endl;
    cout << "5-Misère Tic Tac Toe" << endl;
    cout << "6-Diamond Tic Tac Toe" << endl;
    cout << "7-4x4 Tic Tac Toe" << endl;
    cout << "8-Pyramid Tic Tac Toe" << endl;
    cout << "9-Numerical Tic Tac Toe" << endl;
    cout << "10-Obstacles Tic Tac Toe" << endl;
    cout << "11-Infinity Tic Tac Toe" << endl;
    cout << "12- X-O game" << endl;
    cout << endl;
    cout << "Enter the number of game you want to play : " << endl;
}

void process() {
    int number_of_play;
    cin >> number_of_play;

    if (number_of_play == 7) {
        TicTac_board board;
        TicTac_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i+1 << " name :" <<endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 <<": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name,i==0 ? 'X' : 'O',PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name,i==0 ? 'X' : 'O',PlayerType::COMPUTER);
            }
            set_of_players.push_back(p);
        }

        for (int i = 0; i < 2; i++) {
            players[i] = set_of_players[i];
        }

        GameManager<char> gm(&board, players, &ui);
        gm.run();
        for (int i = 0; i < 2; i++) {
            delete set_of_players[i];
        }
    }

    else if (number_of_play == 8) {
        Py_TicTac_Board board;
        Py_TicTac_UI ui;

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i+1 << " name :" <<endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 <<": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name,i==0 ? 'X' : 'O',PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name,i==0 ? 'X' : 'O',PlayerType::COMPUTER);
            }
            set_of_players.push_back(p);
        }

        for (int i = 0; i < 2; i++) {
            players[i] = set_of_players[i];
        }

        GameManager<char> gm(&board, players, &ui);
        gm.run();
        for (int i = 0; i < 2; i++) {
            delete set_of_players[i];
        }
    }

    else if (number_of_play == 12) {
        X_O_Board board;

        XO_UI ui;

        std::string name1, name2;
        std::cout << "Enter name for Player 1: ";
        std::cin >> name1;
        std::cout << "Enter name for Player 2: ";
        std::cin >> name2;

        Player<char>* p1 = ui.create_player(name1, 'X', PlayerType::HUMAN);
        Player<char>* p2 = ui.create_player(name2, 'O', PlayerType::HUMAN);

        Player<char>* players[2] = {p1, p2};
        GameManager<char> gm(&board, players, &ui);

        gm.run();

        delete p1;
        delete p2;
    }
}

int main() {
    menu();
    process();
    return 0;
}
