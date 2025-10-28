import numpy as np
import pandas as pd
import os
print(pd.__version__)
def generate_synthetic_data(
    num_points=10000,
    start_price=100.0,
    trend_slope=0.0005,
    seasonality_amplitude=0.2,
    seasonality_frequency=0.05,
    noise_std_dev=0.04,
    poisson_lambda=0.002,
    poisson_magnitude=0.5
):
    """
    Generates a synthetic time series and saves it as a CSV.
    The timestamp format is specifically chosen for easy C++ parsing.
    """
    print("Generating synthetic market data...")

    time = np.arange(num_points)

    trend = trend_slope * time
    seasonality = seasonality_amplitude * np.sin(2 * np.pi * seasonality_frequency * time)
    random_noise = np.random.normal(loc=0, scale=noise_std_dev, size=num_points)

    poisson_jumps = np.random.poisson(lam=poisson_lambda, size=num_points) # FOR BIG SHOCKS
    jump_directions = np.random.choice([-1, 1], size=num_points)
    poisson_noise = poisson_jumps * jump_directions * poisson_magnitude

    price = start_price + trend + seasonality + random_noise + np.cumsum(poisson_noise)

    timestamps = pd.to_datetime('2025-01-01 09:30:00') + pd.to_timedelta(time, unit='s')
    
    df = pd.DataFrame({
        'timestamp': timestamps.strftime('%Y-%m-%d %H:%M:%S'),
        'price': price
    })
    
    if not os.path.exists('data'):
        os.makedirs('data')
    
    file_path = 'data/synthetic_market_data.csv'
    df.to_csv(file_path, index=False, float_format='%.4f')
    
    print(f"Successfully saved {num_points} data points to '{file_path}'.")

if __name__ == "__main__":
    generate_synthetic_data()