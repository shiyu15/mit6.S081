#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char *path,char *fname) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
        case T_FILE:
            printf("find:the path is actually a file\n");
            exit(1);
            break;

        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                //printf("            %s %d %d %l\n", de.name, st.type, st.ino, st.size);
                if (de.inum == 0) continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }
                if(!strcmp(de.name,fname)){
                    printf("%s\n",buf);
                }

                else if (st.type == T_DIR && strcmp(de.name, ".") != 0 &&
                         strcmp(de.name, "..") != 0)
                    find(buf,fname);
            }
            break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {

    if (argc == 3) {
        //if(strlen(argv[2])>=)
        find(argv[1],argv[2]);
        
    }
    else{
        printf("error input: find needs 3 arguments ");
        exit(1);
    }
    exit(0);
}