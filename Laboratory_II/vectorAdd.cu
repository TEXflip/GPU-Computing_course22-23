#include <stdio.h>
#include <stdlib.h>

#define dtype float

__global__ void VecAdd(dtype *A, dtype *B, dtype *C, int N) {
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	if (i < N) {
		C[i] = A[i] + B[i];
	}
}

void printVector(dtype *v, int N) {
	for (int i = 0; i < N; i++)
		printf("%.2f\t", v[i]);
	printf("\n");
}

int main(int argc, char *argv[] ) {

	if (argc != 2) {
		printf("Usage: <N> (vector size)\n");
		return;
	}

	int N = atoi(argv[1]);
	size_t size = N * sizeof(dtype);

	dtype *h_A = (dtype *)malloc(size);
	dtype *h_B = (dtype *)malloc(size);
	dtype *h_C = (dtype *)malloc(size);

	// initialize host memory
	for (int i = 0; i < N; i++) {
		h_A[i] = rand() / (dtype)RAND_MAX;
		h_B[i] = rand() / (dtype)RAND_MAX;
	}

	printVector(h_A, N);
	printVector(h_B, N);

	dtype *d_A, *d_B, *d_C;
	cudaMalloc(&d_A, size);
	cudaMalloc(&d_B, size);
	cudaMalloc(&d_C, size);

	// copy host memory to device
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

	int threadsPerBlock = 256;
	int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

	VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

	printVector(h_C, N);

	// free device memory
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	// free host memory
	free(h_A);
	free(h_B);
	free(h_C);

	return 0;
}