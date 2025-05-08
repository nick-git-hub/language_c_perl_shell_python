#!/usr/bin/perl

use warnings;
use strict;

#use usesReleased;
#use Utils;
#use CPE::Project;
#use Net::SSH::Perl;

#require "$ENV{HOME}/cpesvn/Automatisierung/Perl/bin/new_CommonFunctions.pl";

sub snmpwalk {
	my ($host, $oid) = @_;
	my $command = "snmpwalk -t 30 -v 2c -c private $host $oid";
	print "$command\n";
	my $output = `$command`;
	if ($? != 0) {
		die "ERROR: snmpwalk failed with exit code $?.\n";
	}
	print "$output\n";
	return $output;
}

sub snmpset {
	my ($host, $oid, $value) = @_;
	my $command = "snmpset -t 30 -v 2c -c private $host $oid $value";
	print "$command\n";
	my $output = `$command`;
	if ($? != 0) {
		die "ERROR: snmpset failed with exit code $?.\n";
	}
	print "$output\n";
	return $output;
}

sub snmpget {
	my ($host, $oid) = @_;
	my $command = "snmpget -t 30 -v 2c -c private $host $oid";
	print "$command\n";
	my $output = `$command`;
	if ($? != 0) {
		die "ERROR: snmpset failed with exit code $?.\n";
	}
	print "$output\n";
	return $output;
}

sub PNMcheckbox
{
	my $status = shift;
	my $filename = shift;
	my $count = shift;
	my $name = shift;
	my $CM_IP = shift;
	
	my $tmp;

	$tmp = snmpget($CM_IP, "$status");
	if(($tmp =~ /INTEGER: 4/))
	{
		$tmp = snmpget($CM_IP, "$filename");

		$tmp =~ /STRING: "(.*)"/;
		print("ok $count Test $name passed. Generated file name: $1\n\n");
		
		return $1;
	}
	else
	{
		print("not ok $count Test $name failed\n\n");
	}

} 

sub isReady
{
       	my $CM_IP = shift;	

	my $tmp;
        my $timer = 100;	
	do
        {
        	$timer=$timer-1;
		sleep(60);
                $tmp = snmpwalk($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.2.1.3.0");
		if($timer == 0)
		{
			print"not ok box takes too long to generate the file, test will be exited\n";
			exit;
		}

        }
	until($tmp =~ /INTEGER: 2/);
}

sub snmp_check
{
	my $CMD = shift;

        if($CMD =~ /Timeout/)
        {
		print "not ok 1 SNMP Timeout - can't continue with the test\n";
                exit;
        }

        if($CMD =~ /No Such Object/)
        {
		print "not ok 1 SNMP Error - No Such Object - can't continue with the test\n";
                exit;
        }
}

unless(caller)
{
	my $CM_MAC = $ARGV[0];
	
	#my $ACTIVATE = $ENV{'PNM_TEST'};
	my $ACTIVATE = "yes";
	
	if($ACTIVATE eq "no")
	{
		print("ok # skip Test not activated\n");
		exit;
	}

	#my $CM_IP = ip_from_bacc($CM_MAC);
	my $CM_IP = "2001:50:1:26:3131:135f:1e86:d30a"; #DUT CM IP

	test($CM_IP);
}

sub test
{
	my $CM_IP = shift;

	my $CMD;
	my %PNMoid;
	my $ssh;
	my $stdout; 
	my $stderr;
	my $exit; 

	my $testcount = 1;
	my $DSindex = 0;
	my $USindex = 0;
	my $macindex = 2;
	my $T1 = 0;
	my $T2 = 0;
	my $Diff = 0;

	my $PATH_CM = "pnm/";
	my $PATH = "/mnt/d/Nick/2_Tool/TFTP_server/pnm";
	my $TFTPv4 = "0x0a3b12ad"; #10.59.18.173
	my $TFTPv6 = "0x20010050000100590000000034830173";

	#my $TFTP = CPE::Project->getConfigOfAlias('TFTP');
	my $TFTP = "TFTP";
	my $host = "";
	my $user = "";
	my $pass = "";
	
	if($CM_IP eq "NO_IP")
	{
        	print "not ok Can't get IP address of CM\n";
        	exit;
	}

	if($CM_IP eq "NOT_REACHABLE")
	{
        	print "not ok IP address of CM is not reachable\n";
        	exit;
	}

	$CMD = snmpwalk($CM_IP, "1.3.6.1.2.1.2.2.1.3");

	if($CMD =~ /iso.3.6.1.2.1.2.2.1.3\.(.*) = INTEGER: 277/)
	{
		#$DSindex = $1;
		$DSindex = 50; #Sercomm CASA EU env.
	}

	if($CMD =~ /iso.3.6.1.2.1.2.2.1.3\.(.*) = INTEGER: 278/)
	{
		$USindex = $1;
	}

	if($CMD =~ /iso.3.6.1.2.1.2.2.1.3\.(.*) = INTEGER: 127/)
	{
        	$macindex = $1;
	}

	%PNMoid = (
		#docsPnmCmDsOfdmSymCap =>{
		#walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.2",
		#enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.2.1.1.$DSindex",
		#status=>"1.3.6.1.4.1.4491.2.1.27.1.2.2.1.8.$DSindex",
		#filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.2.1.9.$DSindex",
		#channel=>"DS",
		#name=>"DS Sample Capture",
		#},
        	docsPnmCmOfdmChanEstCoef=>{
        	walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.3",
        	enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.3.1.1.$DSindex",
        	status=>"1.3.6.1.4.1.4491.2.1.27.1.2.3.1.7.$DSindex",
        	filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.3.1.8.$DSindex",
        	channel=>"DS",
		name=>"OFDM Channel Estimation Calculation",
        	},
        	docsPnmCmDsConstDispMeas=>{
        	walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.4",
        	enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.4.1.1.$DSindex",
        	status=>"1.3.6.1.4.1.4491.2.1.27.1.2.4.1.5.$DSindex",
        	filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.4.1.6.$DSindex",
        	channel=>"DS",
		name=>"OFDM Constellation",
        	},
        	docsPnmCmDsOfdmRxMer=>{
        	walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.5",
        	enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.5.1.1.$DSindex",
        	status=>"1.3.6.1.4.1.4491.2.1.27.1.2.5.1.7.$DSindex",
        	filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.5.1.8.$DSindex",
        	channel=>"DS",
		name=>"OFDM RxMER Measurement",
        	},
        	docsPnmCmDsOfdmFec=>{
        	walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.7",
        	enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.7.1.2.$DSindex",
        	status=>"1.3.6.1.4.1.4491.2.1.27.1.2.7.1.3.$DSindex",
        	filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.7.1.4.$DSindex",
        	channel=>"DS",
		name=>"OFDM Profile FEC Summary",
        	},
		docsPnmCmDsHist=>{
		walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.9",
		enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.9.1.1.$macindex",
		status=>"1.3.6.1.4.1.4491.2.1.27.1.2.9.1.3.$macindex",
		filename=>"1.3.6.1.4.1.4491.2.1.27.1.2.9.1.4.$macindex",
		channel=>"DS",
		name=>"Histogram For Downstream",
		},
        	docsPnmCmUsPreEq=>{
        	walk=>"1.3.6.1.4.1.4491.2.1.27.1.2.10",
        	enable=>"1.3.6.1.4.1.4491.2.1.27.1.2.10.1.1.$USindex",
        	status=>"1.3.6.1.4.1.4491.2.1.27.1.2.10.1.8.$USindex",
        	filename1=>"1.3.6.1.4.1.4491.2.1.27.1.2.10.1.9.$USindex",
        	filename2=>"1.3.6.1.4.1.4491.2.1.27.1.2.10.1.10.$USindex",
        	channel=>"US",
		name=>"ODFMA Pre-equalization Coefficients",
        	},
	);

	if($CM_IP=~ /:/)
	{       
		print("configure tftp address type\n");
		$CMD = snmpset($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.1.1.1.0", "i 2");
        	snmp_check($CMD);

        	print("configure tftp ip address\n");
        	$CMD = snmpset($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.1.1.2.0", "x $TFTPv6");
        	snmp_check($CMD);
	}
	else
	{
        	print("configure tftp address type\n");
        	$CMD = snmpset($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.1.1.1.0", "i 1");
        	snmp_check($CMD);

		print("configure tftp ip address\n");
		$CMD = snmpset($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.1.1.2.0", "x $TFTPv4");
		snmp_check($CMD);
	}
	
	print("configure tftp file directory\n");
	$CMD = snmpset($CM_IP, "1.3.6.1.4.1.4491.2.1.27.1.1.1.3.0", "s $PATH_CM");
	snmp_check($CMD);
	
	if($DSindex != 0)
	{
		foreach(sort keys %PNMoid)
		{
			if($PNMoid{$_}{channel} eq 'DS')
			{
				print("**************************************************************************************************************************************\n");
				print("Test $PNMoid{$_}{name}\n\n");
				$CMD = snmpwalk($CM_IP, "$PNMoid{$_}{walk}");
                       		$T1 = time();
                       		$CMD = snmpset($CM_IP, "$PNMoid{$_}{enable}", "i 1");
                      		print("Waiting until the test is finished\n\n");
                     		isReady($CM_IP);
                    		$T2 = time();
                      		$Diff = $T2 - $T1;
                  		print("Time needed for $PNMoid{$_}{name} is about $Diff seconds (check done every 60s)\n\n\n");
				$CMD = PNMcheckbox($PNMoid{$_}{status}, $PNMoid{$_}{filename}, $testcount, $PNMoid{$_}{name}, $CM_IP);
				$testcount++;

				#$ssh = Net::SSH::Perl->new("$host", debug=>0);
				#$ssh->login("$user", "$pass");
	
				#($stdout, $stderr, $exit) = $ssh->cmd("ls $PATH/$CMD");
				print("File on TFTP server:\n");
				#print("$stdout\n");
				my $command = "ls $PATH/$CMD";
				print "$command\n";
    				my $output = `$command`;

				#if($stdout =~ /$CMD/)
				if($output =~ /$CMD/)
				{
					print("ok $testcount Test $PNMoid{$_}{name} file $CMD was found on the TFTP server\n\n");
        			}
				else
				{
					print("not ok $testcount Test $PNMoid{$_}{name} file $CMD was not found on the TFTP server\n\n");
				}
			
				$testcount++;
	
				#($stdout, $stderr, $exit) = $ssh->cmd("rm $PATH/$CMD");
				#print("$stderr\n");

                	}
		}
	}
	else
	{
		print("**************************************************************************************************************************************\n");
		print"ok # SKIP OFDM channel not active\n\n"
	}

	if($USindex != 0)
	{
		foreach(sort keys %PNMoid)
		{
			if($PNMoid{$_}{channel} eq 'US')
			{
				print("**************************************************************************************************************************************\n");
				print("Test $PNMoid{$_}{name}\n\n");
				$CMD = snmpwalk($CM_IP, "$PNMoid{$_}{walk}");
				$T1 = time();
				$CMD = snmpset($CM_IP, "$PNMoid{$_}{enable}", "i 1");
				print("Waiting until the test is finished\n\n");
				isReady($CM_IP);
				$T2 = time();
				$Diff = $T2 - $T1;
				print("Time needed for $PNMoid{$_}{name} is about $Diff seconds (check done every 60s)\n\n\n");
				my @CMDS;
				push(@CMDS,PNMcheckbox($PNMoid{$_}{status}, $PNMoid{$_}{filename1}, $testcount, $PNMoid{$_}{name}, $CM_IP));
				$testcount++;
				push(@CMDS,PNMcheckbox($PNMoid{$_}{status}, $PNMoid{$_}{filename2}, $testcount, $PNMoid{$_}{name}, $CM_IP));
				$testcount++;

				#$ssh = Net::SSH::Perl->new("$host", debug=>0);
				#$ssh->login("$user", "$pass");
	
				my $testNAME=$PNMoid{$_}{name};

				foreach(@CMDS){
					#($stdout, $stderr, $exit) = $ssh->cmd("ls $PATH/$_");
				        print("File on TFTP server:\n");
					#print("$stdout\n");
                                	my $command = "ls $PATH/$_";
	                                print "$command\n";
        	                        my $output = `$command`;

					#if($stdout =~ /$_/)
				        if($output =~ /$_/)
                                        {
						print("ok $testcount Test $testNAME file $_ was found on the TFTP server\n\n");

                                        }
                                        else
                                        {
                                                print("not ok $testcount Test $testNAME file $_ was not found on the TFTP server\n\n");
                                        }

                                        $testcount++;
					#($stdout, $stderr, $exit) = $ssh->cmd("rm $PATH/$_");
					#print("$stderr\n");
				}
			}
		}
	}
	else
	{
		print("**************************************************************************************************************************************\n");
		print("ok # SKIP OFDMA channel not active\n\n");
	}
}


