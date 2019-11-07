#include <unistd.h>
#include <stdio.h>

int main(){

	int n;
	read(0, &n, sizeof(int));
	printf("%d\n",n);

}
