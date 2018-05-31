# Xt9 Anti Rootkit  www.xtiger.net

#############install################
unzip process_list.zip;cd process_list;make;make install

####################################
suse10:~ # sleep 12345&
[1] 4091
suse10:~ # sleep 54321&
[2] 4098

suse10:~/tl/adore-ng # insmod adore-ng.ko 
suse10:~/tl/adore-ng # ./ava i 4091
Checking for adore  0.12 or higher ...
Adore 1.56 installed. Good luck.
Made PID 4091 invisible.
suse10:~/tl/adore-ng # vi 
suse10:~/tl/adore-ng # cd ~/programme/del_task_4_hide/
suse10:~/programme/del_task_4_hide # insmod delp.ko 

suse10:~/programme/process_list_proc # make;make install 

suse10:~/programme/process_list_proc # cat /proc/ps_list 
                        --= Xt9 - Anti - Rootkit =--
                        beta v0.11      by xti9er
[4091] sleep    [may be hiddened by vfs_readdir hook]
[4098] sleep    [may be hiddened by REMOVE_LINKS]

