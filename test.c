#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define PROCESS_NAME_LEN 32
#define MIN_SLICE 10
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3
int mem_size = DEFAULT_MEM_SIZE;
int ma_algorithm = MA_FF;
static int pid = 0;
int flag = 0;
struct free_block_type{
	int size;
	int start_addr;
	struct free_block_type*next;
};
struct free_block_type *free_block;
struct allocated_block{
	int pid;
	int size;
	int start_addr;
	char process_name[PROCESS_NAME_LEN];
	struct allocated_block *next;
};
struct allocated_block*allocated_block_head = NULL;
struct free_block_type* init_free_block(int mem_size){
	struct free_block_type*fb;
	fb = (struct free_block_type*)malloc(sizeof(struct free_block_type));
	if(fb == NULL){
		printf("No mem\n");
		return NULL;
	}
	fb->size = mem_size;
	fb->start_addr = DEFAULT_MEM_START;
	fb->next = NULL;
	return fb;
}
void display_menu(){
	printf("\n");
	printf("1-Set memory size (default = %d)\n",DEFAULT_MEM_SIZE);
	printf("2-Select memory allocation algorithm\n");
	printf("3-New process \n");
	printf("4-Terminate a process\n");
	printf("5-Display memory usage\n");
	printf("0-Exit\n");
}
int set_mem_size(){
	int size;
	if(flag!=0){
		printf("Cannot set memory size again\n");
		return 0;
	}
	printf("Total memory size =");
	scanf("%d",&size);
	if(size > 0){
		mem_size = size;
		free_block->size = mem_size;
	}
	flag = 1;
	return 1;
}
int exchange(struct free_block_type* a, struct free_block_type* b){
	int tmpsize, tmpstart;
	tmpsize = a->size;
	tmpstart = a->start_addr;
	a->size = b->size;
	a->start_addr = b->start_addr;
	b->size = tmpsize;
	b->start_addr = tmpstart;
	return 1;
}
void rearrange_FF(){
	struct free_block_type* ab, *temp;
	int tmp;
	ab = free_block;
	if(free_block == NULL || free_block->next == NULL)
		return ;
	printf("into rearrange_FF() success\n");
	while(1){
		tmp = 0;
		ab = free_block;
		while(ab->next != NULL){
			temp = ab->next;
			if(ab->start_addr > temp->start_addr)
				tmp = exchange(ab, temp);
			ab = ab->next;
		}
		if(tmp == 0)
			break;
	}
}
void rearrange_BF(){
	struct free_block_type* ab;
	int tmp;
	ab = free_block;
	if(free_block == NULL || free_block->next == NULL)
		return ;
	while(1){
		tmp = 0;
		ab = free_block;
		while(ab->next != NULL){
			if(ab->size > ab->next->size)
				tmp = exchange(ab, ab->next);
			ab = ab->next;
		}
		if(tmp == 0)
			break;
	}
}
void rearrange_WF(){
	struct free_block_type* ab;
	int tmp;
	ab = free_block;
	while(1){
		tmp = 0;
		ab = free_block;
		while(ab->next != NULL){
			if(ab->size < ab->next->size)
				tmp = exchange(ab, ab->next);
			ab = ab->next;
		}
		if(tmp == 0)
			break;
	}
}
void rearrange(int algorithm){
	switch(algorithm){
		case MA_FF: rearrange_FF();break;
		case MA_BF: rearrange_BF();break;
		case MA_WF: rearrange_WF();break;
	}
}
void set_algorithm(){
	int algorithm;
	printf("\t1-First Fit\n");
	printf("\t2-Best Fit\n");
	printf("\t3-Worst Fit\n");
	scanf("%d", &algorithm);
	if(algorithm>=0 && algorithm <= 3)
		ma_algorithm = algorithm;
	rearrange(ma_algorithm);
}											
new_process(){
	struct allocated_block *ab;
	int size; int ret;
	ab = (struct allocated_block*)malloc(sizeof(struct allocated_block));
	if(!ab)exit(-5);
	ab->next = NULL;
	pid++;
	sprintf(ab->process_name,"PROCESS-%02d",pid);
	ab->pid = pid;
	printf("Memory for %s:",ab->process_name);
	scanf("%d", &size);
	if(size>0)ab->size = size;
	ret = allocate_mem(ab);
	if((ret == 1)&&(allocated_block_head == NULL)){
		allocated_block_head = ab;
		return 1;
	}
	else if(ret == 1){
		ab->next = allocated_block_head;
		allocated_block_head = ab;
		return 2;
	}else if(ret == -1){
		printf("Allocation fail\n");
		free(ab);
		return -1;
	}
	return 3;
}
void free_freelink(struct free_block_type *a){
	struct free_block_type *tmp, *cur;
	cur = tmp = a;
	while(cur != NULL){
		tmp = tmp->next;
		free(cur);
		cur = tmp;
	}
}
int allocate_mem(struct allocated_block *ab){
	struct free_block_type *fbt, *pre;
	struct allocated_block* tmp;
	int request_size = ab->size;
	int next_addr;
	fbt = pre = free_block;
	tmp = allocated_block_head;
	if(free_block == NULL)
		return -1;
	while(pre != NULL){//寻找大小足够分配的内存块
		if(fbt->size >= request_size){
			if((fbt->size - request_size) <= 1){//将多余的少部分空间分配给程
				request_size = ab->size = fbt->size;
				ab->start_addr = fbt->start_addr;
				mem_size -= request_size;//
				fbt->start_addr += request_size;
				fbt->next = pre->next;
				free(pre);
			}else{//剩余空间较大时
				ab->start_addr = fbt->start_addr;
				fbt->size -= request_size;
				fbt->start_addr +=request_size;
				mem_size -= request_size;//
			}
			rearrange(ma_algorithm);
			return 1;
		}
		fbt = fbt->next;
		pre = fbt->next;
	}
	if(mem_size > request_size){//紧缩法
		while(tmp != NULL){//整合分散的分配给进程的内存块的地址
			if(tmp == allocated_block_head){
				tmp->start_addr = DEFAULT_MEM_START;
				next_addr = tmp->size+tmp->start_addr;
			}
			else{
				tmp->start_addr = next_addr;
				next_addr = tmp->size+tmp->start_addr;
			}
			tmp = tmp->next;
		}
		ab->start_addr = next_addr;//给ab它的首地址
		//mem_size -= next_addr;//

		free_freelink(free_block);//释放空闲链
		//合并小的空闲链
		fbt = (struct free_block_type*)malloc(sizeof(struct free_block_type));
		fbt->next = NULL;
		mem_size -= request_size;
		fbt->size = mem_size;
		fbt->start_addr = next_addr+request_size;
		free_block = fbt;
		return 1;
	}
	return -1;
}
struct allocated_block *find_process(int pid){
	struct allocated_block *ab;
	ab = allocated_block_head;
	while(ab != NULL){
		if(ab->pid == pid)
			return ab;
		ab = ab->next;
	}
	return NULL;
}
void kill_process(){
	struct allocated_block* ab;
	int pid;
	scanf("%d",&pid);
	ab = find_process(pid);
	if(ab != NULL){
		free_mem(ab);
		dispose(ab);
	}
}
void show_link(){
	struct free_block_type*fbt, *pre;
	fbt = free_block;
	while(fbt != NULL){
		printf("size = %d, start_addr = %d\n",fbt->size, fbt->start_addr);
		fbt = fbt->next;
	}
}
int free_mem(struct allocated_block *ab){
	int algorithm = ma_algorithm;
	struct free_block_type*fbt, *pre, *work;
	int next_addr;
	pre = free_block;
	fbt = (struct free_block_type*)malloc(sizeof(struct free_block_type));
	if(!fbt)return -1;
	fbt->next = NULL;
	mem_size += ab->size;
	fbt->size = ab->size;
	fbt->start_addr = ab->start_addr;
	while(pre->next != NULL){
		pre = pre->next;
	}
	pre->next = fbt;
	rearrange(MA_FF);
//	show_link();
	pre = work = free_block;//合并分区
	while(pre->next != NULL){
		pre = work->next;
		next_addr = work->start_addr+work->size;
		if(next_addr == pre->start_addr){
			work->size += pre->size;
			work->next = pre->next;
			free(pre);
		}else{
			work = work->next;
		}
			pre = work;
	}
	rearrange(ma_algorithm);
}
int dispose(struct allocated_block*free_ab){
	struct allocated_block *pre, *ab;
	if(free_ab == allocated_block_head){
		allocated_block_head = allocated_block_head->next;
		free(free_ab);
		return 1;
	}
	pre = allocated_block_head;
	ab = allocated_block_head->next;
	while(ab != free_ab){
		pre = ab;
		ab = ab->next;
	}
	pre->next = ab->next;
	free(ab);
	return 2;
}
int display_mem_usage(){
	struct free_block_type *fbt = free_block;
	struct allocated_block*ab = allocated_block_head;
	if(fbt == NULL)return -1;
	printf("----------------------------------------------\n");
	printf("Free Memory:\n");
	printf("%20s %20s\n","start_addr", "   size");
	while(fbt != NULL){
		printf("%20d %20d\n",fbt->start_addr, fbt->size);
		fbt = fbt->next;
	}
	printf("\nUsed Memory:\n");
	printf("%10s%20s%10s%10s\n","PID",
	"ProcessName","start_addr","size");
	while(ab!=NULL){
		printf("%10d%20s%10d%10d\n",ab->pid, ab->process_name, ab->start_addr, ab->size);
		ab = ab->next;
	}
	printf("-------------------------------------------------\n");
	return 0;
}
void do_exit(){
	struct allocated_block*a, *b;
	struct free_block_type* c, *d;
	a = b = allocated_block_head;
	c = d = free_block;
	while(a != NULL){
		a = a->next;
		free(b);
		b = a;
	}
	while(c != NULL){
		c = c->next;
		free(d);
		d = c;
	}
}
int main(void){
	char choice;
	pid = 0;
	free_block = init_free_block(mem_size);
	while(1){
		display_menu();
		fflush(stdin);
		choice = getchar();
		switch(choice){
			case '1':set_mem_size();break;
			case '2':set_algorithm(); flag=1;break;
			case '3':new_process();flag=1;break;
			case '4':kill_process();flag=1;break;
			case '5':display_mem_usage();flag=1;break;
			case '0':do_exit();exit(0);
			default:break;
		}
	}
	return 0;
}
