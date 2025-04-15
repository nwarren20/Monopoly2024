#include "../include/utils.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
//using namespace MonopolyUtils;

    void MonopolyUtils::OutputMessage(string message, int delay)
    {
        cout << "=============================================\n\n";

        cout << message << endl << endl;

        cout << "=============================================\n\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }


