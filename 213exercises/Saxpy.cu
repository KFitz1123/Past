#include <stdint.h>
#include <stdio.h>

#define N 48
#define THREADS_PER_BLOCK 12



__global__ void saxpy(float a, float* x, float* y) {
  // Which index of the array should this thread use?
  size_t index = (THREADS_PER_BLOCK)*(blockIdx.x) + (threadIdx.x);
    if(index >= N) return;
  // Compute a times x plus y for a specific index
  y[index] = a * x[index] + y[index];
}

__global__ void dotproduct(float* x, float* y, float* result) {
  // Compute the index this thread should use to access elements
  size_t index = threadIdx.x + blockIdx.x * THREADS_PER_BLOCK;
  if(index >= N) return;

  // Create space for a shared array that all threads in this block will use to store pairwise products
  __shared__ float temp[THREADS_PER_BLOCK];

  // Compute pairwise products
  temp[threadIdx.x] = x[index] * y[index];
  __syncthreads();

  // The thread with index zero will sum up the values in temp
  if(threadIdx.x == 0) {
    float sum = 0;
    int i;
    for(i=0; i<THREADS_PER_BLOCK; i++) {
      sum += temp[i];
    }

    // Add the sum for this block to the result
    // *result += sum;
    atomicAdd(result, sum);
  }
}


int main() {
  // Allocate arrays for X and Y on the CPU. This memory is only usable on the CPU
  float* cpu_x = (float*)malloc(sizeof(float) * N);
  float* cpu_y = (float*)malloc(sizeof(float) * N);

  // Initialize X and Y
  int i;
  for(i=0; i<N; i++) {
    cpu_x[i] = (float)i;
    cpu_y[i] = 1.0;
  }

  // The gpu_x and gpu_y pointers will only be usable on the GPU (which uses separate memory)
  float* gpu_x;
  float* gpu_y;

  // Allocate space for the x array on the GPU
  if(cudaMalloc(&gpu_x, sizeof(float) * N) != cudaSuccess) {
    fprintf(stderr, "Failed to allocate X array on GPU\n");
    exit(2);
  }

  // Allocate space for the y array on the GPU
  if(cudaMalloc(&gpu_y, sizeof(float) * N) != cudaSuccess) {
    fprintf(stderr, "Failed to allocate Y array on GPU\n");
    exit(2);
  }

  // Copy the cpu's x array to the gpu with cudaMemcpy
  if(cudaMemcpy(gpu_x, cpu_x, sizeof(float) * N, cudaMemcpyHostToDevice) != cudaSuccess) {
    fprintf(stderr, "Failed to copy X to the GPU\n");
  }

  // Copy the cpu's y array to the gpu with cudaMemcpy
  if(cudaMemcpy(gpu_y, cpu_y, sizeof(float) * N, cudaMemcpyHostToDevice) != cudaSuccess) {
    fprintf(stderr, "Failed to copy Y to the GPU\n");
  }

  // Calculate the number of blocks to run, rounding up to include all threads
  size_t blocks = (N + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;

  // Run the saxpy kernel
 // saxpy<<<blocks, THREADS_PER_BLOCK>>>(0.5, gpu_x, gpu_y);
 // Copy the cpu's y array to the gpu with cudaMemcpy  

 float* cpu_result = (float*)malloc(sizeof(float));
 *cpu_result = 0.0;
 float* gpu_result;
  if(cudaMalloc(&gpu_result, sizeof(float)) != cudaSuccess) {
    fprintf(stderr, "Failed to allocate Y array on GPU\n");
    exit(2);
  }

  // Copy the cpu's result to the gpu with cudaMemcpy
  if(cudaMemcpy(gpu_result, cpu_result, sizeof(float), cudaMemcpyHostToDevice) != cudaSuccess) {
    fprintf(stderr, "Failed to copy result to the GPU\n");
  }

 dotproduct<<<1, THREADS_PER_BLOCK>>>(gpu_x, gpu_y, gpu_result);
  // Wait for the kernel to finish
  if(cudaDeviceSynchronize() != cudaSuccess) {
    fprintf(stderr, "CUDA Error: %s\n", cudaGetErrorString(cudaPeekAtLastError()));
  }

  // Copy the y array back from the gpu to the cpu
  if(cudaMemcpy(cpu_y, gpu_y, sizeof(float) * N, cudaMemcpyDeviceToHost) != cudaSuccess) {
    fprintf(stderr, "Failed to copy Y from the GPU\n");
  }

// Copy the cpu's y array to the gpu with cudaMemcpy
//   if(cudaMemcpy(gpu_y, cpu_y, sizeof(float) * N, cudaMemcpyHostToDevice) != cudaSuccess) {
//     fprintf(stderr, "Failed to copy Y to the GPU\n");
//   }

// Copy the cpu's result to the gpu with cudaMemcpy
  if(cudaMemcpy(cpu_result, gpu_result, sizeof(float), cudaMemcpyDeviceToHost) != cudaSuccess) {
    fprintf(stderr, "Failed to copy result from the GPU\n");
  }

  // Print the updated y array
    printf("%d: %f\n", i, *cpu_result);


  cudaFree(gpu_x);
  cudaFree(gpu_y);
  cudaFree(gpu_result);
  free(cpu_x);
  free(cpu_y);
  return 0;
}