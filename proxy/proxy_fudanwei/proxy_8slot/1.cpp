#include <iostream>
#include <sys/time.h>
#include <string.h>
using namespace std;
int main(int argc, char *argv[]){
    int temp_uint32=0x200470;
    temp_uint32=temp_uint32%0x200000;
    printf("temp_uint32=%X\n",temp_uint32);
    struct timeval time;
    char *s;
    int serverPort,cnt;
    if (argc > 1)
	{
        printf("argc=%d",argc);
        for(int i=1;i<=(argc-2);i=i+2){
		if ((strcmp(argv[i], "-r") == 0))
		{
			serverPort = strtol(argv[i+1], &s, 10);
		}
        if ((strcmp(argv[i], "-c") == 0))
		{
			cnt = strtol(argv[i+1], &s, 10);
		}
        }
    }
    printf("serverPort =%d , cnt = %d\n",serverPort,cnt);
    /* 获取时间，理论到us */
    gettimeofday(&time, NULL);
    printf("s: %ld, ms: %ld\n", time.tv_sec, (time.tv_sec*1000 + time.tv_usec/1000));
    while(1){
        struct timeval tmptime;
        gettimeofday(&tmptime, NULL);
        printf("s: %ld, ms: %ld\n", tmptime.tv_sec, (tmptime.tv_sec*1000 + tmptime.tv_usec/1000));
        if(tmptime.tv_sec>time.tv_sec||(tmptime.tv_usec/1000)>(time.tv_usec/1000)){
            break;
        }
    }
    cout<<"end";
    return 0;
}