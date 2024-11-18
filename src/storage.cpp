#include "storage.h"

bool Storage::addGood(const Good &good)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (currentLoad + good.quantity <= capacity)
    {
        currentLoad += good.quantity;
        storage[good.type] += good.quantity;
        return true;
    }
    return false;
}

std::map<std::string, int> Storage::retrieveGoods(int quantity)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::map<std::string, int> retrievedGoods;
    int retrieved = 0;
    for (auto it = storage.begin(); it != storage.end() && retrieved < quantity;)
    {
        int takeAmount = std::min(it->second, quantity - retrieved);
        retrievedGoods[it->first] = takeAmount;
        it->second -= takeAmount;
        retrieved += takeAmount;

        if (it->second == 0)
            it = storage.erase(it);
        else
            ++it;
    }
    currentLoad -= retrieved;
    return retrievedGoods;
}