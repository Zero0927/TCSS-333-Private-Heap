//Siyuan Zhou
#include"mallok.h"
#include<stdio.h>
#include<memory.h>
#include<assert.h>

/*
* create a pool of 1000 bytes.  Count how times you can successfully request a block of size 10
*/
void test_1(){
	int size=1000;
	int block_size=10;
	int time=0;
	void*ptr;
	create_pool(size);
	while(NULL!=(ptr=my_malloc(block_size)))
		++time;
	printf("test_1: pool_size=%d, block=%d, times=%d\n",
		size, block_size, time);
	//assert(time=size/block_size);
	printf("test1: success\n");
}

/*
*  create a pool of 1000 bytes.  Make 5 requests for blocks of 200 bytes.  Free all 5 blocks.  Repeat this request/free 
* pattern several times to make sure you can reuse blocks after they are returned. 
*/
void test_2(){
	int size=1000;
	int blk_size=200;
	void*ptr[5];
	int k, n;
	create_pool(size);
	for(n=0;n<10; ++n){
		for(k=0; k<5; ++k){
			ptr[k]=my_malloc(blk_size);
			assert(ptr[k]!=NULL);
		}
		for(k=0; k<5; ++k){
			my_free(ptr[k]);
			ptr[k]=NULL;
		}
	}
	printf("test2: success\n");
}

/*
* create a pool of 1000 bytes.  
    Make 5 requests for blocks of 200 bytes.   
    Free the middle block. 
    Request a block of 210 bytes (it should fail) 
    Request a block of 150 bytes (it should succeed) 
    Request a block of 60 bytes (it should fail) 
    Request a block of 50 bytes (it should succeed) 
*/
void test_3(){
	int size=1000;
	void*ptr1,*ptr2,*ptr3,*ptr4,*ptr5,*ptr6,*ptr7;
	create_pool(size);
	ptr1=my_malloc(200);
	assert(ptr1);
	ptr2=my_malloc(200);
	assert(ptr2);
	ptr3=my_malloc(200);
	assert(ptr3);
	ptr4=my_malloc(200);
	assert(ptr4);
	ptr5=my_malloc(200);
	assert(ptr5);

	//
	my_free(ptr3);
	ptr3=NULL;
	//
	ptr3=my_malloc(210);
	assert(ptr3==NULL);
	ptr3=my_malloc(150);
	assert(ptr3!=NULL);
	ptr6=my_malloc(60);
	assert(ptr6==NULL);
	ptr7=my_malloc(50);
	assert(ptr7!=NULL);
	printf("test3: success\n");
}

/*
*create a pool of 1000 bytes.    
   Request  5 blocks of 200 bytes.    
   Fill the first block with the letter 'A', the second block with 'B', etc. 
   Verify that the values stored in each block are still there.  (Is the first block full of A's, second block full of B's, etc.)
*/
void test_4(){
	int size=1000;
	void*ptr1,*ptr2,*ptr3,*ptr4,*ptr5;
	char*tmp;
	create_pool(size);
	ptr1=my_malloc(200);
	assert(ptr1);
	memset(ptr1, 'A', 200);
	ptr2=my_malloc(200);
	assert(ptr2);
	memset(ptr2, 'B', 200);
	ptr3=my_malloc(200);
	assert(ptr3);
	memset(ptr3, 'C', 200);
	ptr4=my_malloc(200);
	assert(ptr4);
	memset(ptr4, 'D', 200);
	ptr5=my_malloc(200);
	assert(ptr5);
	memset(ptr5, 'E', 200);
	for(tmp=(char*)ptr1; tmp<(char*)ptr1+200; ++tmp)
		assert(*tmp=='A');
	for(tmp=(char*)ptr2; tmp<(char*)ptr2+200; ++tmp)
		assert(*tmp=='B');
	for(tmp=(char*)ptr3; tmp<(char*)ptr3+200; ++tmp)
		assert(*tmp=='C');
	for(tmp=(char*)ptr4; tmp<(char*)ptr4+200; ++tmp)
		assert(*tmp=='D');
	for(tmp=(char*)ptr5; tmp<(char*)ptr5+200; ++tmp)
		assert(*tmp=='E');
	printf("test4: success\n");
}

/*
* create a pool of 1000 bytes. 
    Request and return a block of 1000 bytes 
    Request and return four blocks of 250 bytes 
    Request and return ten blocks of 100 bytes 
*/
void test_5(){
	int size=1000;
	void*ptr1;
	void*ptr[10];
	int k;
	create_pool(size);
	ptr1=my_malloc(1000);
	assert(ptr1);
	my_free(ptr1);
	for(k=0;k<4;k++){
		ptr[k]=my_malloc(250);
		assert(ptr[k]);
	}
	for(k=0;k<4;k++){
		my_free(ptr[k]);
	}
	for(k=0;k<10;k++){
		ptr[k]=my_malloc(100);
		assert(ptr[k]);
	}
	printf("test5: success\n");
}

int main(int argc, char*argv[]){
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
	return 0;
}

