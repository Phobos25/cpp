#include "profile.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <future>
#include <mutex>

using namespace std;

struct Account{
    int balance = 0;
    vector<int> history;
    mutex m;

    bool Spend(int value){
        lock_guard<mutex> g(m);
        if (value <= balance){
            balance -= value;
            history.push_back(value);
            return true;
        } 
        return false;
    }
    Account(int value = 0){
        balance = value;
    }
};

int SpendMoney(Account& account){
    int total_spent = 0;
    for (int i=0; i< 10'000'000; ++i){
        if (account.Spend(1)){
            ++total_spent;
        }
    }
    return total_spent;
}

int main() {
    Account family_account(10'000'000);
    
    auto husband  = async(SpendMoney, (ref(family_account)));
    auto wife     = async(SpendMoney, (ref(family_account)));
    auto son      = async(SpendMoney, (ref(family_account)));
    auto daughter = async(SpendMoney, (ref(family_account)));

    int spent = husband.get() + wife.get() + son.get() + daughter.get();
    cout << "Total spent: " << spent << endl
         << "Balance: " << family_account.balance << endl;
    return 0;
}