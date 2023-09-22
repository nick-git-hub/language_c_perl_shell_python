#!/bin/bash

#echo -n "398710" | openssl sha256 -hmac "password1"
echo -n "$1" | openssl sha256 -hmac "$2"
