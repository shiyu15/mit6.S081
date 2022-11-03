#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc>1){
        printf("too many arguments\n");
        exit(1);
    }
    int p[2];
    pipe(p);
    int pid=fork();
    int id;
    if(pid==0){
        char rec;
        id=getpid();
        read(p[0],&rec,1);
        close(p[0]);
        printf("%d: received ping\n", id);
        write(p[1],&rec,1);
        close(p[1]);

    }
    else{
        char mail='a',ret;
        write(p[1],&mail,1);
        close(p[1]);
        wait(0);
        read(p[0],&ret,1);
        close(p[1]);
        id=getpid();
        if(ret==mail){
            printf("%d: received pong\n",id);
        }
    }
    exit(0);
}