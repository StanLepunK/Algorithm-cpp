#include <stdio.h>

int factorial(int n) {
   int ret;

   for(ret = 1 ; n > 1 ; n--) {
      ret *= n;
   }
   return (ret);
}

int num_permutation(int n, int r) {
   return (factorial(n)/factorial(n - r));
}


void swap(int *a, int *b) {
   int buf;
   buf = *a;
   *a = *b;
   *b = buf;
}

void print_arr(int arr[], size_t len) {
   int index = 0;
   while(index < len) {
      printf("arr[%i] = %i\n",index, arr[index]);
       index++;
  }
}

// https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/
void permutation(int a[], int size, int n) {
   if (size == 1) {
      print_arr(a, n);
   }
 
   for (int i = 0; i < size; i++) {
      permutation(a, size - 1, n);
      if (size % 2 == 1) {
         // if size is odd, swap 0th i.e (first) and 
         // (size-1)th i.e (last) element
         swap(&a[0], &a[size - 1]);
      } else {
         // If size is even, swap ith and 
         // (size-1)th i.e (last) element
         swap(&a[i], &a[size - 1]);
      }
   }
}



int main() {
  int arr [3] = {0, 1, 2};
  int len = sizeof(arr)/sizeof(arr[0]);
  int max = num_permutation(len, len -1);
  printf("num permutation: %i\n",max);
  permutation(arr, len, len);
  return(0);
}
