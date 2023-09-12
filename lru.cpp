#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
    list<int> cache;    // key list
    unordered_map<int, list<int>::iterator> ma; // key to iterator mapping

public:
    LRUCache(int capacity)
    {
        // nothing to do
    }
    
    void put(int key, int value)
    {
        // check if key already exists
        if (ma.find(key) != ma.end())
        {
            // key exists, so delete it from the list and map
            cache.erase(ma[key]);
        }

        // insert key into front of list and map
        cache.push_front(key);
        ma[key] = cache.begin();

        // check size
        if (cache.size() > capacity)
        {
            // over capacity, so delete least recently used item
            int key_to_delete = cache.back();
            cache.pop_back();
            ma.erase(key_to_delete);
        }
    }
    
    int get(int key)
    {
        // check if exists
        if (ma.find(key) == ma.end())
        {
            // not found
            return -1;
        }

        // exists, so move to front of list
        cache.erase(ma[key]);
        cache.push_front(key);
        ma[key] = cache.begin();

        // return value
        return 1;
    }
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;
    cache.put(3, 3);
    cout << cache.get(2) << endl;
    cache.put(4, 4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;
    return 0;
}