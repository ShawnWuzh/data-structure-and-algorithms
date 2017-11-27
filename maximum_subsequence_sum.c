// witten by Zongheng Wu

#include <stdio.h>

int main(){
  int k;
  scanf("%d",&k);
  int sequence[10000];
  int i = 0;
  while(i < k){
    scanf("%d",sequence+i);
    i++;
  }
  int the_sum = 0;
  int max_sum = 0;
  int start = -1;
  int first = -1;
  int last = -1;
  int start_flag = 0; //use the flag to indicate that the beginning
                //of the potential maximum subsequence
  for(int j = 0;j < k;j++){
    if(sequence[j] + the_sum >= 0){
      the_sum += sequence[j];
      if(start_flag == 0){
        start = j;
        start_flag = 1; // the subsequence begin
      }
    }
    else{
      the_sum = 0;
      start_flag = 0;
    }
    if(the_sum >= max_sum){
      if(first != -1 && last != -1 && the_sum == max_sum){
        if(start < first && j < last){
          first = start;
          last = j;
        }
      }
      else{
        first = start;
        last = j;
      }
      max_sum = the_sum;
    }
  }
  if(max_sum >= 0 && first != -1 && last != -1){
    printf("%d %d %d",max_sum,sequence[first],sequence[last]);
    printf("\n");
  }
  else{
    printf("%d %d %d",0,sequence[0],sequence[k-1]);
    printf("\n");
  }
  return 0;
}
