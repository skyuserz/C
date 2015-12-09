#include<stdio.h>
#include<string.h>
#include "ds.h"
struct dec_map_s{
	char ch;
	char *word;
}dec_map[] = {
	 {'t',"天"},
	 {'d',"地"},
	 {'s',"上"},
	 {'a',"一只"},
	 {'e',"鹅"},
	 {'z',"追"},
	 {'g',"赶"},
	 {'x',"下"},
	 {'n',"蛋"},
	 {'i',"恨"},
};
void stack_init(struct stack* pStack)
{
	pStack->top = -1;
}
char stack_get_top(struct stack* pStack)
{
	return pStack->data[pStack->top];
}

void stack_push(struct stack* pStack,char ch)
{
	pStack->data[++pStack->top] = ch;
}

char stack_pop(struct stack* pStack)
{
	return pStack->data[pStack->top--];
}

int stack_is_empty(struct stack* pStack)
{
	return pStack->top == -1;
}

char queue_pop(struct queue* pQueue)
{
	char ch;
	ch=pQueue->data[pQueue->front];
	pQueue->front++;
	if(pQueue->front == 1024){
		pQueue->front = 0;
	}
	return ch;
}

void queue_push(struct queue * pQueue,char ch)
{
	if(pQueue->rear == 1024)
		pQueue->rear = 0;
	pQueue->data[pQueue->rear] = ch;
	pQueue->rear++;
}

void queue_init(struct queue* pQueue)
{
	pQueue->front = pQueue->rear = 0;
}

int queue_is_empty(struct queue* pQueue)
{
	return pQueue->front == pQueue->rear;
}

void print(struct queue *pQueue)
{
	int len=sizeof(dec_map)/sizeof(dec_map[0]);
	while(!queue_is_empty(pQueue)){
		char ch=queue_pop(pQueue);
		int k;
		for(k=0;k<len;k++)
		{
			if(ch == dec_map[k].ch){
				printf(dec_map[k].word);
				break;
			}
		}
	}
	printf("\n");
}
void decode(char *str)
{
	char *ptr = NULL;
	struct queue q;
	queue_init(&q);
	for (ptr=str;*ptr;ptr++){
		if(*ptr == 'A'){
			queue_push(&q,'s');
			queue_push(&q,'a');
			queue_push(&q,'e');
		}else if(*ptr == '\n'){
			break;
		}else if(*ptr == 'B'){
			queue_push(&q,'t');
                        queue_push(&q,'A');
                        queue_push(&q,'d'); 
			queue_push(&q,'A');
		}else if(*ptr == '('){
			struct stack ss;
			char x;
			++ptr;
			x=*ptr;
			stack_init(&ss);
			for(ptr++;*ptr&&*ptr!=')';ptr++){
				stack_push(&ss,*ptr);
			}
			while(!stack_is_empty(&ss)){
				queue_push(&q,x);
				queue_push(&q,stack_pop(&ss));
			}
			queue_push(&q,x);
		}else{
			queue_push(&q,*ptr);
		}
	}
	{
		struct queue qq;
		queue_init(&qq);
		while(!queue_is_empty(&q)){
			char ch = queue_pop(&q);
			switch(ch){
			case 'A':
				queue_push(&qq,'s');
                        	queue_push(&qq,'a');
                        	queue_push(&qq,'e');
				break;
			default:
				queue_push(&qq,ch);
			}
		}
		print(&qq);
	}			
}

int main(void)
{
	char str[1024];
	for(;;){
		printf("请输入魔王语言:");
		fgets(str,sizeof(str),stdin);
		if(*str == '\n')
			break;
		printf("翻译:");
		decode(str);
		printf("\n");
	}
	return 0;
}
