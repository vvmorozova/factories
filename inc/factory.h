#pragma once
#include <random>

#include "goods.h"

class Factory {
public:
    Factory(int id, int ProduceRate) : id(id), ProduceRate(ProduceRate) {}

    Good produce() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5);
        int quantity = dis(gen) * ProduceRate;
        return Good{"Good_" + std::to_string(id), quantity};
    }

    int getId() const { return id; }

private:
    int id;
    int ProduceRate;
};