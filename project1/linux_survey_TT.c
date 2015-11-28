#include<linux/linkage.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/mm.h>

asmlinkage void sys_linux_survey_TT(int pid, char* result)
{
	struct task_struct *target_task;
	struct mm_struct *target_mm;
	struct vm_area_struct *target_vma;

	for_each_process(target_task){
		if(target_task->pid == pid)
			break;
	}
	printk("<0>\nsurvey: target- %d %s\n", target_task->pid, target_task->comm);
	
	target_mm = target_task->mm;
	printk("<0>"
	"Code Segment start = %lx, end = %lx\n"
	"Data Segement start = %lx, end = %lx\n"
	"Heap Segement start = %lx, end = %lx\n"
	"Stack Segment start = %lx\n",
	target_mm->start_code, target_mm->end_code,
	target_mm->start_data, target_mm->end_data,
	target_mm->start_brk, target_mm->brk,
	target_mm->start_stack);

	for(target_vma = target_mm->mmap; target_vma; target_vma = target_vma->vm_next){
		printk("<0>"
		"VM Area start = %lx, end = %lx\n", target_vma->vm_start, target_vma->vm_end);
	}

}
