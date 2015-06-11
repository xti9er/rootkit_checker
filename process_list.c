//by xti9er @ 2015.4.27
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/stat.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
#define ITERATE_NAME readdir
#define READ_PROC_PROTO char *buffer, char **start, off_t off,int count, int *eof, void *data
#else
#define ITERATE_NAME iterate
#define READ_PROC_PROTO struct file* file, char* buffer, size_t count, loff_t* offset
#endif

static struct file_operations proc_file_ops;

static unsigned short int read_flag;

void *get_vfs_readdir ( const char *path )
{
    void *ret;
    struct file *filep;

    if ( (filep = filp_open(path, O_RDONLY, 0)) == NULL )
        return NULL;
        if(!IS_ERR(filep)){
            if ((ret = filep->f_op->ITERATE_NAME)==NULL)
                return NULL;
            filp_close(filep, 0);
            return ret;
        }
        else{
                return 0;
        }
}

int read_proc(READ_PROC_PROTO) 
{
	int len=0;
	struct task_struct *task_list;
	char path[64]="\0";

	if(read_flag)
		read_flag = 0;
	else {
		read_flag = 1;
		return 0;
	}
	len  += sprintf(buffer+len, "\t\t\tRootkit Checker Demo\n\t\t\tbeta v0.1 [only vfs hook rootkit]\tby xti9er\n");
	for_each_process(task_list) {
		strcpy(path,"/proc/");
		sprintf(path,"%s%d",path,task_list->pid);
		len  += sprintf(buffer+len, "[%d] %s",task_list->pid,task_list->comm);
        printk("[%d] %s",task_list->pid,task_list->comm);

			if(get_vfs_readdir(path)){
				len  += sprintf(buffer+len, "\n");
				printk("\n");
			}
			else{
				len  += sprintf(buffer+len, "\t[may be hiddened by vfs_readdir hook]\n");
				printk("\t[maybe hiddened by vfs_readdir hook]\n");
			}
	}
	  
	return len;
}

int functn_init (void) {

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
	create_proc_read_entry("ps_list",0,NULL,read_proc,NULL);	
#else
	proc_create("ps_list",0,NULL,&proc_file_ops);
	proc_file_ops.read=read_proc;
#endif

	read_flag = 1;
	return 0;
}

void functn_cleanup(void) {
    remove_proc_entry("ps_list",NULL);
}
MODULE_AUTHOR("xti9er");
MODULE_LICENSE("GPL");   
module_init(functn_init);
module_exit(functn_cleanup);
