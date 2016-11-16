#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Tiryoh");
MODULE_DESCRIPTION("A simple driver for controlling RasPi GPIO");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static ssize_t led_write(struct file* flip, const char* buf, size_t count, loff_t* pos){
    char c;
    if(copy_from_user(&c, buf, sizeof(char)))
        return -EFAULT;
    printk(KERN_INFO "receive %c\n", c);
    return 1;
}

static ssize_t sushi_read(struct file* flip, const char* buf, size_t count, loff_t* pos){
    int size = 0;
    char sushi[] = {0xF0, 0x9F, 0x8D, 0xA3, 0x0A}; //sushi
    if(copy_to_user(buf+size, (const char *)sushi, sizeof(sushi))){
        printk(KERN_INFO "sushi : copy_to_user failed\n");
        return -EFAULT;
    }
    size += sizeof(sushi);
    return size;
}


static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .read = sushi_read
};

static int __init init_mod(void){
    int retval;
    retval = alloc_chrdev_region(&dev, 0, 1, "led_blink");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d", MAJOR(dev), MINOR(dev));
        return retval;
    }

    cls = class_create(THIS_MODULE,"myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

    return 0;
}

static void __exit cleanup_mod(void){
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

