#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>

MODULE_DESCRIPTION("Device driver to count letters and return letter in specific casing");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "testchar"
#define IOCTL_SET_LOWER 1
#define IOCTL_SET_UPPER 2
#define IOCTL_SET_CAPS 3

static int major;
static char message[256] = {0};
static int message_len = 0;
static int format = IOCTL_SET_LOWER; // Default to lowercase format
static struct class *charClass = NULL;
static struct cdev charCdev;

// Custom helper functions for case conversion
char to_lower(char ch)
{
    return (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch;
}

char to_upper(char ch)
{
    return (ch >= 'a' && ch <= 'z') ? ch - 32 : ch;
}

static ssize_t dev_read(struct file *file, char __user *user_buffer, size_t len, loff_t *offset)
{
    char processed_message[256];
    int i;

    // Format message based on IOCTL setting
    for (i = 0; i < message_len; i++)
    {
        if (format == IOCTL_SET_LOWER)
            processed_message[i] = to_lower(message[i]);
        else if (format == IOCTL_SET_UPPER)
            processed_message[i] = to_upper(message[i]);
        else if (format == IOCTL_SET_CAPS)
        {
            processed_message[i] = (i == 0 || message[i - 1] == ' ') ? to_upper(message[i]) : to_lower(message[i]);
        }
    }
    processed_message[message_len] = '\0';

    // Append the length of the string
    snprintf(processed_message + message_len, sizeof(processed_message) - message_len, " [%d]", message_len);

    // Copy processed message to user space
    if (copy_to_user(user_buffer, processed_message, strlen(processed_message) + 1))
        return -EFAULT;

    return strlen(processed_message) + 1;
}

static ssize_t dev_write(struct file *file, const char __user *user_buffer, size_t len, loff_t *offset)
{
    if (len > 255)
        return -EINVAL;

    if (copy_from_user(message, user_buffer, len))
        return -EFAULT;

    message[len] = '\0';
    message_len = len;
    return len;
}

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
    case IOCTL_SET_LOWER:
        format = IOCTL_SET_LOWER;
        break;
    case IOCTL_SET_UPPER:
        format = IOCTL_SET_UPPER;
        break;
    case IOCTL_SET_CAPS:
        format = IOCTL_SET_CAPS;
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = dev_read,
    .write = dev_write,
    .unlocked_ioctl = dev_ioctl,
};

static int __init char_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0)
    {
        printk(KERN_ALERT "Failed to register device\n");
        return major;
    }

    charClass = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(charClass))
    {
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(charClass);
    }

    device_create(charClass, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    printk(KERN_INFO "TestChar device initialized with major number %d\n", major);
    return 0;
}

static void __exit char_exit(void)
{
    device_destroy(charClass, MKDEV(major, 0));
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "TestChar device exited\n");
}

module_init(char_init);
module_exit(char_exit);
