#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LEN 250     /* max length of a single command 
                                   string */

#define JOB_STATUS_FORMAT "[%d] %-22s %.40s\n"

enum redirectionType { REDIRECT_INPUT, REDIRECT_OVERWRITE, REDIRECT_APPEND };

struct jobSet {
    struct job * head;      /* head of list of running jobs */
    struct job * fg;        /* current foreground job */
};

struct redirectionSpecifier {
    enum redirectionType type;  /* type of redirection */
    int fd;                 /* file descriptor being redirected */
    char * filename;        /* file to redirect fd to */
};

struct childProgram {
    pid_t pid;              /* 0 if exited */
    char ** argv;           /* program name and arguments */
    int numRedirections;    /* elements in redirection array */
    struct redirectionSpecifier * redirections;  /* I/O redirections */
};

struct job {
    int jobId;              /* job number */
    int numProgs;           /* total number of programs in job */
    int runningProgs;       /* number of programs running */
    char * text;            /* name of job */
    char * cmdBuf;          /* buffer various argv's point into */
    pid_t pgrp;             /* process group ID for the job */
    struct childProgram * progs; /* array of programs in job */
    struct job * next;      /* to track background commands */
};