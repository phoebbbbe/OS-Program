#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

int iterating_over_tasks_linearly_init(void){	//init function, to execute whole thing
	printk(KERN_INFO "Loading module...\n");
	struct task_struct *task;		//using the structure in Linux
	
	for_each_process(task){		//print out all process
		printk(KERN_INFO "pname: %s | state: %ld | pid: %d\n", task->comm, task->state, task->pid);
	}
	
	printk(KERN_INFO "Module loaded. \n");
	return 0;
}

void iterating_over_tasks_linearly_exit(void){
	printk(KERN_INFO "Module removed. \n");
}

module_init(iterating_over_tasks_linearly_init);
module_exit(iterating_over_tasks_linearly_exit);
