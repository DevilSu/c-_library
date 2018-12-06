/*
    20181202
    unistd.h library showcase
    Reference: http://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html
    NEED REVISIT tag -> function not learned yet
*/
#include <stdio.h>

#include <unistd.h>

#include <errno.h>  // get the error message while function fails -> errno
#include <string.h> // convert errno to string -> strerror
#include <limits.h> // useage of PATH_MAX
#include <fcntl.h>  // open() is declared here

int main()
{
    bool f_sleep        =0; 
    bool f_alarm        =0;
    bool f_brk          =0;
    bool f_access       =0;
    bool f_chdir_getcwd =0;
    bool f_chroot       =0;
    bool f_chown        =0;
    bool f_close_read   =0;
    bool f_confstr      =0;
    bool f_crypt        =0;
    bool f_ctermid      =0;
    bool f_cuserid      =0;
    bool f_dup_dup2     =1;

    int tmp, tmp1;
    int fd, fd2;        // file descriptor
    char buf[255];      // for read file text
    char cwd[PATH_MAX]; // for getcwd
    char term[L_ctermid];   // for ctermid
    char *ptr;              // for ctermid
    char username[L_cuserid];   // for cuserid 
    
    // sleep
    if(f_sleep)
    {
        /*
            unsigned int sleep(unsigned int seconds);
            Def: sleep n seconds.
            In : integer
            Out: 0 if success, else return the remaining time suppose to be sleep
        */
        sleep(2);
    }

    // alarm
    // NEED REVISIT
    if(f_alarm)
    {
        /*
            unsigned int alarm(unsigned int seconds);
        */
        alarm(1);
    }

    // brk
    // NEED REVISIT
    if(f_brk)
    {

    }

    // access
    if(f_access)
    {
        /*
            int access(const char *path, int amode);
            Def: check file exist, read, write, exec permissions
            In1: string of filename
            In2: mode
                    F_OK: existance
                    R_OK: read
                    W_OK: write
                    X_OK: exec
            Out: 0 if True, -1 of False
            Err: if false, can check errno for detail
        */
        if(access("unistd_funcs.cpp", F_OK)==0)printf("file exist\n");
        if(access("unistd_funcs.cpp", R_OK)==0)printf("read OK\n");
        if(access("unistd_funcs.cpp", W_OK)==0)printf("write OK\n");
        if(access("unistd_funcs.cpp", X_OK)==0)printf("exec OK\n");
        // a non-exist file
        tmp=access("lkjasldj.c", F_OK);
        printf("tmp=%d, lkjasldj.c: %s\n", tmp, strerror(errno));
    }

    // chdir, getcwd
    if(f_chdir_getcwd)
    {
        /*
            int chdir(const char *path);
            Def: change current working directory
            In : string of pathname
            Out: 0 if True, -1 of False
            Err: if false, can check errno for detail
         */
        tmp=chdir("/media/devilsu/M/Git/MDs");
        printf("tmp=%d, chdir: %s\n", tmp, strerror(errno));

        /*
            char *getcwd(char *buf, size_t size);   
            Def: get current working directory path
            In1: a string
            In2: size of the string
            Out: the origin string
            Err: if false, will return null pointer, check errno for detail
         */
        getcwd(cwd, sizeof(cwd));
        printf("current working directory: %s\n", cwd);
    }
    
    // chroot
    if(f_chroot)
    {
        /*
            int chroot(const char *path);
            !!! NEED ROOT PERMISSION !!!
            Def: change root directory to the string (will search pathname begin with the string)
            In : a string
            Out: 0 if True, -1 of False
            Err: if false, will return -1, check errno for detail
         */
        // get current working directory
        getcwd(cwd, sizeof(cwd));
        printf("current working directory: %s\n", cwd);
        // change root pathname to current working directory
        tmp=chroot(cwd);
        printf("tmp=%d, chroot: %s\n", tmp, strerror(errno));
        // goto "test" folder
        tmp=chdir("/test");
        printf("tmp=%d, chdir: %s\n", tmp, strerror(errno));
        // print current working directory 
        getcwd(cwd, sizeof(cwd));
        printf("current working directory: %s\n", cwd);
    }

    // chown
    // NEED REVISIT
    if(f_chroot)
    {
        /*
            int chown(const char *path, uid_t owner, gid_t group);
            !!! NEED ROOT PERMISSION !!!
            Def: change owner or group of a file (folder?)
            In1: a string
            In2: 
            In3: 
            Out: 0 if True, -1 of False
            Err: if false, will return -1, check errno for detail
         */
    }

    // close, read
    if (f_close_read)
    {
        /*
            int close(int fildes);
            Def: close a file descriptor
            In : file descriptor
            Out: 0 if True, -1 of False
            Err: if false, will return -1, check errno for detail
         */
        
        /*
            open() and close() are not in the same library!!!
            open  -> fcntl.h
            close -> unistd.h
            info of open(): http://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html
         */
        fd=open("README.md", O_RDONLY);
        printf("tmp=%d, open: %s\n", tmp, strerror(errno));

        /*
            ssize_t read(int fildes, void *buf, size_t nbyte);
            Def: read form file
            In1: file descriptor
            In2: pointer to the string buffer
            In3: the char length you want to read
            Out: actual char length being read, -1 if fail
            Err: if false, will return -1, check errno for detail
         */
        tmp1=read(fd, buf, 100);    // read 100 char
        buf[tmp1]='\0';
        printf("First 100 char in \"README.md\" is:\n");
        printf("%s\n", buf);

        // close function
        tmp=close(fd);
        printf("tmp=%d, close: %s\n", tmp, strerror(errno));
    }

    // confstr
    // NEED REVISIT
    if(f_confstr)
    {
        /*
            size_t confstr(int name, char *buf, size_t len);
            Def: gets the value of configuration-dependent string variables
            In1: configuration name (table lookup)
            In2: string buffer
            In3: size of buffer
            Out: 1. size of the string, may be larger than buf
                 2. 0 if name is wrong, or name is valid but string is empty
            Err: when return 0, check errno for detail
         */
        tmp=confstr(_CS_PATH, buf, sizeof(buf));
        printf("confstr str: %s\n", buf);
        printf("tmp=%d, confstr: %s\n", tmp, strerror(errno));
    }

    // crypt
    // NEED REVISIT
    if(f_crypt)
    {
        // char *crypt (const char *key, const char *salt);
    }

    //ctermid
    //NEED REVISIT - where to use?
    if(f_ctermid)
    {
        /*
            char *ctermid(char *s);
            Def: get pathname of current controlling terminal for the current process
            In : string buffer
            Out: pointer to the string, fail will return NULL
         */
        ptr=ctermid(term);
        printf("ptr =%s, addr=%p\n", ptr, ptr);
        printf("term=%s, addr=%p\n", term, term);
    }

    // cuserid
    if(f_cuserid)
    {
        /*
            char *cuserid(char *s);
            Def: get login name of user
            In : string buffer
            Out: pointer to string, NULL if can not found username
         */
        if(cuserid(username)==NULL)
        {
            fprintf( stderr, "cannot find login name\n" );
        }
        printf( "%s\n", username );
    }

    // dup, dup2
    if(f_dup_dup2)
    {
        /*
            fcrtl() can do all these stuffs. Don't use these.
            
            int dup(int fildes);
            Def: duplicate an open file descriptor
            In : a file descriptor
            Out: another file descrpitor (different from In)
            - Close one of the two will not close the other
            - Will read from the end of last read of both fds
                -> read will conut as both!!

            int dup2(int fildes, int fildes2);
            Def: duplicate an open file descriptor
            In : a file descriptor
            Out: 
         */
        fd =open("README.md", O_RDONLY);
        printf("open as read : %s\n", strerror(errno));
        // duplicate from start still will read after the read of origin fd
        // tmp=dup(fd);  

        tmp1=read(fd, buf, 10);    // read 10 char
        buf[tmp1]='\0';
        printf("First 10 char in \"README.md\" is:\n");
        printf("%s\n", buf);
        printf("-----\n");

        // after duplicate, will read from the end of last read
        // not from the begining of the file
        tmp=dup(fd);
        printf("tmp=%d, fd=%d, dup: %s\n", tmp, fd, strerror(errno));
        tmp1=read(tmp, buf, 10);    // read 10 char
        buf[tmp1]='\0';
        printf("another 10 char in \"README.md\" is:\n");
        printf("%s\n", buf);
        printf("-----\n");

        // close function
        tmp1=close(fd);
        printf("tmp=%d, close: %s\n", tmp1, strerror(errno));
        // close one will not close another
        tmp1=close(tmp);
        printf("tmp=%d, close: %s\n", tmp1, strerror(errno));


        // dup and write, write to same file
        fd=open("out.txt", O_WRONLY | O_CREAT);
        printf("open as write: %s\n", strerror(errno));

        tmp1=dup(fd);
        write(fd, "fd\n", 3);
        write(tmp1, "tmp1\n", 5);

        // close one, another still can use
        close(fd);
        write(tmp1, "tmp1-2\n", 7);
        close(tmp1);

        // dup2
        fd=open("out.txt", O_WRONLY | O_CREAT | O_APPEND);
        tmp=dup2(fd, 1);    // bind 1(std_out) with output file
        printf("111 tmp=%d, fd=%d\n", tmp, fd); // printf will print to file, terminal show nothing
        write(fd, "lol\n", 4); // can still write ro fd



    }



    return 0;
}