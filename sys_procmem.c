#include <linux/linkage.h>
#include <linux/sched.h>
struct proc_segs {
	unsigned long mssv;
	unsigned long start_code, end_code, start_data, end_data;
	unsigned long start_heap, end_heap, start_stack;
};
asmlinkage long sys_procmem(int pid, struct proc_segs *info) {
	struct task_struct *ts = NULL;
	struct mm_struct *mm = NULL;
	for_each_process(ts) {
		if(ts->pid == pid) {
			mm = ts->mm;
			break;
		}
	}
	(*info).mssv = 1611290;
	if(mm == NULL) return -1;
	(*info).start_code = mm->start_code;
	(*info).end_code = mm->end_code;
	(*info).start_data = mm->start_data;
	(*info).end_data = mm->end_data;
	(*info).start_heap = mm->start_brk;
	(*info).end_heap = mm->brk;
	(*info).start_stack = mm->start_stack;
	return 0;
}