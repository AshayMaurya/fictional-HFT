#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <thread> 
#include <chrono>

#include "Strategy.h"


Tick parse_csv_line(const std::string& line) {
    std::stringstream ss(line);
    std::string timestamp_str, price_str;
    
    std::getline(ss, timestamp_str, ',');
    std::getline(ss, price_str, ',');
    
    return Tick{timestamp_str, std::stod(price_str)};
}


int main() {
    const std::string data_filepath = "data/synthetic_market_data.csv";
    const int short_window = 50;
    const int long_window = 200;
    const auto simulation_delay = std::chrono::milliseconds(5); // Delay to make it look "live"

    MovingAverageCrossover strategy(short_window, long_window);
    std::ifstream market_data_file(data_filepath);
    
    if (!market_data_file.is_open()) {
        std::cerr << "ERROR: Could not open market data file at " << data_filepath << std::endl;
        return 1;
    }

    std::string line;
    std::getline(market_data_file, line); 

    std::cout << "--- Starting Live HFT Simulation ---" << std::endl;
    std::cout << "Strategy: Moving Average Crossover (" << short_window << ", " << long_window << ")" << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;
    std::cout << "------------------------------------" << std::endl;

    bool in_position = false;
    double entry_price = 0.0;

    while (std::getline(market_data_file, line)) {
        Tick current_tick = parse_csv_line(line);
        IStrategy::Signal signal = strategy.processTick(current_tick);

        if (in_position) {
            if (signal == IStrategy::Signal::SELL) {
                double pnl = current_tick.price - entry_price;
                std::cout << current_tick.timestamp << " | SELL SIGNAL  | Close @" << current_tick.price 
                          << " | PnL: " << (pnl > 0 ? "+" : "") << pnl << std::endl;
                in_position = false;
            }
        } else {
            if (signal == IStrategy::Signal::BUY) {
                std::cout << current_tick.timestamp << " | BUY SIGNAL   | Enter @" << current_tick.price << std::endl;
                in_position = true;
                entry_price = current_tick.price;
            }
        }
        
        // Pausing to make the output readable and simulate a live feed
        std::this_thread::sleep_for(simulation_delay);
    }
    
    std::cout << "--- Simulation Finished ---" << std::endl;

    return 0;
}