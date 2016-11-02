#include <linux/module.h>

MODULE_AUTHOR("Tiryoh");
MODULE_DESCRIPTION("A simple driver for controlling RasPi GPIO");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int __init init_mod(void){
    printk(KERN_INFO "%s is loaded.\n", __FILE__);
    return 0;
}

static void __exit cleanup_mod(void){
    printk(KERN_INFO "%s is unloaded.\n", __FILE__);
}

module_init(init_mod);
module_exit(cleanup_mod);

