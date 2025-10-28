#include "Strategy.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(int short_window, int long_window)
    : short_window_size(short_window), long_window_size(long_window) {
    if (short_window >= long_window) {
        throw std::invalid_argument("Short window must be smaller than long window.");
    }
}

IStrategy::Signal MovingAverageCrossover::processTick(const Tick& tick) {
    price_buffer.push_back(tick.price);

    // Maintaining the buffer size to be no larger than the long window
    if (price_buffer.size() > long_window_size) {
        price_buffer.pop_front();
    }

    if (price_buffer.size() < long_window_size) {
        return Signal::HOLD;
    }

    prev_short_ma = current_short_ma;
    prev_long_ma = current_long_ma;
    
    double short_sum = 0.0;
    for (size_t i = price_buffer.size() - short_window_size; i < price_buffer.size(); ++i) {
        short_sum += price_buffer[i];
    }
    current_short_ma = short_sum / short_window_size;

    double long_sum = std::accumulate(price_buffer.begin(), price_buffer.end(), 0.0);
    current_long_ma = long_sum / long_window_size;

    if (prev_short_ma <= prev_long_ma && current_short_ma > current_long_ma) {
        return Signal::BUY;
    }
    else if (prev_short_ma >= prev_long_ma && current_short_ma < current_long_ma) {
        return Signal::SELL;
    }
    
    return Signal::HOLD;
}