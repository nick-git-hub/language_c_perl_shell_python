#!/usr/bin/python
import getpass
import sys
import telnetlib
import string
import re
import time
import threading
import serial

controller_str = "Controller#"
main_star_flag = 1
##############################################################################
def telnet_connect(HOST,user,password,DEBUG):
	try:
		tn = telnetlib.Telnet(HOST)
	except socket.timeout:
		print "telnet timeout"
	else:
		tn.set_debuglevel(DEBUG)
		tn.read_until("login: ")
		print "login: ",user
		tn.write(user + "\n")
		if password:
			tn.read_until("Password: ")
			tn.write(password + "\n")
			print "Password: "
			return tn

def check_controller_connect_cmc(tn):
	status = 0
	line = tn.read_until("Controller#",300)
	controller_count = line.count("CMC is still booting, trying")
	if controller_count > 50: 
		print "Controller fail!!!!"
		return 0
	else:
		tn.write("con\n")
		tn.read_until("Controller-cfg#")
		tn.write("terminal length 0\n")
		tn.read_until("Controller-cfg#")
		tn.write("exit\n")
		tn.read_until("Controller#")	
		print "Controller#"
		return 1

##############################################################################
def reboot_cmc(tn,status,bootup_wait_sec):
	status = 0
	print controller_str + "reboot"
	tn.write("reboot\n")
	line = tn.read_until("Reboot CMC",1)
	print controller_str + "Reboot CMC ?(y/n)"
	tn.write("y\n")
	time.sleep(5)
	tn.close()
	print "sleep %d sec after telnet..." % (bootup_wait_sec)
	time.sleep(bootup_wait_sec)
	return -1

def show_run(tn,status):
	if status != 1:
		return status

	print controller_str + "show running config"
	tn.write("show run\n")
	while True:
		line = tn.read_until("--More--",1)
		print line
		tn.write(" ")
		searchObj = re.search( r'Controller#', line)
		if searchObj:
			status = 1
			break
	return status

def show_cable_modem_online(tn,status,no_online_retey_times,no_online_retey_wait_sec):
	if status != 1:
		return status

	count = 0
	while True:
		print controller_str + "show cable modem"
		tn.write("show cable modem\n")
		line = tn.read_until("Controller#",5)
		print line
		searchObj = re.search( r'online', line)
		if searchObj:
			status = 1
			break
		else:
			if no_online_retey_times != 0:
				count += 1
				if count == no_online_retey_times:
					status = -2
					print "cm can't online, check dhcp issue"
					break
			print "retey %d and sleep %d sec" % (count,no_online_retey_wait_sec)
			time.sleep(no_online_retey_wait_sec)
	return status

def clear_cable_modem_all(tn,status,succeeded_retey_time,succeeded_wait_sec):
	if status != 1:
		return status

	count = 0
	while True:
		tn.write("clear cable modem all\n")
		line = tn.read_until("Controller#",5)
		print controller_str + line
		searchObj = re.search( r'Succeeded', line)
		if searchObj:
			if succeeded_retey_time != 0:
				count += 1
				if count == succeeded_retey_time:
					break
			status = 1
			time.sleep(succeeded_wait_sec)
		else:
			time.sleep(3)
	return status

def run_cci_client(tn,status,parm_1,parm_2,parm_3,parm_4):
	if status !=1:
		return status
	star = 0
	end = 63
	tn.write("shell\n")
	line = tn.read_until("#",5)
	print line
	while True:
		if (1):
			if parm_1==1 and parm_2==2:
				tn.write("cci_client " + str(parm_1) + " " + str(parm_2) + " " + str(star) + "\n")
				line = tn.read_until("#",5)
				print line
				star = star +1
				if star > 4096:
					status = -2
					break
			else:
				status = -2
				break
		if (0):
			if parm_1==1 and parm_2==9:
				tn.write("cci_client " + str(parm_1) + " " + str(parm_2) + " " + str(star) + " " + str(end) + "\n")
				line = tn.read_until("#",5)
				print line
				star = end + 1 
				end = end + 64
				if star > 4096:
					status = -2
					break
			else:
				status = -2
				break

	return status
##########################################################################
def control_script_thread():
	global main_star_flag
	while True:
		line = sys.stdin.readline()
		searchObj = re.search( r'stop', line)
		if searchObj:
			main_star_flag = 0

		searchObj = re.search( r'star', line)
		if searchObj:
			main_star_flag = 1

		searchObj = re.search( r'quit', line)
		if searchObj:
			main_star_flag = -1

def script_thread():
	DEBUG = 0
	HOST = "192.168.100.1"
	user = "root"
	password = "admin"
	run_script_count = 0
	status = 1
	print "=====star script====="
	while status != -2:
		tn = telnet_connect(HOST,user,password,DEBUG)
		if check_controller_connect_cmc(tn) is 0:
			break
		status = 1
		while status == 1:
			run_script_count += 1
			print "script run ",run_script_count
#######################################################
			#status = show_run(tn,status)
			#status = show_cable_modem_online(tn,status,no_online_retey_times = 0,no_online_retey_wait_sec = 0)
			#status = clear_cable_modem_all(tn,status,succeeded_retey_time = 2,succeeded_wait_sec = 3)
			status = run_cci_client(tn,status,parm_1 = 1,parm_2 = 2,parm_3 = 0,parm_4 = 0)
			#status = reboot_cmc(tn,status,bootup_wait_sec = 60)
######################################################
			time.sleep(1)
	print "=====stop script====="

if __name__ == "__main__":

	#st = threading.Thread(name='script_thread', target=script_thread)
	#ct = threading.Thread(name='control_script_thread', target=control_script_thread)
	#st.start()
	#ct.start()

	script_thread()

