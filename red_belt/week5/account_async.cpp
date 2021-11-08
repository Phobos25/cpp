// проблема асинхронности
// гонка данных --- это когда несколько потоков пытаются записать на одну и ту же память
// разные данные
#include "profile.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <future>
using namespace std;

struct Account{
    int balance = 0;
    bool Spend(int value){
        if (value <= balance){
            balance -= value;
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