#pragma once
#include <string>
#include <map>
#include <iostream>

#include "goods.h"

class Lorry {
public:
    Lorry(int capacity) : capacity(capacity), load(0) {std::cout << " My capacity is " << capacity << std::endl;}

    bool loadGood(const Good& good);

    void unload() {
        goods.clear();
        load = 0;
    }

    int getLoad() const { return load; }
    int getCapacity() const { return capacity; }

    std::map<std::string, int> getGoods() const { return goods; }

private:
    int capacity;
    int load;
    std::map<std::string, int> goods;
};