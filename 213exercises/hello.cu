
#include <stdint.h>
#include <stdio.h>

// // This is a special function that runs on the GPU (device) instead of the CPU (host)
// __global__ void kernel() {
//   printf("Hello world!\n");
// }



__global__ void kernel() {
  printf("Hello from block %d thread %d\n", blockIdx.x, threadIdx.x);
}


int main() {
  // Invoke the kernel function on the GPU with one block of one thread
  kernel<<<4,6>>>();

  // Check for error codes (remember to do this for _every_ CUDA function)
  if(cudaDeviceSynchronize() != cudaSuccess) {
    fprintf(stderr, "CUDA Error: %s\n", cudaGetErrorString(cudaPeekAtLastError()));
  }
  return 0;
}

