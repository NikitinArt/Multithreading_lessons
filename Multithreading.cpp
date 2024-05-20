#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <mutex>

using namespace std;

mutex mtx;

void some_vector_func(vector<int>& vec) {
    this_thread::sleep_for(chrono::milliseconds(5000));

    vec.pop_back();

    cout << "Succes\n";
}

void some_map_func(map<string, int>& mp) {
    mtx.lock();

    for (auto start = mp.begin(); start != mp.end(); start++)
    {
        cout << start->first << "\t" << start->second << "\n";

        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    mtx.unlock();
}

int main()
{
    vector<int> vec{ 1, 2, 3, 4, 5 };

    map<string, int> mp;

    map<string, int> mp2{
        {"d", 5}, {"e", 6}, {"y", 8}
    };

    mp["a"] = 1;
    mp["b"] = 30;
    mp["c"] = 10000;

    thread th1(some_vector_func, ref(vec));

    thread th4(some_map_func, ref(mp2));

    thread th2(some_map_func, ref(mp));

    thread th3([]() {
        cout << "Hello\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "World\n";
    });

    this_thread::sleep_for(chrono::milliseconds(1000));

    cout << "main thread is finished\n";

    th3.detach();

    th1.join();

    th4.join();

    th2.join();

}
