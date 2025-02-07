import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load the CSV files
config_path = "config.csv"
det_analysis_path = "det_analysis.csv"
rand_analysis_path = "rand_analysis.csv"

config_df = pd.read_csv(config_path)
det_analysis_df = pd.read_csv(det_analysis_path)
rand_analysis_df = pd.read_csv(rand_analysis_path)

# Trim spaces from column names
config_df.columns = config_df.columns.str.strip()
det_analysis_df.columns = det_analysis_df.columns.str.strip()
rand_analysis_df.columns = rand_analysis_df.columns.str.strip()

# Extract values from config file
log_n = config_df.iloc[0]["Log2N"]
n = config_df.iloc[0]["N"]
n_log_n = config_df.iloc[0]["Nlog2N"]

# Extract rounds and running times from det_analysis
rounds = det_analysis_df["Round"]
construction_time = det_analysis_df["RunningTimeConstruction"]
finding_time = det_analysis_df["RunningTimeFinding"]
deleting_time = det_analysis_df["RunningTimeDeleting"]
inserting_time = det_analysis_df["RunningTimeInserting"]

# Create the plot
plt.figure(figsize=(10, 6))

# Plot theoretical complexity lines as fine dotted black lines
plt.plot(rounds, [log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [n_log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [2*n_log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)

# Plot benchmark running times as fine slopes
plt.plot(rounds, construction_time, label="Construction Time", linestyle="-", linewidth=1)
plt.plot(rounds, finding_time, label="Finding Time", linestyle="-", linewidth=1)
plt.plot(rounds, deleting_time, label="Deleting Time", linestyle="-", linewidth=1)
plt.plot(rounds, inserting_time, label="Inserting Time", linestyle="-", linewidth=1)

# Labels and title
plt.xlabel("Rounds")
plt.ylabel("Running Time")
plt.title(f"Benchmarking Running Times of Deterministic Skip List (n = {int(n)})")

# Set custom y-ticks with labels at the corresponding positions
plt.yticks([log_n, n, n_log_n, 2*n_log_n], ["log(n)", "n", "n log(n)", "2(n log(n))"])

# Add legend and grid for clarity
plt.legend()
plt.grid(True, axis="x", linestyle="dotted", linewidth=0.5)

# Show plot
plt.show()

# Extract rounds and running times from det_analysis
rounds = rand_analysis_df["Round"]
construction_time = rand_analysis_df["RunningTimeConstruction"]
finding_time = rand_analysis_df["RunningTimeFinding"]
deleting_time = rand_analysis_df["RunningTimeDeleting"]
inserting_time = rand_analysis_df["RunningTimeInserting"]
max_height = rand_analysis_df["MaxHeight"]

# Create the plot
plt.figure(figsize=(10, 6))

# Plot theoretical complexity lines as fine dotted black lines
plt.plot(rounds, [log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [2*log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [n_log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)
plt.plot(rounds, [2*n_log_n] * len(rounds), color="black", linestyle="dotted", linewidth=1)

# Plot benchmark running times as fine slopes
plt.plot(rounds, construction_time, label="Construction Time", linestyle="-", linewidth=1)
plt.plot(rounds, finding_time, label="Finding Time", linestyle="-", linewidth=1)
plt.plot(rounds, deleting_time, label="Deleting Time", linestyle="-", linewidth=1)
plt.plot(rounds, inserting_time, label="Inserting Time", linestyle="-", linewidth=1)
plt.plot(rounds, max_height, label="Max Height", linestyle="-", linewidth=1)

# Labels and title
plt.xlabel("Rounds")
plt.ylabel("Running Time")
plt.title(f"Benchmarking Running Times of Deterministic Skip List (n = {int(n)})")

# Set custom y-ticks with labels at the corresponding positions
plt.yticks([log_n, 2*log_n, n, n_log_n, 2*n_log_n], ["log(n)", "2log(n)", "n", "n log(n)", "2(n log(n))"])

# Add legend and grid for clarity
plt.legend()
plt.grid(True, axis="x", linestyle="dotted", linewidth=0.5)

# Show plot
plt.show()