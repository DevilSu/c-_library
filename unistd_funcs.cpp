/*
	20181202
	unistd.h library showcase
	Reference: http://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html
	NEED REVISIT tag -> function not learned yet
*/
#include <stdio.h>

#include <unistd.h>

#include <errno.h>	// get the error message while function fails -> errno
#include <string.h>	// convert errno to string -> strerror
#include <limits.h> // useage of PATH_MAX

int main()
{
	int tmp;

	bool f_sleep		=0;	
	bool f_alarm		=0;
	bool f_brk			=0;
	bool f_access		=0;
	bool f_chdir_getcwd	=1;
	
	//sleep
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

	//alarm
	//NEED REVISIT
	if(f_alarm)
	{
		/*
			unsigned int alarm(unsigned int seconds);
		*/
		alarm(1);
	}

	//brk
	//NEED REVISIT
	if(f_brk)
	{

	}

	//access
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

	//chdir, getcwd
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
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));
		printf("current working directory: %s\n", cwd);

	}
	

	return 0;
}