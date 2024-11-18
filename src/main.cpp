#include "main.h"

void factoryThread(Storage &storage, Factory &factory, std::atomic<bool> &stopFlag)
{
    while (!stopFlag)
    {
        Good good = factory.produce();
        if (storage.addGood(good))
        {
            std::cout << "Factory " << factory.getId() << " produced " << good.quantity
                      << " units of " << good.type << " added to storage." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void monitorStorage(Storage &storage, std::vector<Lorry> &lorrys, std::atomic<bool> &stopFlag)
{
    while (!stopFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (storage.isFull())
        {
            std::cout << "Storage is 95% full. Starting delivery..." << std::endl;
            for (Lorry &lorry : lorrys)
            {
                auto goods = storage.retrieveGoods(lorry.getCapacity());
                for (auto &[type, quantity] : goods)
                {
                    std::cout << "type " << type << " quantity " << quantity << std::endl;
                    lorry.loadGood(Good{type, quantity});
                }
                std::cout << "Lorry with capacity " << lorry.getCapacity() << " loaded with:";
                for (auto &[type, quantity] : lorry.getGoods())
                {
                    std::cout << " " << type << ": " << quantity;
                }
                std::cout << std::endl;
                lorry.unload();
            }
        }
    }
}

int main()
{
    int StorageCapacity = MIN_STORAGE_MULTIPLIER * MIN_FACTORIES * 10;
    Storage Storage(StorageCapacity);

    std::vector<Factory> factories;
    for (int i = 1; i <= MIN_FACTORIES; ++i)
    {
        factories.emplace_back(i, 10);
    }

    std::vector<Lorry> lorrys = {Lorry(100), Lorry(150)};

    std::atomic<bool> stopFlag(false);

    std::vector<std::thread> factoryThreads;
    for (Factory &factory : factories)
    {
        factoryThreads.emplace_back(factoryThread, std::ref(Storage), std::ref(factory), std::ref(stopFlag));
    }

    std::thread monitorThread(monitorStorage, std::ref(Storage), std::ref(lorrys), std::ref(stopFlag));

    std::this_thread::sleep_for(std::chrono::seconds(60));
    stopFlag = true;

    for (std::thread &t : factoryThreads)
    {
        if (t.joinable())
            t.join();
    }
    if (monitorThread.joinable())
        monitorThread.join();

    return 0;
}