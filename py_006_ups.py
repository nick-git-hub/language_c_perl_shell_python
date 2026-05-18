import matplotlib.pyplot as plt
from datetime import datetime
import numpy as np

log_file = "data/ups.txt"

timestamps = []
emr_values = []

# parse log
with open(log_file, "r") as f:
    for line in f:
        if "EMR[0]" in line:
            time_str = line.split("]")[0][1:]
            ts = datetime.strptime(time_str, "%Y-%m-%d %H:%M:%S.%f")
            timestamps.append(ts)

            emr = int(line.split("EMR[0] = ")[1])
            emr_values.append(emr)

# full battery = 48 hours = 2880 minutes
full_battery = 48 * 60
first_time = timestamps[0]

# x: elapsed minutes → hours
x_minutes = [(ts - first_time).total_seconds() / 60 for ts in timestamps]
x_hours = [m / 60 for m in x_minutes]

# y: minutes → hours
actual_values = [full_battery - m for m in x_minutes]

emr_hours = [m / 60 for m in emr_values]
actual_hours = [m / 60 for m in actual_values]

# plot
plt.figure(figsize=(12,6))

#plt.plot(x_hours, emr_hours, label="Estimated Remaining Time (hours)", marker='.', lw=1, markersize=4)
#plt.plot(x_hours, actual_hours, label="Actual Remaining Time (hours)", marker='.', lw=1, markersize=4)
plt.plot(x_hours, emr_hours, label="Estimated Remaining Time (hours)")
plt.plot(x_hours, actual_hours, label="Actual Remaining Time (hours)")
# 標示第一個 Actual 點
plt.scatter(x_hours[0], actual_hours[0], color="black", s=10, zorder=5)
plt.text(
    x_hours[0] + 0.3,
    actual_hours[0] + 1.5,
    f"{actual_hours[0]}h",
    fontweight='bold',
    fontsize=12,
    color="red",
    zorder=6
)

# 標示第一個 EMR 點
plt.scatter(x_hours[0], emr_hours[0], color="black", s=10, zorder=5)
plt.text(
    x_hours[0] + 0.3,
    emr_hours[0] + 0.5,
    f"{emr_hours[0]}h",
    fontweight='bold',
    fontsize=12,
    color="red",
    zorder=6
)

# 電池資訊文字
battery_info = (
    "Model No: BBS8V1T\n"
    "Input: 11.5~12.5V DC ; 3.5A\n"
    "Rating: 255.5Wh --- 7.3V DC\n"
    "Battery Mode Out: 5.9~8.4V DC ; 5.8A\n"
    "Line Mode Out: 11.2~12.5V DC ; 3.5A\n"
    "Cell Capacity: 35000mAh (5000mAh*7 ; 2S7P)"
)
plt.text(
    0.98, 0.02, battery_info,
    transform=plt.gca().transAxes,
    fontsize=10,
    color="blue",
    verticalalignment='bottom',
    horizontalalignment='right',
    bbox=dict(facecolor='white', alpha=0.7, edgecolor='none')
)

plt.xlabel("Elapsed Time (hours)")
plt.ylabel("Remaining Time (hours)")
plt.title("Estimated Remaining Time                                           vs Actual Remaining Time", fontsize=14)
plt.text(
    0.39, 1.01,  # x:比例 0~1, y:比例 0~1，1.02表示在標題正上方一點
    "(5.3W Constant Power)", 
    color="red", 
    fontsize=14, 
    fontweight='bold',
    ha='left', 
    va='bottom', 
    transform=plt.gca().transAxes
)

# x/y 軸每2小時刻度
plt.xticks(np.arange(0, int(max(x_hours)) + 2, 2))
plt.yticks(np.arange(0, 49, 2))  # 0-48h，每2小時

plt.xlim(0, max(x_hours))
plt.legend()
plt.grid(True)
plt.tight_layout()

# invert y-axis
plt.gca().invert_yaxis()

# save
plt.savefig("emr_vs_actual_hours.png")
print("Plot saved as emr_vs_actual_hours.png")
