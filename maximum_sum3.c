// written by Zongheng Wu for data structure and algorithm course

// the following code,we will implement the max sum with
// 在线更新
// the time complexity is O(n)
#include <stdio.h>

int main(){
  // get the data from the standard input
  int k;
  scanf("%d",&k);
  int sequence[100000] = {0};
  for(int i = 0;i<k;i++){
    scanf("%d",&sequence[i]);
  }
  int the_sum = 0;
  int max_sum = 0;
  for(int j = 0;j < k;j++){
    if(the_sum + sequence[j] > 0){
      the_sum += sequence[j];
    }
    else{
      the_sum = 0;
    }
    if(the_sum > max_sum){
      max_sum = the_sum;
    }
  }
  printf("%d\n",max_sum);
  return 0;
}
