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
struct kmem_cache *test_cachep = NULL;  
struct Foo *object1 = NULL;

static int mod_thread(void *p) {
        //struct Foo f1; 
        struct timespec start, end;
        int iter=0;
        getrawmonotonic(&start);
        while(iter<m_size){
            object1 = kmem_cache_alloc(test_cachep, GFP_KERNEL);  
            if(!object1)  
                return -ENOMEM;  
            else
               kmem_cache_free(test_cachep, object1);  
               iter+=1;
        }
        getrawmonotonic(&end);
        printk(KERN_ALERT "%ld s %ld nanoseconds\n",(end.tv_sec - start.tv_sec), (end.tv_nsec - start.tv_nsec));
        return 0;
    }
    //init function
static int ksync_init(void) {
        task0 = kthread_create(mod_thread, "data for mod_thread0", "thread_func_0");
        test_cachep = kmem_cache_create("slab_test_cachep", sizeof(struct Foo), 0, SLAB_HWCACHE_ALIGN, NULL);  
        if(!test_cachep)  
          return -ENOMEM; 
        kthread_bind(task0,0);
        
        wake_up_process(task0);
        printk(KERN_ALERT "The parameter we get is %lu\n", m_size);
        return 0;
}

//exit function
static void ksync_exit(void){
        //kthread_stop(task0);
        kmem_cache_destroy(test_cachep); 
        printk(KERN_ALERT "Module exit.\n");
}



module_init(ksync_init);
module_exit(ksync_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LTJ");
MODULE_DESCRIPTION("Memory Management Studio");
