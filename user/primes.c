#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void primeSieve(int p[]) {
    close(p[1]);

    // set little space for variables
    // to maintain more processes
    // otherwise the program may meet usertrap
    // in later parts of child's processes 

    int room[35];
    int cnt = 0;
    unsigned char rec;
    while (read(p[0], &rec, 1)) {
        room[cnt++] = rec;
    }
    close(p[0]);

    // the defination of printf is in user/printf.c. 
    // we know xv6 printf can only print %d %x(hex) %p %s.
    // but in ls.c, %l can be used.

    int pr=room[0];
    printf("prime %d\n", pr);

    //_________for debug______
    //
    // printf("cnt:%d\n",cnt);
    // for(int i=0;i<cnt;i++)
    // {
    //     pr = room[i];
    //     printf("%d ", pr);
    // }
    // printf("\n");

    if (cnt == 1)
        exit(0);
    else {
        int q[2];
        pipe(q);
        int pid = fork();
        if (pid > 0) {
            close(q[0]);
            for (unsigned char i = 0; i < cnt; i++) {
                if (room[i] % room[0]) {
                    char t=room[i];
                    write(q[1],&t,1);
                }
            }
            close(q[1]);
            wait(0);
        }
        else{
            primeSieve(q);
            exit(0);
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("prime command only needs one argument.");
        exit(1);
    }
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid == 0) {
        primeSieve(p);

        exit(0);
    } else {
        close(p[0]);
        for (unsigned char i=2; i <= 35; i++) {
            write(p[1], &i, 1);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}