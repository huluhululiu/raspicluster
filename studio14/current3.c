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

struct task_struct *task0;
static unsigned long pid = 0;
struct pid *pid_struct;
struct task_struct *task;
module_param(pid, ulong, 0644);


static int mod_thread(void *p) {
        
        if(pid!=0){
                pid_struct = find_get_pid(pid);
                task = pid_task(pid_struct,PIDTYPE_PID);
                printk(KERN_INFO "pid fs pwd mnt is %p\n",task->fs->pwd.mnt);
                printk(KERN_INFO "pid fs root mnt is %p\n",task->fs->root.mnt);
                printk(KERN_INFO "pid fs pwd dentry is %p\n",task->fs->pwd.dentry);
                printk(KERN_INFO "pid fs root dentry is %p\n",task->fs->root.dentry);
                 if (task->fs->pwd.dentry != task->fs->root.dentry){
                        printk(KERN_ALERT "Dentry is different!\n");
                        printk(KERN_INFO "fs pwd dentry d_iname is %p\n",task->fs->pwd.dentry->d_iname);
                        printk(KERN_INFO "fs root dentry d_iname is %p\n",task->fs->root.dentry->d_iname);
                } 
        }
        else{
              //part 3   
                printk(KERN_INFO "fs pwd mnt is %p\n",current->fs->pwd.mnt);
                printk(KERN_INFO "fs root mnt is %p\n",current->fs->root.mnt);
                //part4
                printk(KERN_INFO "fs pwd dentry is %p\n",current->fs->pwd.dentry);
                printk(KERN_INFO "fs root dentry is %p\n",current->fs->root.dentry);
                //  if (current->fs->pwd.dentry != current->fs->pwd.dentry){
                //         printk(KERN_ALERT "Dentry is different!\n");
                //         printk(KERN_INFO "fs pwd dentry d_iname is %*u\n",current->fs->pwd.dentry->d_iname);
                //         printk(KERN_INFO "fs root dentry d_iname is %*u\n",current->fs->root.dentry->d_iname);
                // }  
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
