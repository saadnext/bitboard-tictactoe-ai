#pragma once
#include "board.h"
#include "search.h"
#include <cctype>
#include <string>

class Game {
  private:
    Board board;
    bool game_over = false;
    bool is_against_ai = false;
    Side ai_side = Side::X;
    template <typename Func> char get_valid_input(const std::string& prompt, Func validator) {
        char choice;
        while (true) {
            std::cout << prompt;
            if (std::cin >> choice && validator(choice))
                break;
            // Handle invalid inputs or occupied slots
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid move. Try again.\n";
        }
        return choice;
    }

  public:
    explicit Game() = default;
    void run() {
        how_to_play();
        ask_to_play_against_ai();
        game_loop();
    }
    void ask_to_play_against_ai() {
        (void)get_valid_input("Do you wanna play against Ai y/n: ", [this](char c) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (c == 'y')
                is_against_ai = true;
            return (c == 'y' || c == 'n');
        });
        (void)get_valid_input("Please choose your side either X or O: ", [this](char c) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (c == 'x')
                ai_side = Side::O;
            return (c == 'x' || c == 'o');
        });
    }
    void how_to_play() const {
        std::cout << "\t--- TIC-TAC-TOE ---\n\n\t--- How To Play ---\n"
                  << "\t  1- Choose whether you want to play against the Ai.\n"
                  << "\t  2- Select the position of X/O on the board between 1-9.\n\n";
        board.print();
    }
    void game_loop() {
        while (!game_over) {
            handle_input();
            clear_screen();
            board.print();
            check_game_state();
            board.switch_side_to_move();
        }
        ask_for_replay();
    }
    void check_game_state() {
        Winner winner = board.check_winner();
        if (winner == Winner::None)
            return;
        else if (winner == Winner::Draw)
            std::cout << "🤝 It's a draw!\n";
        else
            std::cout << "🎉 Player " << board.side_to_move() << " wins!\n";

        game_over = true;
    }
    void ask_for_replay() {
        char replay = get_valid_input("Do you wanna replay the game y/n: ",
                                      [](char c) { return c == 'y' || c == 'n'; });
        if (replay == 'y') {
            *this = Game{};
            clear_screen();
            run();
        } else {
            std::cout << "Thanks for playing! 👋\n";
        }
    }
    void handle_input() {
        Side current_side = (board.side_to_move() == 'X' ? Side::X : Side::O);
        if (is_against_ai && (ai_side == current_side)) {
            board.set(find_best_move(board));
            return;
        }
        int choice;
        while (true) {
            std::cout << "Player " << board.side_to_move() << ", enter slot (1-9): ";
            if (std::cin >> choice && choice >= 1 && choice <= 9 &&
                board.is_valid_move(choice - 1)) {
                board.set(choice - 1); // Convert 1-9 to 0-8 index
                break;
            }
            // Handle invalid inputs or occupied slots
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid move. Try again.\n";
        }
    }
    void clear_screen() { std::cout << "\033[2J\033[1;1H"; }
};
