#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

void dfs(struct task_struct *task){		//create dfs function
	struct task_struct *task_next;	//task_struct is a structure for task define in Linux,
	struct list_head *list;		//so do list_head
	
	list_for_each(list, &task->children){	//To find all children in this task
		task_next = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "pname: %s | state: %ld | pid: %d \n", task_next->comm, task_next->state, task_next->pid);
		dfs(task_next);		//continue for the next task
	}
}

int iterating_over_tasks_dfs_init(void){	//init function, to call dfs function and load the message
	printk(KERN_INFO "Loading module...\n");
	dfs(&init_task);
	printk(KERN_INFO "Module dfs loaded.\n");
	return 0;
}

void iterating_over_tasks_dfs_exit(void){	//exit function
	printk(KERN_INFO "Module dfs removed.\n");
}

module_init(iterating_over_tasks_dfs_init);
module_exit(iterating_over_tasks_dfs_exit);
