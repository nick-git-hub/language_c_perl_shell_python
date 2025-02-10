#!/bin/bash

#root:LANRouter:a2425e7eb29e74ff4ec0cdce23290b47
#HTDIGEST_FILE="1.txt"

REALM="LANRouter"

if [ $# -ne 2 ]; then
    echo "Usage: $0 <username> <password>"
    exit 1
fi

USERNAME=$1
PASSWORD=$2


HA1=$(echo -n "$USERNAME:$REALM:$PASSWORD" | md5sum | awk '{print $1}')

#STORED_HA1=$(grep "^$USERNAME:$REALM:" "$HTDIGEST_FILE" | cut -d':' -f3)
STORED_HA1="a2425e7eb29e74ff4ec0cdce23290b47"

echo "HA1=$HA1"
echo "STORED_HA1=$STORED_HA1"

if [ "$HA1" = "$STORED_HA1" ]; then
    echo "Password for user $USERNAME is correct."
    exit 0
else
    echo "Password for user $USERNAME is incorrect."
    exit 1
fi
