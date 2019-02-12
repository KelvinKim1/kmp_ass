#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string_matching.h"

void print_array(int *arr, int size){
  for (int i=0; i<size; i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}

void short_test (char *text, int N, char * pattern, int M){
	printf("text='%s', pattern='%s'\n", text, pattern);
	int result1 = string_matching_naive(text, N, pattern, M);
	int result2 = string_matching_kmp(text, N, pattern, M);
	printf("Number of occurrences: result1=%d, result2=%d\n", result1, result2);
}

void performance_test(){

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    for (int n = 10000; n <= 1000000; n+=100000){
        printf("The text length: %d, pattern length: 400\n", n);
        int i;
        int m = 400;

        char *text = malloc(n);
        for (i=0; i<n; i++){
            int pos = rand() % (int)(sizeof(charset) -1);
            text[i] = charset[pos];
        }
        
        text[i] = '\0';
        
        char *pattern = malloc(m);
        for (i=0; i<m; i++){
            int pos = rand() % (int)(sizeof(charset) -1);
            pattern[i] = charset[pos];
        }
        
        pattern[i] = '\0';

        int loopCount;
        
        uint64_t startTime = mach_absolute_time( );
        for (loopCount = 0; loopCount < 5; ++loopCount) {
            string_matching_naive(text, n, pattern, m);
        }
        uint64_t endTime = mach_absolute_time( );
        double averageTime = (double)(endTime-startTime) / 5;
        printf("Avg time for naive string matching algorithm is %fns\n", averageTime);
        
        startTime = mach_absolute_time( );
        for (loopCount = 0; loopCount < 5; ++loopCount) {
            string_matching_kmp(text, n, pattern, m);
        }
        endTime = mach_absolute_time( );
        averageTime = (double)(endTime-startTime) / 5;
        printf("Avg time for kmp string matching algorithm is %fns\n", averageTime);
    }
    printf("Texts and patterns are all randomly created.");
}

void stress_test(int N, int M){
  int i;
  static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  srand(time(NULL));   // Initialization, should only be called once.
  
  while (1) {
    int n = rand() % (N-3) + 3;      // Returns a pseudo-random integer between 3 and N.
	int m = rand() % M + 1; 
    
	char *text = malloc(n);
    for (i=0; i<n; i++){
	  int pos = rand() % (int)(sizeof(charset) -1);
      text[i] = charset[pos];      
    }

    text[i] = '\0';
	
	char *pattern = malloc(m);
    for (i=0; i<m; i++){
	  int pos = rand() % (int)(sizeof(charset) -1);
      pattern[i] = charset[pos];      
    }
     
    pattern[i] = '\0';

  
    printf("text='%s', pattern='%s'\n", text, pattern);
	
    int result1 = string_matching_naive(text, n, pattern, m);
    int result2 = string_matching_kmp(text, n, pattern, m);
    
    if (result1==result2)
      printf("OK\n");
    else {
      printf("Wrong answer: correct=%d, got instead=%d\n", result1, result2);
	  exit(0);
	}
	free(text);
	free(pattern);
  }  
}

int main(int argc, char **argv ){
    if (atoi(argv[1]) == 3){
        performance_test();
        return 0;
    }
    if (argc < 4){
        printf("To run: test <1> <text> <N> <pattern> <M> - short test\n or test <2> <N> <M> - stress test\n or test<3> - performance test\n");
        return 0;
    }
   
    int mode = atoi(argv[1]);
   
    if (mode == 1){
        if (argc < 6){
			printf("To run: test <1> <text> <N> <pattern> <M>\n");
			return 0;
	   }
	   char *text = argv[2];
	   int N = atoi(argv[3]);
	   char *pattern = argv[4];
	   int M = atoi(argv[5]);
	   printf("M=%d\n",M);
	   short_test(text, N, pattern, M);
	   return 0;
    }
   
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);
   
    stress_test(N, M);
   
    return 0;
  
}
