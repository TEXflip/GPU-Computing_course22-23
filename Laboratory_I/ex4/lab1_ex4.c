#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define vtype int
#define itype int

vtype* random_vector (int n) {
	vtype* v = (vtype*)malloc(sizeof(vtype)*n);
	for (int i=0; i<n; i++) {
		v[i] = (vtype)rand()/((vtype)(RAND_MAX/5));
	}
	return v;
}

vtype* prefix_sum(vtype* v, int n) {
	vtype* p = (vtype*)malloc(sizeof(vtype)*n);
	p[0] = v[0];
	for (int i=1; i<n; i++) {
		p[i] = p[i-1] + v[i];
	}
	return p;
}

void print_vector(vtype* v, int n) {
	for (int i=0; i<n; i++)
		printf("%.2f\t", (float)v[i]);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <n>\n", argv[0]);
		return 1;
	}
	printf("argv[1] = %s\n", argv[1]);

	int n = atoi(argv[1]);

	vtype* v = random_vector(n);
	print_vector(v, n);
	vtype* p = prefix_sum(v, n);
	print_vector(p, n);
	return 0;
}
