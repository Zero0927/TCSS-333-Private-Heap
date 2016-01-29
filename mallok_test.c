//Siyuan Zhou
#include"mallok.h"
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<assert.h>

struct _Block;

typedef struct _Block{
	void* address;//memory address
	unsigned size;//number of bytes
	char isFree;
	struct _Block*next;
}Block;

static Block*firstBlock=NULL;

void create_pool(int size){
	void*memory=malloc(size);
	if(firstBlock){
		free(firstBlock->address);
		free(firstBlock);
		firstBlock=NULL;
	}
	assert(firstBlock==NULL);
	if(memory!=NULL){
		firstBlock=(Block*)malloc(sizeof(Block));
		firstBlock->next=NULL;
		firstBlock->isFree=1;
		firstBlock->size=size;
		firstBlock->address=memory;
	}
}

void *my_malloc(int size){
	Block*tmp,*cur,*next;
	cur=firstBlock;
	//find the first block that has enough memory
	while(cur!=NULL&&(!cur->isFree||cur->size<size)){
		cur=cur->next;
	}
	//find the first block
	if(cur!=NULL&&cur->isFree&&cur->size>=size){
		if(cur->size>size){//block size is bigger than size requsted, so split this block to two blocks
			tmp=(Block*)malloc(sizeof(Block));
			tmp->next=cur->next;
			tmp->isFree=1;
			tmp->size=cur->size-size;
			tmp->address=(void*)(size+(char*)cur->address);
			cur->next=tmp;
		}
		cur->isFree=0;
		cur->size=size;
		return cur->address;
	}else
		return NULL;
}

void my_free(void *block){
	Block*prev,*cur,*next;
	prev=NULL;
	cur=firstBlock;
	//find the block whose address is block to free
	while(cur!=NULL&&cur->address!=block){
		prev=cur;
		cur=cur->next;
	}
	//the block is invalid pointer
	if(cur==NULL)
		return;
	assert(!cur->isFree);
	cur->isFree=1;
	//join the previous free block with this block
	if(prev!=NULL&&prev->isFree){
		prev->size+=cur->size;
		prev->next=cur->next;
		free(cur);
		cur=prev;
	}
	//join the next free block with this block
	next=cur->next;
	if(next!=NULL&&next->isFree){
		cur->size+=next->size;
		cur->next=next->next;
		free(next);
	}
}



