#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

//call a program for one line arges
void myXargs(int argc, char *argv[], int cnt, char *newArgv[]){
    // for(int i=0;i<cnt;i++)
    // {
    //     printf("%s ",newArgv[i]);
    // }
    // printf("\n");
    char *finalArg[MAXARG];
    int finalCnt=0;
    for(int i=1;i<argc;i++){
        finalArg[finalCnt++]=argv[i];
    }
    for (int i = 0; i < cnt; i++) {
        finalArg[finalCnt++] = newArgv[i];
    }
    exec(finalArg[0],finalArg);
    exit(0);
}

int main(int argc, char *argv[]) {
    char *newArgv[MAXARG];
    for(int i=0;i<MAXARG;i++)
    {
        newArgv[i]=malloc(sizeof(char)*32);
    }
    if (argc < 2) {
        printf("xargs: needs at least arguments ");
        exit(1);
    }
    int cnt = 0;
    char *p = newArgv[0];
    char temp;
    while (read(0, &temp, 1)) {
        if (temp == ' ') {//read a parameter
            cnt++;
            p = newArgv[cnt];
            if(cnt>=MAXARG){
                printf("xargs:too many pipe arges");
            }
            continue;
        }
        else if (temp == '\n') {//after read a line, exec one time 
            cnt++;
            if (cnt >= MAXARG) {
                printf("xargs:too many pipe arges");
            }
            int pid=fork();
            if(pid==0){
                myXargs(argc,argv,cnt,newArgv);
            }
            wait(0);
            cnt=0;
            p=newArgv[0];
            for (int i = 0; i < MAXARG; i++) {//restore param space to start
                memset(newArgv[i],0,32);
            }
            continue;
        }
        *p++ = temp;
    }

    exit(0);
}