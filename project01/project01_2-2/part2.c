#include <linux/list.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>//kmalloc

/*linked list初始化*/
static LIST_HEAD(birthday_list);

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};
/*產生有5個struct birthday 節點的linkedlist(birthday_list)*/
int birthday_list_init(void)
{
	struct birthday *p;
	int i;
	for(i = 0; i < 5 ;i++) {
		p = kmalloc(sizeof(*p), GFP_KERNEL);
		p->day = 1+i;
		p->month = 4;
		p->year = 2022;
		INIT_LIST_HEAD(&p->list);
		list_add_tail(&p->list, &birthday_list);//添加節點到birthday_list
	}

	printk(KERN_INFO "Loading module\n");
	printk(KERN_INFO "The list~\n");
	/*遍歷每個節點並在日誌輸出資訊*/
	list_for_each_entry(p, &birthday_list, list) {
		printk(KERN_INFO "Day: %d Month: %d Year: %d\n", p->day, p->month, p->year);
	}

	return 0;
}

void birthday_list_exit(void)
{
	struct birthday *person, *next;
	/*遍歷刪除節點*/
	list_for_each_entry_safe(person, next, &birthday_list, list) {
		printk(KERN_INFO "Freeing node");
		list_del(&person->list);
		kfree(person);
	}
	printk(KERN_INFO "Removing module\n");
}

module_init(birthday_list_init);
module_exit(birthday_list_exit);

