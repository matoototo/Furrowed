struct Move {
    Move() : from(0), to(0), promotion(0) {}
    Move(int from, int to, int promotion = 0) : from(from), to(to), promotion(promotion) {}

    int from;
    int to;
    int promotion;
};
