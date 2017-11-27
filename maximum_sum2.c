// written by Zongheng Wu
// the algothim i used is a brutal alogorithm with
// time complexity O(n^2)
#include <stdio.h>
int main(){
  int k;
  scanf("%d",&k);
  int sequence[100000] = {0};
  int i = 0;
  int max_sum = 0;
  int the_sum = 0;
  while(i < k){
    scanf("%d",&sequence[i]);
    i++;
  }
  for(int p = 0;p < k;p++){
    for(int j = p;j < k;j++){
      the_sum += sequence[j];
      if(the_sum > max_sum){
        max_sum = the_sum;
      }
    }
    the_sum = 0;
  }
  printf("%d\n",max_sum);
  return 0;
}
