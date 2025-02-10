#!/bin/bash
cm_ip="10.30.2.37"
community="private"
count=0;
while [ "$count" -lt 1000000 ] ; do
        let count++;
	date
	echo "go start ($count)";
	snmpset -v 2c -c $community $cm_ip 1.3.6.1.2.1.69.1.1.3.0 i 1;

        echo "waiting for 600 seconds";
        sleep 600;

done
