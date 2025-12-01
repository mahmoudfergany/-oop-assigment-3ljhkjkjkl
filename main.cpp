#include <iostream>
#include <cstdlib>
#include <ctime>
#include "XO_Classes.h"
#include "TicTacTeo.h"
#include "BoardGame_Classes.h"
#include "Pyramid_TicTac.h"
#include "sus.h"
#include "Four-in-a-row.h"
#include "Misere.h"
#include "Diamond.h"
#include "Numerical Tic-Tac.h"

using namespace std;

void menu() {
    cout << "\n================================\n";
    cout << "  CS213 Board Games Menu\n";
    cout << "================================\n";
    cout << "1. SUS\n";
    cout << "2. Four-in-a-row\n";
    cout << "3. 5x5 Tic Tac Toe\n";
    cout << "4. Word Tic Tac Toe\n";
    cout << "5. Misere Tic Tac Toe\n";
    cout << "6. Diamond Tic Tac Toe\n";
    cout << "7. 4x4 Tic Tac Toe\n";
    cout << "8. Pyramid Tic Tac Toe\n";
    cout << "9. Numerical Tic Tac Toe\n";
    cout << "10. Obstacles Tic Tac Toe\n";
    cout << "11. Infinity Tic Tac Toe\n";
    cout << "12. X-O Game\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    cout << "Enter your choice: ";
}

void process() {
    int number_of_play;
    cin >> number_of_play;

    if (number_of_play == 0) {
        cout << "Thanks for playing!\n";
        return;
    }

    if (number_of_play == 1) {
        sus_board board;
        sus_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'S' : 'U', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'S' : 'U', PlayerType::COMPUTER);
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

    else if (number_of_play == 2) {
        Four_in_a_row_board board;
        Four_in_a_row_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::COMPUTER);
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
    else if (number_of_play == 5) {
        Misere_Board board;
        Misere_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::COMPUTER);
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
    else if (number_of_play == 6) {
        Diamond_Board board;
        Diamond_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::COMPUTER);
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
    else if (number_of_play == 7) {
        TicTac_board board;
        TicTac_UI ui(&board);

        Player<char>* players[2];
        vector<Player<char>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::COMPUTER);
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
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<char>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 'X' : 'O', PlayerType::COMPUTER);
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
    else if (number_of_play == 9) {
        num_TicTac_board board;
        num_TicTac_UI ui;

        Player<int>* players[2];
        vector<Player<int>*> set_of_players;

        for (int i = 0; i < 2; i++) {
            int type;
            string name;
            cout << "Enter player" << i + 1 << " name :" << endl;
            cin >> name;
            cout << "Enter the type of player " << i + 1 << ": \n 1-HUMAN \n 2-COMPUTER : ";
            cin >> type;
            Player<int>* p;
            if (type == 1) {
                p = ui.create_player(name, i == 0 ? 1 : 2, PlayerType::HUMAN);
            }
            else if (type == 2) {
                p = ui.create_player(name, i == 0 ? 3 : 4, PlayerType::COMPUTER);
            }
            set_of_players.push_back(p);
        }

        for (int i = 0; i < 2; i++) {
            players[i] = set_of_players[i];
        }

        GameManager<int> gm(&board, players, &ui);
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

        Player<char>* players[2] = { p1, p2 };
        GameManager<char> gm(&board, players, &ui);

        gm.run();

        delete p1;
        delete p2;
    }
    else {
        cout << "Game not implemented yet!\n";
    }
}

int main() {

    //srand(static_cast<unsigned int>(time(0)));

    menu();
    process();

    return 0;
}
