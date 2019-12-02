#include <stdio.h>
#include <pthread.h>
void func(int x);
long count = 0;
int main(){
	pthread_t t1;
	pthread_t t2;
	pthread_create( &t1, NULL, (void*)func, (void*)1);
	pthread_create( &t2, NULL, (void*)func, (void*)2);
	printf("main()\n");

	pthread_join( t1, NULL);
	pthread_join( t2, NULL);
	return 0;
}

void func(int x){
	int i;
	printf("count = %ld\n",count);
	for(i = 0;i < 1000000;i ++){ // すぐに終了する場合は，この値を大きくする．
		count ++;
	}
	printf("count = %ld\n",count);
}
