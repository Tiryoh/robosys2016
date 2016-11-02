#include <linux/module.h>
#include <linux/fs.h>

MODULE_AUTHOR("Tiryoh");
MODULE_DESCRIPTION("A simple driver for controlling RasPi GPIO");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;

static int __init init_mod(void){
    int retval;
    retval = alloc_chrdev_region(&dev, 0, 1, "led_blink");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));
    return 0;
}

static void __exit cleanup_mod(void){
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

