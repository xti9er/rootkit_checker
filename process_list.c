//by xti9er @ 2015.6.19
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/stat.h>
#include <linux/version.h>
#include <asm/current.h>
#include <linux/pid.h>

//#include <linux/pid_namespace.h>

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
        return NULL;
    }
}

struct task_struct *x_find_task_by_pid(pid_t nr)
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 27)
	return find_task_by_pid(nr);
#else
    struct pid *pid;
    struct task_struct *ts = NULL;
	pid = find_get_pid(nr);
	if(pid) {
		ts = pid_task(pid,PIDTYPE_PID);
		put_pid(pid);
	}
	return ts;
#endif
}

int find_task_list(pid_t nr){
	struct task_struct *task_list;
	char path[64]="\0";
        for_each_process(task_list) {
		if(task_list->pid==nr){
        	        strcpy(path,"/proc/");
                	sprintf(path,"%s%d",path,nr);

                        if(get_vfs_readdir(path)){
				return nr;
                        }
                        else{
				return -1;
                        }
		}
        }

	return 0;
}

int read_proc(READ_PROC_PROTO) 
{
	int len=0;
	pid_t p=1;
	
	struct task_struct *t;

	if(read_flag)
		read_flag = 0;
	else {
		read_flag = 1;
		return 0;
	}
	len  += sprintf(buffer+len, "\t\t\t--= Xt9 - Anti - Rootkit =--\n\t\t\tbeta v0.11\tby xti9er\n");


	while(p< PID_MAX_LIMIT ){

		if(t=x_find_task_by_pid(p)){	
			
			if(t->tgid!=p)	//thread id
				goto N;
		
			int p_flag=find_task_list(p);

			if(!x_find_task_by_pid(p)){	//when the process is stopped
//				printk("skip %d\n",p);
				goto N;
			}

			if(p_flag==-1){
				len  += sprintf(buffer+len, "[%d] %s\t[may be hiddened by vfs_readdir hook]\n",t->pid,t->comm);
				printk("[%d] %s\t[maybe hiddened by vfs_readdir hook]\n",t->pid,t->comm);
			}
			else if(p_flag==0){
				len  += sprintf(buffer+len, "[%d] %s\t[may be hiddened by REMOVE_LINKS]\n",t->pid,t->comm);
				printk("[%d] %s\t[maybe hiddened by REMOVE_LINKS]\n",t->pid,t->comm);
			}
			else{
		        	//printk("\n");
//	                	len  += sprintf(buffer+len, "[%d] (%d)\n",t->pid,p_flag);
			}
		}
	
/*	
		else{
			printk("[%d] failed\n",i);
		}
*/
		N:
		p++;
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
