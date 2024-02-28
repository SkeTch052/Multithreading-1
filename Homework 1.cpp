#include <iostream>
#include <algorithm>
#include <execution>
#include <thread>
#include <chrono>

const unsigned int MAX_CLIENTS = 6;

void client(int& queue) {
    for (; queue < MAX_CLIENTS; ++queue) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "New client ..." << "\tQueue: " << (queue + 1) << std::endl;
    }
}

void q_operator(int& queue) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1050));
    for (; queue > 0; --queue) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Client served ..." << "\tQueue: " << (queue - 1) << std::endl;
    }
    std::cout << "No clients left" << std::endl;
}

int main()
{
    int queue = 0;

    std::thread client_tr(client, std::ref(queue));
    std::thread q_operator_tr(q_operator, std::ref(queue));

    client_tr.join();
    q_operator_tr.join();

    return 0;
}