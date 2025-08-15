#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include <algorithm>

// Global variables
std::mutex mtx;
std::map<std::string, int> system_stats;

// Function to update system stats
void update_stats() {
    while (true) {
        // Simulate system stats updating
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::lock_guard<std::mutex> lock(mtx);
        system_stats["CPUUsage"] = rand() % 100;
        system_stats["MemoryUsage"] = rand() % 100;
        system_stats["DiskUsage"] = rand() % 100;
    }
}

// Function to display system stats
void display_stats() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "System Stats:" << std::endl;
        for (auto& stat : system_stats) {
            std::cout << stat.first << ": " << stat.second << "%" << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(0));

    // Create threads for updating and displaying system stats
    std::thread update_thread(update_stats);
    std::thread display_thread(display_stats);

    // Wait for threads to finish
    update_thread.join();
    display_thread.join();

    return 0;
}