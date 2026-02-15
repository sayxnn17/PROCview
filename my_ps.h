#ifndef MY_PS_H
#define MY_PS_H

// Structure for ps -eLf data
typedef struct {
    char uid[50]; //user id
    int pid; //process id
    int lwp; //Light Weight Process
    int ppid;  //parent process id  
    int nlwp; //number of threads in process
    int c; //CPU utilization factor
} ps_elf;

// Structure for ps aux data
typedef struct {
    char tty[20]; //terminal associated with process
    char stat[10]; //process state
    char start[20]; // time when process started
    char time[20]; //total CPU time used
    char command[200]; //full command that started process
    char user[50]; //user name of process owner
    int pid; //for storing process id
    float cpu; //percentage of CPU usage
    float mem; //percentage of memory usage
    int vsz; //virtual memory size 
    int rss; //Resident Set Size
} ps_aux;


#endif
