# SSH_basic
ssh server  basic

*****************************************************************************
                SSH Server Config for "password less" login. 
                           
                                     o
                                    (^)
                                   -=H=- BISHOP
                                    ] [
                                   /___\
  
*****************************************************************************
( A not So crazy way to take the hand on your wifi domain and any GPIOs via
                     simple C or python programs. )
 In that way your program can internally talk to your remote servers without 
 typing password at each time.
 that the clever add of any hosted linux single board with embedded wifi. 
 From touch screen you can remotely control any switchs, alarm, light ect
 with time referance, auto boot up and internet update of the wlan status.
 this technic is an easy way of doing this without heavy new software skills 
 while keeping the full transparency for the end user. so why closing eyes 
 on this amazing possibility. 

                   The penguins take care of your home :)
                                .-"""-.
                               '       \
                              |,.  ,-.  |
                              |()L( ()| |
                              |,'  `".| |
                              |.___.',| `
                             .j `--"' `  `.
                            / '        '   \
                           / /          `   `.
                          / /            `    .
                         / /              l   |
                        . ,               |   |
                        ,"`.             .|   |
                     _.'   ``.          | `..-'l
                    |       `.`,        |      `.
                    |         `.    __.j         )
                    |__        |--""___|      ,-'
                       `"--...,+""""   `._,.-' mh
		 
     A raspberry pi or beagelboard are recommanded for regular security updates.
but mainly linux is the dreamed platform for learning and tweaking everything...
without this pure opensource philosophy, we are stuck in corporation, politic & dictat ... 
                    So, get your yellow palm ready !
***********************************************************************************

-> first step make a public and private key for encrypted link.

$ sudo ssh-keygen -t rsa

" just enter no passphrase
" then locate the path of the genrated key ( ~/.ssh in general )

->step2 copy the key on the server:

**(on the server side !!!!!!!!!):

$ sudo systemctl enable ssh 
$ sudo systemctl start ssh 
$ ip addr 
and note the ssh server ip for wlan0

**(on your client side!!!!!!!!!)

$ sudo ssh-copy-id -i ~/.ssh/id_rsa username@ipserver

then now you can simply login remotely on server with 

$ ssh username@ipserver 

no password are needed anymore...

if everything work well 
on **(server side !) you can now go in:

$sudo vim /etc/sshd_config 

and add the two following text line instructions:
PubkeyAuthentication yes
PasswordAuthentication no
( this will disable password login on the server )

!!! only encrypted link will work from now... !!!
(*** established by the ssh-copy-id command... ***)

"switch to PasswordAuthentication yes for reenabling remote connection via 
password for eventualy adding other parrallel clients this allow to restart
the procedure on each new clients localy by gnerating encrypted key
then link them with the ssh-copy-id command (for every singel one...)
and once all link are made lock the server by switching 
PasswordAuthentication to "no"

by the way the list of allowed keys by the server are stored in plane text 
at ~/.ssh on server side.

next type on terminal (**serverside!):
$ sudo systemctl restart ssh
for refreshing the new list of host allowed on the server.

Now you can code a simple program for controling gpio or anything remotly with 
simple command line as simple as that !!! (  more on this in a moment... )

for controling the server (on server side):
	
	$ sudo systemctl disable ssh
        ( will not start up ssh server anymore, after reboot... )
	$ sudo systemctl stop ssh
	( will just stop for this session the server)
	$ sudo systemctl enable ssh
	(start the server)
	$ sudo systemctl status ssh    
        ( for cheking actual status )

additional security program:
        * use a compiled and minimalist linux kernel.
	* "failtoban" and "ufw" is also recomanded.
	
special trick for remote control from program:

for on server password restriction type (on the server side!):
$ sudo visudo 
under the line starting %root or %admin type
your_user_name_session ALL=NOPASSWD: ALL

like this:

%sudo   ALL=(ALL:ALL) ALL
julien ALL=NOPASSWD: ALL

f2 for saving with nano ( be care full to don't make error before saving you can mess your login file
a warning is triggered in case of error before save as protectio read well the escape without saving instructions )
then loggout & login your session for update the server status.

* now you have type your password only one time by session !!!

now for security purpose you have to log on server via $ ssh username@serverip 
once then type sudo apt update (or anything else in sudo one time !) 
this allow the next comming sudo instructions to run properly 
but once done one time it's ok for all the day !!! ( it's like a bluetooth pairing )

Now with a simple C line code like this: 
system("ssh -t username@sshipserver touch ~/My_yellow_palm"); // Warning ! Your mind must be pure ! now you remotely control a computer !
you can do anything you want easly on your private home network with safety and encryption. 

***********************************************************************************
Is that things is for naive children ? certenly not ! but 
it's bound to comunication domain with the whole security issue comming with ! 
i say that because often we see 8 years old childrens with raspberrypi picture promotion. 
that fun and positive ! but a computer is open on internet and bad people my 
be every where even inside your smart wc !!! we have to be aware of that a soon as 
possible !   -> next notice server socket through outside internet connection Yeah !
***********************************************************************************

the following is a unix more advance way to run command in pure C:
'''
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

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

void main(int argc, char* argv[])
{
    run_cmd(argv[1]);
    return;
}
'''
******************************************************************************