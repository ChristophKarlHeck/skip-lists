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

# Extract rounds and running times from deterministic analysis
rounds_det = det_analysis_df["Round"]
construction_time_det = det_analysis_df["RunningTimeConstruction"]
finding_time_det = det_analysis_df["RunningTimeFinding"]
deleting_time_det = det_analysis_df["RunningTimeDeleting"]
inserting_time_det = det_analysis_df["RunningTimeInserting"]

# Extract rounds and running times from randomized analysis
rounds_rand = rand_analysis_df["Round"]
construction_time_rand = rand_analysis_df["RunningTimeConstruction"]
finding_time_rand = rand_analysis_df["RunningTimeFinding"]
deleting_time_rand = rand_analysis_df["RunningTimeDeleting"]
inserting_time_rand = rand_analysis_df["RunningTimeInserting"]
max_height_rand = rand_analysis_df["MaxHeight"]

# Create a figure with two subplots
fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(10, 12))

# First subplot - Deterministic Skip List
axes[0].plot(rounds_det, [log_n] * len(rounds_det), color="black", linestyle="dotted", linewidth=1)
axes[0].plot(rounds_det, [n] * len(rounds_det), color="black", linestyle="dotted", linewidth=1)
axes[0].plot(rounds_det, [n_log_n] * len(rounds_det), color="black", linestyle="dotted", linewidth=1)
axes[0].plot(rounds_det, [2*n_log_n] * len(rounds_det), color="black", linestyle="dotted", linewidth=1)

axes[0].plot(rounds_det, construction_time_det, label="Construction Time", linestyle="-", linewidth=1)
axes[0].plot(rounds_det, finding_time_det, label="Finding Time", linestyle="-", linewidth=1)
axes[0].plot(rounds_det, deleting_time_det, label="Deleting Time", linestyle="-", linewidth=1)
axes[0].plot(rounds_det, inserting_time_det, label="Inserting Time", linestyle="-", linewidth=1)

axes[0].set_xlabel("Rounds")
axes[0].set_ylabel("Running Time")
axes[0].set_title(f"Deterministic Skip List (n = {int(n)})")
axes[0].set_yticks([log_n, n, n_log_n, 2*n_log_n])
axes[0].set_yticklabels(["log(n)", "n", "n log(n)", "2(n log(n))"])
axes[0].legend()
axes[0].grid(True, axis="x", linestyle="dotted", linewidth=0.5)

# Second subplot - Randomized Skip List
axes[1].plot(rounds_rand, [log_n] * len(rounds_rand), color="black", linestyle="dotted", linewidth=1)
axes[1].plot(rounds_rand, [2*log_n] * len(rounds_rand), color="black", linestyle="dotted", linewidth=1)
axes[1].plot(rounds_rand, [n] * len(rounds_rand), color="black", linestyle="dotted", linewidth=1)
axes[1].plot(rounds_rand, [n_log_n] * len(rounds_rand), color="black", linestyle="dotted", linewidth=1)
axes[1].plot(rounds_rand, [2*n_log_n] * len(rounds_rand), color="black", linestyle="dotted", linewidth=1)

axes[1].plot(rounds_rand, construction_time_rand, label="Construction Time", linestyle="-", linewidth=1)
axes[1].plot(rounds_rand, finding_time_rand, label="Finding Time", linestyle="-", linewidth=1)
axes[1].plot(rounds_rand, deleting_time_rand, label="Deleting Time", linestyle="-", linewidth=1)
axes[1].plot(rounds_rand, inserting_time_rand, label="Inserting Time", linestyle="-", linewidth=1)
axes[1].plot(rounds_rand, max_height_rand, label="Max Height", linestyle="-", linewidth=1)

axes[1].set_xlabel("Rounds")
axes[1].set_ylabel("Running Time")
axes[1].set_title(f"Randomized Skip List (n = {int(n)})")
axes[1].set_yticks([log_n, 2*log_n, n, n_log_n, 2*n_log_n])
axes[1].set_yticklabels(["log(n)", "2log(n)", "n", "n log(n)", "2(n log(n))"])
axes[1].legend()
axes[1].grid(True, axis="x", linestyle="dotted", linewidth=0.5)

# Adjust layout and show the plot
plt.tight_layout()
plot_filename = "skip_list_analysis.png"
plt.savefig(plot_filename)
plt.show()