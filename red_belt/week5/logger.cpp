#include <iostream>
#include <vector>

using namespace std;

class Logger {
public:
    Logger() {cout << "Default ctor\n";}    
    Logger(const Logger&) {cout << "Copy ctor\n";}
    void operator=(const Logger&) {cout << "Copy assignment\n";}
};

int main () {
    Logger source;
    Logger target = source;
    
    vector <Logger> logger;
    logger.push_back(target);

    source = target;
    return 0;
}