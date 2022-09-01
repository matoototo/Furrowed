#include "uci.hpp"

#include <mutex>
#include <atomic>
#include <thread>
#include <sstream>
#include <iostream>

#include "move.hpp"
#include "evaluate.hpp"

void UCI::go(std::istringstream& is) {
    std::string command;
    Time t;
    engine.stop = false;

    while (is >> command) {
        if (command == "searchmoves")
            while (is >> command)
                ; // restrict to these moves
        else if (command == "ponder") t.ponder = true;
        else if (command == "wtime") is >> t.wtime;
        else if (command == "btime") is >> t.btime;
        else if (command == "winc") is >> t.winc;
        else if (command == "binc") is >> t.binc;
        else if (command == "movestogo") is >> t.movestogo;
        else if (command == "depth") is >> t.depth;
        else if (command == "nodes") is >> t.nodes;
        else if (command == "mate") is >> t.mate;
        else if (command == "movetime") is >> t.movetime;
        else if (command == "infinite") t.infinite = true;;
    }
    // start thinking async
    engine.thread = std::thread(&Engine::think, &engine, t);
}

void UCI::position(std::istringstream &is) {
    std::string command;
    Board board;
    while (is >> command) {
        if (command == "fen") {
            std::string fen, part;
            // fen is made up of multiple strings separated by spaces
            while (is >> part) {
                fen += part + " ";
            }
            board = Board(fen);
        } else if (command == "startpos") {
            board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        } else if (command == "moves") {
            while (is >> command) {
                board.make_move(Move::from_str(command, board));
            }
        }
    }
    engine.board = board;
}

void UCI::run() {
    std::string command, line;
    do {
        getline(std::cin, line);
        std::istringstream is(line);

        if (engine.stop && engine.thread.joinable()) {
            engine.thread.join();
            std::cout << "info string engine stopped" << std::endl;
        }

        command.clear();
        is >> std::skipws >> command;

        if (command == "quit" || command == "stop") {
            std::cout << "info string stopping engine" << std::endl;
            engine.stop = true;
        }
        else if (command == "uci")
            std::cout << "id name furrowed\n" << "uciok" << std::endl;
        else if (command == "debug")
            ; // switch debug on/off
        else if (command == "isready")
            std::cout << "readyok" << std::endl;
        else if (command == "setoption")
            ; // set option
        else if (command == "ucinewgame")
            engine.board.set_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        else if (command == "position")
            position(is);
        else if (command == "go" && engine.stop)
            go(is);
        else if (command == "legalmoves") {
            for (Move move : engine.board.legal_moves()) {
                std::cout << move.to_str() << " ";
            }
        }
        else if (command == "eval") {
            std::string move;
            is >> move;
            Board temp_board = engine.board;
            temp_board.make_move(Move::from_str(move, temp_board));
            std::cout << evaluate(temp_board) << std::endl;
        }

    } while (command != "quit"); // The command-line arguments are one-shot
}
