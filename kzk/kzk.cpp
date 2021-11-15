#include <vector>
#include <random>     
#include <algorithm> 
#include <iterator>   
#include <iostream>   
#include <functional>
#include <cmath>
#include <numeric>


std::vector<long long> triw_podzial(const long long sekret, const long long k, const int n=2) {
    std::random_device device;
    std::uniform_int_distribution<long long> dist(1, k-1);
    std::vector<long long> udzialy;
    long long sums = sekret;
    for (int i = 0; i < n; i++) {
        if (i != n-1) {
            auto udzial = dist(device);
            std::cout << "udzial " << i << " : " << dist(device) << std::endl;
            udzialy.push_back(udzial);
            sums -= udzial;
        }
        else {
            auto udzial = sums % k;
            std::cout << "udzial " << i+1 << " : " << dist(device) << std::endl;
            udzialy.push_back(udzial);
        }
        
    }
    return udzialy;
}

long long triw_sklad(const std::vector<long long> udzialy, const long long k) {
    long long sum = 0;
    for (auto i : udzialy) sum += i;
    return sum % k;
}

std::vector<std::pair<int, long long>> shamir_podzial(const long long sekret, const long long p, const int n = 2, const int t = 2) {
    std::random_device device;
    std::uniform_int_distribution<long long> dist(1, p - 1);
    std::vector<long long> a;
    std::cout << "wielomian: " << sekret;
    for (int i = 0; i < t-1 ; i++) {
        a.push_back(dist(device));
        std::cout << " + " << a[i] << "*x^" << i + 1;
    }
    std::cout<<std::endl;
    std::vector<std::pair<int, long long>> udzialy;
    for (int i = 1; i <= n; i++) {
        long long fx = 0;
        for (int j = 1; j <= t-1; j++) {
            fx += a[j - 1] * std::pow(i, j);
        }
        auto udzial = (sekret + fx) % p;
        std::cout << "udzial " << i << " : " << udzial << std::endl;
        udzialy.push_back(std::pair<int, long long>(i, udzial));
    }

    return udzialy;
}

long long fraction_mod(long long licznik, long long mianownik, long long p) {
    long long i = 1;
    auto licmod = licznik % p;
    if (licmod < 0) licmod += p;
    while (true) {
        auto mod = mianownik * i % p;
        if (mod < 0) {
            if (mod + p == licmod) break;
        }
        else {
            if (mod == licmod) break;
        }
        i++;
    }
    return i;
}

long long shamir_sklad(std::vector<std::pair<int, long long>> udzialy, const long long p) {
    std::vector<int> indexes;
    long long wynikl = 0;
    long long wynikm = 1;
    for (auto const i : udzialy) {
        auto licznik = i.second;
        long long mianownik = 1;
        for (auto const j : udzialy) {
            if (i.first == j.first) {
                continue;
            }
            else {
                licznik *= -j.first;
                mianownik *= i.first - j.first;
            }
        }
        auto dodaj = (licznik / mianownik);
        //if (dodaj < 0) dodaj += p;
        wynikl = wynikl*mianownik + licznik*wynikm;
        wynikm *= mianownik;
        std::cout << i.first << " wolny " << licznik << "/" << mianownik << std::endl;
    }
    std::cout << wynikl << "/" << wynikm << std::endl;
    //auto wynik = ((wynikl % p) * wynikm) % p;
    return fraction_mod(wynikl, wynikm, p);
}


int main()
{
    std::cout << (-144*954) % 1523 << std::endl;
    long long sekret = 954;
    //long long k = 2617;
    long long k = 1523;
    /*auto udzialy = triw_podzial(sekret, k, 5);
    std::cout << triw_sklad(udzialy, k) << std::endl;*/
    auto udzialyy = shamir_podzial(sekret, k, 10, 5);
    udzialyy.erase(udzialyy.begin());
    udzialyy.erase(udzialyy.begin());
    udzialyy.erase(udzialyy.begin());
    udzialyy.erase(udzialyy.begin());
    udzialyy.erase(udzialyy.begin());
    //udzialyy.erase(udzialyy.begin() + 1);
    std::cout << udzialyy.size() << std::endl;
    std::cout << shamir_sklad(udzialyy, k);
}
