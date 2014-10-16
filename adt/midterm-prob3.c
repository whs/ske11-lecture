#include <stdio.h>
#include <stdlib.h>

struct list{
	int value;
	struct list *next;
};

struct list * delete(struct list *head, struct list *prev, struct list *item){
	if(prev == NULL){
		head = item->next;
	}else{
		prev->next = item->next;
	}
	free(item);
	return head;
}

void print_list(struct list *head){
	struct list *last = head;
	int first = 1;
	while(last != NULL){
		if(first == 0){
			printf(" --> ");
		}
		printf("%d", last->value);
		first = 0;
		last = last->next;
	}
	printf("\n");
}

int main(){
	struct list *head = malloc(sizeof(struct list));
	struct list *last = head;
	struct list *last2 = NULL;
	int i;
	int fib1=1, fib2=1;

	head->value = 1;
	head->next = NULL;

	// make list of 2-1000 (1 is manually set)
	for(i = 2; i <= 1000; i++){
		struct list *current = malloc(sizeof(struct list));
		current->value = i;
		current->next = NULL;
		last->next = current;
		last = current;
	}

	// print
	print_list(head);

	// delete all fib
	last = head;
	while(last != NULL){
		struct list *next = last->next;
		if(fib2 < last->value){
			// generate fib
			int tmp = fib1;
			fib1 = fib2;
			fib2 = fib2+tmp;
		}
		if(fib2 == last->value){
			head = delete(head, last2, last);
		}else{
			last2 = last;
		}
		last = next;
	}

	// make it circular
	last2->next = head;
	// note: there is no more "head"

	// skip delete
	last = head;
	last2 = NULL;
	i = 0;
	while(last2 != last){
		struct list *next = last->next;
		if(i == 1){
			delete(head, last2, last);
		}else{
			last2 = last;
		}
		last = next;
		i = (i+1) % 2;
	}

	// print one element
	printf("%d\n", last->value);

	return 0;
}
