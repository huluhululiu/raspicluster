#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/gfp.h>
struct task_struct *task0;
static unsigned long m_size = 2000;
module_param(m_size, ulong, 0644);
#define BILLION 1E9
struct Foo {
  unsigned int some_array[8];
};

static int mod_thread(void *p) {
        //clock_t start, finish;
        //unsigned long long  duration;
        struct Foo f1; 
        int pnum=0;
        int ordernum=1;
//	int secdur;
//	int nanosecdur;
        struct page *pages=NULL;
        struct timespec start, end;
        printk(KERN_ALERT "The struct size is %d", sizeof(f1.some_array));
        
        pnum = m_size*sizeof(f1.some_array)/4096;
	printk(KERN_ALERT "%d\n", pnum);
        while(pnum!=1){
                pnum=pnum/2;
                ordernum+=1;
        }
        //pnum=get_ordernum(pnum);
        printk(KERN_ALERT "%d\n", ordernum);
        getrawmonotonic(&start);
	pages = alloc_pages(GFP_KERNEL,ordernum);
          if (!pages){
                printk(KERN_ALERT "no page\n");
                return -1;
          }
          
        __free_pages(pages, ordernum);
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
