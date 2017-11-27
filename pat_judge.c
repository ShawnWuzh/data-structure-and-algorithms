// wriiten by Zongheng WU for DS

#include <stdio.h>
#include <stdlib.h>
#define MAXPROBLEMS 6
#define MAXSTUDENTS 10001

typedef struct _student{
  int perfectly_solved_problems;
  int score;
  int id;
  int tag;
}Student;

typedef Student* pStudent;

int cmp1(const void *a, const void *b);
void GetInput(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int M,int problems[MAXPROBLEMS]);
int StrToInt(char id[6]);
void Initialize(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int N,int K);
void Print(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int start,int end,int rank,int k);

int main(){
  int N,K,M;
  scanf("%d %d %d",&N,&K,&M);
  int problems[MAXPROBLEMS];
  int students_problems[MAXSTUDENTS][MAXPROBLEMS-1];
  Student students[MAXSTUDENTS];
  for(int i=1;i <= K;i++){
    scanf("%d",&problems[i]);     // use the problems to save the full score of each problem
  }
  Initialize(students,students_problems,N,K);
  GetInput(students,students_problems,M,problems);
  qsort(students+1,N,sizeof(students[1]),cmp1);
  int start = 1;
  int rank = 1;
  int end;
  while(start < N+1){
    if(students[start].tag == 0){
      break;
    }
    end = start;
    while(students[end].score == students[end+1].score && end < N+1){
      end++;
    }
    if(end >= N+1){
      end -= 1;
    }
    Print(students,students_problems,start,end,rank,K);
    rank += (end - start + 1);
    start = end+1;
  }
  return 0;
}

void Print(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int start,int end,int rank,int k){
  for(int i=start;i<=end;i++){
    printf("%d %05d %d",rank,students[i].id,students[i].score);
    for(int j=0;j<k;j++){
      if(students_problems[students[i].id][j] == -2){
        printf(" -");
      }
      else if(students_problems[students[i].id][j] == -1){
        printf(" 0");
      }
      else{
        printf(" %d", students_problems[students[i].id][j]);
      }
    }
    printf("\n");
  }
}

int cmp1(const void *a, const void *b){
  pStudent a1 = (pStudent)a;
  pStudent b1 = (pStudent)b;
  if(b1->score > a1->score){
    return 1;
  }
  else if(b1->score < a1->score){
    return -1;
  }
  if(b1->perfectly_solved_problems > a1->perfectly_solved_problems){
    return 1;
  }
  else if(b1->perfectly_solved_problems < a1->perfectly_solved_problems){
    return -1;
  }
  if(a1->id > b1->id){
    return 1;
  }
  else if(a1->id < b1->id){
    return -1;
  }
  else{
    return 0;
  }
}

void GetInput(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int M,int problems[MAXPROBLEMS]){
  char id[6];
  int id_number,problem_number,problem_score;
  for(int i=0;i<M;i++){
    scanf("%s %d %d",id,&problem_number,&problem_score);
    id_number = StrToInt(id);
    students[id_number].id = id_number;
    if(problem_score > students_problems[id_number][problem_number-1]){
      if(problem_score == -1){   // indicate the not compile successfully
        students_problems[id_number][problem_number-1] = problem_score;
      }
      else{
        if(students[id_number].tag == 0){
          students[id_number].tag = 1;   // means the student will be shown in the rank list
        }
        if(students[id_number].score < 0){
          students[id_number].score = 0;
        }
        if(students_problems[id_number][problem_number-1] == -2){
          students[id_number].score += problem_score;
        }
        else if(students_problems[id_number][problem_number-1] == -1){
          students[id_number].score += problem_score;
        }
        else{
          students[id_number].score -= students_problems[id_number][problem_number-1];
          students[id_number].score += problem_score;
        }
        if(problem_score == problems[problem_number]){
          students[id_number].perfectly_solved_problems += 1;
        }
        students_problems[id_number][problem_number-1] = problem_score;
      }
    }
  }
}

int StrToInt(char id[6]){
  int i = 0;
  while(id[i] == '0'){
    i++;
  }
  int id_number = id[i] - '0';
  for(int j = i+1;j<5;j++){
    id_number = id_number * 10 + id[j] - '0';
  }
  return id_number;
}

void Initialize(Student students[MAXSTUDENTS],int students_problems[MAXSTUDENTS][MAXPROBLEMS-1],int N,int K){
  for(int i=1;i<N+1;i++){
    students[i].perfectly_solved_problems = 0;  // set the number of questions that a student finish to 0
    students[i].score = -1;                      // set the total score of each student to 0
    students[i].tag = 0;  // use a tag indicate the submit history
    for(int j=0;j<K;j++){
      students_problems[i][j] = -2;   // set the score of each problem to -2
    }
  }
}
