#pragma once
#include <thread>
#include <mutex>
#include <map>

#include "goods.h"

class Storage {
public:
    Storage(int capacity) : capacity(capacity), currentLoad(0) {}

    bool addGood(const Good& good);

    bool isFull() const { return (float)currentLoad / capacity >= 0.95; }

    std::map<std::string, int> retrieveGoods(int quantity);

private:
    int capacity;
    int currentLoad;
    std::map<std::string, int> storage;
    std::mutex mtx;
};