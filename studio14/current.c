#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <asm/current.h>


struct task_struct *task0;
static unsigned long m_size = 2000;
module_param(m_size, ulong, 0644);


static int mod_thread(void *p) {
        // printk("This is a function called mod_thread and it is running");    
	printk(KERN_INFO "fs is %p\n",current->fs);
	printk(KERN_INFO "files is %p\n",current->files);
	printk(KERN_INFO "nsproxy is %p\n",current->nsproxy);
        
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
