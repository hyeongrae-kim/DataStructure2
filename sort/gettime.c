#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	struct timeval bgn, end;
	double diff;
	gettimeofday(&bgn, NULL);
	sleep(1);
	gettimeofday(&end, NULL);
	diff = (end.tv_sec - bgn.tv_sec) + ((end.tv_usec - bgn.tv_usec)/1000000.0);
	printf("%f\n", diff);

	return 0;
}
