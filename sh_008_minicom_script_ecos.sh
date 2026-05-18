#!/bin/bash

#CM / RG console
#screen -S minicom-session minicom -D /dev/ttyAMA1 -O timestamp=extended -C /home/user/Desktop/DG4278VF/rg_monitor_$(date +%Y-%m-%d_%H-%M).log
#screen -S minicom-session minicom -D /dev/ttyAMA2 -O timestamp=extended -C /home/user/Desktop/DG4278VF/cm_monitor_$(date +%Y-%m-%d_%H-%M).log

while true; do
	screen -S minicom-session -X stuff "/cm/errors$(printf \\r\\r\\r)"
	sleep 3
	screen -S minicom-session -X stuff "/doc/dsd$(printf \\r\\r)"
	sleep 3
	screen -S minicom-session -X stuff "/doc/usd$(printf \\r\\r)"
	sleep 3
	screen -S minicom-session -X stuff "/cm/ofdm_analyzer 32$(printf \\r)"
	sleep 1
	screen -S minicom-session -X stuff "$(printf \\r\\r)"
	sleep 3
	screen -S minicom-session -X stuff "/cm/ofdm_analyzer 33$(printf \\r)"
	sleep 1
	screen -S minicom-session -X stuff "$(printf \\r\\r)"
	sleep 10
done
