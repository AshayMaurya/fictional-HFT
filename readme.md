# C++ High-Frequency Trading Terminal Simulation

![Language](https://img.shields.io/badge/<img width="725" height="368" alt="project_img" src="https://github.com/user-attachments/assets/626e7097-1fee-41e0-8b62-6c9714c496e2" />
Language-C%2B%2B%20%26%20Python-blue.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)

This project demonstrates a high-performance trading algorithm simulation. It uses Python for realistic, synthetic market data generation and a pure C++ application for processing the data and simulating a live trading environment directly in the terminal.

## Core Features

-   **High-Performance C++ Core:** All time-sensitive logic, data parsing, and strategy execution is written in C++ for maximum speed.
-   **Python Data Generation:** A simple Python script generates a CSV file with a realistic time series, including trend, noise, and market shocks.
-   **Live Terminal Output:** The C++ application reads the data and prints trade signals to the console with timestamps, simulating a live feed.
-   **Strategy Implemented:** A classic Moving Average Crossover strategy is used to generate BUY and SELL signals.
-   **Clean & Modular:** The project is structured with a clear separation between the C++ application and the data generation script.

## Demo Output

Here is an example of what the live simulation looks like running in the terminal.

**(Suggestion: Replace the code block below with a screenshot or a GIF of your actual application running!)**

```bash
--- Starting Live HFT Simulation ---
Strategy: Moving Average Crossover (50, 200)
Press Ctrl+C to stop.
------------------------------------
2025-01-01 09:34:12 | BUY SIGNAL   | Enter @100.3128
2025-01-01 09:39:45 | SELL SIGNAL  | Close @101.1560 | PnL: +0.8432
2025-01-01 09:48:21 | BUY SIGNAL   | Enter @101.9870
2025-01-01 09:55:03 | SELL SIGNAL  | Close @101.7540 | PnL: -0.2330
...
--- Simulation Finished ---
```

## How to Run

### Prerequisites

-   A C++ compiler (GCC, Clang, MSVC)
-   [CMake](https://cmake.org/download/) (version 3.12 or higher)
-   [Python](https://www.python.org/downloads/) (version 3.6 or higher)
-   Required Python packages: `pip install numpy pandas`

### Step 1: Clone the Repository

```bash
git clone https://github.com/AshayMaurya/fictional-HFT.git
cd fictional-HFT
```

### Step 2: Generate Market Data

Run the Python script to create the `synthetic_market_data.csv` file.

```bash
python generate_data.py
```
This will create the necessary CSV file inside the `data/` directory.

### Step 3: Build the C++ Application

Use CMake to build the executable. This will create a `build` directory with the compiled program.

```bash
# Navigate to the C++ app directory
cd cpp_app

# Create a build directory
mkdir build
cd build

# Configure and build the project
cmake ..
cmake --build .
```

### Step 4: Run the Simulation

Execute the compiled application from the **project's root directory**.

```bash
# On Windows
.\cpp_app\build\hft_app.exe

# On macOS / Linux
./cpp_app/build/hft_app
```

You will now see the live trade signals printed to your terminal.
