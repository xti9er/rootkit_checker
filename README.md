# rootkit_checker
rootkit(vfs_hookd)_checker

#############install################
unzip process_list.zip;cd process_list;make;make install

####################################
suse10:~/programme/process_list_proc # sleep 1000&
[1] 20076
suse10:~/programme/process_list_proc # ../../t
tdl  tl/  
suse10:~/programme/process_list_proc # ../../tl/adore-ng/ava i 20076
Checking for adore  0.12 or higher ...
Adore 1.56 installed. Good luck.
Made PID 20076 invisible.
suse10:~/programme/process_list_proc # cat /proc/ps_list            
suse10:~/programme/process_list_proc # cat /proc/ps_list 
                        Rootkit Checker Demo
                        beta v0.1 [only vfs hook rootkit]       by xti9er
[1] init
[2] ksoftirqd/0
[3] events/0
[4] khelper
[5] kthread
[8] kblockd/0
[9] kacpid
[10] kacpi_notify
[218] pdflush
[219] pdflush
[221] aio/0
[220] kswapd0
[492] cqueue/0
[493] kseriod
[537] kpsmoused
[1026] scsi_eh_0
[1102] ata/0
[1103] ata_aux
[1135] reiserfs/0
[1204] udevd
[1822] khubd
[2112] shpchpd_event
[2478] kauditd
[2694] dbus-daemon
[2727] acpid
[2734] resmgrd
[2805] hald
[2952] hald-addon-acpi
[2970] hald-addon-stor
[3100] syslog-ng
[3103] klogd
[3123] slpd
[3130] portmap
[3133] auditd
[3240] master
[3275] qmgr
[3301] cron
[3489] nscd
[3660] sshd
[3680] powersaved
[3696] login
[3697] mingetty
[3698] mingetty
[3699] mingetty
[3700] mingetty
[3701] mingetty
[3797] bash
[19713] pickup
[19857] sshd
[19863] bash
[20049] bash
[20076] sleep   [may be hiddened by vfs_readdir hook]
[20079] cat
suse10:~/programme/process_list_proc # grep hiddened /var/log/messages
Feb 16 06:06:01 suse10 kernel: [20076] sleep    [maybe hiddened by vfs_readdir hook]
