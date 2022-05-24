#!/usr/bin/python
import getpass
import sys
import telnetlib
import string
HOST = "192.168.1.251"
user = "root"
password = "admin"

tn = telnetlib.Telnet(HOST)
#tn.set_debuglevel(2)

tn.read_until("login: ")
tn.write(user + "\n")
if password:
    tn.read_until("Password: ")
    tn.write(password + "\n")

tn.read_until("Controller#")
tn.write("show run\n")
while True:
	line = tn.read_until("--More--",1)
	print line
	tn.write(" ")
	if line is  " " :
		line2 = tn.read_until("Controller",1)
		print line2
		print "finish"
		break
tn.close()
