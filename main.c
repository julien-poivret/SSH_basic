#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string.h>

/*
	        Some documentation on data structures lists for database storage.
     and remote server instructions for home automated private network managment throught ssh server.
	          ( tested and working. on beagelbord AI last Debian 11 build )
*/

typedef struct{
	uint_fast8_t count;
	char name[50]; 
}transient_log;

extern char **environ;

void run_cmd(char *cmd)
{
    pid_t pid;
    char *argv[] = {"sh", "-c", cmd, NULL};
    int status;
    printf("Run command: %sn", cmd);
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        printf("Child pid: %in", pid);
        do {
          if (waitpid(pid, &status, 0) != -1) {
            printf("Child status %dn", WEXITSTATUS(status));
          } else {
            perror("waitpid");
            exit(1);
          }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        printf("posix_spawn: %sn", strerror(status));
    }
}

void data_read(transient_log data_input[2]){
	printf("\33[37m\33[5;1H\33[3J %d  ---> %s \33[0m\n",data_input[0].count,data_input[1].name); 
}
void data_read2(transient_log data_input[2]){
	printf("\33[37m\33[6;1H\33[3J %s  ---> %s \33[0m\n",data_input->name,(data_input+1)->name); 
}

int main(int argc,char* argv[]){
	
	// Command line instructions.
	// system("ssh -t debian@192.168.3.12 touch My_yellow_palm");
	run_cmd("ssh -t debian@192.168.3.12 touch My_better_yellow_palm"); // simply create a file in ~/ on server.
	
	
	// Data structure initialisation.
	transient_log _A[2] = {{3,"Exupery \"biplan\"\0"},{4,"\"Short takeoff\""}};
	transient_log _B[2] = {{5,"Spining real !"},{6,"hardware is king !"}};
	transient_log _C[2] = {{7,"Language Machine you have to understand"},{6,"for making differance !"}};
	// Some data access and print experiment.
	printf("\33[33m\33[2J\33[1;35HData Structure.\33[0m\n");
	printf("\33[37m\33[3J\33[3;1H %d  ---> %s \33[0m\n",_A[0].count,_A[0].name); 
	printf("\33[37m\33[3J\33[4;1H %d  ---> %s \33[0m\n",_A[1].count,_A[1].name); 
	data_read(_B);
	data_read2(_C); // pointer on pointer...

	
	return EXIT_SUCCESS;
}


