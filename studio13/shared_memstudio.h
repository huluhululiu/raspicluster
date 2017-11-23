#define shared_mem_size 10
const char* mem_region;
struct shared_data {
volatile int write_guard;
volatile int read_guard;
volatile int delete_guard;
volatile int data[shared_mem_size];
}

