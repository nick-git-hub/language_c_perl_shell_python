#!/bin/bash

count=0;
while [ "$count" -lt 1000000 ] ; do
	let count++;
	snmpwalk -v 2c -c private 192.168.100.1 .;
	printf $count;
	sleep 3;
done
