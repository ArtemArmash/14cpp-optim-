#include<iostream>
#include <thread>
#include <chrono>
using namespace std;
class Timer
{
public:
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<float> duration;


    Timer()
    {
        start = chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end = chrono::high_resolution_clock::now();
        duration = end - start;

        float resultat = duration.count();
        cout << "\nTime left: " << resultat << "sec\n";
    }
};

void Random(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

long long Math1(int* arr, int size) {
    long long res1 = 0;
    for (int i = 0; i < size / 4; i++) {
        res1 += arr[i];
    }
    return res1;
}

long long Math2(int* arr, int size) {
    long long res2 = 0;
    for (int i = size / 4; i < size / 2; i++) {
        res2 += arr[i];
    }
    return res2;
}

long long Math3(int* arr, int size) {
    long long res3 = 0;
    for (int i = size / 2; i < 3 * size / 4; i++) {
        res3 += arr[i];
    }
    return res3;
}

long long Math4(int* arr, int size) {
    long long res4 = 0;
    for (int i = 3 * size / 4; i < size; i++) {
        res4 += arr[i];
    }
    return res4;
}

int main() {
    srand(time(0));
    Timer time;
    const int size = 1000000000;
    int* arr = new int[size];
    Random(arr, size);
    long long res1 = 0, res2 = 0, res3 = 0, res4 = 0;
    thread th1([&]() { res1 = Math1(arr, size); });
    thread th2([&]() { res2 = Math2(arr, size); });
    thread th3([&]() { res3 = Math3(arr, size); });
    thread th4([&]() { res4 = Math4(arr, size); });

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    cout << "Res = " << res1 + res2 + res3 + res4;

    delete[]arr;


}