#pragma once

#include <string>
#include <vector>
#include <deque>
#include <numeric>

struct Tick {
    std::string timestamp;
    double price;
};

class IStrategy {
public:
    enum class Signal { HOLD, BUY, SELL };
    
    virtual Signal processTick(const Tick& tick) = 0;
    
    virtual ~IStrategy() = default;
};

class MovingAverageCrossover : public IStrategy {
public:
    MovingAverageCrossover(int short_window, int long_window);

    Signal processTick(const Tick& tick) override;

private:
    int short_window_size;
    int long_window_size;
    // Variable state calC
    std::deque<double> price_buffer;
    double current_short_ma = 0.0;
    double current_long_ma = 0.0;
    double prev_short_ma = 0.0;
    double prev_long_ma = 0.0;
};