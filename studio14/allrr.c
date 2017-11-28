#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/path.h>
#include <linux/mount.h>
#include <linux/dcache.h>
#include <linux/fs_struct.h>
#include <linux/pid.h>
#include <linux/fs.h>
#include <linux/list.h>

struct task_struct *task0;
static unsigned long pid = 0;
struct pid *pid_struct;
struct task_struct *task;
module_param(pid, ulong, 0644);


static int mod_thread(void *p) {
        //struct file * fi;
        struct dentry * thedentry;
        struct dentry * curdentry;
        // const char * curname = NULL;
        // printk(KERN_INFO "Hello android kernel...\n");

        // fi = filp_open("/root/", O_RDONLY, 0);
        thedentry = current->fs->root.dentry;

        list_for_each_entry(curdentry, &thedentry->d_subdirs, d_child) {
            //curname = curdentry->d_name.name;

            printk(KERN_INFO "Filename: %p \n", curdentry->d_iname);
        }

        return 0;
}

//init function
static int ksync_init(void) {
	
	

        task0 = kthread_create(mod_thread, "data for mod_thread0", "thread_func_0");
  
        kthread_bind(task0,0);
        
        wake_up_process(task0);
        return 0;
}

//exit function
static void ksync_exit(void){
        //kthread_stop(task0);
        

        printk(KERN_INFO "Module exit.\n");
}



module_init(ksync_init);
module_exit(ksync_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LTJ");
MODULE_DESCRIPTION("VFS Layer Studio");
