#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/gfp.h>
#include<linux/slab.h>
#include <linux/vmalloc.h>
struct task_struct *task0;
static unsigned long m_size = 2000;
module_param(m_size, ulong, 0644);
#define BILLION 1E9
struct Foo {
  unsigned int some_array[8];
};

static int mod_thread(void *p) {
        struct Foo f1; 
        struct timespec start, end;
        unsigned char *kmallocmem;
        int iter=0;
        getrawmonotonic(&start);
        while(iter<m_size){
           kmallocmem = (unsigned char*)kmalloc(sizeof(f1.some_array), GFP_KERNEL);
              if (!kmallocmem){
                    printk(KERN_ALERT "no kmallocmem\n");
                    return -1;
              }

              //printk(KERN_ALERT "wangbaduzi\n");
              kfree(kmallocmem);
              iter+=1;
              //printk(KERN_ALERT "wangbaduffdsafazi\n");
        }
        //printk(KERN_ALERT "wangbaduffdsafazi\n");
        getrawmonotonic(&end);
        printk(KERN_ALERT "%ld s %ld nanoseconds\n",(end.tv_sec - start.tv_sec), (end.tv_nsec - start.tv_nsec));
        return 0;
    }
    //init function
static int ksync_init(void) {
    
    

        task0 = kthread_create(mod_thread, "data for mod_thread0", "thread_func_0");
  
        kthread_bind(task0,0);
        
        wake_up_process(task0);
        printk(KERN_ALERT "The parameter we get is %lu\n", m_size);
        return 0;
}

//exit function
static void ksync_exit(void){
        //kthread_stop(task0);
        printk(KERN_ALERT "Module exit.\n");
}



module_init(ksync_init);
module_exit(ksync_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LTJ");
MODULE_DESCRIPTION("Memory Management Studio");
