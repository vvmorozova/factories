#include "lorry.h"

bool Lorry::loadGood(const Good &good)
{
    if (load + good.quantity <= capacity)
    {
        load += good.quantity;
        goods[good.type] += good.quantity;
        return true;
    }
    return false;
}