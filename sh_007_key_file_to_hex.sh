#!/bin/bash

KEY_STREAM=`hexdump -C $1 | awk -F \| '{print $1}' | awk '{print $2 $3 $4 $5 $6 $7 $8 $9 $10 $11 $12 $13 $14 $15 $16 $17}' | tr -d '\n'`
echo $KEY_STREAM
