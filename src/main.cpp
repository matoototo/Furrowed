#include "uci.hpp"
#include "board.hpp"
#include "search.hpp"
#include "engine.hpp"
#include "evaluate.hpp"
#include "constants.hpp"

#include <chrono>
#include <iostream>

int main() {
    Engine engine{};
    engine.board.set_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    UCI uci = UCI(engine);
    uci.run();

    return 0;
}
