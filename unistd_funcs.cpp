/*
	20181202
	unistd.h library showcase
*/
#include <stdio.h>

#include <unistd.h>

#include <errno.h>	// get the error message while function fails -> errno
#include <string.h>	// convert errno to string -> strerror 

int main()
{
	int tmp;

	bool f_sleep	=0;
	bool f_access	=0;
	bool f_alarm	=1;
	
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
	
	//alarm
	if(f_alarm)
	{
		/*
			unsigned int alarm(unsigned int seconds);
		*/
		alarm(1);
	}
	
	return 0;
}