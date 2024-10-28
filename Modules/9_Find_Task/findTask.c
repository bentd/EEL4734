#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/string.h>
#include <linux/moduleparam.h>

MODULE_DESCRIPTION("Kernel module finds process by name with PID.");
MODULE_VERSION("1.0");

static char *name = "";
module_param(name, charp, 0644);
MODULE_PARM_DESC(name, "The name of the process to find");

static int __init findTask_init(void)
{
    struct task_struct *task;
    int found = 0;

    if (strlen(name) == 0)
    {
        printk(KERN_INFO "findTask: No process name specified.\n");
        return -EINVAL;
    }

    for_each_process(task)
    {
        if (strcmp(task->comm, name) == 0)
        {
            printk(KERN_INFO "Found process %s with pid %d\n", task->comm, task->pid);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printk(KERN_INFO "Not Found process %s\n", name);
    }

    return 0;
}

static void __exit findTask_exit(void)
{
    printk(KERN_INFO "findTask module exited\n");
}

module_init(findTask_init);
module_exit(findTask_exit);
